#include "functions.h"
#include "sigScaner.h"
#include "Cheat.h"
typedef FMatrix* (__thiscall* this_get_bone_matrix)(Mesh* mesh, FMatrix* matrix, int bone_id);
this_get_bone_matrix m_get_bone_matrix;

typedef bool(__thiscall* this_ProjectWorldLocationToScreen)(PlayerController* playerController, FVector pos, FVector2D* screen, bool bPlayerViewportRelative);
this_ProjectWorldLocationToScreen m_ProjectWorldLocationToScreen;

auto addrsworldtoscreen = sigScaner::find(NULL, "48 89 ? ? ? 48 89 ? ? ? 48 89 ? ? ? 57 48 81 EC ? ? ? ? 41 0F ? ? 49 8B ? 48 8B ? 48 8B ? 48 85 ? 0F 84");
auto addrsbonematrix = sigScaner::find(NULL, "48 8B ? 48 89 ? ? 48 89 ? ? 57 48 81 EC ? ? ? ? F6 81 88 00 00 00");
bool functions::ProjectWorldLocationToScreen(PlayerController* playerController, FVector pos, FVector2D* screen, bool bPlayerViewportRelative)
{
	this_ProjectWorldLocationToScreen m_projworld = (this_ProjectWorldLocationToScreen)(DWORD64)addrsworldtoscreen;
	return m_projworld(playerController, pos, screen, bPlayerViewportRelative);
}
FMatrix* get_bone_matrix(Mesh* mesh, FMatrix* matrix, int bone_id)
{
	this_get_bone_matrix m_get_bone_matrix = (this_get_bone_matrix)((DWORD64)addrsbonematrix);
	return m_get_bone_matrix(mesh, matrix, bone_id);
}
void functions::get_bone_location(Mesh* mesh, FVector* vec, int bone_id)
{
	FMatrix v_matrix;
	FMatrix* v_temp_matrix = get_bone_matrix(mesh, &v_matrix, bone_id);
	*vec = v_matrix.WPlane;
}
void functions::SetReplicateMovement(AActor* ACharacter, bool InReplicateMovement)
{
	static uintptr_t addr = 0;
	if (!addr)
		addr = sigScaner::find(NULL, "40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8B 8B ? ? ? ? 48 85 C9 74 55");
	using SetReplicateMovement = void(*)(AActor* ACharacter, bool InReplicateMovement);
	const auto SetReplicateMovementF = reinterpret_cast <SetReplicateMovement>(addr);
	return SetReplicateMovementF(ACharacter, InReplicateMovement);
}

float functions::GetDistanceTo(AActor* start, AActor* end)
{
	static uintptr_t addr = 0;
	if (!addr)
		addr = sigScaner::find(NULL, "48 83 EC ? 48 85 ? 0F 84 ? ? ? ? 48 8B ? ? ? ? ? 8B 15 ? ? ? ? F2 0F ? ? ? ? ? ? 48 85 ? 74 ? 0F 10 ? ? ? ? ? 0F 28 ? F3 0F ? ? ? ? 0F C6 C1 ? 0F C6 C9 ? F3 0F ? ? ? ? F3 0F ? ? ? ? EB ? F2 0F ? ? ? ? 89 54 ? ? 48 8D ? ? ? F2 0F ? ? 8B 40 ? 89 44 ? ? 48 8B ? ? ? ? ? F2 0F ? ? ? 48 85 ? 74 ? 0F 10 ? ? ? ? ? 0F 28 ? F3 0F ? ? ? ? 0F C6 C1 ? 0F C6 C9 ? F3 0F ? ? ? ? F3 0F ? ? ? ? EB ? F2 0F ? ? ? ? 89 54 ? ? 48 8D ? ? ? F2 0F ? ? 8B 40 ? 0F 28 ? 0F 28");
	using GetDistanceTo = float(*)(AActor* start, AActor* end);
	const auto GetDistanceToF = reinterpret_cast <GetDistanceTo>(addr);
	return GetDistanceToF(  start,   end);
}
void functions::K2DrawLine(UCanvas* Canvas, FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor) {

	static uintptr_t addr = 0;
	if (!addr)
		addr = sigScaner::find(NULL, "4C 8B DC 48 81 EC ? ? ? ? 4C 89 44 24 ? 66 48 0F 6E D2 F3 0F 10 64 24 ? F3 0F 10 6C 24 ? 0F 28 C4");
	using DrawLine = void(*)(UCanvas* Canvas, FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor);
	const auto DrawLineF = reinterpret_cast <DrawLine>(addr);
	return DrawLineF(Canvas, ScreenPositionA, ScreenPositionB, Thickness, RenderColor);
}
void functions::K2DrawCircle(UCanvas* UCanvas, FVector2D pos, int radius, int numSides, FLinearColor Color)
{
	float PI = 3.1415927f;

	float Step = PI * 2.0 / numSides;
	int Count = 0;
	FVector2D V[128];
	for (float a = 0; a < PI * 2.0; a += Step) {
		float X1 = radius * cos(a) + pos.X;
		float Y1 = radius * sin(a) + pos.Y;
		float X2 = radius * cos(a + Step) + pos.X;
		float Y2 = radius * sin(a + Step) + pos.Y;
		V[Count].X = X1;
		V[Count].Y = Y1;
		V[Count + 1].X = X2;
		V[Count + 1].Y = Y2;
		//Draw_Line(FVector2D{ pos.X, pos.Y }, FVector2D{ X2, Y2 }, 1.0f, Color); // Points from Centre to ends of circle
		K2DrawLine(UCanvas, { V[Count].X, V[Count].Y }, { X2, Y2 }, 1.0f, Color);// Circle Around
	}
}
void functions::K2DrawRect(UCanvas* UCanvas, float x1, float y1, float x2, float y2, FLinearColor color, float linesize)
{
	functions::K2DrawLine(UCanvas, { x1, y1 }, { x2, y1 }, linesize, color);
	functions::K2DrawLine(UCanvas, { x1, y1 }, { x1, y2 }, linesize, color);
	functions::K2DrawLine(UCanvas, { x2, y2 }, { x2, y1 }, linesize, color);
	functions::K2DrawLine(UCanvas, { x2, y2 }, { x1, y2 }, linesize, color);
}
void functions::K2DrawText(UCanvas* canvas, uintptr_t* RenderFont, FString RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor RenderColor, float Kerning, FLinearColor ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor OutlineColor)
{
	static uintptr_t addr = 0;
	if (!addr)
		addr = sigScaner::find(NULL, "40 53 55 56 41 56 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 41 83 78 ? ? 48 8B DA 48 8B AC 24 ? ? ? ?");
	using DrawLine = void(*)(UCanvas* canvas, uintptr_t* RenderFont, FString RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor RenderColor, float Kerning, FLinearColor ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor OutlineColor);
	const auto DrawLineF = reinterpret_cast <DrawLine>(addr);
	return DrawLineF( canvas,   RenderFont,  RenderText,  ScreenPosition,  Scale,  RenderColor,  Kerning,  ShadowColor,  ShadowOffset,  bCentreX,  bCentreY,  bOutlined,  OutlineColor);
}
void functions::GetViewportSize(PlayerController* localplayer, int32_t* SizeX, int32_t* SizeY)
{
	static uintptr_t addr = 0;
	if (!addr)
		addr = sigScaner::find(NULL, "48 89 ? ? ? 48 89 ? ? ? 57 48 83 EC ? 33 C0 49 8B ? 89 02");
	using GetViewportSize = void(*)(PlayerController* localplayer, int32_t* SizeX, int32_t* SizeY);
	const auto GetViewportSizeF = reinterpret_cast <GetViewportSize>(addr);
	return GetViewportSizeF(localplayer, SizeX, SizeY);
}
void functions::drawbone(Mesh* enemyMesh, PlayerController* pcontroller, UCanvas* canvas, int bone1, int bone2) {
	FVector2D BoneStart;
	FVector2D BoneEnd;
	FVector	postargt;
	FVector	postargt2;
	functions::get_bone_location(enemyMesh, &postargt, bone1);
	functions::get_bone_location(enemyMesh, &postargt2, bone2);
	if (functions::ProjectWorldLocationToScreen(pcontroller, postargt, &BoneStart, false))
	{
		if (functions::ProjectWorldLocationToScreen(pcontroller, postargt2, &BoneEnd, false))
		{
			
				functions::K2DrawLine(canvas, { BoneStart.X, BoneStart.Y }, { BoneEnd.X, BoneEnd.Y }, 2, Cheat::colorskeleton);
		}
	}
}