#include "DelayedGrat.h"
#include "iostream"


DelayedGrat::DelayedGrat() : GameObject(ObjectType::DISPLAY)
{}

 
void DelayedGrat::Update(double frametime)
{ 
    std::string timeText = "Time: " + std::to_string(m_time);
    std::string scoreText = "Score: " + std::to_string(m_PlayerScore);


    HtGraphics::instance.WriteTextAligned(1400, 950, timeText, HtGraphics::WHITE, 1, 1.0);
    HtGraphics::instance.WriteTextAligned(1400, 900, scoreText, HtGraphics::WHITE, 1, 1.0);

    m_time += 1 * frametime;
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

    if (m_GratTimer >= 25 && m_Block == false) {
        m_Block = true;
        std::cout << "Block set to true" << std::endl;
    }

    if (m_PlayerScore >= 300 && m_Dash == false) {
        m_Dash = true;
        std::cout << "Dash set to true" << std::endl;
    }
   
    if (m_PlayerScore >= 200 && m_Heavy == false) {
        m_Heavy = true;
        std::cout << "Heavy set to true" << std::endl;
    }

    if (m_GratTimer >= 30 && m_OgreHBuff == false) {
        m_OgreHBuff = true;
        std::cout << "Ogre's Health Buffed" << std::endl;
    }
    if (m_PlayerScore >= 400 && m_OgreABuff == false) {
        m_OgreABuff = true;
        std::cout << "Ogre's Attack Increased" << std::endl;
    }

    if (m_GratTimer >= 40 && m_PlayerHBuff == false) {
        m_PlayerHBuff = true;
        std::cout << "Player's Health is buffed" << std::endl;
    }

}

void DelayedGrat::Initialise(Vector2D startpos)
{
    m_GratTimer = 0;
    startpos = Vector2D(300, 300);
    m_time = 0;
    m_PlayerScore = 0;

}
void DelayedGrat::Render()
{
}

void DelayedGrat::addScore(int points)
{
    m_PlayerScore += points;

}

int DelayedGrat::getScore()
{
    return m_PlayerScore;
}
