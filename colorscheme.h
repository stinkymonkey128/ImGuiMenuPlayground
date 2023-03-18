#pragma once

#include "imgui/imgui.h"

namespace CScheme {
	constexpr ImU32 MAIN_BG = IM_COL32(15, 6, 7, 255);// IM_COL32(32, 11, 11, 255);

	constexpr ImU32 MAIN_NAVBAR_BG = IM_COL32(126, 25, 27, 255); //IM_COL32(47, 0, 0, 255);//IM_COL32(32, 11, 11, 255);
	constexpr ImU32 MAIN_NAVBAR_ON = IM_COL32(225, 179, 1, 50);
	constexpr ImU32 MAIN_NAVBAR_OFF = IM_COL32(0, 0, 0, 0);
	constexpr ImU32 MAIN_NAVBAR_HIGHLIGHT = IM_COL32(229, 196, 83, 50);

	constexpr ImU32 SUB_NAVBAR_BG = IM_COL32(0, 0, 0, 0);
	constexpr ImU32 SUB_NAVBAR_ON = IM_COL32(225, 179, 1, 255);
	constexpr ImU32 SUB_NAVBAR_OFF = IM_COL32(255, 255, 255, 255);
	constexpr ImU32 SUB_NAVBAR_HIGHLIGHT = IM_COL32(229, 196, 83, 255);

	constexpr ImU32 MAIN_CONT_BG = IM_COL32(32, 11, 11, 255);

	constexpr ImU32 UNI_BORDER = IM_COL32(126, 25, 27, 255);
}