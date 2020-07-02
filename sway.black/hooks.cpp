#include <iostream>
#include "valve_sdk/sdk.hpp"
#include "helpers/vfunc_hook.hpp"
#include "hooks.h"

vfunc_hook chl;

void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	static auto oCreateMove = chl.get_original<decltype(&hkCreateMove)>(22);

	oCreateMove(sequence_number, input_sample_frametime, active);

	auto cmd = g_Input->GetUserCmd(sequence_number);
	auto verified = g_Input->GetVerifiedCmd(sequence_number);

	if (!cmd || !cmd->command_number)
		return;

	// Place functions here

	verified->m_cmd = *cmd;
	verified->m_crc = cmd->GetChecksum();
}

void hooks::HookCSGO()
{	
	chl.setup(g_CHLClient);

	chl.hook_index(22, hkCreateMove);
}

void hooks::UnHook()
{
	chl.unhook_index(22);
}
