#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "detours.h"
#include "sigScaner.h"
#include "ZeroGUI.h"
#include "Cheat.h"
#pragma comment(lib, "detours.lib")
uintptr_t AddressOfpostrender = sigScaner::find(NULL, "48 8B ? 48 FF ? ? ? ? ? CC CC CC CC CC CC 41 ? 48 83 EC ? 48 89");
typedef __int64(*postrender)(__int64* viewport, UCanvas* canvas);
uintptr_t GameEngineAddr = sigScaner::find(NULL, "48 8B ? ? ? ? ? 48 89 ? ? ? ? ? ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? E8");
GEngine* gEngine = (GEngine*)(*(uintptr_t*)sigScaner::GetAbsoluteAddress(GameEngineAddr, 3, 7));
int test_number;
FVector2D pos;
void Tick(UCanvas* canvas)
{
	ZeroGUI::Input::Handle();
	Cheat::Start(gEngine,canvas);
	static bool menu_opened = false;
	if (GetAsyncKeyState(VK_INSERT) & 1) menu_opened = !menu_opened; //Our menu key

	if (ZeroGUI::Window(gEngine, (char*)"EZHACKBYSCUB!", &pos, FVector2D{ 500.0f, 400.0f }, menu_opened))
	{
		ZeroGUI::Checkbox(gEngine,(char*)"Skeleton",&Cheat::skeletonactive);
		ZeroGUI::Checkbox(gEngine, (char*)"TeamCheck", &Cheat::teamcheck);
	}
	ZeroGUI::Render(gEngine);//Custom Render. I use it for drawing Combobox and ColorPicker over the menu
	ZeroGUI::Draw_Cursor(canvas, menu_opened);
}

__int64 Hookpostrender(__int64* viewport, UCanvas* canvas)
{
	if (!canvas)
	{
		postrender originalpostrender = (postrender)AddressOfpostrender;
		return originalpostrender(viewport, canvas);
	}
    ZeroGUI::SetupCanvas(canvas);
	Tick(canvas);
    postrender originalpostrender = (postrender)AddressOfpostrender;
    return originalpostrender( viewport,  canvas);
}
void inithook()
{
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)AddressOfpostrender, &Hookpostrender);
    DetourTransactionCommit();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    inithook();
    return TRUE;
}

