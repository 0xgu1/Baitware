#pragma once
#include <Windows.h>
#include <stdio.h>

BOOL Rc4BySystemFunction(IN PBYTE Rc4key, IN PBYTE Rc4CipherText, IN DWORD Sizekey, IN DWORD SizeCipherText);