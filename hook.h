#pragma once//s
bool __forceinline Main()
{
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, ("CONOUT$"), ("w"), stdout);
	CachedData::Base = *(uint64_t*)(__readgsqword(0x60) + 0x10);
	auto scanneduworld = ResolveRelativeAddress(PScan(("48 89 05 ? ? ? ? 44 38 3D ? ? ? ?")), 7);
	GetNameByIndex = decltype(GetNameByIndex)(PScan(("48 8B C4 48 89 58 08 48 89 70 18 48 89 78 20 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 ED 48 8B FA 4C 89 2A 4C 89 6A 08 8B 19 E8 ? ? ? ? 48 8B D0 8B CB 48 C1 E9 10 0F B7 C3 44 8D 3C 00 4C 03 7C CA ? 66 41 83 3F ? 0F 82 ? ? ? ? 41 0F B7 07 C1 E8 06 85 C0 44 89 6F 08 8D 50 01 41 0F 44 D5 3B 57 0C 0F 8F ? ? ? ?")));
	LineSightOfTo = decltype(LineSightOfTo)(PScan(("48 8B C4 48 89 58 20 55 56 57 41 54 41 56 48 8D 68")));
	GetBoneMatrix = PScan(("E8 ? ? ? ? 0F 10 40 68"));
	GetBoneMatrix = RVA(GetBoneMatrix, 5);
	auto GWorld = *(uintptr_t*)(scanneduworld);
	auto World = (UWorld*)GWorld;
	auto Game = World->GameInstance();
	auto LocalPlayers = Game->LocalPlayers();
	auto LocalPlayer = LocalPlayers->LocalPlayer();
	auto Controller = LocalPlayer->PlayerController();
	auto Viewport = LocalPlayer->ViewPortClient();
	UKismetStringLibrary::SetupKeys();
	auto index = 110;
	vmt((void*)(std::uintptr_t)Viewport, Hook, index, (void**)&Orig);
	return true;


	
	
}

inline BOOL IsInScreen(Vector2 Pos)
{
	if (((Pos.x <= 0 or Pos.x > width) and (Pos.y <= 0 or Pos.y > height)) or ((Pos.x <= 0 or Pos.x > width) or (Pos.y <= 0 or Pos.y > height))) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

#pragma warning(disable : 4996)


void SetMouseAbsPosition(DWORD x, DWORD y)
{
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = x;
	input.mi.dy = y;
	SendInput(1, &input, sizeof(input));
}
void aimbot(float x, float y)
{
	float ScreenCenterX = (width / 2);
	float ScreenCenterY = (height / 2);
	int AimSpeed = config.smoothing;
	float TargetX = 0;
	float TargetY = 0;

	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	SetMouseAbsPosition(TargetX, TargetY);
	return;
}


