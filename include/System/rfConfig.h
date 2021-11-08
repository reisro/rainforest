
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfConfig.h														 //
//                                                                           //
// Desc : Configuration settings of the engine				                 //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFCONFIG_H_
#define _RFCONFIG_H_

#include "RFGEAPI.h"

namespace EngineConfig
{
	enum class Platform
	{
		Windows,
		Mac,
		Linux
	};

	enum class GraphicsAPI
	{
		DirectX9,
		DirectX11,
		DirectX12,
		DirectX12Ultimate,
		OpenGL,
		Vulkan
	};

	enum class PhysicsAPI
	{
		PhysX_ver2_81,
		PhysX_ver3_34
	};

	enum class WindowResolution
	{
		HighDefinition,
		FullHighDefinition,
		UltraHighDefinition
	};
}

//-----------------------------------------------------------------------------
// API Support
//-----------------------------------------------------------------------------
// 
// Support DirectX 9 rendering API (render driver and resource types).
#if !defined (RFGE_DX9_RENDER_SUPPORT)
#define RFGE_DX9_RENDER_SUPPORT
#else
//#undef RFGE_DX9_RENDER_SUPPORT
#endif

struct RFGE_API rfConfig
{
public:

	// Constructor
	rfConfig() :

	#if defined(RFGE_DX9_RENDER_SUPPORT)
		graphicsAPI(EngineConfig::GraphicsAPI::DirectX9),
	#endif	
		platform(EngineConfig::Platform::Windows),
		physicsAPI(EngineConfig::PhysicsAPI::PhysX_ver2_81),
		windowResolution(EngineConfig::WindowResolution::FullHighDefinition),
		multiThreaded(false), windowed(false) {}

	static rfConfig Instance;
	
	EngineConfig::Platform			platform;
	EngineConfig::GraphicsAPI		graphicsAPI;
	EngineConfig::PhysicsAPI		physicsAPI;
	EngineConfig::WindowResolution	windowResolution;
	bool							multiThreaded;
	bool							windowed;
}; 

#endif _RFCONFIG_H_