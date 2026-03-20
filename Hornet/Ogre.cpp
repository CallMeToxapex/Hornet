#include "Ogre.h"
#include <iostream>
#include "HtGraphics.h"

Ogre::Ogre() : GameObject(ObjectType::OGRE)
{
}

void Ogre::Render()
{
    if (m_imageNumber >= 0 && m_imageNumber < (int)m_images.size())
    {
        HtGraphics::instance.DrawAt(m_position, m_images[m_imageNumber], m_scale, m_angle, m_transparency, m_flipped);
    }
}

void Ogre::Update(double frametime)
{
    Instructions inst = GetInstructions();


    m_Velocity += inst.acceleration * frametime;
    if (m_Velocity.XValue != 0 && !m_busy) {
        m_imageNumber = m_Walktimer;

        if (m_Walktimer < 14) {
            m_Walktimer += 5 * frametime;
        }
        else
        {
            m_Walktimer = 6;

        }

    }

    if (m_BHurt) {
        m_imageNumber = m_Hurt;
        m_Hurt += 3 * frametime;
        m_busy = true;

        if (m_Hurt > 18) {
            m_busy = false;
            m_Hurt = 15;
            m_BHurt = false;
        }
    }

    m_position += m_Velocity * frametime;

    if (m_Velocity.XValue <= 0) {
        m_flipped = true;
    }
    else if (m_Velocity.XValue >= 0) {
        m_flipped = false;
    }

    m_hitbox.PlaceAt(m_position, 25);

    if (m_life <= 0) {
        m_PDelayedGrat->addScore(50);
        m_Velocity = Vector2D(0,0);
        Deactivate();
    }
}

void Ogre::Initialise(World* pWorld, Vector2D startpos)
{
    LoadImage("assets/Orc-Idle(1).png"); // ImageNumber_0
    LoadImage("assets/Orc-Idle(2).png");
    LoadImage("assets/Orc-Idle(3).png");
    LoadImage("assets/Orc-Idle(4).png");
    LoadImage("assets/Orc-Idle(5).png");
    LoadImage("assets/Orc-Idle(6).png"); // ImageNumber _5
    LoadImage("assets/Orc-Walk(1).png"); // ImageNumber_6
    LoadImage("assets/Orc-Walk(2).png");
    LoadImage("assets/Orc-Walk(3).png");
    LoadImage("assets/Orc-Walk(4).png");
    LoadImage("assets/Orc-Walk(5).png");
    LoadImage("assets/Orc-Walk(6).png");
    LoadImage("assets/Orc-Walk(7).png");
    LoadImage("assets/Orc-Walk(8).png"); //ImageNumber_14
    LoadImage("assets/Orc-Hurt(1).png");//ImageNumber _15
    LoadImage("assets/Orc-Hurt(2).png");
    LoadImage("assets/Orc-Hurt(3).png");
    LoadImage("assets/Orc-Hurt(4).png"); // ImageNuMBER_18


    m_hitbox.PlaceAt(m_position, 25);
    SetCollidable();
    m_scale = 4.0;
    m_move = 50;
    m_life = 50;
    m_World = pWorld;
    m_position = startpos;
    GenerateNode();
    m_flipped = false;
    m_Walktimer = 6;
    m_busy = false;
    m_Hurt = 15;
}

void Ogre::ProcessCollision(GameObject& other)
{
}

void Ogre::setPos(Vector2D pos)
{
    m_position = pos;

}

void Ogre::TakeDamage(int damage)
{
    m_life -= damage;
    std::cout << "Damage taken" << std::endl;
    m_BHurt = true;

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
    int Size = nodeList.size();
    for (int i = 0; i < Size; i++) {
        for (int f = 0; f < Size; f++) {
            if (i != f && m_World->LineOfSight(nodeList[i].position, nodeList[f].position)) {
                Edge newEdge;
                newEdge.fromIndex = i;
                newEdge.toIndex = f;
                newEdge.cost = (nodeList[i].position - nodeList[f].position).magnitude();
                nodeList[i].edgeList.push_back(newEdge);

            }
        }
    }
}

void Ogre::DrawNodes()
{
    for (PathNode next : nodeList) {
        Circle2D dot;
        dot.PlaceAt(next.position, 10);
        HtGraphics::instance.FillCircle(dot, HtGraphics::WHITE);

        for (Edge nextEdge : next.edgeList) {
            Segment2D Seg;
            Seg.PlaceAt(next.position, nodeList[nextEdge.toIndex].position);
          //  HtGraphics::instance.DrawSegment(Seg, HtGraphics::CYAN);
        }
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
