#include "Cheat.h"
#include <string>
#include "Bones.h"

void aimbot(PlayerController* playerController, FVector headpos, PlayerCameraManager* camera, bool visible)
{
	FVector2D headscr;
	
		if (!visible) return;

	FRotator AngleToTraget = functions::GetaimAnglesTo(camera->ViewTarget_POV_Location, headpos);
	(*(__int64(__fastcall**)(__int64, FRotator))(*(__int64*)playerController + 0x680))((__int64)playerController, { -AngleToTraget.Pitch,AngleToTraget.Yaw ,0 });//SetControlRotation;
}
void Cheat::Start(GEngine* gEngine, UCanvas* canvas)
{
	GameInstance* gameinstace = gEngine->GameInstance;
	LocalPlayer* localplayer = gameinstace->LocalPlayers[0];
	if (localplayer == nullptr) return;
	PlayerController* localplayercontroller = localplayer->PlayerController;
	if (localplayercontroller == nullptr) return;
	Player* localplayerstate = localplayercontroller->playerstate;
	if (!localplayerstate) return;
	PawnPriv* localplayerpawn = localplayercontroller->APawn;
	if (localplayerpawn == nullptr) return;
	UWorld* uworld = gEngine->ViewPort->World;
	if (uworld == nullptr) return;
	GameState* gamestate = uworld->GameState;
	if (gamestate == nullptr) return;
	ULevel* perslevel = uworld->PersistentLevel;
	if (!perslevel) return;
	WorldSettings* worldset = perslevel->worldsettings;
	if (!worldset) return;
	worldset->TimeDilation = WorldSpeed;
	PlayerCameraManager* camera = localplayercontroller->PlayerCameraManager;
	if (!camera) return;
	if (!width || !height)
		functions::GetViewportSize(localplayercontroller, &width, &height);
	/*if (Cheat::width && Cheat::height)
		functions::K2DrawCircle(canvas, { (float)Cheat::width / 2 ,(float)Cheat::height / 2 }, Cheat::fov, 60, FLinearColor{ 1,1,1,1 });*/
	for (int i = 0; i < gamestate->Player.Num(); i++)
	{
		Player* player = gamestate->Player[i];
		if (!player) continue;
		PawnPriv* playerpawn = player->Pawn;
		if (!playerpawn) continue;
		if (playerpawn->ZeroHealthInfo_bIsZeroHealth) continue;
		Mesh* playermesh = playerpawn->mesh;
		if (!playermesh) continue;
		if (localplayerstate == player) continue;
		if(teamcheck)
		if (localplayerstate->TeamID == player->TeamID) continue;
		if (skeletonactive)
		{
			//Middle
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::spine_03, Bones::spine_02); //1);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::spine_02, Bones::spine_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::spine_03, Bones::neck_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::neck_01, Bones::head);
			//arm_l 
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::clavicle_l, Bones::neck_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::clavicle_l, Bones::upperarm_l);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::upperarm_l, Bones::lowerarm_l);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::lowerarm_l, Bones::hand_l);
			//arm_R
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::clavicle_r, Bones::neck_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::clavicle_r, Bones::upperarm_r);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::upperarm_r, Bones::lowerarm_r);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::lowerarm_r, Bones::hand_r);
			////foot_l
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::calf_l, Bones::spine_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::calf_l, Bones::foot_l);
			////foot_r
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::calf_r, Bones::spine_01);
			functions::drawbone(playermesh, localplayercontroller, canvas, Bones::calf_r, Bones::foot_r);
		}	
		FVector headpos;
		functions::get_bone_location(playermesh,&headpos,Bones::head);
		bool isVisible = functions::LineOfSign(localplayercontroller,playerpawn);
		aimbot(localplayercontroller, headpos, camera, isVisible);
	}
}