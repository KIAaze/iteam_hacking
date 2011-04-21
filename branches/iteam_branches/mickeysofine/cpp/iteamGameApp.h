#ifndef ITEAMGAMEAPP_H_INCLUDED
#define ITEAMGAMEAPP_H_INCLUDED

#include "globals.h"
#include "WeaponsList.h"
#include "physics.h"
#include "players.h"
#include "explosions.h"


#include <vector>


namespace iteam {

    const int g_RoundLenght = 60;

    enum {
      ITEAMGAMEAPP_NORMAL_PLAYER
    , ITEAMGAMEAPP_AI_PLAYER
    };
    /*!
        class iteamGameApp

        Usage:

        One class to bring them all and in the darkness bind them!

        ... er ... this does all the loading and running of the ingame
        part of the application.
    */
    class iteamGameApp {
        public:
            iteamGameApp();
            ~iteamGameApp();

            void CreateDefaultEnvironment(void);

            InitGameEnvironment(
              char *GameEnvFilename
            , int a_GameType
            , settings &iteamSettings
            );

            void AddPlayer(
              int a_TypeOfPlayer
            , int PlayerID
            , GLfloat x
            , GLfloat y
            , bool Mirror2
            , GLfloat Scaling
            );


            void DoIteamBehaviours();

            void Run();
            PlayerObj* AccessCurrentPlayer() { return m_CurrentPlayer; }
        protected:
            // FUNCTIONS
            void InitWeapons(
              PhysicsSystem *physics
            );

            GetUserInputs();
            DrawApp();

            // VARIABLES
            WeaponsList* m_WeaponList;
            PhysicsSystem* m_PhysicsSystem;
            Explosions* m_Explosions;
            vector <PlayerObj *> m_Players;
            PlayerObj* m_CurrentPlayer;
            int m_NumberOfPlayers;
            vector <gp2d::Sprite *> m_Level;
            vector <gp2d::Sprite *> m_InGameGUI;
            vector <gp2d::Font *>   m_Font;
            vector <gp2d::Timer>  m_Timer;
            vector <gp2d::Sound *>  m_Audio;
            vector <gp2d::Music *>  m_Song;
            gp2d::Camera m_Cam;

            int m_RoundLenghtInSeconds;
            int m_NumberOfSecondsInRound;
            int m_GameType;
    }

}
#endif // ITEAM_H_INCLUDED
