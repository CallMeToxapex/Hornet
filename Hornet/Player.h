#pragma once
#include "GameObject.h"
#include "DelayedGrat.h"
#include "World.h"
class Player :public GameObject
{
public:
    Player();
    void Update(double frametime) override;
    void Render() override;
    void Initialise(Vector2D startPos, DelayedGrat* pGrat, World* pWorld);
    void ProcessCollision(GameObject& other) override; 
    IShape2D& GetCollisionShape() override;
    bool NPressed();
    bool NpressedFlag();
    bool NPressedToggle();
    bool LPressed();
    bool LPressedFlag();
    bool BPressed();
    bool BPressedFlag();
    bool BPressedToggle();
    Vector2D GetVelocity();


private: 
    Vector2D m_velocity;
    DelayedGrat* m_PGrat;
    World* m_PWorld;
    Vector2D m_Ymovement;
    Vector2D m_Xmovement;
    double m_attackDelay;
    bool m_flipped;
    Circle2D m_collisionshape;
    bool m_Hashit;


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

    // Blocking Variables
    bool m_blocking;
    double m_Blocktime;
    double m_BlockCD;
    bool B_Toggle;
    bool m_BPressed;
    PictureIndex m_Shield;

    // Dashing Variables
    Vector2D m_lastDirection;
    bool m_dashing;
    double m_dashTimer;
    double m_dashSpeed;
    double m_DashCD;
};

