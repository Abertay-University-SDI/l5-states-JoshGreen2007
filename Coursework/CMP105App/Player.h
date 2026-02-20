#pragma once
#include "Framework/GameObject.h"
class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setFlag(GameObject* flag) { m_pFlag = flag; }
    void getFlag();

    void setSwitch(GameObject* pSwitch) { m_pSwitch = pSwitch; }
    void getSwitch();

private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    sf::Vector2f m_previousPosition;
    GameObject* m_pFlag;
    GameObject* m_pSwitch;

    bool m_isOnGround = false;
    bool m_switchState = false;

    float m_speed = 5.f;
    const float GRAVITY = 10.f;
    const float MAX_SPEED = 10.f;
    const float JUMP_FORCE = 6.f;
    const float RESTITUTION = 0.8f;
    const float INTERACT_RANGE = 50.f;

};

