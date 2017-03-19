#include "Header.h"


struct Codecave Cave;

__declspec(naked) void CC_ExtractScore()
{
	__asm mov [ebp-0x18], 0x000C
	__asm add dword ptr[Cave.score], 0x08
	__asm mov edx, [Cave.score]
	__asm jmp Cave.back

}

void PlaceJMP(BYTE *Adress, DWORD jumpTO, DWORD length)
{
	DWORD dwOldPRotect, dwBkup, dwRelAddr;													
	VirtualProtect(Adress, length, PAGE_EXECUTE_READWRITE, &dwOldPRotect);
	dwRelAddr = (DWORD) (jumpTO - (DWORD)Adress) - 5;
	*Adress = 0xE9;
	*((DWORD *)(Adress + 0x1)) = dwRelAddr;
	for (DWORD x = 0x5; x < length; x++)
		*(Adress + x) = 0x90;
	VirtualProtect(Adress, length, dwOldPRotect, &dwBkup);
}


BOOL APIENTRY DllMain(HMODULE, DWORD ul_reason_for_call, LPVOID lpReserverd)				//Dll Main
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		PlaceJMP((BYTE*)Cave.start, (DWORD)CC_ExtractScore, 9);			
	}
	return TRUE;
}

