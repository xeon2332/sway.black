#include "chams.h"
#include <fstream>

#include "valve_sdk/csgostructs.hpp"
#include "hooks.h"
#include "options.h"

Chams::Chams() {
	materialRegular = g_MatSystem->FindMaterial("debug/debugambientcube");
	materialFlat = g_MatSystem->FindMaterial("debug/debugdrawflat");
}

Chams::~Chams() {
}


void Chams::OverrideMaterial(bool ignoreZ, bool flat, bool wireframe, bool glass, const Color& rgba) {
	IMaterial* material = nullptr;

	if (flat) {
		material = materialFlat;
	}
	else {
		material = materialRegular;
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignoreZ);


	if (glass) {
		material = materialFlat;
		material->AlphaModulate(0.45f);
	}
	else {
		material->AlphaModulate(
			rgba.a() / 255.0f);
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wireframe);
	material->ColorModulate(
		rgba.r() / 255.0f,
		rgba.g() / 255.0f,
		rgba.b() / 255.0f);

	g_MdlRender->ForcedMaterialOverride(material);
}


void Chams::OnDrawModelExecute(
	IMatRenderContext* ctx,
	const DrawModelState_t& state,
	const ModelRenderInfo_t& info,
	matrix3x4_t* matrix)
{
	static auto fnDME = hooks::draw_model_hook.get_original<decltype(&hooks::hkDrawModelExecute)>(21);

	const auto mdl = info.pModel;

	bool is_arm = strstr(mdl->szName, "arms") != nullptr;
	bool is_player = strstr(mdl->szName, "models/player") != nullptr;
	bool is_sleeve = strstr(mdl->szName, "sleeve") != nullptr;
	//bool is_weapon = strstr(mdl->szName, "weapons/v_")  != nullptr;

	if (is_player && options::chams_player) {
		// 
		// Draw player Chams.
		// 
		auto ent = C_BasePlayer::GetPlayerByIndex(info.entity_index);

		if (ent && g_LocalPlayer && ent->IsAlive()) {
			const auto enemy = ent->m_iTeamNum() != g_LocalPlayer->m_iTeamNum();
			if (!enemy && options::chams_player_enemy)
				return;

			const auto clr_front = enemy ? options::color_chams_player_enemy_visible : options::color_chams_player_ally_visible;
			const auto clr_back = enemy ? options::color_chams_player_enemy_occluded : options::color_chams_player_ally_occluded;

			if (options::chams_player_ignored) {
				OverrideMaterial(
					true,
					options::chams_player_flat,
					options::chams_player_wire_frame,
					false,
					clr_back);
				fnDME(g_MdlRender, 0, ctx, state, info, matrix);
				OverrideMaterial(
					false,
					options::chams_player_flat,
					options::chams_player_wire_frame,
					false,
					clr_front);
			}
			else {
				OverrideMaterial(
					false,
					options::chams_player_flat,
					options::chams_player_wire_frame,
					options::chams_player_glass,
					clr_front);
			}
		}
	}
	else if (is_sleeve && options::chams_player_arms) {
		auto material = g_MatSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
		if (!material)
			return;
		// 
		// Remove sleeves when drawing Chams.
		// 
		material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
		g_MdlRender->ForcedMaterialOverride(material);
	}
	else if (is_arm) {
		auto material = g_MatSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
		if (!material)
			return;
		if (options::chams_no_hands) {
			// 
			// No hands.
			// 
			material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			g_MdlRender->ForcedMaterialOverride(material);
		}
		else if (options::chams_arms_enabled) {
			if (options::chams_arms_ignored) {
				OverrideMaterial(
					true,
					options::chams_arms_flat,
					options::chams_arms_wire_frame,
					false,
					options::color_chams_arms_occluded);
				fnDME(g_MdlRender, 0, ctx, state, info, matrix);
				OverrideMaterial(
					false,
					options::chams_arms_flat,
					options::chams_arms_wire_frame,
					false,
					options::color_chams_arms_visible);
			}
			else {
				OverrideMaterial(
					false,
					options::chams_arms_flat,
					options::chams_arms_wire_frame,
					options::chams_arms_glass,
					options::color_chams_arms_visible);
			}
		}
	}
}