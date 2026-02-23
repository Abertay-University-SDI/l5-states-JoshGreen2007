#pragma once
#include "Framework/GameObject.h"
#include "Switch.h"

class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setFlag(GameObject* flag) { m_pFlag = flag; }
    void setSwitch(Switch* pSwitch) { m_pSwitch = pSwitch; }

    bool getWantGameOver() { return m_wantsToEndGame; };
    void setWantGameOver(bool isOver) { m_wantsToEndGame = isOver; } // Setter for private function

private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_previousPosition;
    GameObject* m_pFlag = nullptr;
    Switch* m_pSwitch = nullptr;

    bool m_isOnGround = false;
    bool m_switchState = false;
    bool m_wantsToEndGame = false;

    float m_speed = 5.f;
    const float GRAVITY = 10.f;
    const float MAX_SPEED = 10.f;
    const float JUMP_FORCE = 6.f;
    const float RESTITUTION = 0.8f;
    const float INTERACT_RANGE = 50.f;

};

