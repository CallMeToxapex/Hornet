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


private:

    double m_GratTimer;
    int m_PlayerScore;
    double m_time;

};

