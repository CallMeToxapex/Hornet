#pragma once
#include "GameObject.h"
#include "World.h"



class GameManager :
    public GameObject
{
private:
    World m_theWorld;

public:
    GameManager();
    World* GetWorld() { return &m_theWorld; }
    ~GameManager();
    void Initialise();
    void Update(double frametime) override;
    void Render() override;

};
