// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_0E6F&PID_0213\06062CE6\Device Parameters

#include <windows.h>
#include <winusb.h>
#include <iostream>
#include <corecrt_malloc.h>

void printLastError(const char* source) {

	const char* message = "None";

	ULONG lastError = GetLastError();
	if (lastError) {
		switch (GetLastError()) {
		case ERROR_INVALID_HANDLE:
			message = "invalid handle";
			break;
		case ERROR_BAD_DEVICE:
			message = "bad device";
			break;
		case ERROR_NOT_ENOUGH_MEMORY:
			message = "memory";
			break;
		case ERROR_INVALID_PARAMETER:
			message = "invalid parameter";
			break;
		default:
			message = "something else";
		}
		printf("\n");
		printf("Source: %s, Errors: %d, Message: %s\n", source, lastError, message);
	}
}

int main()
{
	//Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Enum\USB\VID_0E6F&PID_0213\06062CE6\Device Parameters
	const char* symbolicName = "//?/USB#VID_046D&PID_C077#6&289c360f&0&3#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	const char* symbolicName2 = "{88bae032-5a81-49f0-bc3d-a4ff138216d6}";
	const char* testName = "//?/USB#VID_046D&PID_C077#6&289c360f&0&4#{29823b7d-3f09-463f-ab5d-17dcf635a1da}";
	const char* myDevice = "//?/USB#VID_2E8A&PID_1100#My_Special_Device#{b321087d-3c7f-4ec2-bcc9-fa164a1e63f9}";
	const char* myDevice2 = "//?/USB#VID_2E8A&PID_1100#My_Special_Device#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	const char* myDevice3 = "//?/globalroot/Device/USBPDO-14";

	const char* thing1 = "//?/USB#VID_2E8A&PID_1100#My_Special_Device#{a5dcbf10-6530-11d2-901f-00c04fb951ed}";
	const char* thing2 = "//?/USB#VID_2E8A&PID_1100#My_Special_Device#{b321087d-3c7f-4ec2-bcc9-fa164a1e63f9}";
	const char* thing3 = "//?/USB#VID_2E8A&PID_1100#My_Special_Device#{dee824ef-729b-4a0e-9c14-b7117d33a817}";
	void* fileHandle = CreateFileA(thing3, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	printLastError("CreateFileA");

	void* interfaceHandle;
	bool initialized = WinUsb_Initialize(fileHandle, &interfaceHandle);
	if (!initialized) {
		printLastError("WinUsb_Initialize");
	}

	USB_INTERFACE_DESCRIPTOR interfaceDescriptor;
	WinUsb_QueryInterfaceSettings(interfaceHandle, 0, &interfaceDescriptor);

	WinUsb_ResetPipe(interfaceHandle, 0x81);
	printLastError("reset Pipe");

	unsigned char* buffer = (UCHAR*)malloc(5);
	unsigned long transferredLength;
	for (int i = 0; i < 10; i++) {
		WinUsb_ReadPipe(interfaceHandle, 0x81, buffer, 64, &transferredLength, 0);
		printLastError("ReadPipe");
		if (transferredLength == 0) {
			printf("empty read");
		}
		else {
			printf("value: %x", *(ULONG*)buffer);
		}
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
