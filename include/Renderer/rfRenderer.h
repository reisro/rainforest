
//---------------------------------------------------------------------------//
//                                                                           //
// File : Directx9Renderer.h                                                 //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Mange 2020.	Rodrigo dos Reis (reisro)			                     //
//---------------------------------------------------------------------------//

#pragma once

#include "RFGEAPI.h"
#include "System/Interfaces/IStartup.h"
#include "Renderer/rfRenderCommand.h"
#include "System/Platform/rfWindowSystem.h"
#include <functional>

class rfWindowSystem;
class rfPhysics;

class RFGE_API rfRenderer: public IStartup
{
public:
						rfRenderer();
	virtual				~rfRenderer();

	static void         CreateInstance();
	static bool			Init();

	// interface
	bool 				Initialized() override;

	virtual bool		Initialize();
	virtual bool		PostInit();
	virtual bool		CreateVertexBuffer();
	virtual bool		CreateIndexBuffer();
	virtual bool		beginFrame();
	virtual bool		endFrame();
	virtual void		Render();
	virtual void		SendRenderCmdList(const std::vector<rfRenderCommand>& list);
	virtual void		SetRenderWindow(rfWindowSystem* windowSystem);
	virtual void		SetRenderState();
	virtual void		Cleanup();
	virtual void		GetDevice();
	virtual void		CameraSetup();

	static rfRenderer*	GetInstance();

protected:

	static rfRenderer* Singleton;
};