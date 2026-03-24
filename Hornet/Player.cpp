#include "Player.h"
#include "DelayedGrat.h"
#include "HtKeyboard.h"
#include "iostream"
#include "Arrow.h"
#include "ObjectManager.h"
#include "World.h"
#include "Ogre.h"


double const ARROWSPEED = 350;


Player::Player(): GameObject(ObjectType::PLAYER)
{
}

void Player::Update(double frametime)
{
    HtGraphics::instance.FillCircle(m_collisionshape, HtGraphics::RED);

    std::string Health = "Health: " + std::to_string(m_life);
    HtGraphics::instance.WriteTextAligned(-1400, 950, Health, HtGraphics::WHITE, 1, 1.0);



    m_collisionshape.PlaceAt(m_position, 50);
    m_idleTimer += 1 * frametime;
    m_arrowCD = m_arrowCD - 1 * frametime;


    if (m_Blocktime >= 4) {
        m_Blocktime = 4;
    }

    if (NPressed()) {}
    if (BPressed()) {}
    if (BPressedFlag()) {}


    if (m_idleTimer > 1)
    {
        m_IdleCount += 4 * frametime;
        m_imageNumber = m_IdleCount;
        if (m_IdleCount > 5) {
            m_IdleCount = 0;
        }

    }

    if (m_PGrat->m_Movement) {

        if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_D)) {
            m_flipped = false;
            m_lastDirection = Vector2D(1, 0);
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
        m_flipped = true;
        m_lastDirection = Vector2D(-1, 0);
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
        m_lastDirection = Vector2D(0, 1);

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
        m_lastDirection = Vector2D(0, -1);

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

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_SPACE) && m_PGrat->m_Dash && m_DashCD > 6)
    {
        m_DashCD = 0;
        m_dashing = true;
    }

    if (m_dashing)
    {
        m_position += m_lastDirection * m_dashSpeed * frametime;
        m_dashTimer -= frametime;

        if (m_dashTimer <= 0)
        {
            m_dashing = false;
        }
    }

    if (!m_dashing) {
        m_dashTimer = 0.2;
        m_DashCD += 1 * frametime;
    }


    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_N)) {
    }

    if (m_PGrat->m_Arrow && m_arrowCD <= 0 && LPressedFlag())
    {
        m_idleTimer = 0;
        m_aTimer = 21;
        m_Aattacking = true;
        m_arrowCD = 3;

    }

    if (m_Aattacking) {
        m_imageNumber = m_aTimer;
        m_aTimer += 9 * frametime;
        m_imageNumber = (int)m_aTimer;
    }

    if (m_aTimer > 28 && m_Aattacking) {
        m_aTimer = 21;
        m_Aattacking = false;
        Arrow* pArrow = new Arrow();
        Vector2D shootDirection;
        if (m_flipped) {
            shootDirection = Vector2D(-ARROWSPEED, 0);
        }
        else
            shootDirection = Vector2D(ARROWSPEED, 0);
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
        m_aTimer += 8 * frametime;
        m_imageNumber = (int)m_aTimer;
        Rectangle2D lightHit;

        if (m_flipped) {
            lightHit.PlaceAt(m_position + Vector2D(-120, -50), m_position + Vector2D(0, 50));
        }
        else
        {
            lightHit.PlaceAt(m_position + Vector2D(0, -50), m_position + Vector2D(120, 50));
        }

        for (Ogre* pOgre : m_ogres)
        {
            if (pOgre != nullptr && lightHit.Intersects(pOgre->GetCollisionShape()) && !m_Hashit){
                pOgre->TakeDamage(15);
            m_Hashit = true;
        }
    }


    }
    if (m_aTimer > 21 && m_Lattacking)
    {
        m_aTimer = 15;
        m_Lattacking = false;
        m_Hashit = false;

    }



    if (m_PGrat->m_Block && m_Blocktime >= 0 &&  BPressedToggle()){    
        m_blocking = true;
        m_idleTimer = 0;

    }

    if (m_blocking) {
        m_Blocktime -= 1 * frametime;
        HtGraphics::instance.DrawAt(m_position, m_Shield, 0.09 * 0.5, m_angle, m_transparency);

    }



    if (!BPressedToggle() || m_Blocktime <= 0) {
        m_blocking = false;
        B_Toggle = false;
        m_Blocktime += 0.5 * frametime;

    }

    if (HtKeyboard::instance.KeyPressed(SDL_SCANCODE_M) && m_PGrat->m_Heavy)
    {
        m_Hattacking = true;
        m_idleTimer = 0;
        m_aTimer = 29;
    }

    if (m_Hattacking) {
        m_imageNumber = m_aTimer;
        m_aTimer += 5 * frametime;
        m_imageNumber = (int)m_aTimer;
        Rectangle2D lightHit;

        if (m_flipped) {
            lightHit.PlaceAt(m_position + Vector2D(-120, -50), m_position + Vector2D(0, 50));
        }
        else
        {
            lightHit.PlaceAt(m_position + Vector2D(0, -50), m_position + Vector2D(120, 50));
        }

        for (Ogre* pOgre : m_ogres)
        {
            if (pOgre != nullptr && lightHit.Intersects(pOgre->GetCollisionShape()) && !m_Hashit) {
                pOgre->TakeDamage(25);
                m_Hashit = true;
            }
        }

    }
    if (m_aTimer > 34 && m_Hattacking)
    {
        m_aTimer = 29;
        m_Hattacking = false;
        m_Hashit = false;
    }

    if (m_imageNumber < 0) m_imageNumber = 0;
    if (m_imageNumber > 38) m_imageNumber = 38;

    Vector2D normal = m_PWorld->CollisionNormal(m_collisionshape);
    m_position += normal * 10;


    if (m_Lattacking) {
        Rectangle2D debugHit;
        if (m_flipped)
            debugHit.PlaceAt(m_position + Vector2D(-120, -50), m_position + Vector2D(0, 50));
        else
            debugHit.PlaceAt(m_position + Vector2D(0, -50), m_position + Vector2D(120, 50));

        HtGraphics::instance.DrawRect(debugHit, HtGraphics::RED);
    }


    if (m_hurt)
    {
        m_aTimer = 35;
        m_imageNumber = (int)HurtTimer;
        m_idleTimer = 0;

        if (m_flipped) {
            m_position += Vector2D(50, 0) * frametime;
        }
        else
        {
            m_position -= Vector2D(50, 0) * frametime;
        }
        HurtTimer += 3 * frametime;

        if (HurtTimer >= 38) {
            m_hurt = false;
            HurtTimer = 35;
        }
        

    }




}
    

void Player::Render()
{
    if (m_imageNumber >= 0 && m_imageNumber < (int)m_images.size())
    {
        HtGraphics::instance.DrawAt(m_position, m_images[m_imageNumber], m_scale, m_angle, m_transparency, m_flipped);
    }
}

void Player::Initialise(Vector2D startPos, DelayedGrat* PGrat, World* PWorld)
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

    // Hurt Animations
    LoadImage("assets/Soldier-Hurt(1).png"); // ImageNumber_35
    LoadImage("assets/Soldier-Hurt(2).png");
    LoadImage("assets/Soldier-Hurt(3).png");
    LoadImage("assets/Soldier-Hurt(4).png"); // ImageNumber_38










    SetCollidable();
    m_Hashit = false;
    m_flipped = false;
    m_scale = 4.0;
    m_collisionshape.PlaceAt(m_position, 1);
    m_life = 3;
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
    m_Blocktime = 2;
    m_PGrat = PGrat;
    m_PWorld = PWorld;
    m_Shield = HtGraphics::instance.LoadPicture("assets/Shield.png");

    m_dashing = false;
    m_dashTimer = 0;
    m_dashSpeed = 600;
    m_DashCD = 6;

    HurtTimer = 35;

    
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

bool Player::BPressed()
{
    return HtKeyboard::instance.KeyPressed(SDL_SCANCODE_B);

}

bool Player::BPressedFlag()
{

    if (BPressed()) {

        if (!m_BPressed) {
            B_Toggle = !B_Toggle;
            m_BPressed = true;
            return true;
        }
        else {
            if (m_BPressed == true) {
                return false;
            }
        }
    }
    m_BPressed = false;
    return false;
}

bool Player::BPressedToggle()
{
    return B_Toggle;
}

Vector2D Player::GetVelocity()
{
    return m_velocity;
}

void Player::TakeDamage() 
{
    if (!m_blocking){ 
    m_life -= 1;
    m_hurt = true;
    std::cout << "Hurt Hurt Hurt" << std::endl;
    HurtTimer = 35;
    }
    if (!m_blocking && m_PGrat->m_OgreABuff) {
        m_life -= 2;
        m_hurt = true;
        std::cout << "Really Hurt Hurt" << std::endl;
        HurtTimer = 35;
    }
}

void Player::GainHealth()
{
    if (m_PGrat->m_PlayerScore % 150 == 0) {
        if (m_PGrat->m_PlayerHBuff && m_life < 3) {
            m_life += 1;
            std::cout << "Health Gained" << std::endl;
        }

        if (m_life < 5 && m_PGrat->m_PlayerHBuff) {
            m_life += 1;
            std::cout << "Health Gained" << std::endl;


        }
    }

}

void Player::AddOgre(Ogre* ogre)
{
    m_ogres.push_back(ogre);
}

void Player::RemoveOgre(Ogre* ogre)
{
    for (int i = 0; i < m_ogres.size(); i++) {
        if (m_ogres[i] == ogre) {
            m_ogres.erase(m_ogres.begin() + i);
                break;
        }
    }
}

