
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfMatrix.h														 //
//                                                                           //
// Desc : matrix class for math operations                                   //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#pragma once

#ifndef _RFMATRIXH_
#define _RFMATRIXH_

#include <RFGEAPI.h>
#include <rfBaseTypes.h>
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <d3d9.h>	
#include <d3dx9.h>

class rfMatrix
{

public:

	rfMatrix();

	rfMatrix(rfFloat i11, rfFloat i12, rfFloat i13, rfFloat i14,
		rfFloat i21, rfFloat i22, rfFloat i23, rfFloat i24,
		rfFloat i31, rfFloat i32, rfFloat i33, rfFloat i34,
		rfFloat i41, rfFloat i42, rfFloat i43, rfFloat i44) :
		rows(4), columns(4),
		_11(i11), _12(i12), _13(i13), _14(i14),
		_21(i21), _22(i22), _23(i23), _24(i24),
		_31(i31), _32(i32), _33(i33), _34(i34),
		_41(i41), _42(i42), _43(i43), _44(i44)
	{}

	//-------------------------------------------------------------------------
	// Public Static Methods
	//-------------------------------------------------------------------------
	inline static rfMatrix* Translation(rfMatrix& out, rfFloat x, rfFloat y, rfFloat z)
	{
		return (rfMatrix*)D3DXMatrixTranslation((D3DXMATRIX*)&out, x, y, z);
	}

	inline static rfMatrix* Multiply(rfMatrix& out, const rfMatrix& m1, const rfMatrix& m2)
	{
		return (rfMatrix*) D3DXMatrixMultiply((D3DXMATRIX*) &out, (D3DXMATRIX*) &m1, (D3DXMATRIX*) &m2);
	}

	inline static rfMatrix* Scale(rfMatrix& out, rfFloat x, rfFloat y, rfFloat z)
	{
		return (rfMatrix*)D3DXMatrixScaling((D3DXMATRIX*)&out, x, y, z);
	}

	inline static bool IsIdentity(rfMatrix& mat)
	{
		return ( D3DXMatrixIsIdentity( (D3DXMATRIX*) &mat) == TRUE);
	}

	inline static rfMatrix* Identity(rfMatrix& out)
	{
		return (rfMatrix*) D3DXMatrixIdentity((D3DXMATRIX*) &out);
	}

	inline static rfMatrix* Tranpose(rfMatrix& out, rfMatrix& mat)
	{
		return (rfMatrix*) D3DXMatrixTranspose((D3DXMATRIX*) &out, (D3DXMATRIX*) &mat);
	}

	inline static rfFloat Determinant(rfMatrix& mat)
	{
		return D3DXMatrixDeterminant((D3DXMATRIX*) &mat);
	}

	inline static rfMatrix* Inverse(rfMatrix& out, const rfMatrix& mat)
	{
		return (rfMatrix*) D3DXMatrixInverse((D3DXMATRIX*)&out, NULL, (D3DXMATRIX*)&mat);
	}

	inline static rfMatrix* Inverse(rfMatrix& out, rfFloat& determinant, const rfMatrix& mat)
	{
		return (rfMatrix*) D3DXMatrixInverse((D3DXMATRIX*)&out, &determinant, (D3DXMATRIX*)&mat);
	}

    //-------------------------------------------------------------------------
   // Public Members
   //-------------------------------------------------------------------------
	union
	{
		struct
		{
			rfFloat _11, _12, _13, _14;
			rfFloat _21, _22, _23, _24;
			rfFloat _31, _32, _33, _34;
			rfFloat _41, _42, _43, _44;
		};
		float m[4][4];
	};

private:

	int rows;
	int columns;
};

#endif _RFMATRIXH_