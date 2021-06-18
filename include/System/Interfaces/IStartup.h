//---------------------------------------------------------------------------//
//                                                                           //
// File : rApplication.h                                                     //
//                                                                           //
// Desc : Provides support types, macros and other items necessary to        //
//        interoperate correctly with DLL or library exports.                //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFI_STARTUP_H_
#define _RFI_STARTUP_H_

class RFGE_API IStartup
{
public:

	virtual bool Initialized() = 0;
};

#endif _RFI_STARTUP_H_ 
