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
		m_acceleration.x -= m_speed;
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
		m_acceleration.x += m_speed;
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

	if (m_input->isPressed(sf::Keyboard::Scancode::F))
	{
		
		// If flag position - player position < interact range (I.E if the Player is inside the range)
		if ((m_pFlag->getPosition() - getPosition()).length() < INTERACT_RANGE)
			m_wantsToEndGame = true;
		else { m_wantsToEndGame = false; }

		// Note to self: .length() = the sqrt(x^2 + y^2). It converts a 2D vector into a single number
		if ((m_pSwitch->getPosition() - getPosition()).length() < INTERACT_RANGE)
			m_pSwitch->toggle(); // Call toggle from switch

	}

	if (m_speed >= MAX_SPEED)
		m_speed = MAX_SPEED;
}

void Player::update(float dt)
{

	/*std::cout << "Hi\n";*/

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

	float oldBottom = m_previousPosition.y + playerCollider.size.y;
	float tileTop = wallBounds.position.y;

	auto overlap = playerCollider.findIntersection(wallBounds);
	if (!overlap) return;

	if (oldBottom <= tileTop)
	{
		
		if (m_velocity.y > 0)
		{

			m_velocity.y = 0;
			// Set position to top of tile
			setPosition({ getPosition().x, getPosition().y - overlap->size.y });
			m_isOnGround = true;

		}

	}

	// Left / Right side collision
	else
	{

		m_velocity.x *= -RESTITUTION; // Apply restitution

		if (playerCollider.position.x < wallBounds.position.x)
			setPosition({ getPosition().x - overlap->size.x , getPosition().y });
		else
			setPosition({ getPosition().x + overlap->size.x, getPosition().y });

	}

}
