#include "Arrow.h"

const double RADIUS = 30;
Arrow::Arrow() : GameObject(ObjectType::ARROW)
{
}

void Arrow::Update(double frametime)
{
        m_position = m_position + m_velocity * frametime;
        m_ArrowTime -= frametime;
    m_collisionshape.PlaceAt(m_position, RADIUS);

    HtGraphics::instance.FillCircle(m_collisionshape, HtGraphics::RED);

    if (m_ArrowTime <= 0)
        Deactivate();

}

void Arrow::Initialise(Vector2D startPos, Vector2D startVel)
{
    Lifetime = 10;
    LoadImage("assets/Arrow.png");
    m_scale = 3;
    m_position = Vector2D(0, 0);
    m_velocity.setBearing((rand() % 320) - 1200, (rand() % -500) - 300);
    m_position = startPos;
    m_velocity = startVel;
    m_ArrowTime = Lifetime;
    SetCollidable();
    m_collisionshape.PlaceAt(m_position, RADIUS);
    m_hasHit = false;


}

IShape2D& Arrow::GetCollisionShape()
{
    return m_collisionshape;
}

void Arrow::ProcessCollision(GameObject& other)
{
    if (other.GetType() == ObjectType::OGRE) {
        Deactivate();
    }
}
