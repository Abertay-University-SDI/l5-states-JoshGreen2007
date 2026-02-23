#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Framework/TileMap.h"
#include "Framework/Collision.h"

#include "Player.h"
#include "Switch.h"

class Level1 : BaseLevel {
public:
	Level1(sf::RenderWindow& window, Input& input, GameState& gameState);
	~Level1() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

	void setFlag(GameObject* flag);
	void setSwitch(Switch* pSwitch);

	void pauseToggle() { m_isPaused = !m_isPaused; };

private:

	bool m_isPaused = false;
	sf::Font m_pausedFont;
	sf::Text m_pausedText;

	sf::Texture m_tileTexture;

	TileMap m_tileMap;

	Player m_player;
	Switch m_switch;
	GameObject m_flag;

};