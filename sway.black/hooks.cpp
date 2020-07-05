#include <iostream>
#include "valve_sdk/sdk.hpp"
#include "helpers/vfunc_hook.hpp"
#include "chams.h"
#include "hooks.h"
#include "options.h"
#include "bhop.h"
#include "glow.h"

namespace hooks
{
	vfunc_hook create_move_hook;
	vfunc_hook draw_model_hook;
	vfunc_hook post_screen_effect_hook;

	void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
	{
		static auto oCreateMove = create_move_hook.get_original<decltype(&hkCreateMove)>(hooks::create_move_index);

		oCreateMove(sequence_number, input_sample_frametime, active);

		auto cmd = g_Input->GetUserCmd(sequence_number);
		auto verified = g_Input->GetVerifiedCmd(sequence_number);

		if (!cmd || !cmd->command_number)
			return;

		if (options::bunny_hop)
			BunnyHop::OnCreateMove(cmd);

		if (options::reveal_ranks && cmd->buttons & IN_SCORE)
			g_CHLClient->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);

		verified->m_cmd = *cmd;
		verified->m_crc = cmd->GetChecksum();
	}

	void __fastcall hkDrawModelExecute(void* _this, int edx, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
	{
		static auto ofunc = draw_model_hook.get_original<decltype(&hkDrawModelExecute)>(hooks::draw_model_index);

		if (g_MdlRender->IsForcedMaterialOverride() &&
			!strstr(pInfo.pModel->szName, "arms") &&
			!strstr(pInfo.pModel->szName, "weapons/v_")) {
			return ofunc(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);
		}

		Chams::Get().OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

		ofunc(_this, edx, ctx, state, pInfo, pCustomBoneToWorld);

		g_MdlRender->ForcedMaterialOverride(nullptr);
	}

	int __fastcall hkDoPostScreenEffects(void* _this, int edx, int a1)
	{
		static auto oDoPostScreenEffects = post_screen_effect_hook.get_original<decltype(&hkDoPostScreenEffects)>(hooks::post_screen_effect_index);

		if (g_LocalPlayer && options::glow_enabled)
			Glow::Get().Run();

		return oDoPostScreenEffects(g_ClientMode, edx, a1);
	}

	void hooks::HookCSGO()
	{
		create_move_hook.setup(g_CHLClient);
		draw_model_hook.setup(g_MdlRender);
		post_screen_effect_hook.setup(g_ClientMode);

		create_move_hook.hook_index(hooks::create_move_index, hkCreateMove);
		draw_model_hook.hook_index(hooks::draw_model_index, hkDrawModelExecute);
		post_screen_effect_hook.hook_index(hooks::post_screen_effect_index, hkDoPostScreenEffects);
	}

	void hooks::UnHook()
	{
		create_move_hook.unhook_all();
		draw_model_hook.unhook_all();
		post_screen_effect_hook.unhook_all();
	}
}
