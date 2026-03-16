#include <vector>
#include "Shapes.h"
#include"GameObject.h"


#pragma once
class World : public GameObject
{
public:
    std::vector<Rectangle2D> buildings;

    World();

    // Some basic code to set up the world. Hard coded.
    void Setup();

    // Draws the world
    void Draw() const;

    // returns true if there is a line of sight from from to to
    bool LineOfSight(Vector2D from, Vector2D to) const;

    // returns true if the specified position is inside a building
    bool Collides(Vector2D position) const;

    // returns true if the specified shape is inside a building
    bool Collides(IShape2D& shape) const;

    // If the shape collides with a building, returns a vector pointing away from the building.
    // The size of the vector is larger, the more the overlap (0=minimal overal   1=circle is half inside the building)
    // If the shape does not collide, returns a (0,0) vector
    Vector2D CollisionNormal(Circle2D& area) const;
};

