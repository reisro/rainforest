#pragma once

#ifndef _RENDERCOMMANDS_H
#define _RENDERCOMMANDS_H

#include "RFGEAPI.h"
#include <d3d9.h>

class RFGE_API rfRenderCommand
{
	friend class rfRenderer;

public:

	enum class CommandType
	{
		ClearColor,
		DrawPrimitive,
		DrawIndexedPrimitive,
		DrawTexturedPrimitive,
		Draw3DText,
		CreateVertexBuffer,
		CreateIndexBuffer,
		CreateMaterial,
		CreateLight,
		CreateTexture,
		CreateTextureFromFile,
		Wireframe,
		DefaultLit,
		Unlit,
		EnableLight
	};

	enum class PrimitiveType
	{
		Cube,
		Sphere,
		Torus,
		Teapot
	};


	rfRenderCommand();
	rfRenderCommand(CommandType type);

	static void SetRenderState();
	static void Execute();

private:
	CommandType renderCmdType;
	IDirect3DDevice9* device;
};

#endif _RENDERCOMMANDS_H
