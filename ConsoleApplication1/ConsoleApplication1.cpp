// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_0E6F&PID_0213\06062CE6\Device Parameters

#include <windows.h>
#include <winusb.h>
#include <iostream>
#include <corecrt_malloc.h>

void printLastError(const char* source) {
	
	ULONG lastError = GetLastError();
	if (lastError) {
		printf("%s - Errors?: %d\n", source, lastError);
	}
	switch (GetLastError()) {
	case ERROR_INVALID_HANDLE:
		printf("invalid handle");
		break;
	case ERROR_BAD_DEVICE:
		printf("bad device");
		break;
	case ERROR_NOT_ENOUGH_MEMORY:
		printf("memory");
		break;
	case ERROR_INVALID_PARAMETER:
		printf("invalid parameter");
		break;
	default:
		printf("something else");
	}
	printf("\n");
}

int main()
{
	//Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_0E6F&PID_0213\06062CE6\Device Parameters
	const char* symbolicName = "//?/USB#VID_046D&PID_C077#6&289c360f&0&3#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	void* fileHandle = CreateFileA(symbolicName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);

	printLastError("test");
	void* interfaceHandle;
	bool initialized = WinUsb_Initialize(fileHandle, &interfaceHandle);
	if (!initialized) {
		printLastError("WinUsb_Initialize");
	}
	USB_INTERFACE_DESCRIPTOR interfaceDescriptor;
	WinUsb_QueryInterfaceSettings(interfaceHandle, 0, &interfaceDescriptor);

	unsigned char* buffer = (UCHAR*)malloc(5);
	unsigned long transferredLength;
	for (int i = 0; i < 10000; i++) {
		WinUsb_ReadPipe(interfaceHandle, 0x81, buffer, 4, &transferredLength, 0);
		printLastError("ReadPipe");
		printf("value: %x", *(ULONG*)buffer);
	}

	WinUsb_Free(interfaceHandle);
	std::cout << "Hello World!\n";

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
