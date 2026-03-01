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
    bool m_Movement = false;
    bool m_Attack = false;
    bool m_Arrow = false;



private:

    double m_GratTimer;

};

