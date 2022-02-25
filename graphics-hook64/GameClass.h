#include "UnrealEngineClasses.h"
class WorldSettings
{
public:
    char pad_0000[0x2E8]; //0x0000
    float TimeDilation;
};
class ULevel
{
public:
    char pad_0000[0x258]; //0x0000
    class WorldSettings* worldsettings;
};
class Mesh
{

};
class AActor
{
};
class RootComponet
{
public:
    char pad_0000[0x11c]; //0x0000
    FVector realcpos;
};
class PawnPriv
{
public:
    char pad_0000[0x130]; //0x0000
    class RootComponet* RootComponet; //0x0130
    char pad_0138[328]; //0x0138
    class Mesh* mesh; //0x0280
    char pad_0288[2652]; //0x0288
    bool ZeroHealthInfo_bIsZeroHealth; //0x0CE4
};
class LocalPlayers
{
public:
    class LocalPlayer* LocalPlayer; //0x0000
}; //Size: 0x0008
class PlayerCameraManager
{
public:
    char pad_0000[0xe80]; //0x0000
    FVector ViewTarget_POV_Location;
};
class PlayerController
{
public:
    char pad_0000[148]; //0x0000
    float InitialLifeSpan; //0x0094
    char pad_0098[152]; //0x0098
    class RootComponet* RootComponet; //0x0130
    char pad_0138[240]; //0x0138
    class Player* playerstate; //0x0228
    char pad_0230[32]; //0x0230
    class PawnPriv* APawn; //0x0250
    char pad_0258[96]; //0x0258
    class PlayerCameraManager* PlayerCameraManager; //0x02B8

}; //Size: 0x085C
class LocalPlayer
{
public:
    char pad_0000[16]; //0x0000
    class ClassType* Type; //0x0010
    char pad_0018[24]; //0x0018
    class PlayerController* PlayerController; //0x0030
}; //Size: 0x1008
class GameInstance
{
public:
    char pad_0000[16]; //0x0000
    class ClassType* Type; //0x0010
    char pad_0018[32]; //0x0018
    TArray<LocalPlayer*>(LocalPlayers);
}; //Size: 0x0108
class Player
{
public:
    char pad_0000[0x280]; //0x0000
    class PawnPriv* Pawn;//0x0280
    char pad_0288[120]; //0x0288
    wchar_t* name; //0x0300
    char pad_0308[424]; //0x0308
    int32_t TeamID; //0x04B0
    char pad_04B4[20]; //0x04B4
    bool bIsDying; //0x04C8
};
class GameState
{
public:
    char pad_0000[0x238]; //0x0000
    TArray<Player*>(Player);
}; //Size: 0x0848
class UWorld
{
public:
    char pad_0000[48]; //0x0000
    class ULevel* PersistentLevel; //0x0030
    char pad_0038[224]; //0x0038
    class AGameModeBase* AuthorityGameMode; // 0x118
    class GameState* GameState; //0x0120
    char pad_0128[88]; //0x0128
    class OwningGameInstance* OwningGameInstance; //0x0180
}; //Size: 0x0408
class GameViewport
{
public:
    void* Vtable; //0x0000
    char pad_0008[8]; //0x0008
    class ClassType* type; //0x0010
    char pad_0018[80]; //0x0018
    int32_t MaxSplitscreenPlayers; //0x0068
    char pad_006C[12]; //0x006C
    class UWorld* World; //0x0078
    class GameInstance* gameinstance; //0x0080
}; //Size: 0x0108
class ClassType
{
public:
    char pad_00010[0x10]; //0x0008
    class ClassType* ClType; //0x0010
    int32_t FnameIndex; //0x0018

};
class GEngine
{
public:
    void* Vtable; //0x0000
    char pad_0008[8]; //0x0008
    class ClassType* type; //0x0010
    char pad_0018[24]; //0x0018
    uintptr_t* TinyFont; //0x0030
    char pad_0038[24]; //0x0038
    uintptr_t* SmallFont; //0x0050
    char pad_0058[24]; //0x0058
    uintptr_t* MediumFont; //0x0070
    char pad_0078[24]; //0x0078
    uintptr_t* LargeFont; //0x0090
    char pad_0098[24]; //0x0098
    uintptr_t* SubtitleFont; //0x00B0
    char pad_00B8[368]; //0x00B8
    class GameUserSettings* GameUserSettings; //0x0228
    char pad_0230[1360]; //0x0230
    class GameViewport* ViewPort; //0x0780
    char pad_0788[1632]; //0x0788
    class GameInstance* GameInstance; //0x0DE8
}; //Size: 0x1950