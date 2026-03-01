#include "DelayedGrat.h"
#include "iostream"


DelayedGrat::DelayedGrat() : GameObject(ObjectType::DISPLAY)
{}

 
void DelayedGrat::Update(double frametime)
{
    m_GratTimer += 1 * frametime;
    if (m_GratTimer > 10 && m_Movement == false)
    {
        m_Movement = true;
       std::cout << "Movement set to true" << std::endl;
    }

    if (m_GratTimer > 15 && m_Attack == false)
    {
        m_Attack = true;
        std::cout << "Attack set to true" << std::endl;

    }

    if (m_GratTimer >= 20 && m_Arrow == false) {
        m_Arrow = true;
        std::cout << "Arrow set to true" << std::endl;

    }
}
void DelayedGrat::Initialise(Vector2D startpos)
{
    m_GratTimer = 0;
    startpos = Vector2D(300, 300);

}
void DelayedGrat::Render()
{
}