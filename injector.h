#pragma once
#include <Windows.h>
#include <stdio.h>

BOOL ProcessInjector(IN PVOID Shellcode, IN SIZE_T sShellcode, HANDLE* hThread);
