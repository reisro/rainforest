
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

#ifndef _RF_SUBSYSTEM_H_
#define _RF_SUBSYSTEM_H_

#include "RainForest.h"

class RFGE_API rfSubsystem
{
public:

	static void CreateInstance();
};

#endif _RF_SUBSYSTEM_H_
