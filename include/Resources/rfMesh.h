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

#ifndef RFMESH_H_
#define RFMESH_H_

#include <d3dx9.h>
#include <vector>

class rfMesh
{
public:

	D3DXMATRIX  worldPosition;

	rfMesh();
	rfMesh(IDirect3DDevice9* device);
	~rfMesh();

	ID3DXMesh* GetGeometry() const;
	std::vector<D3DMATERIAL9> GetMaterial() const;
	bool LoadMeshGeometry(LPCSTR filename);
	void SetMaterials();
	void SetRenderDevice(IDirect3DDevice9* device);
	int GetNumberMaterials() const;

private:

	IDirect3DDevice9*                   renderDevice;
	ID3DXMesh*                          geometry = 0;
	ID3DXBuffer*						adjacentBuffer = 0;
	ID3DXBuffer*						materialBuffer = 0;
	DWORD								numberMaterials = 0;
	std::vector<D3DMATERIAL9>			materials;
	std::vector<IDirect3DTexture9*>		textures;
};

#endif RFMESH_H_