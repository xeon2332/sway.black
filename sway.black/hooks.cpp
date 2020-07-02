#include <iostream>
#include "valve_sdk/sdk.hpp"
#include "helpers/vfunc_hook.hpp"
#include "hooks.h"

vfunc_hook chl;

void __stdcall hkCreateMove(int sequence_number, float input_sample_frametime, bool active)
{
	static auto oCreateMove = chl.get_original<decltype(&hkCreateMove)>(22);

	oCreateMove(sequence_number, input_sample_frametime, active);

	std::cout << "hooked lmao" << std::endl;
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
