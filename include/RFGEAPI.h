//---------------------------------------------------------------------------//
//                                                                           //
// File : RFGEAPI.h                                                          //
//                                                                           //
// Desc : Provides support types, macros and other items necessary to        //
//        interoperate correctly with DLL or library exports.                //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFGE_API_H_
#define _RFGE_API_H_

// Rain Forest Header includes
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <list>
#include <stack>
#include <map>
#include <set>

// PhysicX define to suppress windows global min.max macros

#define NOMINMAX
#include <Windows.h>

//-----------------------------------------------------------------------------
// Utilities Macros
//-----------------------------------------------------------------------------
#define _RFGE_STRING(String)
#define RFGE_LOG(x) DebugLog(x)

#ifndef _RFGE_SAFE_DELETE
#define _RFGE_SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif

#ifndef _RFGE_SAFE_DELETE_ARRAY
#define _RFGE_SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif 

#ifndef _RFGE_SAFE_RELEASE
#define _RFGE_SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

//-----------------------------------------------------------------------------
// Global Defines & Macros
//-----------------------------------------------------------------------------
// Macros to provide automatic integration with DLL interface where applicable.
// DLL Compilation
#if defined RFGE_API_EXPORTS
#define RFGE_API __declspec(dllexport)
#elif (RFGE_API_IMPORTS)
#define RFGE_API __declspec(dllimport)
#else
#define RFGE_API
#endif

//-----------------------------------------------------------------------------
// Utilities Functions
//-----------------------------------------------------------------------------
static void DebugLog(std::string msg)
{
	std::cout << msg << std::endl;
}

//-----------------------------------------------------------------------------
// List Typedefs
//-----------------------------------------------------------------------------
// Stack Declaration
#define RFGE_STACK_DECLARE(renderCmd, type, typeDefName) typedef std::stack< std::pair<renderCmd,type> > typeDefName;

#endif _RFGE_API_H_