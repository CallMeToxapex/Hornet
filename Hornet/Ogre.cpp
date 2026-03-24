#include "Ogre.h"
#include <iostream>
#include "HtGraphics.h"
#include "ObjectManager.h"

int Ogre::s_ogreCount = 0;

Ogre::Ogre() : GameObject(ObjectType::OGRE)
{
    m_Pplayer = nullptr;
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

    if (m_Pplayer == nullptr)
        return;
    Instructions inst = GetInstructions();

    m_AttackCD -= 1 * frametime;

    Rectangle2D m_attackHitBox;

    if (m_flipped) {
        m_attackHitBox.PlaceAt(m_position + Vector2D(-50, -50), m_position + Vector2D(0, 50));
    }
    else
    {
        m_attackHitBox.PlaceAt(m_position + Vector2D(0, -50), m_position + Vector2D(50, 50));

    }


    if (m_attackHitBox.Intersects(m_Pplayer->GetCollisionShape())) {
        Attack();
    }

    if (!m_busy) {
        m_position += m_Velocity * frametime;
        m_Velocity += inst.acceleration * frametime;
        if (m_Velocity.XValue != 0) {
            m_imageNumber = m_Walktimer;
            if (m_Walktimer < 14) {
                m_Walktimer += 5 * frametime;
            }
            else {
                m_Walktimer = 6;
            }
        }
    }
    else if (m_BHurt) {
        m_Velocity = Vector2D(0, 0); 
        m_imageNumber = m_HurtA;
        m_HurtA += 3 * frametime;

        if (m_HurtA >= 18) {
            m_busy = false;
            m_HurtA = 15;
            m_BHurt = false;
        }
    }
    else if (m_Attacking) {
        m_Velocity = Vector2D(0, 0); 
        m_imageNumber = m_AttackA;
        m_AttackA += 5 * frametime;

        if (m_AttackA >= 24) {
            if (m_attackHitBox.Intersects(m_Pplayer->GetCollisionShape())) {
                m_Pplayer->TakeDamage();
            }
            m_busy = false;
            m_Attacking = false;
            m_AttackCD = 2;
            m_AttackA = 19;
        }
    }

    m_hitbox.PlaceAt(m_position, 25);

    if (m_life <= 0) {
        m_PDelayedGrat->addScore(50);
        m_Velocity = Vector2D(0,0);

        Ogre* pNewOgre = new Ogre();
        Vector2D spawnPos(rand() % 800 - 400, rand() % 800 - 400);
        pNewOgre->Initialise(m_World, spawnPos, m_PDelayedGrat, m_Pplayer);
        pNewOgre->setPlayer(m_Pplayer);
        ObjectManager::instance.AddItem(pNewOgre);

        m_Pplayer->RemoveOgre(this);
        m_Pplayer->AddOgre(pNewOgre);

        Deactivate();
    }


    if (m_Velocity.XValue <= 0 && !m_busy) {
        m_flipped = true;
    }
    else if (m_Velocity.XValue >= 0 && !m_busy) {
        m_flipped = false;
    }


    HtGraphics::instance.DrawRect(m_attackHitBox, HtGraphics::RED);
        
   /* if (m_PDelayedGrat->m_OgreHBuff) {
        m_life = 65;
    }*/
    Vector2D normal = m_World->CollisionNormal(m_hitbox);
    m_position += normal * 10;
}



void Ogre::Attack() {

    if (m_AttackCD <= 0) {
        m_busy = true;
        m_Attacking = true;
    }
}

void Ogre::Initialise(World* pWorld, Vector2D startpos, DelayedGrat* pGrat, Player* pPlayer)
{
    m_Pplayer = pPlayer;
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
    LoadImage("assets/Orc-Attack(1).png");// ImageNumber_19
    LoadImage("assets/Orc-Attack(2).png");
    LoadImage("assets/Orc-Attack(3).png");
    LoadImage("assets/Orc-Attack(4).png");
    LoadImage("assets/Orc-Attack(5).png");
    LoadImage("assets/Orc-Attack(6).png");// ImageNumber 24




    m_PDelayedGrat = pGrat;
    m_hitbox.PlaceAt(m_position, 25);
    SetCollidable();
    m_scale = 4.0;
    m_move = 75;
    m_life = 50;
    m_World = pWorld;
    m_position = startpos;
    GenerateNode();
    m_flipped = false;
    m_Walktimer = 6;
    m_busy = false;
    m_HurtA = 15;
    m_BHurt = false;
    // Attacking Variables
    m_AttackCD = 2;
    m_Attacking = false;
    m_AttackA = 19;
    s_ogreCount++;
    m_behaviour = OgreBehaviour::SEEKER;
}

void Ogre::ProcessCollision(GameObject& other)
{

    if (other.GetType() == ObjectType::ARROW) {
        TakeDamage(10);
        std::cout << "Arrow Hit" << std::endl;
        std::cout << "Ogre Health Currently: " << m_life << std::endl;
        
    }

}

void Ogre::setPos(Vector2D pos)
{
    m_position = pos;

}

void Ogre::TakeDamage(int damage)
{
    if (!m_BHurt) {
        m_life -= damage;
        std::cout << "Damage taken" << std::endl;
        std::cout << "Ogre's Healtb: " << m_life << std::endl;
        m_BHurt = true;
        m_busy = true;

    }
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

    switch (m_behaviour) {
    case OgreBehaviour::FLEE:
        answer.acceleration = Flee(position);
        break;
    case OgreBehaviour::SEEKER:

        if (m_World->LineOfSight(m_position, position)) {
            answer.acceleration = Seek(position);
        }
        else {
            FindPath(m_position, position);

            if (path.size() > 0) {
                while (path.size() > 1 && m_World->LineOfSight(m_position, path[1])) {
                    path.erase(path.begin());
                }
                answer.acceleration = Seek(path[0]);

                if ((m_position - path[0]).magnitude() < 10) {
                    path.erase(path.begin());
                }
            }
        }        break;
    case OgreBehaviour::BUNKER: {
        double distance = (position - m_position).magnitude();

        if (distance < 100) {
            m_triggered = true;
        }
                if (m_triggered) {
                    if (m_World->LineOfSight(m_position, position)) {
                        answer.acceleration = Seek(position) * 2;
                    }
                    else {
                        FindPath(m_position, position);

                        if (path.size() > 0) {
                            while (path.size() > 1 && m_World->LineOfSight(m_position, path[1])) {
                                path.erase(path.begin());
                            }
                            answer.acceleration = Seek(path[0]) * 2;

                            if ((m_position - path[0]).magnitude() < 10) {
                                path.erase(path.begin());
                            }
                        }
                    }
                }
                else
                {
                    answer.acceleration = Vector2D(0, 0);
                    m_Velocity = Vector2D(0, 0);
                }
            break;
        }
    }



    // And now your code
    answer.acceleration += AvoidWalls();
    answer.pPlayer = nullptr;
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

void Ogre::SetOgreBehaviour(OgreBehaviour behaviour) {
    
    m_behaviour = behaviour;
}
Vector2D Ogre::AvoidWalls()
{
    Circle2D avoidance;
    avoidance.PlaceAt(m_position + m_Velocity, 150);

    if (m_World->Collides(avoidance)) {
        Vector2D normal = m_World->CollisionNormal(avoidance);
        Vector2D acceleration = normal * 200;

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
        //  HtGraphics::instance.FillCircle(dot, HtGraphics::WHITE);

        for (Edge nextEdge : next.edgeList) {
            Segment2D Seg;
            Seg.PlaceAt(next.position, nodeList[nextEdge.toIndex].position);
           // HtGraphics::instance.DrawSegment(Seg, HtGraphics::CYAN);
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

void Ogre::FindPath(Vector2D startpoint, Vector2D endpoint)
{
    PathNode* pStart = &nodeList[0];
    double distance = (startpoint - nodeList[0].position).magnitude();

    for (int i = 1; i < nodeList.size(); i++) {

        if ((m_position - nodeList[i].position).magnitude() < distance) {
            pStart = &nodeList[i];
            distance = (startpoint - nodeList[i].position).magnitude();
        }
    }


        PathNode* pEnd = &nodeList[0];
        double Enddistance = (endpoint - nodeList[0].position).magnitude();

        for (int i = 1; i < nodeList.size(); i++) {

            if ((endpoint - nodeList[i].position).magnitude() < Enddistance) {
                pEnd = &nodeList[i];
                Enddistance = (endpoint - nodeList[i].position).magnitude();
            }
        }

        path.clear();
        GenerateRoute(pStart, pEnd);
        path.push_back(endpoint);

}

void Ogre::GenerateRoute(PathNode* startnode, PathNode* endpoint)
{

    PathNode* pCurrent = startnode;

    //Clearing Existing data
    for (int i = 0; i < nodeList.size(); i++) {
        nodeList[i].f = 0;
        nodeList[i].g = 0;
        nodeList[i].pParent = nullptr;
        nodeList[i].h = (endpoint->position - nodeList[i].position).magnitude();

    }
    // Creating Open and close list

    std::list<PathNode*> openlist;
    std::list<PathNode*> closedlist;

    openlist.push_back(pCurrent);
    while (true) {
        if (openlist.size() == 0) {
            break;
        }
        pCurrent = FindBestNode(openlist);
        openlist.remove(pCurrent);
        closedlist.push_back(pCurrent);
        if (pCurrent == endpoint) {
            break;
        }
        for (Edge next : pCurrent->edgeList) {
            PathNode* pNext = &nodeList[next.toIndex];
            double g = pCurrent->g + next.cost;
            if (pNext->g == 0 || pNext->g > g) {
                pNext->g = g;
                pNext->f = (pNext->g + pNext->h);

            }
            if (!Contain(openlist, pNext) && !Contain(closedlist, pNext)) {
                pNext->g = g;
                pNext->f = (pNext->g + pNext->h);
                pNext->pParent = pCurrent;
                openlist.push_back(pNext);
            }
            else if (g < pNext->g) {
                pNext->g = g;
                pNext->f = (pNext->g + pNext->h);
                pNext->pParent = pCurrent;
            }

        }
    }
         PathNode* pTrace = endpoint;
         while (pTrace != startnode && pTrace !=nullptr)
         {
             path.push_back(pTrace->position);
             pTrace = pTrace->pParent;
         }
         if (pTrace != nullptr) {
             path.push_back(startnode->position);
             std::reverse(path.begin(), path.end());
         }
    
}


PathNode* Ogre::FindBestNode(std::list<PathNode*> &openlist)
{
    
    double BestF = 9999;
    PathNode* index = nullptr;

    for (PathNode* next : openlist) {
        if (BestF > next->f) {
            BestF = next->f;
            index = next;
        }
        
    }
    return index;
}

bool Ogre::Contain(std::list<PathNode*>& list, PathNode* Target)
{ 
    for (PathNode* next : list) {
        if (next == Target) {
            return true;
        }
    }

    return false;
}

