#include "obfuscation.h"

typedef struct {
	DWORD Length;
	DWORD MaximumLength;
	PVOID Buffer;
} USTRING;


typedef NTSTATUS(NTAPI* fnSystemFunction032)(

	USTRING* Image,
	USTRING* Key
);


BOOL Rc4BySystemFunction(IN PBYTE Rc4key, IN PBYTE Rc4CipherText, IN DWORD Sizekey, IN DWORD SizeCipherText) {

	NTSTATUS STATUS = 0;

	USTRING Image = { .Buffer = Rc4CipherText, .Length = SizeCipherText, .MaximumLength = SizeCipherText },
		    Key = { .Buffer = Rc4key, .Length = Sizekey, .MaximumLength = Sizekey };

	fnSystemFunction032 pSystemFunction032 = (fnSystemFunction032)GetProcAddress(LoadLibraryA("Advapi32"), "SystemFunction032");

	if ((STATUS = pSystemFunction032(&Image, &Key)) != 0x0) {
		printf("[!] SystemFunction032 FAILED With Error: 0x%0.8X \n", STATUS);
		return FALSE;
	}
	
	return TRUE;
}

