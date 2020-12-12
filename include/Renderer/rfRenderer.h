
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
	virtual bool		Initialize();
	virtual bool		PostInit();
	virtual bool		beginFrame();
	virtual bool		endFrame();
	virtual void		Draw();
	virtual void		SendRenderCmdList(const std::vector<rfRenderCommand>& list);
	virtual void		SetRenderWindow(rfWindowSystem* windowSystem);
	virtual void		Cleanup();

	static rfRenderer*	GetInstance();

protected:

	static rfRenderer*	Singleton;
};