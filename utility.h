#pragma once
#include <windows.h>
#include <winternl.h>
#include <process.h>
#include <tlhelp32.h>
#include <inttypes.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <d3d9.h>

#pragma comment (lib, "d3d9.lib")



HANDLE DriverHandle;
uint64_t base_address;
HWND hwnd = NULL;
DWORD processID;

int Width;
int Height;
int Depth;

#define M_PI 3.14159265358979323846264338327950288419716939937510

#define ctl_write    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0569, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ctl_read    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0567, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define ctl_base    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0568, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct info_t {
	int pid = 0;
	DWORD_PTR address;
	void* value;
	SIZE_T size;
	void* data;
}	info, * p_info;

template <typename Type>
Type read(void* DriverHandle, unsigned long int Process_Identifier, unsigned long long int Address)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = Process_Identifier;

	Input_Output_Data.address = Address;

	Type Return_Value;

	Input_Output_Data.value = &Return_Value;

	Input_Output_Data.size = sizeof(Type);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DriverHandle, ctl_read, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);

	return *(Type*)&Return_Value;
}

void writefloat(unsigned long long int Address, float stuff)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = processID;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &stuff;

	Input_Output_Data.size = sizeof(float);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DriverHandle, ctl_write, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
}

void writedouble(unsigned long long int Address, double stuff)
{
	info_t Input_Output_Data;

	Input_Output_Data.pid = processID;

	Input_Output_Data.address = Address;

	Input_Output_Data.value = &stuff;

	Input_Output_Data.size = sizeof(double);

	unsigned long int Readed_Bytes_Amount;

	DeviceIoControl(DriverHandle, ctl_write, &Input_Output_Data, sizeof Input_Output_Data, &Input_Output_Data, sizeof Input_Output_Data, &Readed_Bytes_Amount, nullptr);
}




struct FQuat
{
	float x;
	float y;
	float z;
	float w;
};





std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);

	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr(pBuf);

	delete[]pwBuf;
	delete[]pBuf;

	pwBuf = NULL;
	pBuf = NULL;

	return retStr;
}




