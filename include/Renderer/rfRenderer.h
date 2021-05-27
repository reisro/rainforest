
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
#include "Renderer/rfRenderCommand.h"
#include "System/Platform/rfWindowSystem.h"

class RFGE_API rfRenderer
{
public:
						rfRenderer() {};
	virtual				~rfRenderer() {};

	static void			CreateInstance();
	static void			GetDevice();
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

	virtual void		CameraSetup();
	static rfRenderer*	GetInstance();

protected:

	static rfRenderer*	Singleton;
};