#pragma once

#ifndef _RENDERCOMMANDS_H
#define _RENDERCOMMANDS_H

#include "RFGEAPI.h"

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
		Lit,
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

	static void Execute();

private:
	CommandType renderCmdType;
};

#endif _RENDERCOMMANDS_H
