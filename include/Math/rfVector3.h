
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

#include <iostream>
#include <math.h>
#include <d3d9.h>
#include <d3dx9.h>

class rfMatrix;

class rfVector3
{
public:

	// constructors
	rfVector3();
	rfVector3(double x, double y, double z);
	rfVector3(const rfVector3& _vector);
	~rfVector3();

	// Getters
	double xValue() const;
	double yValue() const;
	double zValue() const;
	rfVector3& Value();

	// Setters
	void SetXValue(double _x);
	void SetYValue(double _x);
	void SetZValue(double _x);
	void SetValue(rfVector3* _vector);

	// Operator overloading
	rfVector3& operator=(const rfVector3& vector) const;

	// returns the length of the vector
	static inline float Magnitude(const rfVector3& vec);

	static inline rfVector3* Up(const rfVector3& vec);
	static inline rfVector3* Right(const rfVector3& vec);
	static inline rfVector3* Forward(const rfVector3& vec);

	// returns the normalized vector
	static inline rfVector3* Normalize(rfVector3& out, rfVector3& vec);

	static inline float Dot(const rfVector3& vec, const rfVector3& vec2);

	static inline rfVector3* Cross(const rfVector3& vec, const rfVector3& vec2, const rfVector3& vec3);

	// converts to a Matrix
	//rfMatrix& ToMatrix(const rfVector3& _vector) const;

private:
	double _x, _y, _z;
};

#endif _RFVECTOR3H_