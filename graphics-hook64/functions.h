#pragma once
#include <Windows.h>
#include "GameClass.h"

class functions
{
public:
	static bool ProjectWorldLocationToScreen(PlayerController* playerController, FVector pos, FVector2D* screen, bool bPlayerViewportRelative);
	static void K2DrawCircle(UCanvas* UCanvas, FVector2D pos, int radius, int numSides, FLinearColor Color);
	static void K2DrawLine(UCanvas* Canvas, FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, FLinearColor RenderColor);
	static void K2DrawRect(UCanvas* UCanvas, float x1, float y1, float x2, float y2, FLinearColor color, float linesize);
	static void K2DrawText(UCanvas* canvas, uintptr_t* RenderFont, FString RenderText, FVector2D ScreenPosition, FVector2D Scale, FLinearColor RenderColor, float Kerning, FLinearColor ShadowColor, FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, FLinearColor OutlineColor);
	static void get_bone_location(Mesh* mesh, FVector* vec, int bone_id);
	static void SetReplicateMovement(AActor* ACharacter, bool InReplicateMovement);
	static float GetDistanceTo(AActor* start, AActor* end);
	static void GetViewportSize(PlayerController* localplayer, int32_t* SizeX, int32_t* SizeY);
	static void drawbone(Mesh* enemyMesh, PlayerController* pcontroller, UCanvas* canvas, int bone1, int bone2);
};

