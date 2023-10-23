#include "GavityValidObjectPos.h"

Math::Vector3 GavityValidObjectPos::GetPos()
{
	return m_pos;
}

void GavityValidObjectPos::SetPos(Math::Vector3 _pos)
{
	m_pos = _pos;
}
