
#include "Resources/rfMesh.h"

rfMesh::rfMesh(IDirect3DDevice9* device)
{
	renderDevice = device;
}

rfMesh::~rfMesh()
{

}

ID3DXMesh* rfMesh::GetGeometry() const
{
	return geometry;
}

bool rfMesh::LoadMeshGeometry(LPCWSTR filename)
{
	HRESULT hr;

	hr = D3DXLoadMeshFromX(
		filename,
		D3DXMESH_MANAGED,
		renderDevice,
		&adjacentBuffer,
		&materialBuffer,
		0,
		&numberMaterials,
		&geometry);

	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXLoadMeshFromX() - FAILED", 0, 0);
		return false;
	}

	if (materialBuffer != 0 && numberMaterials != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();

		for (int i = 0; i < numberMaterials; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			materials.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* texture = 0;

				D3DXCreateTextureFromFile(
					renderDevice,
					(LPCWSTR) mtrls[i].pTextureFilename,
					&texture);

				textures.push_back(texture);
			}
			else
			{
				textures.push_back(0);
			}
		}
	}

	return true;
}

int rfMesh::GetNumberMaterials() const
{
	return 0;
}
