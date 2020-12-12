
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

#ifndef _RFVERTEXBUFFER_H
#define _RFVERTEXBUFFER_H

#include <d3d9.h>
#include <d3dx9.h>
#include "RFGEAPI.h"
#include "Renderer/rfRenderer.h"

class RFGE_API rfVertexBuffer
{
public:
	rfVertexBuffer();
	virtual ~rfVertexBuffer();

	//-------------------------------------------------------------------------
	// Public Virtual Methods
	//-------------------------------------------------------------------------
	virtual bool Create();
	virtual void AccessMemory();
	virtual bool Release();

	virtual void Lock();
	virtual void Unlock();

private:
	UINT Length;
};

#endif _RFVERTEXBUFFER_H