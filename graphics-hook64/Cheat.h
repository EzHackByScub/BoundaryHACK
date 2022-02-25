#pragma once
#include "functions.h"
class Cheat
{
public:
	static void Start(GEngine* gEngine, UCanvas* canvas);
	inline static int width, height,WorldSpeed = 1;
	inline static bool skeletonactive,teamcheck, activevisiblecheck;
	inline static FLinearColor colorskeleton = { 1, 0, 0,1 };
};