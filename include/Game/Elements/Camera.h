//---------------------------------------------------------------------------//
//                                                                           //
// File : rfCamera.h                                                         //
//                                                                           //
// Desc : Provides camera functinality to render engine scenes               //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2021.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef RFGE_CAMERA_H_
#define RFGE_CAMERA_H

#include <d3d9.h>
#include <d3dx9.h>
#include "RFGEAPI.h"
#include "rfBaseTypes.h"
#include "Math/rfVector3.h"
#include "Math/rfMatrix.h"

class Camera
{
public:

	Camera();
	Camera(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt);
	~Camera();

	void Setup(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt);

	D3DXVECTOR3* GetPosition() const { return Position; }
	D3DXVECTOR3* GetTarget() const { return Target; }
	D3DXVECTOR3* GetUp() const { return Up; }
	D3DXVECTOR3* GetLookAt() const { return LookAt; }
	D3DXMATRIX GetView() const { return View; }
	D3DXMATRIX GetProjectionMatrix() const { return Projection; }

private:

	D3DXVECTOR3* Position;
	D3DXVECTOR3* Target;
	D3DXVECTOR3* Up;
	D3DXVECTOR3* LookAt;
	D3DXMATRIX   View;
	D3DXMATRIX   Projection;

};

#endif RFGE_CAMERA_H