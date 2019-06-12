#include <stdio.h>
#include <ansi_c.h>
#include <stdafx.h>
#include <targetver.h>
#include <msunistd.h>
#include <macrodef.h>
#include <EasyDAQmx.h>
#include <string.h>
#include <NIDAQmx.h>

int main()
{
	int				buffersize = 0; // Buffer size datatypes
	int				devicetype_buffersize = 0; //devicesernum_buffersize;
	int				tempDAQmxEnumeratedDevCount = 0; // temp DAQmx dev count that is used to crosscheck

	//Device Info variable initialization
	char* DAQmxDevNameList = NULL; // primary device name string
	char* remainder_DAQmxDevNameList = NULL; // remainder device name string
	char* DAQmxDeviceType = NULL; // device type string
	char* DAQmxDevName = NULL;
	DAQmxDevice* newDevice = NULL;

	int				deviceSerial;
	int				isSimulated;
	unsigned long	devNUM = 0;
	int				isObjInserted = 0, DEVenumERR = 0;
	cListElem* list_elem = NULL;

	// obtain device names from NI-DAQmx
	buffersize = DAQmxGetSystemInfoAttribute(DAQmx_Sys_DevNames, (void*)DAQmxDevNameList);
	DAQmxDevNameList = (char*)malloc(buffersize); // DYN-M: dynamically allocate devicenames. Cleared at the end of this function.
	remainder_DAQmxDevNameList = DAQmxDevNameList;

	//Get the string of devicenames from NI-DAQmx
	DAQmxGetSystemInfoAttribute(DAQmx_Sys_DevNames, DAQmxDevNameList, buffersize);

	fprintf(LOGSTREAM, "Full Device name list: %s\n\n", DAQmxDevNameList);
	fprintf(LOGSTREAM, "*** LIST OF DEVICES ON THIS COMPUTER ******************************************************************\n");
	fprintf(LOGSTREAM, "| Dev# || Dev Type || Dev Serial# || Sim? || AI Ch# || AO Ch# || DI Ch# || DO Ch# || CI Ch# || CO Ch# |\n");
	fprintf(LOGSTREAM, "*******************************************************************************************************\n");

	for (DAQmxDevName = strtok_s(remainder_DAQmxDevNameList, ",", &remainder_DAQmxDevNameList); DAQmxDevName != NULL && DEVenumERR == 0; DAQmxDevName = strtok_s(remainder_DAQmxDevNameList, ", ", &remainder_DAQmxDevNameList), tempDAQmxEnumeratedDevCount++) {
		// Obtain some device properties
		devicetype_buffersize = DAQmxGetDeviceAttribute(DAQmxDevName, DAQmx_Dev_ProductType, NULL); //Get Product Type for a DAQmx device pointed to by devToken
		DAQmxDeviceType = (char*)malloc(devicetype_buffersize); // DYN-M: dynamically allocate memory for devicetype. Memory is cleared later in this function.
		DAQmxGetDeviceAttribute(DAQmxDevName, DAQmx_Dev_ProductType, DAQmxDeviceType, devicetype_buffersize); //Get device type		
		DAQmxGetDeviceAttribute(DAQmxDevName, DAQmx_Dev_SerialNum, &deviceSerial, 1); //Get Product Serial Number for the device
		DAQmxGetDeviceAttribute(DAQmxDevName, DAQmx_Dev_IsSimulated, &isSimulated, 1); //Get "Is device simulated?" flag for the device

		newDevice = (DAQmxDevice*)malloc(sizeof(DAQmxDevice)); // DYN-M: dynamically allocate newDevice for DAQmx device. Freed recursively in ArduDAQmxClearEnumeratedDevices().

		fprintf(LOGSTREAM, "| %4d || %s || %11d ||", devNUM, DAQmxDeviceType, deviceSerial);
		if (isSimulated = 0)	fprintf(LOGSTREAM, "   NO ||");
		else					fprintf(LOGSTREAM, "  YES ||");
		fprintf(LOGSTREAM, " %6d || %6d || %6d || %6d || %6d || %6d |\n", newDevice->numAIch, newDevice->numAOch, newDevice->numDIch, newDevice->numDOch, newDevice->numCIch, newDevice->numCOch);

	return 1;
}