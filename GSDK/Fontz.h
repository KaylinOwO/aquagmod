#pragma once

#include "imgui\imgui.h"

class CFontz
{
public:
	ImFont*  bigFont = nullptr;
	ImFont*  forTabs = nullptr;
	ImFont*  menuText = nullptr;
	ImFont* Tabs = nullptr;
	ImFont* Text = nullptr;
	ImFont* wep = nullptr;
	ImFont* icon2 = nullptr;
	ImFont* weaponxd = nullptr;
	ImFont* icon = nullptr;
	ImFont* menubarxd = nullptr;
};

extern CFontz gFontz;