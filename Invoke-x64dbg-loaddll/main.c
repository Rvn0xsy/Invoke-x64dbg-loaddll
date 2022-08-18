#include <Windows.h>
#include <stdio.h>
#include <sddl.h>

WCHAR dllPath[1024] = L"C:\\Windows\\Temp\\Test\\DllMain.dll";
WCHAR loaderPath[] = L"C:\\Windows\\Temp\\Test\\loaddll.exe";

HANDLE CreateMapFile() {
	HANDLE hFile = NULL;
	hFile = CreateFile(L"C:\\Windows\\Temp\\Test\\2.log", FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		NULL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}
	WriteFile(hFile, dllPath, sizeof(dllPath), NULL, NULL);
	return hFile;
}

int __stdcall WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {
	wchar_t szName[256];
	DWORD dwFileSize = 0;

	HANDLE hFile = NULL;
	HANDLE hFileMap = NULL;
	SECURITY_ATTRIBUTES attributes;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&attributes, sizeof(attributes));
	attributes.nLength = sizeof(attributes);

	ConvertStringSecurityDescriptorToSecurityDescriptorA(
		"D:P(A;OICI;GA;;;SY)(A;OICI;GA;;;BA)(A;OICI;GWGR;;;IU)",
		SDDL_REVISION_1,
		&attributes.lpSecurityDescriptor,
		NULL);

	hFile = CreateMapFile();
	if (hFile == NULL) {
		return 0;
	}


	BOOL bStatus = CreateProcessW(loaderPath, NULL, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	if (bStatus == NULL) {
		/*wprintf(L"[-] CreateProcess Error %d \n", GetLastError());*/
		return 0;
	}

	ZeroMemory(szName, sizeof(szName));

	wsprintfW(szName, L"Local\\szLibraryName%X", (unsigned int)pi.dwProcessId);


	hFileMap = CreateFileMappingW(hFile, &attributes, PAGE_READWRITE, 0, 1024, szName);


	ResumeThread(pi.hThread);

	Sleep(3000);
	return 0;
}