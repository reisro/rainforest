
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfVertex.h                                                         //
//                                                                           //
// Desc : Provides functionality of window creation.                         //
//                                                                           //
//---------------------------------------------------------------------------//
//     Rain Forest Game Engine.	Rodrigo dos Reis (reisro)			         //
//---------------------------------------------------------------------------//

#ifndef RFVERTEX_H_
#define RFVERTEX_H_

#include "RFGEAPI.h"
#include <d3d9.h>

namespace rfVertex
{
	struct Vertex
	{
        Vertex() { _x = 0.0f; _y = 0.0f; _z = 0.0f; color = D3DCOLOR_XRGB(0, 0, 0); }
        Vertex(float x, float y, float z, D3DCOLOR _color)
        {
            _x = x; _y = y; _z = z; color = _color;
        }
        float _x, _y, _z;
        D3DCOLOR color;
        static const DWORD FVF = D3DFVF_XYZ;
	};

	struct VertexColor
	{
		VertexColor() { _x = 0.0f; _y = 0.0f; _z = 0.0f; color = D3DCOLOR_XRGB(0, 0, 0); }
		VertexColor(float x, float y, float z, D3DCOLOR _color)
		{
			_x = x; _y = y; _z = z; color = _color;
		}
		float _x, _y, _z;
		D3DCOLOR color;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};

	struct VertexNormal
	{
		VertexNormal() { _x = 0.0f; _y = 0.0f; _z = 0.0f; _nx = .0f; _ny = .0f; _nz = .0f; }
		VertexNormal(float x, float y, float z, float nx, float ny, float nz)
		{
			_x = x; _y = y; _z = z; _nx = nx; _ny = ny; _nz = nz;
		}
		float _x, _y, _z;
		float _nx, _ny, _nz;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
	};

	struct VertexCoordinates
	{
		VertexCoordinates() { _x = 0.0f; _y = 0.0f; _z = 0.0f; _nx = .0f; _ny = .0f; _nz = .0f; _u = .0f; _v = .0f; }
		VertexCoordinates(float x, float y, float z, float nx, float ny, float nz, float u, float v)
		{
			_x = x; _y = y; _z = z; _nx = nx; _ny = ny; _nz = nz, _u = u, _v = v;
		}
		float _x, _y, _z;
		float _nx, _ny, _nz;
		float _u, _v;
		static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
	};
}

#endif RFVERTEX_H_