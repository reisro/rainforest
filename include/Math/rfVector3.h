
//---------------------------------------------------------------------------//
//                                                                           //
// File : rfVector.h														 //
//                                                                           //
// Desc : Provides graphics rendering using the DirectX 9 SDK                //
//															                 //
//---------------------------------------------------------------------------//
//     Rain Forest 2020.	Rodrigo dos Reis (reisro)			             //
//---------------------------------------------------------------------------//

#ifndef _RFVECTOR3H_
#define _RFVECTOR3H_

#include <RFGEAPI.h>
#include <rfBaseTypes.h>
#include <iostream>
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>

class rfMatrix;

class RFGE_API rfVector3
{
public:

	// constructors
	rfVector3();
	rfVector3(rfFloat x, rfFloat y, rfFloat z);
	rfVector3(const rfVector3& _vector);
	~rfVector3();

	// Getters
	rfFloat x() const;
	rfFloat y() const;
	rfFloat z() const;
	rfVector3& Value();

	// Setters
	void SetXValue(rfFloat _x);
	void SetYValue(rfFloat _x);
	void SetZValue(rfFloat _x);
	void SetValue(rfVector3* _vector);

	// Operator overloading
	rfVector3& operator=(const rfVector3& vector) const;

	// Conversion to D3DVECTOR3
	D3DXVECTOR3 toD3DVECTOR3();

	// returns the length of the vector
	static inline float Magnitude(const rfVector3& vec);

	// zero vector and basis vector values
	static inline rfVector3& Zero() { return *new rfVector3(rfFloat(.0f), rfFloat(.0f), rfFloat(.0f)); }
	static inline rfVector3* Up(const rfVector3& vec);
	static inline rfVector3* Right(const rfVector3& vec);
	static inline rfVector3* Forward(const rfVector3& vec);

	// returns the normalized vector
	static inline rfVector3* Normalize(rfVector3& out, rfVector3& vec);

	static inline rfFloat Dot(const rfVector3& vec, const rfVector3& vec2);

	static inline rfVector3* Cross(const rfVector3& vec, const rfVector3& vec2, const rfVector3& vec3);

	// converts to a Matrix
	//rfMatrix& ToMatrix(const rfVector3& _vector) const;

	rfFloat _x, _y, _z;

private:
	
};

#endif _RFVECTOR3H_