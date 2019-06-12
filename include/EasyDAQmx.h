#pragma once
#ifndef EASYDAQMX_H
#define EASYDAQMX_H

#include <ansi_c.h>
#include <NIDAQmx.h>
#include <macrodef.h>
#include <msunistd.h>
#include <stdafx.h>
#include <targetver.h>

//-----------------------------
// EasyDAQmx Macro Declarations
//-----------------------------

// Macros defined to handle any errors that may be thrown
#define EasyDAQmxErrChk(functionCall) if( functionCall < 0) goto EasyDAQmxErr; else
#define NIDAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else

//NI-DAQmx max string size
#define DAQMX_MAX_STR_LEN			255

//DAQmx device constants
#define DAQMX_MAX_DEV_CNT			14
#define DAQMX_MAX_DEV_PREFIX_LEN	14
#define DAQMX_DEF_DEV_PREFIX		"PXI1Slot"
#define DAQMX_MAX_DEV_STR_LEN		DAQMX_MAX_DEV_PREFIX_LEN + 2

//DAQmx pin constants
#define DAQMX_MAX_PIN_CNT			32
#define DAQMX_MAX_PIN_STR_LEN		16

//-----------------------
// EasyDAQmx TypeDef List
//-----------------------

/*!
* Enumerates the list of possible status modes of the ArduDAQmx library as set in 'EasyDAQmxStatus'.
*/
typedef enum _EasyDAQmxStatusMode {
	/*! Indicates that EasyDAQmx library has been initialized.*/
	STATUS_INIT = -2,
	/*! EasyDAQmx configuration may be altered only in the preconfigure state.*/
	STATUS_PRECONFIG = -1,
	/*! States that the EasyDAQmx library has been configured. NI-DAQmx may now be setup.*/
	STATUS_CONFIG = 0,
	/*! The NI-DAQmx synchronization, clocks and triggers are setup and is ready to run.*/
	STATUS_READY = 1,
	/*!	The library is in operation and running. Data is being collected using it now.*/
	STATUS_RUN = 2
}EasyDAQmxStatusMode;

/*!
 * Enumerates the list of error codes of the EasyDAQmx library as set in 'EasyDAQmxErrorCode'.
 */
typedef enum _EasyDAQmxErrorCode {
	/*! Library is not ready to run. Configure library, sample clock and pin mode first!*/
	ERROR_NOTREADY = -7,
	/*! A feature or functionality that is unsupported by EasyDAQmx requested.*/
	ERROR_UNSUPPORTED = -6,
	/*!	An invalid or unsupported I/O type has been selected.*/
	ERROR_INVIO = -5,
	/*! NI-DAQmx has generated an error. Need to check 'NIDAQmxErrorCode' for details.*/
	ERROR_NIDAQMX = -4,
	/*! List of NI-DAQmx devices detected by EasyDAQmx library has changed.*/
	ERROR_DEVCHANGE = -3,
	/*! No NI-DAQmx devices detected by EasyDAQmx library.*/
	ERROR_NODEVICES = -2,
	/*! Pin and task configuratoin may be altered only in the preconfigure state.*/
	ERROR_NOTCONFIG = -1,
	/*! No error has occured.*/
	ERROR_NONE = 0,
}EasyDAQmxErrorCode;


/*!
 * Defines the types of I/O modes suported by this library.
 */
typedef enum _IOmode {
	// Invalid I/O mode
		/*! Pin I/O mode: INVALID IO mode*/
	INVALID_IO = 32767,

	// pin I/O modes
		/*! Pin I/O mode: ANALOG IN*/
		ANALOG_IN = 0,
		/*! Pin I/O mode: DIGITAL IN*/
		DIGITAL_IN = 1,
		/*! Pin I/O mode: ANALOG OUT*/
		ANALOG_OUT = 2,
		/*! Pin I/O mode: DIGITAL OUT*/
		DIGITAL_OUT = 3,

		// counter I/O modes
			/*! Counter I/O mode: COUNTER IN - reads angular position*/
			CTR_ANGLE_IN = 4,
			/*! Counter I/O mode: COUNTER OUT - writes ticks*/
			CTR_TICK_OUT = 5
}IOmode;

/*!
 * Possible I/O directions - Input and Output, defined for easy programming.
 */
typedef enum _IO_Direction {
	INPUT = 0,
	OUTPUT = 1,
	INOUT = 2
}IO_Direction;

/*!
 * Some default values for NI-DAQmx.
 */
/*
typedef struct _NIdefaults {
	float64 AImin = -10;
	float64 AImax = 10;
	int32	NItermConf = DAQmx_Val_RSE;

	float64 AOmin = -10;
	float64 AOmax = 10;
	int32	NIanlgUnits = DAQmx_Val_Volts;

	int32	NIdigiGrp = DAQmx_Val_ChanForAllLines;

	int32	NIctrMode = DAQmx_Val_X4;
	bool32  ZEN = 0;
	float64 Zval = 0.0;
	int32	Zphase = DAQmx_Val_AHighBHigh;
	int32	NIctrunits = DAQmx_Val_Degrees;
	float64 angleInit = 0.0;

	uInt32	encoderPPR = 2048; // For CUI AMT103 encoder

	int32	plsIdleSt = DAQmx_Val_Low;
	int32	plsInitDel = 0;
	int32	plsLoTick = 1;
	int32	plsHiTick = 1;

	float64 IOtimeout = 10.0;

}NIdefaults;
*/

//------------------------------
// EasyDAQmx Glabal Declarations
//------------------------------
extern char						*DAQmxDevPrefix;

extern unsigned int				EasyDAQmxFirstEnumerate;
extern long						DAQmxErrorCode;

//--------------------------------
// EasyDAQmx Function Declarations
//--------------------------------
inline char* dev2string(char* strBuf, unsigned int devNum);
char* pin2string(char* strbuf, unsigned int devNum, IOmode ioMode, unsigned int pinNum);


#endif // !EASYDAQMX_H

