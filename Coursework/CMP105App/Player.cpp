#include "Player.h"
#include <iostream>

Player::Player()
{
	if (!m_texture.loadFromFile("gfx/dino1.png"))
		std::cerr << "No dino texture. sad";


	setTexture(&m_texture);
	setSize({ 36,36 });
	setCollisionBox({ {6,6}, { 24,25 } });
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
	if (m_input->isKeyDown(sf::Keyboard::Scancode::Space) && m_isOnGround)
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

	m_previousPosition = getPosition();

	m_isOnGround = false;

	// newtonian model
	m_acceleration.y += GRAVITY;
	m_velocity += dt * m_acceleration;
	move(m_velocity);
}

void Player::collisionResponse(GameObject& collider)
{

	sf::FloatRect playerCollider = getCollisionBox();
	sf::FloatRect wallBounds = collider.getCollisionBox();

	float previousPlayerBottom = (m_previousPosition.y + m_collisionBox.position.y + m_collisionBox.size.y);

	float tileTop = wallBounds.position.y;
	
	// Floor collision
	if (m_velocity.y > 0 && previousPlayerBottom <= tileTop )
	{

		m_isOnGround = true;
		m_velocity.y = 0;
		setPosition({ getPosition().x, tileTop - m_collisionBox.position.y - m_collisionBox.size.y });

	}

}
