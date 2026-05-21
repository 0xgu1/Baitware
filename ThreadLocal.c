#include "ThreadLocal.h"
#include "Baitfunction.h"
#include "injector.h"



BOOL CreateThreadInoffensive(OUT HANDLE* hThread) {

	HANDLE hThreadLocal = NULL;


	hThreadLocal = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&BaitFunction, NULL, CREATE_SUSPENDED, NULL);
	if (hThreadLocal == NULL) {
		printf("Error CreateThread: %d \n", GetLastError());
		return FALSE;
	}

	*hThread = hThreadLocal;

	return TRUE;
}
