#pragma once

#ifndef _RENDERCOMMANDS_H
#define _RENDERCOMMANDS_H

#include "RFGEAPI.h"
#include "Renderer/Platform/Directx9Renderer.h"

class RFGE_API rfRenderCommand
{
	friend class Directx9Renderer;

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

public:
	rfRenderCommand();
	rfRenderCommand(CommandType type);

	static void SetRenderState(rfgeDX9RenderState state);
	static void Execute();

private:
	CommandType renderCmdType;
	IDirect3DDevice9* device;
};

#endif _RENDERCOMMANDS_H
