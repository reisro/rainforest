//---------------------------------------------------------------------------//
//                                                                           //
// File : rfQuaternion.h													 //
//                                                                           //
// Desc : Handle operations regarding orientation                            //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2021.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFQUATERNION_H_
#define _RFQUATERNION_H_

//-----------------------------------------------------------------------------
// rfQuaternion Header Includes
//-----------------------------------------------------------------------------
#include <rfBaseTypes.h>
#include <iostream>
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>
#include <d3dx9.h>
#undef WIN32_LEAN_AND_MEAN

//-----------------------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------------------
class rfVector3;
class rfMatrix;

//-----------------------------------------------------------------------------
// Main class declarations
//-----------------------------------------------------------------------------
class rfQuaternion
{
public:

	rfQuaternion();
	rfQuaternion(rfFloat _x, rfFloat _y, rfFloat _z, rfFloat _w);
	~rfQuaternion();

	rfQuaternion* Conjugate();

	//-------------------------------------------------------------------------
	// Public Methods
	//-------------------------------------------------------------------------
	inline static rfQuaternion* RotationYawPitchRoll(rfQuaternion& out, rfFloat yaw, rfFloat pitch, rfFloat roll)
	{
		return (rfQuaternion*)D3DXQuaternionRotationYawPitchRoll((D3DXQUATERNION*)&out, yaw, pitch, roll);
	}

	//-------------------------------------------------------------------------
	// Public Members
	//-------------------------------------------------------------------------
	rfFloat x, y, z, w;
};

#endif _RFQUATERNION_H_