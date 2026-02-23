#pragma once

#include "Framework/GameObject.h"

class Switch : public GameObject
{

public:

	Switch();
	~Switch();

	void toggle();
	bool getState() { return m_isOn; } // Return active boolean state when called

private:

	bool m_isOn;

	sf::IntRect m_offIntRect = { {4 * 19,3 * 19}, {18,18} };
	sf::IntRect m_onIntRect = { {6 * 19,3 * 19}, {18,18} };

};

// Note to self: make changes to Level.h so it can interact