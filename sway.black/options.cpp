#include "valve_sdk/misc/Color.hpp"
#include "options.h"

namespace options
{
	// Aimbot
	bool aimbot = false;
	float smooth = false;
	float fov = false;
	bool aim_key = false;
	int aimkey = false;

	bool triggerbot = false;
	int delay = false;
	bool trigger_key = false;
	int triggerkey = false;
	bool flick = false;
	float flickfov = 0.0f;

	bool bunny_hop = false;

	bool glow_enabled = false;
	bool glow_players = false;
	bool glow_enemies = false;
	bool glow_c4_carrier = false;
	bool glow_planted_c4 = false;
	bool glow_defuse_kit = false;
	bool glow_chickens = false;
	bool glow_weapons = false;

	Color color_glow_players = { 255, 255, 255, 255 };
	Color color_glow_enemies = { 255, 255, 255, 255 };
	Color color_glow_ally = { 255, 255, 255, 255 };
	Color color_glow_c4_carrier = { 255, 255, 255, 255 };
	Color color_glow_planted_c4 = { 255, 255, 255, 255 };
	Color color_glow_defuse_kit = { 255, 255, 255, 255 };
	Color color_glow_chickens = { 255, 255, 255, 255 };
	Color color_glow_weapons = { 255, 255, 255, 255 };

	bool chams_player = false;
	bool chams_player_enemy = false;
	bool chams_player_arms = false;
	bool chams_player_ignored = false;

	bool chams_player_flat = false;
	bool chams_player_wire_frame = false;
	bool chams_player_glass = false;

	bool chams_no_hands = false;
	bool chams_arms_enabled = false;
	bool chams_arms_ignored = false;

	bool chams_arms_flat = false;
	bool chams_arms_wire_frame = false;
	bool chams_arms_glass = false;

	Color color_chams_arms_visible = { 255, 255, 255, 255 };
	Color color_chams_arms_occluded = { 255, 255, 255, 255 };

	Color color_chams_player_enemy_visible = { 255, 255, 255, 255 };
	Color color_chams_player_ally_visible = { 255, 255, 255, 255 };
	Color color_chams_player_enemy_occluded = { 255, 255, 255, 255 };
	Color color_chams_player_ally_occluded = { 255, 255, 255, 255 };

	bool reveal_ranks = false;
}