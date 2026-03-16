#include "GameManager.h"
#include "HtCamera.h"
#include "Game.h"
#include "ObjectManager.h"


GameManager::GameManager() {}


GameManager::~GameManager()
{
}

void GameManager::Initialise()
{


    // Spawn world

    //World* TheWorld;
    //TheWorld->Setup();
    //TheWorld->SetCollidable(
    
    m_theWorld.Setup();
    m_theWorld.SetCollidable();  // make sure it's marked collidable
  //  ObjectManager::instance.AddItem(&m_theWorld);


}

void GameManager::Update(double frametime)
{
}

void GameManager::Render()
{
    m_theWorld.Draw();
}

