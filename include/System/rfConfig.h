
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
}

class RFGE_API rfConfig
{
public:
	rfConfig();
	virtual ~rfConfig();

	EngineConfig::Platform	  platform;
	EngineConfig::GraphicsAPI graphicsAPI;
};

#endif _RFCONFIG_H_