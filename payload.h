#pragma once
#include <Windows.h>
#include <stdio.h>
#include "resource.h"

extern unsigned char Rc4Key[16];

BOOL GetPayloadRSRC(OUT PVOID* pPayload, OUT PSIZE_T sPayload);