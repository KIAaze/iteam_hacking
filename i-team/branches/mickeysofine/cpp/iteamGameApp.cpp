#include "iteamGameApp.h"

namespace iteam {

    iteamGameApp::iteamGameApp()
    {

        m_PhysicsSystem = new PhysicsSystem();

        InitWeapons( m_PhysicsSystem );

        m_NumberOfPlayers = 2;
        m_GameType = ITEAMGAMEAPP_SINGLEPLAYER;
        m_RoundLenghtInSeconds = g_RoundLenght;
    }

    void iteamGameApp::CreateDefaultEnvironment(void)
    {
        // Setup the camera
        m_Cam.Create();

        // load the default level data
        gp2d::Sprite* l_LevelSprite= new gp2d::Sprite();

        l_LevelSprite->Load("data/levels/grassymt/terrain.png");
        l_LevelSprite->Move(VIEWPORT_WIDTH/2,VIEWPORT_HEIGHT-l_LevelSprite->height[0]/2);

        Level.push_back(l_LevelSprite);

        l_LevelSprite = new gp2d::Sprite();
        l_LevelSprite->Load("data/levels/grassymt/layer1.png");
        l_LevelSprite->width[0]=2048;
        l_LevelSprite->height[0]=1024;

        Level.push_back(l_LevelSprite);

        l_LevelSprite = new gp2d::Sprite();

        l_LevelSprite->Load("data/levels/grassymt/layer2.png");


        l_LevelSprite->ResizePropW(GameResW);
        Level.push_back(l_LevelSprite);
    }

    bool iteamGameApp::CreateDefaultEnvironment(char *GameEnvFilename)
    {
        bool ReturnVal = false;
        // load the environment file and parse the setting into temp vars

        return ReturnVal;
    }

    iteamGameApp::InitGameEnvironment(
      char *GameEnvFilename
    , int a_GameType
    , settings *a_iteamSettings
    )
    {
        // load the level data
        if("" == *GameEnvFilename) {
            CreateDefaultEnviroment();
        } else {
            if(!LoadEnvironment(GameEnvFilename))   {
              CreateDefaultEnviroment();
            }
        }
        // create player list according to what type of game it is
        m_GameType = a_iteamSettings->GetGameType();
        switch(m_GameType)  {
            case ITEAMSETTING_SINGLEPLAYER:
                AddPlayer(
                  ITEAMGAMEAPP_NORMAL_PLAYER
                , IT_PLAYER_SUSI
                , (int) rand_uniform(50,180)
                , 50
                , IT_PLAYER_FACE_RIGHT
                , 1
                );

                AddPlayer(
                  ITEAMGAMEAPP_AI_PLAYER
                , IT_PLAYER_SUSI
                , (int) rand_uniform(50,180)
                , 50
                , IT_PLAYER_FACE_RIGHT
                , 1
                );
                break;
            case ITEAMSETTING_SINGLEPLAYER:
                AddPlayer(
                  ITEAMGAMEAPP_NORMAL_PLAYER
                , IT_PLAYER_SUSI
                , (int) rand_uniform(50,180)
                , 50
                , IT_PLAYER_FACE_RIGHT
                , 1
                );

                AddPlayer(
                  ITEAMGAMEAPP_NORMAL_PLAYER
                , IT_PLAYER_SUSI
                , (int) rand_uniform(50,180)
                , 50
                , IT_PLAYER_FACE_LEFT
                , 1
                );
                break;
            default:
                break;
        }
    }

    void iteamGameApp::InitWeapons(
      PhysicsSystem *physics
    )
    {
        // Init weapons List
        m_WeaponList = new WeaponsList();

        // add weapons to the List
        iteamGrenade* l_Grenade = new iteamGrenade();

        l_Grenade->UsePhysicsSystem(physics);
        m_WeaponList->Add(l_Grenade);

        iteamMissile* l_Missile = new iteamMissile();
        l_Missile->UsePhysicsSystem(physics);
        m_WeaponList->Add(l_Missile);

        iteamClusterBomb* l_ClusterBomb = new iteamClusterBomb();
        l_ClusterBomb->UsePhysicsSystem(physics);
        m_WeaponList->Add(l_ClusterBomb);

        iteamDynamite* l_Dynamite = new iteamDynamite();
        l_Dynamite->UsePhysicsSystem(physics);
        m_WeaponList->Add(l_Dynamite);

    }

    iteamGameApp::GetUserInputs()
    {

    }

    iteamGameApp::Run()
    {
        GetUserInputs();
        DoBehaviours();
        DrawApp();
    }

    iteamGameApp::DrawApp()
    {

    }

    iteamGameApp::NextTurn()
    {
        // reset previous player
        PlayerObj* l_Player = m_Players[m_CurPlayerCounter];
        l_Player->CanMove = false;
        l_Player->CanJump = false;
        l_Player->setAnimationSpeed(0.0f);
        l_Player->Movement.walkingRight = false;
        l_Player->Movement.walkingLeft = false;
        l_Player->SetNotTimeToTakeMyTurn();
        // reset seconds counter
        m_NumberOfSecondsInRound = m_RoundLenghtInSeconds;
        // move to next player
        m_CurPlayerCounter++;
        if(m_CurPlayerCounter > m_NumberOfPlayers){
            m_CurPlayerCounter = 0;
        }

        l_Player = m_Players[m_CurPlayerCounter];
        l_Player->CanMove = true;
        l_Player->CanJump = true;
        l_Player->SetTimeToTakeMyTurn();
        // set the current player
        m_CurrentPlayer = l_Player;
    }


    void iteamGameApp::DoBehaviours()
    {
        // Weapons
        m_WeaponList->DoWeaponBehaviours();

        // Players Last

        vector <PlayerObj *>::iterator l_Player;
        for(l_Player = m_Players.begin(); l_Player != m_Players.end(); l_Player++)  {
            l_Player->DoBehaviours();
        }


    }

    void iteamGameApp::AddPlayer(
      int a_TypeOfPlayer
    , int PlayerID
    , GLfloat x
    , GLfloat y
    , bool Mirror2
    , GLfloat Scaling
    )
	{

        PlayerObj *l_tmpPlayer = 0;

        switch(a_TypeOfPlayer)    {
            case ITEAMGAMEAPP_NORMAL_PLAYER:
                PlayerObj *l_Player = new PlayerObj();
                l_tmpPlayer = l_Player;
                break;
            case ITEAMGAMEAPP_AI_PLAYER:
                AIPlayerObj *l_Player = new AIPlayerObj();
                l_tmpPlayer = l_Player;
                break;
        }

		switch(PlayerID) {
		    case  IT_PLAYER_SUSI:
                l_tmpPlayer->iterateSheets = true;
                l_tmpPlayer->setAnimationSpeed(0.0f);
                l_tmpPlayer->animationTimer.Start();
                strcpy(l_tmpPlayer->Name,"Susi");
                l_tmpPlayer->Load("data/chars/susi_film_1of2.png", 8, 1);
                l_tmpPlayer->Load("data/chars/susi_film_2of2.png", 4, 1);
                break;
            default:
                break;
		}
		l_tmpPlayer->Move(x,y);
		l_tmpPlayer->Mirror=Mirror2;
		l_tmpPlayer->Scale(Scaling);
		l_tmpPlayer->CanMove=false;
		l_tmpPlayer->CanJump=false;
		l_tmpPlayer->m_FireAngle=iRand(0,360);
		l_tmpPlayer->col_x[0]=(64/2)-10;
		l_tmpPlayer->col_y[0]=8;
		l_tmpPlayer->col_width[0]=20;
		l_tmpPlayer->col_height[0]=60-8;
		l_tmpPlayer->CurrentWeapon = 0;
		l_tmpPlayer->Elasticity = 0.3;
		l_tmpPlayer->SetNotTimeToTakeMyTurn();

        m_Players.push_back(l_tmpPlayer);
	}

	 iteamGameApp::~iteamGameApp()
    {

        vector <gp2d::Sprite *>::iterator l_Level;
        for(l_Level = m_Level.begin(); l_Level != m_Level.end(); l_Level++) {
            delete l_Level;
        }
        // destroy the player sprites
        vector <PlayerObj *>::iterator l_Player;
        for(l_Player = m_Players.begin(); l_Player != m_Players.end(); l_Player++)  {
            delete l_Player;
        }
        // destroy the game cam onject
        m_Cam.End();
        // destroy the physics system
        delete m_PhysicsSystem;



    }

}
