#pragma once
#include "GameObject.h"
#include "HtAudio.h"
class DelayedGrat : public GameObject
{
public:
    DelayedGrat();
    void Update(double frametime) override;
    void Initialise(Vector2D startpos);
    void Render();
    void addScore(int points);
    int getScore();
    bool m_Movement = true;
    bool m_Attack = true;
    bool m_Arrow = true;
    bool m_Block = false;
    bool m_Dash = false;
    int m_PlayerScore;
    bool m_Heavy = false;
    bool m_OgreHBuff = false;
    bool m_OgreABuff = false;
    bool m_PlayerHBuff = false;
private:

    double m_GratTimer;
    double m_time;

};

