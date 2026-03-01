#pragma once
#include "GameObject.h"
class Arrow : public GameObject
{
public:
    Arrow();
    void Update(double frametime) override;
    void Initialise(Vector2D startPos, Vector2D startVel);
    IShape2D& GetCollisionShape();
    void ProcessCollision(GameObject& other) override;
private:
    Vector2D m_velocity;
    Vector2D m_ArrowSpeed;
    double m_ArrowTime;
    Circle2D m_collisionshape;
    double Lifetime;

};

