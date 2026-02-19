#include "Player.h"
#include <iostream>

Player::Player()
{
	if (!m_texture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad";


	setTexture(&m_texture);
	setSize({ 72,72 });
	setCollisionBox({ {6,6}, { 48,50 } });
	setPosition({ 50,0 });
	m_isOnGround = false;
	setTextureRect({ { 0,0 }, { 24,24 } });
}

void Player::handleInput(float dt)
{
	m_acceleration = { 0,0 };

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
		m_acceleration.x -= SPEED;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_acceleration.x += SPEED;
	if (m_input->isPressed(sf::Keyboard::Scancode::Space) && m_isOnGround)
	{

		m_velocity.y = -JUMP_FORCE;
		m_isOnGround = false;

	}

	if (m_input->isKeyDown(sf::Keyboard::Scancode::R))	// Reset (for debugging)
	{
		setPosition({ 50,0 });
		m_velocity = { 0,0 };
	}
}

void Player::update(float dt)
{

	if (m_velocity.y > 0) m_isOnGround = false;

	m_previousPosition = getPosition();

	// newtonian model
	m_acceleration.y += GRAVITY;
	m_velocity += dt * m_acceleration;
	move(m_velocity);
}

void Player::collisionResponse(GameObject& collider)
{

	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();

	float tileTop = wallBounds.position.y;

	auto overlap = playerCollider.findIntersection(wallBounds);
	if (!overlap) return;
	
	// Top/Bottom collision
	if (overlap->size.x >= overlap->size.y)
	{

		if (m_previousPosition.y <= tileTop && m_velocity.y > 0)
		{

			m_velocity.y = 0;
			// Set position to top of tile
			setPosition({ getPosition().x, collider.getPosition().y - getCollisionBox().size.y });
			m_isOnGround = true;

		}

	}

	// Left / Right side collision
	else
	{

		m_velocity.x *= -RESTITUTION; // Apply restitution

	}

}
