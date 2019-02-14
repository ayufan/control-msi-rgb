// ControlLeds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>

typedef int (__stdcall *FuncCheckMbVersion)(LPCWCH mb, LPCWCH ver, LPCWCH market, LPCWCH sioinit);
typedef int (__stdcall *FuncControlCorsairProDRAMLED)(int style, int colorType, int direction, int r, int g, int b, int bright, int speed);
typedef int(__stdcall *FuncInitialDDRTIMING)();

void DbgPrintf(const char *fmt, ...)
{
	va_list marker;
	char szBuf[256];

	va_start(marker, fmt);
	vsprintf_s(szBuf, fmt, marker);
	va_end(marker);

	OutputDebugStringA(szBuf);
	fprintf(stdout, "%s", szBuf);
}

int main()
{
	auto lib = LoadLibraryA("C:\\Program Files (x86)\\MSI\\MysticLight\\Lib\\MBAPI_x86.dll");
	if (!lib) {
		DbgPrintf("Cannot load LIB\n");
		return 1;
	}

	auto init = (FuncCheckMbVersion)GetProcAddress(lib, "CheckMBVersion");
	if (!lib) {
		DbgPrintf("Cannot get lib function\n");
		return 1;
	}

	auto result = init(L"MSI-7B46", L"1", L"Z370 KRAIT GAMING", L"T");
	if (!result) {
		DbgPrintf("Failed to init\n");
		return 1;
	}

	auto initDDR = (FuncInitialDDRTIMING)GetProcAddress(lib, "InitialDDRTIMING");
	if (!lib) {
		DbgPrintf("Cannot get lib function\n");
		return 1;
	}

	result = initDDR();
	if (!result) {
		DbgPrintf("Failed to initDDR\n");
		return 1;
	}

	auto dramLED = (FuncControlCorsairProDRAMLED)GetProcAddress(lib, "ControlCorsairProDRAMLED");
	if (!lib) {
		DbgPrintf("Cannot get lib function\n");
		return 1;
	}
	
	DbgPrintf("Got it\n");

	result = dramLED(1, 0, 0, 99, 33, 129, 80, 2);
	printf("result=%d\n", result);

	return 0;
}
