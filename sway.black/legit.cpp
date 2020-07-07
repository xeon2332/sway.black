#include "./valve_sdk/sdk.hpp"
#include "legit.h"
#include "options.h"
#include "valve_sdk/csgostructs.hpp"
#include "helpers/math.hpp"

bool Checkplayer(C_BasePlayer* player)
{
	if (!player)
		return false;

	if (player == g_LocalPlayer)
		return false;

	if (!player->IsAlive())
		return false;

	if (player->m_iTeamNum() == g_LocalPlayer->m_iTeamNum())
		return false;

	if (player->IsDormant())
		return false;

	if (player->m_bGunGameImmunity())
		return false;

	if (!options::aimflashed && g_LocalPlayer->IsFlashed())
		return false;

	int firedShots = g_LocalPlayer->m_iShotsFired();
	Vector targetpos = player->GetHitboxPos(HITBOX_HEAD);

	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = g_LocalPlayer;
	auto start = g_LocalPlayer->GetEyePos();

	ray.Init(start, targetpos);
	g_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

	if (tr.hit_entity != player)
		return false;
}

int Gettarget(CUserCmd* cmd)
{
	float nearest = options::fov;
	int index = -1;
	float fov = options::fov;

	for (int i = 1; i < g_GlobalVars->maxClients; i++)
	{
		auto player = C_BasePlayer::GetPlayerByIndex(i);

		if (!Checkplayer(player))
			continue;

		QAngle viewangles;
		g_EngineClient->GetViewAngles(&viewangles);

		Vector targetpos = player->GetHitboxPos(HITBOX_HEAD);

		auto dist = Math::GetFOV(viewangles, Math::CalcAngle(g_LocalPlayer->GetEyePos(), targetpos));

		if (nearest > dist && fov > dist)
		{
			nearest = dist;
			index = i;
		}
	}
	return index;
}

void legit::Aimbot(CUserCmd* cmd)
{
	auto target = C_BasePlayer::GetPlayerByIndex(Gettarget(cmd));
	if (!Checkplayer(target))
		return;

	QAngle angle;

	angle = Math::CalcAngle(g_LocalPlayer->GetEyePos(), target->GetHitboxPos(options::hitbox));

	if (options::smooth > 0.0f)
		Math::SmoothAngle(cmd->viewangles, angle, options::smooth);

	cmd->viewangles = angle;
	g_EngineClient->SetViewAngles(&angle);
}

void legit::Triggerbot(CUserCmd* cmd)
{
	Vector rem, forward,
		src = g_LocalPlayer->GetEyePos();

	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = g_LocalPlayer;

	QAngle viewangles = cmd->viewangles;

	viewangles += g_LocalPlayer->m_aimPunchAngle() * 2.f;

	Math::AngleVectors(viewangles, forward);

	forward *= g_LocalPlayer->m_hActiveWeapon()->GetCSWeaponData()->flRange;

	rem = src + forward;

	ray.Init(src, rem);
	g_EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

	if (!tr.hit_entity)
		return;

	bool dh = false;

	if (tr.hitgroup == HITGROUP_HEAD || tr.hitgroup == HITGROUP_CHEST || tr.hitgroup == HITGROUP_STOMACH || (tr.hitgroup == HITGROUP_LEFTARM || tr.hitgroup == HITGROUP_RIGHTARM) || (tr.hitgroup == HITGROUP_LEFTLEG || tr.hitgroup == HITGROUP_RIGHTLEG))
		dh = true;

	auto player = reinterpret_cast<C_BasePlayer*>(tr.hit_entity);
	if (player && !player->IsDormant() && player->m_iHealth() > 0 && player->IsPlayer())
	{
		if (player->m_iTeamNum() != g_LocalPlayer->m_iTeamNum())
		{
			if (options::trigger_key)
			{
				if (!(cmd->buttons & IN_ATTACK) && GetAsyncKeyState(VK_MENU))
					cmd->buttons |= IN_ATTACK;
			}
			else
			{
				if (!(cmd->buttons & IN_ATTACK))
					cmd->buttons |= IN_ATTACK;

				static bool already_shot = false;
				if (g_LocalPlayer->m_hActiveWeapon().Get()->IsPistol())
				{
					if (cmd->buttons & IN_ATTACK)
						if (already_shot)
							cmd->buttons &= ~IN_ATTACK;

					already_shot = cmd->buttons & IN_ATTACK ? true : false;
				}
			}
		}
	}
}

void legit::tick(CUserCmd* cmd)
{
	if (options::aimbot)
		Aimbot(cmd);

	if (options::triggerbot)
		Triggerbot(cmd);
}