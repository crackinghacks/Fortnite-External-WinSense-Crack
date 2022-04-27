#pragma once
#include <vector>


float rainbow_speed = 0.25f;

struct {
	// Basic colors: ========================================================
	float Black[3];
	float RGBRed[3] = { 1.0f, 0.0f, 0.0f };
	float RGBYelllow[3] = { 1.0f, 1.0f, 0.0f };
	float RGBGreen[3] = { 0.0f, 1.0f, 0.0f };
	float RGBBlue[3] = { 0.0f, 0.0f, 1.0f };
	float CMYKRed[3] = { 0.92f, 0.10f, 0.14f };
	float CMYKYellow[3] = { 1.0f, 0.94f, 0.0f };
	float CMYKGreen[3] = { 0.0f, 0.65f, 3.17f };
	float CMYKBlue[3] = { 0.18f, 0.19f, 0.57f };
	float PastelRed[3] = { 0.96f, 0.58f, 0.47f };
	float PastelRedOrange[3] = { 0.97f, 0.67f, 0.50f };
	float PastelYellowOrange[3] = { 0.99f, 0.77f, 0.53f };
	float PastelYellow[3] = { 1.0f, 0.96f, 0.6f };
	float PastelPeaGreen[3] = { 0.76f, 0.87f, 0.60f };
	float PastelYellowGreen[3] = { 0.63f, 0.82f, 0.61f };
	float PastelGreen[3] = { 0.50f, 0.79f, 0.61f };
	float PastelGreenCyan[3] = { 0.47f, 0.8f, 0.78f };
	float PastelCyan[3] = { 0.42f, 0.81f, 0.96f };
	float PastelCyanBlue[3] = { 0.49f, 0.65f, 0.85f };
	float PastelBlue[3] = { 0.51f, 0.57f, 0.79f };
	float PastelBlueViolet[3] = { 0.52f, 0.50f, 0.74f };
	float PastelViolet[3] = { 0.63f, 0.52f, 0.74f };
	float PastelVioletMagenta[3] = { 0.74f, 0.54f, 0.74f };
	float PastelMagenta[3] = { 0.95f, 0.60f, 0.75f };
	float PastelMagentaRed[3] = { 0.96f, 0.59f, 0.61f };
	float LightRed[3] = { 0.94f, 0.42f, 0.30f };
	float LightRedOrange[3] = { 0.96f, 0.55f, 0.33f };
	float LightYellowOrange[3] = { 0.98f, 0.68f, 0.36f };
	float LightYellow[3] = { 1.0f, 0.96f, 0.40f };
	float LightPeaGreen[3] = { 0.67f, 0.82f, 0.45f };
	float LightYellowGreen[3] = { 0.48f, 0.77f, 0.46f };
	float LightGreen[3] = { 0.23f, 0.72f, 0.47f };
	float LightGreenCyan[3] = { 0.10f, 0.73f, 0.70f };
	float LightCyan[3] = { 0.0f, 0.74f, 0.95f };
	float LightCyanBlue[3] = { 0.26f, 0.54f, 0.79f };
	float LightBlue[3] = { 0.33f, 0.45f, 0.72f };
	float LightBlueViolet[3] = { 0.37f, 0.36f, 0.65f };
	float LightViolet[3] = { 0.52f, 0.37f, 0.65f };
	float LightVioletMagenta[3] = { 0.65f, 0.39f, 0.65f };
	float LightMagenta[3] = { 0.94f, 0.43f, 0.66f };
	float LightMagentaRed[3] = { 0.94f, 0.42f, 0.49f };
	float Red[3] = { 0.92f, 0.10f, 0.14f };
	float RedOrange[3] = { 0.94f, 0.39f, 0.13f };
	float YellowOrange[3] = { 0.96f, 0.58f, 0.11f };
	float Yellow[3] = { 1.0f, 0.94f, 0.0f };
	float PeaGreen[3] = { 0.55f, 0.77f, 0.24f };
	float YellowGreen[3] = { 0.22f, 0.70f, 0.29f };
	float Green[3] = { 0.0f, 0.65f, 0.31f };
	float GreenCyan[3] = { 0.0f, 0.66f, 0.61f };
	float Cyan[3] = { 0.0f, 0.68f, 0.93f };
	float CyanBlue[3] = { 0.0f, 0.44f, 0.34f };
	float Blue[3] = { 0.0f, 0.32f, 0.65f };
	float BlueViolet[3] = { 0.19f, 0.19f, 0.57f };
	float Violet[3] = { 0.18f, 0.19f, 0.57f };
	float VioletMagenta[3] = { 0.57f, 0.15f, 5.63f };
	float Magenta[3] = { 0.92f, 0.0f, 0.54f };
	float MagentaRed[3] = { 0.92f, 0.07f, 0.35f };
	float DarkRed[3] = { 0.61f, 0.04f, 0.05f };
	float DarkROrange[3] = { 0.62f, 0.25f, 0.05f };
	float DarkYellowOrange[3] = { 0.53f, 0.38f, 0.03f };
	float DarkYellow[3] = { 0.67f, 0.62f, 0.0f };
	float DarkPeaGreen[3] = { 0.34f, 0.52f, 0.15f };
	float DarkYellowGreen[3] = { 0.09f, 0.48f, 0.18f };
	float DarkGreen[3] = { 0.0f, 0.44f, 0.21f };
	float DarkGreenCyan[3] = { 0.0f, 0.45f, 0.41f };
	float DarkCyan[3] = { 0.0f, 0.46f, 0.63f };
	float DarkCyanBlue[3] = { 0.0f, 0.29f, 0.50f };
	float DarkBlue[3] = { 0.0f, 0.20f, 0.44f };
	float DarkBlueViolet[3] = { 0.10f, 0.07f, 0.39f };
	float DarkViolet[3] = { 0.26f, 0.05f, 0.38f };
	float DarkVioletMagenta[3] = { 0.38f, 0.01f, 0.37f };
	float DarkMagenta[3] = { 0.61f, 0.0f, 0.36f };
	float DarkMagentaRed[3] = { 0.61f, 0.0f, 0.22f };
	float DarkerRed[3] = { 0.47f, 0.0f, 0.0f };
	float DarkerROrange[3] = { 0.48f, 0.18f, 0.0f };
	float DarkerYellowOrange[3] = { 0.49f, 0.28f, 0.0f };
	float DarkerYellow[3] = { 0.50f, 0.48f, 0.0f };
	float DarkerPeaGreen[3] = { 0.25f, 0.4f, 0.09f };
	float DarkerYellowGreen[3] = { 0.0f, 0.36f, 0.12f };
	float DarkerGreen[3] = { 0.0f, 0.34f, 0.14f };
	float DarkerGreenCyan[3] = { 0.0f, 0.34f, 0.32f };
	float DarkerCyan[3] = { 0.0f, 0.35f, 0.49f };
	float DarkerCyanBlue[3] = { 0.0f, 0.21f, 0.38f };
	float DarkerBlue[3] = { 0.0f, 0.12f, 0.34f };
	float DarkerBlueViolet[3] = { 0.05f, 0.0f, 0.29f };
	float DarkerViolet[3] = { 0.19f, 0.0f, 0.29f };
	float DarkerVioletMagenta[3] = { 0.29f, 0.0f, 0.28f };
	float DarkerMagenta[3] = { 0.48f, 0.0f, 0.27f };
	float DarkerMagentaRed[3] = { 0.47f, 0.27f, 0.14f };
	float PaleCoolBrown[3] = { 0.78f, 0.69f, 0.61f };
	float LightCoolBrown[3] = { 0.6f, 0.52f, 0.45f };
	float MiumCoolBrown[3] = { 0.45f, 0.38f, 0.34f };
	float DarkCoolBrown[3] = { 0.32f, 0.27f, 0.25f };
	float DarkerCoolBrown[3] = { 0.21f, 0.18f, 0.17f };
	float PaleWarmBrown[3] = { 0.77f, 0.61f, 0.43f };
	float LightWarmBrown[3] = { 0.65f, 0.48f, 0.32f };
	float MiumWarmBrown[3] = { 0.54f, 0.38f, 0.22f };
	float DarkWarmBrown[3] = { 0.45f, 0.29f, 0.14f };
	float DarkerWarmBrown[3] = { 0.37f, 0.22f, 0.07f };
	float purple[3] = { 144.00f, 0.00f, 255.00f };
	float white[3] = { 3.00f, 3.00f, 3.00f };
	float white2[3] = { 0.00f, 0.00f, 0.00f };
	float whitetrans[3] = { 3.00f, 3.00f, 3.00f };
	float blacktrans[3] = { 26.0f, 22.0f, 23.0f };





} color;

std::string anticrackbios = "C:\\ProgramData\\Microsoft\\Windows\\";

struct {
	// item set ==============================================================

	float Active_Tab;
	float Aimbot_Page;
	float Color_Page = 1;
	float Switch_Page;
	float aimkey;
	float hitbox = 66.0;
	float aimkeypos;
	float hitboxpos = 1;
	float boneswitch = 2;
	float Aim_Speed = 2;
	float VisDist = 150;
	float AimFOV = 150.0f;
	float RectFOV = 150.0f;
	float EspDist = 150.0f;
	float HeadDotLine = 150.0f;
	float AimbotMaximalDistance = 100.0f;
	bool AimKey_RMB = true;
	bool AimKey_SHIFT = false;
	bool AimKey_DOWN = false;
	int AimKey;


	float AimbotFOV;
	bool Show_Menu = false;
	bool Dev = true;
	bool Auto_Bone_Switch = false;
	bool Draw_FOV_Circle = true;
	bool Draw_FOV_Circle2 = false;
	bool FovFilled = false;
	bool DrawRect = false;
	bool DrawFov = false;
	bool fov = true;
	bool Aim_Prediction;
	bool Cross_Hair = false;
	bool Radar = true;
	bool Lock_Line = false;
	bool Auto_Fire = false;
	bool ShowMenu = false;
	bool outlinedskel = true;
	bool ballesp = true;
	bool outlinedtext = true;
	bool enableSmoothing = false;

	bool MenuAimBoneInt0 = true;
	bool MenuAimBoneInt1 = false;
	bool MenuAimBoneInt2 = false;
	bool MenuAimBoneInt3 = false;

	bool MenuAimKeyInt0 = true;
	bool MenuAimKeyInt1 = false;
	bool MenuAimKeyInt2 = false;






	int MaxSkeletonDrawDistance = 30;


	bool Chest = true;


	// enemy ==============================================================
	bool Aimbot = true;

	bool Esp_box = false;
	bool filledboxes = false;
	bool cornered = true;
	bool Esp_box_fill = false;
	bool showconsole = false;
	bool Esp_Circle = false;
	bool Esp_Circle_Fill;
	bool Triangle_ESP;
	bool Triangle_ESP_Filled;
	bool Head_dot;
	bool Distance_Esp = true;
	bool Esp_line;
	bool Esp_Skel = false;
	bool skeleton = true;
	bool Reticle = true;
	bool botesp = true;
	bool silentaim = false;

	bool IsFilled = false;
	bool outlinedbox = true;
	bool outlinedfov = true;
	bool ThreeDESP = true;
	bool Selfesp = true;
	bool enableVisuals = false;

	float RadarESPRange = true;

	//enemy item color ==============================================================
	float DrawFOVCircle[4] = { color.white[0], color.white[1], color.white[2] };

	float fl_InvisibleColor[3] = { 255.f / 255,0.f,0.f };

	float Espbox[3] = { color.white[0], color.white[1], color.white[2] };
	float SkelColor[3] = { color.white[0], color.white[1], color.white[2] };
	float BoxCornerESP[3] = { color.white[0], color.white[1], color.white[2] };
	float Espboxfill[3] = { color.white[0], color.white[1], color.white[2] };
	float DistanceEsp[3] = { color.white[0], color.white[1], color.white[2] };
	float EspSkel[3] = { color.white[0], color.white[1], color.white[2] };
	float EspCircle[3] = { color.RGBBlue[0], color.RGBBlue[1], color.RGBBlue[2] };
	float EspCircleFill[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float TriangleESP[3] = { color.RGBBlue[0], color.RGBBlue[1], color.RGBBlue[2] };
	float Skeleton[3] = { color.RGBBlue[0], color.RGBBlue[1], color.RGBBlue[2] };
	float TriangleESPFilled[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float Headdot[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float LineESP[3] = { color.Red[0], color.Red[1], color.Red[2] };
	float LineFilled[3] = { color.Red[0], color.Red[1], color.Red[2] };




	float Text[3] = { color.white[0], color.white[1], color.white[2] };
	float Button[3] = { color.Black[0], color.Black[1], color.Black[2] };
	float Checkbox[3] = { color.Red[0], color.Red[1], color.Red[2] };
	float OverlayLine[3] = { color.white[0], color.white[1], color.white[2] };
	float Window[3] = { color.Black[0], color.Black[1], color.Black[2] };

	float CrossHair[3] = { color.Violet[0], color.Violet[1], color.Violet[2] };
	float LockLine[3] = { color.Red[0], color.Red[1], color.Red[2] };
	float ReticleCol[3] = { color.Red[0], color.Red[1], color.Red[2] };

	// item color set ==============================================================
	float Thickness = 1.0f;
	float Shape = 40.0f;

	float Transparency = 0.5f;

	float Transparencyy = 0.5f;

	//team ==============================================================
	bool Team_Aimbot;

	bool Team_Esp_box;
	bool Team_Esp_Corner_Box;
	bool Team_Esp_box_fill;
	bool Team_Esp_Circle;
	bool Team_Esp_Circle_Fill;
	bool Team_Triangle_ESP;
	bool Team_Triangle_ESP_Filled;
	bool Team_Head_dot;
	bool Team_Distance_Esp = true;
	bool fps = true;
	bool OutlinedSkeleton = false;
	bool rainbowmode = true;
	bool PlayersCorner = false;
	bool names = true;
	bool cornered2 = false;
	bool box2 = false;
	bool Team_Esp_line;

	//team item color ==============================================================
	float TeamEspbox[3] = { color.Green[0], color.Green[1], color.Green[2] };
	float TeamBoxCornerESP[3] = { color.Green[0], color.Green[1], color.Green[2] };
	float TeamEspboxfill[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float TeamEspCircle[3] = { color.RGBBlue[0], color.RGBBlue[1], color.RGBBlue[2] };
	float TeamEspCircleFill[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float TeamTriangleESP[3] = { color.RGBBlue[0], color.RGBBlue[1], color.RGBBlue[2] };
	float TeamTriangleESPFilled[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float TeamHeaddot[3] = { color.RGBRed[0], color.RGBRed[1], color.RGBRed[2] };
	float TeamLineESP[3] = { color.LightBlue[0], color.LightBlue[1], color.LightBlue[2] };

#define CFG Configuration::Settings::Get()
} item;


