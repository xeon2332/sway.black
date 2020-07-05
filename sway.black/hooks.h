#pragma once
#include "helpers/vfunc_hook.hpp"

namespace hooks
{
	constexpr auto create_move_index = 22;
	constexpr auto draw_model_index = 21;
	constexpr auto post_screen_effect_index = 44;

	void HookCSGO();
	void UnHook();

	vfunc_hook create_move_hook;
	vfunc_hook draw_model_hook;
	vfunc_hook post_screen_effect_hook;

	void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active);
	void __fastcall hkDrawModelExecute(void* _this, int, IMatRenderContext* ctx, const DrawModelState_t& state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld);
}