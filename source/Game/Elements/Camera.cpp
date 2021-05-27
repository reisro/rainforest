#include "Game/Elements/Camera.h"

Camera::Camera()
{
	Position = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Target = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Up = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LookAt = new D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

Camera::Camera(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt)
{
	Position = (D3DXVECTOR3*)&position;
	Target = (D3DXVECTOR3*)&target;
	Up = (D3DXVECTOR3*)&up;
	LookAt = (D3DXVECTOR3*)&lookAt;
}

Camera::~Camera()
{
}

void Camera::Setup(rfVector3 position, rfVector3 target, rfVector3 up, rfVector3 lookAt)
{
	Position = (D3DXVECTOR3*)&position;
	Target = (D3DXVECTOR3*)&target;
	Up = (D3DXVECTOR3*)&up;
	LookAt = (D3DXVECTOR3*)&lookAt;
}