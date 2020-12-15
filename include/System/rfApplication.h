
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

#ifndef _RF_APPLICATION_H_
#define _RF_APPLICATION_H_

#include "System/rfApplicationWindow.h"
#include "System/Platform/rfWindowSystem.h"
#include "System/Platform/Windows/rfWindowSystemWin32.h"
#include "Renderer/rfRenderer.h"
#include "Renderer/Platform/Directx9Renderer.h"
#include "Resources/rfVertexBuffer.h"
#include "Resources/rfIndexBuffer.h"
#include "Resources/Platform/Directx9VertexBuffer.h"
#include "Resources/Platform/Directx9IndexBuffer.h"
#include "System/rfConfig.h"

using namespace EngineConfig;

class RFGE_API rfApplication
{
public:
	rfApplication();
	virtual ~rfApplication();

	static void					Setup(const rfConfig& config);
	static bool					Init();
	static bool					InitWindow();
	static bool					InitRenderer();
	static void					Run();
	static void					Stop();
	static void					ShutDown();
	static rfConfig&			GetEngineConfig();
};

#endif _RF_APPLICATION_H_