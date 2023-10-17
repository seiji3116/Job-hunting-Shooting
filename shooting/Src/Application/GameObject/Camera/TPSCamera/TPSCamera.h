#pragma once
#include "Application/GameObject/Camera/CameraBase.h"

class TPSCamera : public CameraBase
{
public:
	TPSCamera() { Init(); }
	virtual ~TPSCamera()	override {}

	void Init()					override;
	void Update()				override;

private:
	void UpdateRotateByMouse();
	void Collider();

	POINT m_FixMousePos;
};