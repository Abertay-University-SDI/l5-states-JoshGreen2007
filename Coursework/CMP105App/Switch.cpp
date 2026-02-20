#include "Switch.h"

Switch::Switch()
{

	m_isOn = false;

}

Switch::~Switch()
{



}

void Switch::toggle()
{

	// When called switch the boolean state
	m_isOn = !m_isOn;
	if (m_isOn) setTextureRect(m_onIntRect);
	else setTextureRect(m_offIntRect);

}