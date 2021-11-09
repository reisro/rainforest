#include "Math/rfVector3.h"

rfVector3::rfVector3()
{
    this->_x = 0.0f;
    this->_y = 0.0f;
    this->_z = 0.0f;
}

rfVector3::rfVector3(rfFloat x, rfFloat y, rfFloat z)
{
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

rfVector3::rfVector3(const rfVector3& _vector)
{
    *this = _vector;
}

rfVector3::~rfVector3()
{
}

rfFloat rfVector3::x() const
{
    return this->_x;
}

rfFloat rfVector3::y() const
{
    return this->_y;
}

rfFloat rfVector3::z() const
{
    return this->_z;
}

rfVector3& rfVector3::Value()
{
    return *this;
}

void rfVector3::SetXValue(rfFloat _x)
{
    this->_x = _x;
}

void rfVector3::SetYValue(rfFloat _x)
{
    this->_x = _y;
}

void rfVector3::SetZValue(rfFloat _x)
{
    this->_x = _z;
}

void rfVector3::SetValue(rfVector3* _vector)
{
    this->_x = _vector->_x;
    this->_y = _vector->_y;
    this->_z = _vector->_z;

    D3DXVECTOR3(_x, _y, _z);
}

rfVector3& rfVector3::operator=(const rfVector3& vector) const
{
    rfVector3* newVector = new rfVector3();

    newVector->_x = vector._x;
    newVector->_y = vector._y;
    newVector->_z = vector._z;

    return *newVector;
}

D3DXVECTOR3 rfVector3::toD3DVECTOR3()
{
    return D3DXVECTOR3(_x,_y, _z);
}

inline rfFloat rfVector3::Magnitude(const rfVector3& vec)
{
    return D3DXVec3LengthSq((D3DXVECTOR3*)& vec);
}

inline rfVector3* rfVector3::Up(const rfVector3& vec)
{
    return new rfVector3(.0f, 1.0f, .0f);
}

inline rfVector3* rfVector3::Right(const rfVector3& vec)
{
    return new rfVector3(1.0f, .0f, .0f);
}

inline rfVector3* rfVector3::Forward(const rfVector3& vec)
{
    return new rfVector3(.0f, .0f, 1.0f);
}

inline rfVector3* rfVector3::Normalize(rfVector3& out, rfVector3& vec)
{
    return (rfVector3 *) D3DXVec3Normalize((D3DXVECTOR3*)&out, (D3DXVECTOR3*)&vec);
}

inline float rfVector3::Dot(const rfVector3& vec, const rfVector3& vec2)
{
    return D3DXVec3Dot((D3DXVECTOR3*)& vec, (D3DXVECTOR3*)& vec2);
}

inline rfVector3* rfVector3::Cross(const rfVector3& vec, const rfVector3& vec2, const rfVector3& vec3)
{
    return (rfVector3 *) D3DXVec3Cross((D3DXVECTOR3*)&vec, (D3DXVECTOR3*)&vec2, (D3DXVECTOR3*)&vec3);
}