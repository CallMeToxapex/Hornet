#pragma once
#include "GameObject.h"
#include "DelayedGrat.h"
class Player :public GameObject
{
public:
    Player();
    void Update(double frametime) override;
    void Initialise(Vector2D startPos, DelayedGrat* pGrat);
    void ProcessCollision(GameObject& other) override; 
    IShape2D& GetCollisionShape() override;
    bool NPressed();
    bool NpressedFlag();
    bool NPressedToggle();
    bool LPressed();
    bool LPressedFlag();

private: 
    DelayedGrat* m_PGrat;
    Vector2D m_Ymovement;
    Vector2D m_Xmovement;
    double m_attackDelay;
    Circle2D m_collisionshape;
    //Animation Variables
    bool m_Lattacking;
    double m_WalkTimer;
    double m_idleTimer;
    double m_IdleCount;
    //Light Attack Variables
    double m_aTimer;
    bool m_LightAPressed;
    bool N_Toggle;
    //Arrow Variables
    double m_arrowCD;
    bool L_Toggle;
    bool m_LPressed;
    bool m_Aattacking;
    // Heavy Variables
    bool m_Hattacking;

};

