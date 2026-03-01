#include "Player.h"
#include "DelayedGrat.h"
#include "HtKeyboard.h"
#include "iostream"
#include "Arrow.h"
#include "ObjectManager.h"


double const ARROWSPEED = 400;


Player::Player(): GameObject(ObjectType::ROCK)
{
}

void Player::Update(double frametime)
{
    m_collisionshape.PlaceAt(m_position, 85);
    m_idleTimer += 1 * frametime;
    m_arrowCD = m_arrowCD - 1 * frametime;

    if (NPressed()) {}



    if (m_idleTimer > 1)
    {
        m_IdleCount += 4 * frametime;
        m_imageNumber = m_IdleCount;
        if (m_IdleCount > 7) {
            m_IdleCount = 0;
        }

    }

    if (m_PGrat->m_Movement) {

        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D)) {

            m_position += m_Xmovement * frametime;
            m_idleTimer = 0;
            m_imageNumber = m_WalkTimer;

            m_imageNumber = m_WalkTimer;

            if (m_WalkTimer < 14) {
                m_WalkTimer += 5 * frametime;
            }
            else
            {
                m_WalkTimer = 6;

            }
        }
    }



    if ((HtKeyboard::instance.KeyPressed(SDL_SCANCODE_A))) {
        m_position -= m_Xmovement * frametime;
        m_idleTimer = 0;
        m_imageNumber = m_WalkTimer;

        if (m_WalkTimer < 14) {
            m_WalkTimer += 5 * frametime;
        }
        else
        {
            m_WalkTimer = 6;

        }

    }

    if ((HtKeyboard::instance.KeyPressed(SDL_SCANCODE_W))) {
        m_position += m_Ymovement * frametime;
        m_idleTimer = 0;
        m_imageNumber = m_WalkTimer;

        if (m_WalkTimer < 14) {
            m_WalkTimer += 5 * frametime;
        }
        else
        {
            m_WalkTimer = 6;

        }

    }

    if ((HtKeyboard::instance.KeyPressed(SDL_SCANCODE_S))) {
        m_position -= m_Ymovement * frametime;
        m_idleTimer = 0;
        m_imageNumber = m_WalkTimer;
        if (m_WalkTimer < 14) {
            m_WalkTimer += 5 * frametime;
        }
        else
        {
            m_WalkTimer = 6;

        }

    }


    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_N)) {
    }

    if (m_PGrat->m_Arrow && m_arrowCD <= 0 && LPressedFlag())
    {
        m_idleTimer = 0;
        m_aTimer = 21;
        m_Aattacking = true;
        m_arrowCD = 4;

    }

    if (m_Aattacking) {
        m_imageNumber = m_aTimer;
        m_aTimer += 5 * frametime;
        m_imageNumber = (int)m_aTimer;
    }

    if (m_aTimer > 28 && m_Aattacking) {
        m_aTimer = 21;
        m_Aattacking = false;
        Arrow* pArrow = new Arrow();
        Vector2D shootDirection;
        shootDirection.setBearing((m_angle + 90), ARROWSPEED);
        pArrow->Initialise(m_position, shootDirection);
        ObjectManager::instance.AddItem(pArrow);
    }


    if (m_PGrat->m_Attack && NpressedFlag())
    {
        m_Lattacking = true;
        m_idleTimer = 0;
        m_aTimer = 15;
    }

    if (m_Lattacking) {
        m_imageNumber = m_aTimer;
        m_aTimer += 5 * frametime;
        m_imageNumber = (int)m_aTimer;
    }
    if (m_aTimer > 21 && m_Lattacking)
    {
        m_aTimer = 15;
        m_Lattacking = false;
    }


    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_M))
    {
        m_Hattacking = true;
        m_idleTimer = 0;
        m_aTimer = 29;
    }

    if (m_Hattacking) {
        m_imageNumber = m_aTimer;
        m_aTimer += 5 * frametime;
        m_imageNumber = (int)m_aTimer;
    }
    if (m_aTimer > 34 && m_Hattacking)
    {
        m_aTimer = 29;
        m_Hattacking = false;
    }
}
    



void Player::Initialise(Vector2D startPos, DelayedGrat* PGrat)
{
   // Idle Animation
    LoadImage("assets/Soldier-Idle(1).png");
    LoadImage("assets/Soldier-Idle(2).png");
    LoadImage("assets/Soldier-Idle(3).png");
    LoadImage("assets/Soldier-Idle(4).png");
    LoadImage("assets/Soldier-Idle(5).png");
    LoadImage("assets/Soldier-Idle(6).png"); // ImageNumber_5


    // Walking Animation
    LoadImage("assets/Soldier-Walk(1).png"); // ImageNumber_6
    LoadImage("assets/Soldier-Walk(2).png");
    LoadImage("assets/Soldier-Walk(2).png");
    LoadImage("assets/Soldier-Walk(3).png");
    LoadImage("assets/Soldier-Walk(4).png");
    LoadImage("assets/Soldier-Walk(5).png");
    LoadImage("assets/Soldier-Walk(6).png");
    LoadImage("assets/Soldier-Walk(7).png");
    LoadImage("assets/Soldier-Walk(8).png"); // ImageNumber_14

  //LightAttack Animation
    LoadImage("assets/Soldier-Attack(1).png"); // ImageNumber_15
    LoadImage("assets/Soldier-Attack(2).png");
    LoadImage("assets/Soldier-Attack(3).png"); 
    LoadImage("assets/Soldier-Attack(4).png");
    LoadImage("assets/Soldier-Attack(5).png");
    LoadImage("assets/Soldier-Attack(6).png"); // ImageNumber_20*/

    // ArrowAttack Animatiions
    LoadImage("assets/Soldier-Arrow(1).png"); // ImageNumber_21
    LoadImage("assets/Soldier-Arrow(2).png");
    LoadImage("assets/Soldier-Arrow(3).png");
    LoadImage("assets/Soldier-Arrow(4).png");
    LoadImage("assets/Soldier-Arrow(5).png");
    LoadImage("assets/Soldier-Arrow(6).png");
    LoadImage("assets/Soldier-Arrow(7).png"); 
    LoadImage("assets/Soldier-Arrow(8).png");//ImageNumber_28

    //HeavyAttack Animations
    LoadImage("assets/Soldier-AttackH(1).png"); // ImageNumber_29
    LoadImage("assets/Soldier-AttackH(2).png"); 
    LoadImage("assets/Soldier-AttackH(3).png");
    LoadImage("assets/Soldier-AttackH(4).png");
    LoadImage("assets/Soldier-AttackH(5).png");
    LoadImage("assets/Soldier-AttackH(6).png");//ImageNumber_34






    SetCollidable();
    m_scale = 4.0;
    m_collisionshape.PlaceAt(m_position, 1);
    m_WalkTimer = 6;
    m_aTimer = 15;
    m_Xmovement = Vector2D(150, 0);
    m_Ymovement = Vector2D(0, 150);
    m_position = startPos;
    m_imageNumber = 0;
    m_arrowCD = 0;
    m_aTimer = 21;
    m_Lattacking = false;
    m_Aattacking = false;
    m_PGrat = PGrat;
}

void Player::ProcessCollision(GameObject& other)
{
}

IShape2D& Player::GetCollisionShape()
{
    return m_collisionshape;
}

bool Player::NPressed()
{
    return HtKeyboard::instance.KeyPressed(SDL_SCANCODE_N);
}

bool Player::NpressedFlag()
{
    if (NPressed()) {
        if (!m_LightAPressed) {
            N_Toggle = !N_Toggle;
            m_LightAPressed = true;
            return true;
        }
        else {
            if (m_LightAPressed == true) {
                return false;
            }
        }
    }
    m_LightAPressed = false;
    return false; 
}

bool Player::NPressedToggle() {
    return N_Toggle;
}

bool Player::LPressed()
{
    return HtKeyboard::instance.KeyPressed(SDL_SCANCODE_L);
}

bool Player::LPressedFlag()
{
    if (LPressed()) {
        if (!m_LPressed) {
            L_Toggle = !L_Toggle;
            m_LPressed = true;
            return true;
        }
        else {
            if (m_LPressed == true) {
                return false;
            }
        }
    }
    m_LPressed = false;
    return false;
}
