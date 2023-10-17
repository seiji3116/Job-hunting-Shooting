#pragma once
#include "Application/GameObject/Camera/CameraBase.h"

class TitleCamera : public CameraBase
{
public:
	TitleCamera() { Init(); }
	virtual ~TitleCamera()	override {}

	void Init()					override;
	void Update()				override;

private:

	POINT m_FixMousePos;
};