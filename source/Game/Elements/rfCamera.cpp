#include "Game/Elements/rfCamera.h"

rfCamera::rfCamera()
{
	Position = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Right =   new D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	Up =       new D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	LookAt =   new D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

rfCamera::rfCamera(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt)
{
	Position = (D3DXVECTOR3*)&position;
	Right = (D3DXVECTOR3*)&target;
	Up = (D3DXVECTOR3*)&up;
	LookAt = (D3DXVECTOR3*)&lookAt;
}

rfCamera::~rfCamera()
{
}

void rfCamera::Setup(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt)
{
	Position = (D3DXVECTOR3*)&position;
	Right = (D3DXVECTOR3*)&target;
	Up = (D3DXVECTOR3*)&up;
	LookAt = (D3DXVECTOR3*)&lookAt;
}

void rfCamera::SetPosition(D3DXVECTOR3 pos)
{
	Position->x = pos.x;
	Position->y = pos.y;
	Position->z = pos.z;
}

void rfCamera::SetRight(D3DXVECTOR3 right)
{
	Right->x = right.x;
	Right->y = right.y;
	Right->z = right.z;
}

void rfCamera::SetUp(D3DXVECTOR3 up)
{
	Up->x = up.x;
	Up->y = up.y;
	Up->z = up.z;
}

void rfCamera::SetLookAt(D3DXVECTOR3 lookAt)
{
	LookAt->x = lookAt.x;
	LookAt->y = lookAt.y;
	LookAt->z = lookAt.z;
}

D3DXMATRIX rfCamera::BuildViewMatrix()
{
	// Make LookAt vector unit length
	D3DXVec3Normalize(LookAt, LookAt);

	// Produce the up vector from cross product operation
	D3DXVec3Cross(Up, LookAt, Right);

	// Make LookAt vector unit length
	D3DXVec3Normalize(Up, Up);

	// Produce the right vector from cross product operation
	D3DXVec3Cross(Right, Up, LookAt);

	// Make Right vector unit length
	D3DXVec3Normalize(Right, Right);

	// Align camera translation to base normal axis vectors
	float posX = -D3DXVec3Dot(Right, Position);
	float posY = -D3DXVec3Dot(Up, Position);
	float posZ = -D3DXVec3Dot(LookAt, Position);

	// View Matrix Column 1
	View(0, 0) = Right->x; View(0, 1) = Up->x; View(0, 2) = LookAt->x; View(0, 3) = 0.0f;
	View(1, 0) = Right->y; View(1, 1) = Up->y; View(1, 2) = LookAt->y; View(1, 3) = 0.0f;
	View(2, 0) = Right->z; View(2, 1) = Up->z; View(2, 2) = LookAt->z; View(2, 3) = 0.0f;
	View(3, 0) = posX; View(3, 1) = posY; View(3, 2) = posZ; View(3, 3)           = 1.0f;

	return View;
}

void rfCamera::Move(float units)
{
	*Position += GetLookAt() * units;
}

void rfCamera::MoveUp(float units)
{
	*Position += GetUp() * units;
}

void rfCamera::RotatePitch(rfFloat angle)
{
	D3DXMATRIX P;
	D3DXMatrixRotationAxis(&P, Right, angle);

	D3DXVec3TransformCoord(Up, Up, &P);
	D3DXVec3TransformCoord(LookAt, LookAt, &P);
}

void rfCamera::RotateYaw(rfFloat angle)
{
	D3DXMATRIX Y;
	D3DXMatrixRotationY(&Y, angle);

	D3DXVec3TransformCoord(Right, Right, &Y);
	D3DXVec3TransformCoord(LookAt, LookAt, &Y);
}

void rfCamera::RotateRoll(rfFloat angle)
{
	D3DXMATRIX R;

	D3DXMatrixRotationAxis(&R, LookAt, angle);

	D3DXVec3TransformCoord(Right, Right, &R);
	D3DXVec3TransformCoord(Up, Up, &R);
}