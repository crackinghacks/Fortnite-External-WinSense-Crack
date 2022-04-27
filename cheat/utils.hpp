#include "cheat/ImGui/imgui.h"
#include "cheat/ImGui/imgui_impl_dx9.h"
#include "cheat/ImGui/imgui_impl_win32.h"
#include "cheat/Include/d3dx9.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <tchar.h>
#include <winioctl.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")
#define M_PI 3.14159265358979323846264338327950288419716939937510

typedef struct _ActorStruct
{
	uint64_t pObjPointer, Mesh, PlayerController, PlayerState;

	int ID;
} ActorStruct;



struct Vector3
{
public:
	float x;
	float y;
	float z;
	inline Vector3() : x(0.f), y(0.f), z(0.f) {}
	inline Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	inline Vector3 ToFRotator()
	{
		float Radpi = (float)(180.f / 3.1415926f);
		float Yaw = atan2f(y, x) * Radpi;
		float Pitch = atan2f(z, sqrtf((x * x) + (y * y))) * Radpi;
		float Roll = 0.f;
		return Vector3(Pitch, Yaw, Roll);
	}
	inline Vector3 Clamp()
	{
		if (x > 180.0f)
			x -= 360.0f;
		else if (x < -180.0f)
			x += 360.0f;

		if (y > 180.0f)
			y -= 360.0f;
		else if (y < -180.0f)
			y += 360.0f;

		if (x < -89.0f) { x = -89.0f; }

		if (x > 89.0f) { x = 89.0f; }

		while (y < -180.0f) { y += 360.0f; }

		while (y > 180.0f) { y -= 360.0f; }
		z = 0.0f;
		return Vector3(x, y, z);
	}
	inline float Dot(Vector3 v)
	{
		return x * v.x + y * v.y + z * v.z;
	}
	inline float Distance(Vector3 v)
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
	}
	inline float Length()
	{
		return sqrtf((x * x) + (y * y) + (z * z));
	}
	inline float LengthWithoutZ() {
		return sqrtf((x * x) + (y * y));
	}
	inline Vector3 operator*(float v) const
	{
		return Vector3(x * v, y * v, z * v);
	}
	inline Vector3 operator/(float v) const
	{
		return Vector3(x / v, y / v, z / v);
	}
	inline Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}
	inline Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}
	inline Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	inline Vector3& operator*=(const Vector3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}
	inline Vector3& operator/=(const Vector3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}
};

struct Vector4	
{
public:
	float x;
	float y;
	float z;
	float w;
	inline Vector4() : x(0.f), y(0.f), z(0.f), w(0.f) {}
	inline Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};




struct FTransform
{
public:
	Vector4 Rotation;
	Vector3 Translation;
	CHAR Data1[4];
	Vector3 Scale3D;
	CHAR Data2[4];
	D3DXMATRIX ToMatrixWithScale()
	{
		D3DXMATRIX m;
		m._41 = Translation.x;
		m._42 = Translation.y;
		m._43 = Translation.z;

		float x2 = Rotation.x + Rotation.x;
		float y2 = Rotation.y + Rotation.y;
		float z2 = Rotation.z + Rotation.z;

		float xx2 = Rotation.x * x2;
		float yy2 = Rotation.y * y2;
		float zz2 = Rotation.z * z2;

		m._11 = (1 - (yy2 + zz2)) * Scale3D.x;
		m._22 = (1 - (xx2 + zz2)) * Scale3D.y;
		m._33 = (1 - (xx2 + yy2)) * Scale3D.z;

		float yz2 = Rotation.y * z2;
		float wx2 = Rotation.w * x2;

		m._32 = (yz2 - wx2) * Scale3D.z;
		m._23 = (yz2 + wx2) * Scale3D.y;

		float xy2 = Rotation.x * y2;
		float wz2 = Rotation.w * z2;

		m._21 = (xy2 - wz2) * Scale3D.y;
		m._12 = (xy2 + wz2) * Scale3D.x;

		float xz2 = Rotation.x * z2;
		float wy2 = Rotation.w * y2;

		m._31 = (xz2 + wy2) * Scale3D.z;
		m._13 = (xz2 - wy2) * Scale3D.x;

		m._14 = 0;
		m._24 = 0;
		m._34 = 0;
		m._44 = 1;
		return m;
	}
};

D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}



Vector3 CalculatePrediction(Vector3 AimedBone, Vector3 Velocity, float Distance, float BulletSpeed = 275.f)
{
	BulletSpeed *= 100;
	float Gravity = 9.81f * 100.0f;
	float Time = Distance / BulletSpeed;

	Vector3 TargetPos = AimedBone + (Velocity * Time);

	return TargetPos;
}





void DrawCornerBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {

	float lineW = (W / 3);
	float lineH = (H / 3);
	

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
