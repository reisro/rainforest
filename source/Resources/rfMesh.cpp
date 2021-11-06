
#include "Resources/rfMesh.h"

rfMesh::rfMesh()
{
	renderDevice = nullptr;
}

rfMesh::rfMesh(IDirect3DDevice9* device)
{
	renderDevice = device;
	materialBuffer = 0;
}

rfMesh::~rfMesh()
{
}

ID3DXMesh* rfMesh::GetGeometry() const
{
	return geometry;
}

std::vector<D3DMATERIAL9> rfMesh::GetMaterial() const
{
	return materials;
}

bool rfMesh::LoadMeshGeometry(LPCSTR filename)
{
	HRESULT hr;

	hr = D3DXLoadMeshFromXA(
		filename,
		D3DXMESH_MANAGED,
		renderDevice,
		&adjacentBuffer,
		&materialBuffer,
		0,
		&numberMaterials,
		&geometry);

		D3DXMatrixTranslation(&this->worldPosition, .0f, .0f, .0f);

		if (materialBuffer != 0 && numberMaterials != 0)
		{
			D3DXMATERIAL* mtrls = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

			for (int i = 0; i < numberMaterials; i++)
			{
				mtrls[i].MatD3D.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				materials.push_back(mtrls[i].MatD3D);

				if (mtrls[i].pTextureFilename != 0)
				{
					IDirect3DTexture9* texture = 0;

					D3DXCreateTextureFromFileA(
						renderDevice,
						mtrls[i].pTextureFilename,
						&texture);

					textures.push_back(texture);
				}
				else
				{
					textures.push_back(0);
				}
			}
		}

	if (FAILED(hr))
	{
		::MessageBoxA(0, "D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}

	return true;
}

void rfMesh::SetMaterials()
{
}

void rfMesh::SetRenderDevice(IDirect3DDevice9* device)
{
	renderDevice = device;
}

int rfMesh::GetNumberMaterials() const
{
	return materials.size();
}
