#pragma once
#include "GameObject.h"
#include "Player.h"
#include "World.h"
#include <list>
#include "DelayedGrat.h"

class Graph
{
   //std::vector<Node> NodeVector;
};

struct Edge
{
    int fromIndex;
    int toIndex;
    double cost;
};

class PathNode
{

public:
    int indexNumber;
    Vector2D position;
   std::list<Edge> edgeList;
   double f, g, h;
   PathNode* pParent;
   std::list<PathNode*> openList;
   std::list<PathNode*> closedList;
};
struct Instructions
{
    Vector2D acceleration;  // Desired acceleration. If >MAXACCELERATION, will get clamped
    Player* pPlayer;        // Pointer to bot to shoot at. If not, will be nullptr.
};

class Ogre : public GameObject

{
  public:
        Ogre();
        void Render() override;
        void Update(double frametime) override;
        void Initialise(World* pWorld, Vector2D startpos);
        void ProcessCollision(GameObject& other) override;
        void setPos(Vector2D pos);
        void TakeDamage(int damage);
        Instructions GetInstructions();
        IShape2D& GetCollisionShape() override;
        Vector2D Seek(Vector2D targetPoint);
        Vector2D Arrive(Vector2D targetPoint);
        Vector2D Flee(Vector2D targetPoint);
        Vector2D Pursuit(Vector2D targetPoint, Vector2D targetVelocity);
        Vector2D Avoid(Vector2D targetPoint, Vector2D targetVelocity);
        Vector2D AvoidWalls();
        void GenerateNode();
        void DrawNodes();
        void CheckSquare(Rectangle2D square);
        bool IsInClosedList(PathNode* pNode);
        bool IsInOpenList(PathNode* pNode);
        void setPlayer(Player* player);



private:
    double m_move;
    Vector2D m_Velocity;
    double m_life;
    Circle2D m_hitbox;
    Player* m_Pplayer;
    DelayedGrat* m_PDelayedGrat;
    World* m_World;
    std::vector<PathNode> nodeList;
    bool m_flipped;
    double m_Walktimer;
    bool m_busy;

    double m_Hurt;
    bool m_BHurt;
};

