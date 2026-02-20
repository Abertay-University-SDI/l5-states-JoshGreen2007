#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Framework/TileMap.h"
#include "Player.h"
#include "Framework/Collision.h"

class Level1 : BaseLevel {
public:
	Level1(sf::RenderWindow& window, Input& input, GameState& gameState);
	~Level1() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:

	GameObject m_flag, m_switch;

	sf::Texture m_tileTexture;

	TileMap m_tileMap;

	Player m_player;

};