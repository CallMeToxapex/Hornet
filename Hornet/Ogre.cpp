#include "Ogre.h"
#include <iostream>
#include "HtGraphics.h"

Ogre::Ogre()
{
}

void Ogre::Update(double frametime)
{
    Instructions inst = GetInstructions();

    m_Velocity += inst.acceleration * frametime;
    

    //// Optional: clamp to max speed
    //if (m_Velocity.magnitude() > m_move)
    //    m_Velocity = m_Velocity.unitVector() * m_move;

    m_position += m_Velocity * frametime;

    m_hitbox.PlaceAt(m_position, 25);
}

void Ogre::Initialise(World* pWorld)
{
    LoadImage("assets/Orc-Idle(1).png");
    LoadImage("assets/Orc-Idle(2).png");
    LoadImage("assets/Orc-Idle(3).png");
    LoadImage("assets/Orc-Idle(4).png");
    LoadImage("assets/Orc-Idle(5).png");
    LoadImage("assets/Orc-Idle(6).png");
    m_hitbox.PlaceAt(m_position, 25);
    m_scale = 4.0;
    m_move = 50;
    m_life = 50;
    m_World = pWorld;
    GenerateNode();

}

void Ogre::ProcessCollision(GameObject& other)
{
}

void Ogre::setPos(Vector2D pos)
{
    m_position = pos;

}

Instructions Ogre::GetInstructions()
{

    Instructions answer;        // Use this to report what you want the bot to do

    // The next few lines might make your life easier, but you can delete them if you want
    Vector2D position = m_Pplayer->GetPosition();
    Vector2D velocity = m_Pplayer->GetVelocity();
  //  Vector2D acceleration = m_Pplayer->GetAcceleration();
    //int health = m_pBot->GetHealth();
    //bool isDead = m_pBot->IsDead();
    //int holdingFlag = m_pBot->GetHoldingFlag();
    //int ownNumber = m_pBot->GetNumber();

    // And now your code
    answer.acceleration = Seek(position);
    answer.acceleration += AvoidWalls();
    answer.pPlayer = nullptr;
  //  answer.pPlayer = theGameState.pBots[1][3];
    DrawNodes();
    return answer;
}

IShape2D& Ogre::GetCollisionShape()
{
    return m_hitbox;
}

Vector2D Ogre::Seek(Vector2D targetPoint)
{
    Vector2D desiredVelocity = (targetPoint - m_position).unitVector() * m_move;
    Vector2D behaviourAccn = desiredVelocity - m_Velocity;
  //  std::cout << "Hello" << std::endl;
    return behaviourAccn;

}

Vector2D Ogre::Arrive(Vector2D targetPoint)
{
    double distance = (targetPoint - m_position).magnitude();
    double speed = distance * 0.5;
    Vector2D desiredVelocity = (targetPoint - m_position).unitVector() * speed;
    Vector2D behaviourAccn = desiredVelocity - m_Velocity;
    return behaviourAccn;
}

Vector2D Ogre::Flee(Vector2D targetPoint)
{
    Vector2D desiredVelocity = ( m_position- targetPoint).unitVector() * m_move;
    Vector2D behaviourAccn = desiredVelocity - m_Velocity;
    //  std::cout << "Hello" << std::endl;
    return behaviourAccn;
}

Vector2D Ogre::Pursuit(Vector2D targetPoint, Vector2D targetVelocity)
{
    return Vector2D();
}

Vector2D Ogre::Avoid(Vector2D targetPoint, Vector2D targetVelocity)
{
    return Vector2D();
}

Vector2D Ogre::AvoidWalls()
{
    Circle2D avoidance;
    avoidance.PlaceAt(m_position + m_Velocity, 150);

    if (m_World->Collides(avoidance)) {
        Vector2D normal = m_World->CollisionNormal(avoidance);
        Vector2D acceleration = normal * 50;

        return acceleration;
    }
    return Vector2D(0, 0);  

}

void Ogre::GenerateNode()
{
    nodeList.clear();


    Rectangle2D MapArea;
    MapArea.PlaceAt(1200, -1200, -1200, 1200);
    CheckSquare(MapArea);
}

void Ogre::DrawNodes()
{
    for (PathNode next : nodeList) {
        Circle2D dot;
        dot.PlaceAt(next.position, 10);
        HtGraphics::instance.FillCircle(dot, HtGraphics::WHITE);
    }
}

void Ogre::CheckSquare(Rectangle2D square)
{
    if (square.GetArea() < 2500)
        return;

    if (!m_World->Collides(square)) {
        PathNode newNode;
        newNode.position = square.GetCentre();
        nodeList.push_back(newNode);
    }
    else
    {
        double top = square.GetTopLeft().YValue;
        double bottom = square.GetBottomLeft().YValue;
        double left = square.GetTopLeft().XValue;
        double right = square.GetBottomRight().XValue;

        Rectangle2D r1;
        r1.PlaceAt(top, left, (top + bottom) / 2, (left + right) / 2);

        Rectangle2D r2;
        r2.PlaceAt(top, (left + right) / 2, (top + bottom) / 2 , right);

        Rectangle2D r3;
        r3.PlaceAt((top + bottom) / 2, left, bottom, (left + right) / 2);

        Rectangle2D r4;
        r4.PlaceAt((top + bottom) / 2, (left + right) / 2, bottom, right);

        CheckSquare(r1);
        CheckSquare(r2);
        CheckSquare(r3);
        CheckSquare(r4);
    }

    

}

void Ogre::setPlayer(Player* player)
{
    m_Pplayer = player;

}
