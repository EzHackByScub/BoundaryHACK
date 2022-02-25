#pragma once
#include "functions.h"
class Cheat
{
public:
	static void Start(GEngine* gEngine, UCanvas* canvas);
	inline static int width, height;
	inline static bool skeletonactive,teamcheck;
	inline static FLinearColor colorskeleton = { 1, 1, 1,1 };
};