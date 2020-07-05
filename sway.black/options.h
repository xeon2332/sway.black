#pragma once
#include "valve_sdk/misc/Color.hpp"

namespace options
{
	// Aimbot
	extern bool aimbot;
	extern float smooth;
	extern float fov;
	extern bool aim_key;
	extern int aimkey;

	extern bool triggerbot;
	extern int delay;
	extern bool trigger_key;
	extern int triggerkey;
	extern bool flick;
	extern float flickfov;

	extern bool bunny_hop;

	extern bool glow_enabled;
	extern bool glow_players;
	extern bool glow_enemies;
	extern bool glow_c4_carrier;
	extern bool glow_planted_c4;
	extern bool glow_defuse_kit;
	extern bool glow_chickens;
	extern bool glow_weapons;

	extern Color color_glow_players;
	extern Color color_glow_enemies;
	extern Color color_glow_ally;
	extern Color color_glow_c4_carrier;
	extern Color color_glow_planted_c4;
	extern Color color_glow_defuse_kit;
	extern Color color_glow_chickens;
	extern Color color_glow_weapons;

	extern bool chams_player;
	extern bool chams_player_enemy;
	extern bool chams_player_arms;
	extern bool chams_player_ignored;
	 
	extern bool chams_player_flat;
	extern bool chams_player_wire_frame;
	extern bool chams_player_glass;
	 
	extern bool chams_no_hands;
	extern bool chams_arms_enabled;
	extern bool chams_arms_ignored;
	 
	extern bool chams_arms_flat;
	extern bool chams_arms_wire_frame;
	extern bool chams_arms_glass;
	 
	extern Color color_chams_arms_visible;
	extern Color color_chams_arms_occluded;
	 
	extern Color color_chams_player_enemy_visible;
	extern Color color_chams_player_ally_visible;
	extern Color color_chams_player_enemy_occluded;
	extern Color color_chams_player_ally_occluded;

	extern bool reveal_ranks;
}