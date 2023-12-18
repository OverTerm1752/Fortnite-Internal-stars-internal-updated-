#pragma once 
int width;
int height;
#include "menu_render.hh"
#include "Hyper_menu.h"
#include "safecall.h"


AFortPawn* TargetPawn;


void Hook(UGameViewportClient* Viewport, UCanvas* Canvas)
{
	auto GWorld = (UWorld*)*(uintptr_t*)(Gworld);
	auto GameInstance = GWorld->GameInstance();
	auto LocalPlayer = GameInstance->LocalPlayers()->LocalPlayer();
	auto Controller = LocalPlayer->PlayerController();
	auto ViewportClient = LocalPlayer->ViewPortClient();
	AcknowledgedPawn = Controller->AcknowledgedPawn();
	TArray<AFortPawn*> get_cars;
	static UGameplayStatics* GameplayStatics;
	GameplayStatics = UGameplayStatics::StaticClass();
	static UClass* FortAthenaVehicle;
	FortAthenaVehicle = UObject::FindClass(("Class FortniteGame.FortAthenaVehicle"));


	if (config.Fov_cricle)
	{
		KGUI::DrawCircle(Canvas->SZE() / 2, (config.Fov_cricle_value * Canvas->SZE().x / config.angle) / 2, { 1,1,1,1 }, 128);
	}

	if (Controller->WasInputKeyJustPressed(keys::Insert))menu_opened = !menu_opened;
	{
		if (menu_opened)
		{
			KGUI::SetupCanvas(Canvas);
			GUI::Input::Handle();
			lit_menu();
		}
	}
	
	if (config.Cars)
	{
	
		GameplayStatics->GetAllActorsOfClass(GWorld, FortAthenaVehicle, &get_cars);
		for (int i = 0; i < get_cars.Num(); i++)
		{
			auto vehicle = get_cars[i];
			auto screen_location = Vector2();
			auto world_location = vehicle->RootComponent()->RelativeLocation();
			if (Controller->w2s(world_location, &screen_location))
			{
				Canvas->ADrawText(Vector2((double)screen_location.x, (double)screen_location.y), s2wc(("Vehicle")), { 1.f, 1.f, 1.f, 1.f }, true, false);
			}
		}
	}

	static UFortKismetLibrary* FortKismetLibrary;
	FortKismetLibrary = UFortKismetLibrary::StaticClass();
	auto Players = FortKismetLibrary->GetFortPawn((UObject*)GWorld);

	for (int i = 0; i < Players.Num(); i++)
	{
		AFortPawn* Player = Players[i];
		if (!id::Get_id(Controller, Player)) continue;
		{
			if (!Player || Player == AcknowledgedPawn || !Player->RootComponent() || !Player->Mesh()) continue;
			{
				FLinearColor box_color = { 0.20f, 0.25f, 0.94f, 1.0f };
				FLinearColor Skeleton_color = { 0.20f, 0.25f, 0.94f, 1.0f };
				FLinearColor snapline_color = { 0.20f, 0.25f, 0.94f, 1.0f };



				if (config.Box)
				{
					float BoxHeight = (float)(id::s_bottom_2.y - id::s_head_2.y);
					float BoxWidth = BoxHeight * 0.50f;
					Canvas->DrawLine(Vector2(id::s_head_2.x - BoxWidth / 2, id::s_bottom_2.y), Vector2(id::s_head_2.x + BoxWidth / 2, id::s_bottom_2.y), 1.f, box_color);
					Canvas->DrawLine(Vector2(id::s_head_2.x + BoxWidth / 2, id::s_bottom_2.y), Vector2(id::s_head_2.x + BoxWidth / 2, id::s_head_2.y), 1.f, box_color);
					Canvas->DrawLine(Vector2(id::s_head_2.x + BoxWidth / 2, id::s_head_2.y), Vector2(id::s_head_2.x - BoxWidth / 2, id::s_head_2.y), 1.f, box_color);
					Canvas->DrawLine(Vector2(id::s_head_2.x - BoxWidth / 2, id::s_head_2.y), Vector2(id::s_head_2.x - BoxWidth / 2, id::s_bottom_2.y), 1.f, box_color);
				}



				if (config.conbox)
				{
					float BoxHeight = (float)(id::s_bottom_2.y - id::s_head_2.y);
					float BoxWidth = BoxHeight * 0.50f;
					Canvas->DrawLine(Vector2(id::s_head_2.x - BoxWidth / 2, id::s_head_2.y), Vector2(id::s_head_2.x + BoxWidth / 2, id::s_bottom_2.y), 1.f, box_color);
					Canvas->DrawLine(Vector2(id::s_bottom_2.x + BoxWidth / 2, id::s_bottom_2.y), Vector2(id::s_head_2.x + BoxWidth / 2, id::s_head_2.y), 1.f, box_color);
				
				}

				if (config.AIm and TargetPawn and (GetAsyncKeyState)(VK_RBUTTON))
				{
					Vector3 headmarket = TargetPawn->GetBoneLocation(68);
					Vector2 headlarketn;
					//aimbot(headlarketn.x, headlarketn.y);
				}
				

				if (config.SkeletonESP)
				{
					Canvas->DrawLine(id::s_neck, id::s_chest, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_chest, id::s_pelvis, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_chest, id::s_rshoulder, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_rshoulder, id::s_relbow, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_relbow, id::s_rhand, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_pelvis, id::s_rthigh, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_rthigh, id::s_rknee, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_rknee, id::s_rfoot, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_rfoot, id::s_rfootout, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_chest, id::s_lshoulder, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_lshoulder, id::s_lelbow, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_lelbow, id::s_lhand, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_pelvis, id::s_lthigh, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_lthigh, id::s_lknee, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_lknee, id::s_lfoot, 1.f, Skeleton_color);
					Canvas->DrawLine(id::s_lfoot, id::s_lfootout, 1.f, Skeleton_color);







				}


				if (config.SnapLines)
				{
					float BoxHeight = (float)(id::s_bottom_2.y - id::s_head_2.y);
					float BoxWidth = BoxHeight * 0.50f;
					canvas->DrawLine(Vector2(BoxWidth / 2, BoxHeight / 1080), id::s_head_2, 2, snapline_color);
					


				}

				
				
				

				
				

				if (config.distance)
				{

				   Canvas->ADrawText(Vector2((double)id::s_head_2.x, (double)id::s_head_2.y), s2wc(("[%2.fm]")),  { 0.f, 0.f, 1.f, 1.f }, true, false);
				   


				}





			}
		}
		
		
	}
	return ((void(*)(UGameViewportClient*, UCanvas*))(Orig))(Viewport, Canvas);
}


