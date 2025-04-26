#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include <Windows.h>
#include <tchar.h>
#include <direct.h>
#include <cstdlib>
#include <string>

#undef _DEBUG
#include <Python.h>
#define _DEBUG
 
void CBG(char* Buf, DWORD dataNum, std::string fileName);