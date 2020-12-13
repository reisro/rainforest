//---------------------------------------------------------------------------//
//                                                                           //
// File : Directx9Renderer.h                                                 //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef DIRECT9_INDEX_BUFFER_SDK_H_
#define DIRECT9_INDEX_BUFFER_SDK_H_

#include "Renderer/Platform/Directx9Renderer.h"
#include "Resources/rfIndexBuffer.h"

class Directx9IndexBuffer : public rfIndexBuffer
{
public:
	Directx9IndexBuffer();
	virtual ~Directx9IndexBuffer();

	bool Create() override;

	IDirect3DIndexBuffer9* GetBuffer();

protected:
	IDirect3DIndexBuffer9* indexBuffer;
};

#endif DIRECT9_VERTEX_BUFFER_SDK_H_