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

#ifndef DIRECT9_VERTEX_BUFFER_SDK_H_
#define DIRECT9_VERTEX_BUFFER_SDK_H_

#include "Renderer/Platform/Directx9Renderer.h"
#include "Resources/rfVertexBuffer.h"

class Directx9VertexBuffer: public rfVertexBuffer
{
public:
	Directx9VertexBuffer();
	virtual ~Directx9VertexBuffer();

	bool Create() override;
	void AccessMemory() override;
	void Lock() override;

	IDirect3DVertexBuffer9* GetBuffer();

protected:
	IDirect3DVertexBuffer9* vertexBuffer;
};

#endif DIRECT9_VERTEX_BUFFER_SDK_H_