#include "World.h"
#include "HtGraphics.h"

World::World() : GameObject(ObjectType::WALL)
{
}

void World::Setup()
    {
    buildings.clear();
    Rectangle2D box;

    // Edge bars
    box.PlaceAt(830, -1400, 820, 1400);
    buildings.push_back(box);
    box.PlaceAt(-820, -1400, -830, 1400);
    buildings.push_back(box);

    // Centre boxes
    box.PlaceAt(470, -200, 430, 200);
    buildings.push_back(box);
    box.PlaceAt(-430, -200, -470, 200);
    buildings.push_back(box);
    box.PlaceAt(200, -370, -200, -330);
    buildings.push_back(box);
    box.PlaceAt(200, 330, -200, 370);
    buildings.push_back(box);

    // L-shape
    box.PlaceAt(200, 975, -450, 1000);
    buildings.push_back(box);
    box.PlaceAt(-450, 725, -475, 1000);
    buildings.push_back(box);
    box.PlaceAt(450, -1000, -200, -975);
    buildings.push_back(box);
    box.PlaceAt(475, -1000, 450, -725);
    buildings.push_back(box);

    // Last lines
    box.PlaceAt(462, 700, 438, 1400);
    buildings.push_back(box);
    box.PlaceAt(-438, -1400, -462, -700);
    buildings.push_back(box);
    }


void World::Draw() const
{
    const int BASERADIUS = 20;
    for (const Rectangle2D& box : buildings)
    {
        HtGraphics::instance.FillRect(box, HtGraphics::WHITE);
    }

   
}

bool World::LineOfSight(Vector2D from, Vector2D to) const
{
    Segment2D line;
    line.PlaceAt(from, to);
    for (const Rectangle2D& box : buildings)
    {
        if (box.Intersects(line))
            return false;
    }
    return true;
}

bool World::Collides(Vector2D position) const
{
    for (const Rectangle2D& box : buildings)
    {
        if (box.Intersects(position))
            return false;
    }
    return true;
}

bool World::Collides(IShape2D& shape) const
{
    for (const Rectangle2D& box : buildings)
    {
        if (box.Intersects(shape))
            return true;
    }
    return false;
}

Vector2D World::CollisionNormal(Circle2D& area) const
{
    for (const Rectangle2D& box : buildings)
    {
        if (box.Intersects(area))
        {
            Vector2D normal = area.GetCentre() - box.Intersection(area);
            if (box.Intersects(area.GetCentre()))
            {
                normal = -normal;
            }
            double overlap = area.GetRadius() - normal.magnitude();
            double  severity = overlap / area.GetRadius();
            normal = normal.unitVector() * severity;

            return normal;
        }
    }
    return Vector2D(0, 0);
}
