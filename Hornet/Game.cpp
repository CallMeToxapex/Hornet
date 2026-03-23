

#include "Game.h"
#include "HtCamera.h"
#include "ObjectManager.h"
#include "Player.h"
#include "DelayedGrat.h"
#include "GameManager.h"
#include "Ogre.h"
void Game::StartOfProgram()
{
    HtMouse::instance.SetPointerVisiblity(false);
}

void Game::StartOfGame()
{

    
    
    m_pGameManager = new GameManager();
    m_pGameManager->Initialise();
    ObjectManager::instance.AddItem(m_pGameManager);

    DelayedGrat* pDelayedGrat = new DelayedGrat();
    pDelayedGrat->Initialise(Vector2D(300, 0));
    ObjectManager::instance.AddItem(pDelayedGrat);

    Player* pPlayer = new Player();
    pPlayer->Initialise(Vector2D(0, 0), pDelayedGrat, m_pGameManager->GetWorld());
    ObjectManager::instance.AddItem(pPlayer);

    Ogre* pOgre = new Ogre();
    pOgre->Initialise(m_pGameManager->GetWorld(), Vector2D(0,0), pDelayedGrat);
    pOgre->setPlayer(pPlayer);  
    ObjectManager::instance.AddItem(pOgre);


}

void Game::Update(double frametime)
{
    // All tiles are managed by ObjectManager, so they render automatically
    ObjectManager::instance.UpdateAll(frametime);
    ObjectManager::instance.ProcessCollisions();
    ObjectManager::instance.RenderAll();
    

#ifdef _DEBUG
    ObjectManager::instance.CycleDebugObject();
    ObjectManager::instance.RenderDebug();
#endif

    ObjectManager::instance.DeleteInactiveItems();
    HtGraphics::instance.Present();
}

void Game::OnSuspend() {}
void Game::OnResume() {}

void Game::EndOfGame()
{
    ObjectManager::instance.DeleteAllObjects();
}

void Game::EndOfProgram() {}