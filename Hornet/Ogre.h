#pragma once
#include "GameObject.h"
#include "Player.h"
#include "World.h"


class PathNode
{

public:
    Vector2D position;

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
        void Update(double frametime) override;
        void Initialise(World* pWorld);
        void ProcessCollision(GameObject& other) override;
        void setPos(Vector2D pos);
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
        void setPlayer(Player* player);



private:
    double m_move;
    Vector2D m_Velocity;
    double m_life;
    Circle2D m_hitbox;
    Player* m_Pplayer;
    World* m_World;
    std::vector<PathNode> nodeList;
};

