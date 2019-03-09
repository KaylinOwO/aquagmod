typedef HRESULT(__stdcall* EndSceneFn)(IDirect3DDevice9*);
EndSceneFn orgEndScene = nullptr;

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC orgproc = nullptr;

LRESULT __stdcall proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_KEYDOWN)
		if (wParam == VK_INSERT){Menu::InsertDown = true;}
		
	if (msg == WM_KEYUP)
		if (wParam == VK_INSERT) { Menu::InsertDown = false; }

	ImGui_ImplDX9_WndProcHandler(hwnd, msg, wParam, lParam);

	return CallWindowProcA(orgproc, hwnd, msg, wParam, lParam);
}

#include "../../../Fonts.hpp"
#include "../../../Fontz.h"

CFontz gFontz;

HRESULT __stdcall hookEndScene(IDirect3DDevice9* device)
{
	if (!Menu::initialised)
	{
		auto gmod = FindWindowW(L"Valve001", nullptr);
		ImGuiIO& io = ImGui::GetIO();
		orgproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(gmod, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(proc)));
		gFontz.icon = io.Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_data13, MyFont_compressed_size13, 25.f);
		gFontz.icon2 = io.Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_dataxdd, MyFont_compressed_sizexdd, 25.f);
		gFontz.menubarxd = io.Fonts->AddFontFromMemoryCompressedTTF(MyFont_compressed_data13, MyFont_compressed_size13, 15.f);
		//gFontz.eagle = io.Fonts->AddFontFromMemoryCompressedTTF(eagle2_compressed_data, eagle2_compressed_size, 70.f);
		gFontz.feagle = io.Fonts->AddFontFromMemoryCompressedTTF(eagle_compressed_data, eagle_compressed_size, 25.f);
		gFontz.NCCIcon = io.Fonts->AddFontFromMemoryCompressedTTF(ncc_compressed_data, ncc_compressed_size, 45.f);
		gFontz.Text = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 12.f);
		ImGui_ImplDX9_Init(gmod, device);

		ImGuiStyle& style = ImGui::GetStyle();
		style.Alpha = 1.0f;
		style.WindowPadding = ImVec2(8, 8);
		style.WindowMinSize = ImVec2(32, 32);
		style.WindowRounding = 0.0f;
		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.ChildWindowRounding = 0.0f;
		style.FramePadding = ImVec2(4, 1);
		style.FrameRounding = 0.0f;
		style.ItemSpacing = ImVec2(15, 4);
		style.ItemInnerSpacing = ImVec2(4, 4);
		style.TouchExtraPadding = ImVec2(0, 0);
		style.IndentSpacing = 21.0f;
		style.ColumnsMinSpacing = 3.0f;
		style.ScrollbarSize = 12.0f;
		style.ScrollbarRounding = 0.0f;
		style.GrabMinSize = 0.1f;
		style.GrabRounding = 16.0f;
		style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
		style.DisplayWindowPadding = ImVec2(22, 22);
		style.DisplaySafeAreaPadding = ImVec2(4, 4);
		style.AntiAliasedLines = true;
		style.AntiAliasedShapes = true;
		style.CurveTessellationTol = 1.25f;


		ImVec4 Color_Title_Text = ImColor(165, 75, 100);

		int MenuRed, MenuGreen, MenuBlue;

		MenuRed = 255;
		MenuGreen = 255;
		MenuBlue = 255;

		ImColor mainColor = ImColor(MenuRed, MenuGreen, MenuBlue);
		ImColor bodyColor = ImColor(24, 24, 24, 239);
		ImColor fontColor = ImColor(150, 150, 150, 255);


		ImVec4 mainColorHovered = ImVec4(mainColor.Value.x + 0.1f, mainColor.Value.y + 0.1f, mainColor.Value.z + 0.1f, mainColor.Value.w);
		ImVec4 mainColorActive = ImVec4(mainColor.Value.x + 0.2f, mainColor.Value.y + 0.2f, mainColor.Value.z + 0.2f, mainColor.Value.w);
		ImVec4 menubarColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w - 0.8f);
		ImVec4 frameBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .1f);
		ImVec4 tooltipBgColor = ImVec4(bodyColor.Value.x, bodyColor.Value.y, bodyColor.Value.z, bodyColor.Value.w + .05f);
		style.Colors[ImGuiCol_Button] = ImColor(113, 221, 229, 255);

		style.Colors[ImGuiCol_MainTheme] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_MainTheme2] = ImColor(113, 221, 229, 255);

		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(1.f, 1.f, 1.f, 1.f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.13f, 0.13f, 1.f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.f);
		style.Colors[ImGuiCol_Border] = ImColor(15, 30, 15, 255);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.22f, 0.22f, 0.22f, 0.f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.22f, 0.22f, 0.22f, 1.f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.22f, 0.22f, 0.22f, 1.f);
		style.Colors[ImGuiCol_TitleBg] = ImColor(MenuRed, MenuGreen, MenuBlue, 255);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(MenuRed, MenuGreen, MenuBlue, 255);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(MenuRed, MenuGreen, MenuBlue, 255);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(frameBgColor.x + .1f, frameBgColor.y + .1f, frameBgColor.z + .1f, frameBgColor.w);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.f);
		style.Colors[ImGuiCol_ComboBg] = frameBgColor;
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.76f, 0.10f, 0.24f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(68, 140, 255);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(68, 140, 255);
		style.Colors[ImGuiCol_Button] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(113, 221, 229, 255);
		style.Colors[ImGuiCol_Header] = ImColor(113, 221, 229, 225);
		style.Colors[ImGuiCol_HeaderHovered] = ImColor(113, 221, 229, 125);
		style.Colors[ImGuiCol_HeaderActive] = ImColor(113, 221, 229, 225);

		style.Colors[ImGuiCol_Column] = ImVec4(.30f, .30f, .30f, 1.f);
		style.Colors[ImGuiCol_ColumnHovered] = mainColorHovered;
		style.Colors[ImGuiCol_ColumnActive] = mainColorActive;

		Menu::initialised = true;
	}
	else
	{
		if (Menu::opened)
		{
			InputSystem()->EnableInput(false);
			surface()->SetCursorAlwaysVisible(true);
			ImGuiStyle& style = ImGui::GetStyle();
			D3DCOLOR rectColor = D3DCOLOR_XRGB(255, 0, 0);
			D3DRECT BarRect = { 1, 1, 1, 1 };

			device->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, rectColor, 0, 0);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
			device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
			device->SetRenderState(D3DRS_SRGBWRITEENABLE, false);
			ImGui::GetIO().MouseDrawCursor = 1;
		}
		else
		{
			InputSystem()->EnableInput(true);
			surface()->SetCursorAlwaysVisible(false);
			ImGui::GetIO().MouseDrawCursor = 0;
		}
		ImGui_ImplDX9_NewFrame();
		Menu::OpenMenuThing();
		if (Menu::opened)
			Menu::drawMenu();
		else
			ImGui::GetIO().MouseDrawCursor = 0;
		ImGui::Render();
	}
	return orgEndScene(device);
}
