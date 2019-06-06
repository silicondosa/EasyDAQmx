# EasyDAQmx
`EasyDAQmx` is a simple wrapper for the National Instruments NI-DAQmx ANSI C API.

#### NOTE: This library is a work-in-progress and not ready for use yet.

## Introduction
National Instruments provides a powerful and fully functional C developer API
for their DAQ hardware called DAQmx. Unfortunately, there isn't a lot of easily
accessible documentation or examples to get people up and running with it.
Furthermore, the library is not beginner friendly with a large amount of
configuration necessary before users record thir first data sample.

`EasyDAQmx` tries to bridge this gap by providing a simple interface/wrapper that
makes using NI-DAQmx easier by (mostly) emulating the function calls a
programmer would make when using an Arduino while also exposing additional
features such as timing and triggering support.

## Usage
* This wrapper should work on all platforms supported by NI-DAQmx. As of
October 2018, NI-DAQmx is supported by Windows and Linux operating systems.
* Before using this library, please install the NI-DAQmx software available on
the [National Instruments website.](https://www.ni.com/dataacquisition/nidaqmx.htm/)
* You need to get a copy of the NI-DAQmx library files from the location where
* they are stored as described on the [NI website](http://www.ni.com/product-documentation/54392/en/).
* Maybe move these files to a particular directory?
* You may now use the ArduDAQmx wrapper in tandem with the NI-DAQmx library.

## EasyDAQmx Documentation
Documentation for the wrapper will be available soon.

## Legal
`EasyDAQmx` is distributed under the MIT license.

DAQmx, and NI-DAQmx are trademarks of the National Instruments Corporation.

DAQmx software including libraries are governed by the copyrights and patents
awarded to the National Instruments Corporation.

Please check the `LICENCE` file for more legal information on ArduDAQmx.

Location of additional legal information on National Instruments software:
* Notices are located in the `<National Instruments>\_Legal Information` and `<National Instruments>` directories.
* EULAs are located in the `<National Instruments>\Shared\MDF\Legal\license` directory.
* Review `<National Instruments>\_Legal Information.txt` for information on including legal information in installers built with NI products.
