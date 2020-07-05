#pragma once

namespace options
{
	// Aimbot
	bool aimbot;
	float smooth;
	float fov;
	bool aim_key;
	int aimkey;

	bool triggerbot;
	float delay;
	bool trigger_key;
	int triggerkey;

	bool bunny_hop;

	bool glow_enabled;
	bool glow_players;
	bool glow_enemies;
	bool glow_c4_carrier;
	bool glow_planted_c4;
	bool glow_defuse_kit;
	bool glow_chickens;
	bool glow_weapons;

	Color color_glow_players;
	Color color_glow_enemies;
	Color color_glow_ally;
	Color color_glow_c4_carrier;
	Color color_glow_planted_c4;
	Color color_glow_defuse_kit;
	Color color_glow_chickens;
	Color color_glow_weapons;

	bool chams_player;
	bool chams_player_enemy;
	bool chams_player_arms;
	bool chams_player_ignored;

	bool chams_player_flat;
	bool chams_player_wire_frame;
	bool chams_player_glass;

	bool chams_no_hands;
	bool chams_arms_enabled;
	bool chams_arms_ignored;

	bool chams_arms_flat;
	bool chams_arms_wire_frame;
	bool chams_arms_glass;

	Color color_chams_arms_visible;
	Color color_chams_arms_occluded;

	Color color_chams_player_enemy_visible;
	Color color_chams_player_ally_visible;
	Color color_chams_player_enemy_occluded;
	Color color_chams_player_ally_occluded;

	bool reveal_ranks;
}