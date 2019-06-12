/*!
 * \file EasyDAQmx.c
 * \brief EasyDAQmx: An easy-to-use wrapper for the National Instruments NI-DAQmx C/C++ API
 * \author Suraj Chakravarthi Raja
 */

//#include "stdafx.h"
#include <stdio.h>
#include <EasyDAQmx.h>
#include <ansi_c.h>
#include <macrodef.h>
#include <NIDAQmx.h>
#include <string.h>

//-----------------------------
// EasyDAQmx Glabal Definitions
//-----------------------------
char						*DAQmxDevPrefix = DAQMX_DEF_DEV_PREFIX;

unsigned int				EasyDAQmxFirstEnumerate = 1;
long						DAQmxErrorCode = 0;


//-------------------------------
// EasyDAQmx Function Definitions
//-------------------------------

// Library support function definitions
inline char* dev2string(char* strBuf, unsigned int devNum)
{
	snprintf(strBuf, 1 + DAQMX_MAX_DEV_STR_LEN, "%s%d", DAQmxDevPrefix, devNum);
	return strBuf;
}

char* pin2string(char* strbuf, unsigned int devNum, IOmode ioMode, unsigned int pinNum)
{
	char pinType[DAQMX_MAX_PIN_STR_LEN];
	switch (ioMode)
	{
	case ANALOG_IN:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "ai");
		break;
	case ANALOG_OUT:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "ao");
		break;
	case DIGITAL_IN:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "port");
		break;
	case DIGITAL_OUT:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "port");
		break;
	case CTR_ANGLE_IN:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "ctr");
		break;
	case CTR_TICK_OUT:
		snprintf(pinType, DAQMX_MAX_PIN_STR_LEN, "ctr");
		break;
	default:
		fprintf(ERRSTREAM, "ArduDAQmx library: FATAL: Invalid I/O type requested.\n");
		break;
	}
	snprintf(strbuf, DAQMX_MAX_STR_LEN, "%s%d/%s%d", DAQmxDevPrefix, devNum, pinType, pinNum);
	return strbuf;
}

/*!
 * \fn int32 DAQmxErrChk(int32 NIerrCode)
 * Checks if passed value represents a valid NI-DAQmx error. If DAQmx error is detected it sets 'NIDAQmxErrorCode.'
 * Then, it shuts down all NI-DAQmx tasks and terminates ArduDAQmx library immediately.
 *
 * \param NIerrCode the INT32 error code from NI-DAQmx is passed here.
 * \return Returns the NI-DAQmx error code as an INT32 value.
 */
inline int32 DAQmxErrChk(int32 NIerrCode)
{
	if (NIerrCode < 0) {
		char DAQmxErrChkStr[2048];
		DAQmxGetExtendedErrorInfo(DAQmxErrChkStr, 2048);
		DAQmxErrorCode = NIerrCode;
	}
	return NIerrCode;
}