/*! \file iteam-ai.h
\brief AI functions

Contains functions essential for the AI.
*/
/***************************************************************************
 *            iteam-ai.h
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef IT_AI_H
#define IT_AI_H

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#ifdef _WIN32
#include "../../gamepower/GP2D/trunk/lib/gp2d.h"
#else
#include "library_h/gp2d.h"
#endif
#include "players.h"
#include "WeaponsList.h"
#include "physics.h"

using std::cout;
using std::endl;

namespace iteam {

	#define IT_AI_OK 1
	#define IT_AI_GIVEUP 2

    class AIPlayerObj : public PlayerObj {
        public:
            AIPlayerObj();

            /*! \brief calculates velocity+flighttime for a given angle

            returns true if shot possible, else false
            Can also return negative speeds when necessary. ;)
            Also works with negative gravity :D
            */
            bool CalculateVelocity(
              double angle_deg
            , GLfloat &StartVelocity
            , GLfloat &time
            , double gravity
            , double player_x
            , double player_y
            , double target_x
            , double target_y
            );

            /*! \brief calculates angle+flighttime for a given velocity

            returns true if shot possible, else false
            There are 2 possible (angle,time) pairs for a given speed
            works with negative speeds too
            */
            bool CalculateAngle(
              double StartVelocity
            , GLfloat &angle_deg1
            , GLfloat &time1
            , GLfloat &angle_deg2
            , GLfloat &time2
            , double gravity
            , double player_x
            , double player_y
            , double target_x
            , double target_y
            );

            /*! \brief calculates velocity+angle for a given flighttime (useful for bombs)

            returns true if shot possible, else false
            works with negative flighttimes too because it is equivalent to -vector(v0)
            */
            bool CalculateVector(
              double time
            , GLfloat &angle_deg
            , GLfloat &StartVelocity
            , double gravity
            , double player_x
            , double player_y
            , double target_x
            , double target_y
            );

            /*! \brief finds the highest point between the player and the target

            return the height in pixels
            */
            GLfloat GetMaxHeightOfObstacle();

            /*! \brief performs the logical steps of Weapon selection, weapons setup and firing

            returns false if the AI concludes it cant take the shot by any available Weapon, else true
            */
            int TakeTurn();

            /*! \brief identify the nearest enemy player

            returns the integer number of the enemy player in the Players[] array
            */
            bool FindNearestEnemy();

            /*! \brief moves player to a new destination if the current one is not good for shot

            returns nothing
            */
            void MovePlayer();

            /*! \brief works out whta is the best position to use the current weapon from

            returns nothing
            */
            void EstablistBestPosition();

            /*! \brief chooses a Weapon if current is not suitable

            returns nothing
            */
            bool ChooseWeapon();

            virtual void DoBehaviours();
            void SetLevel(gp2d::Sprite* a_Level)    { m_Level = a_Level; }

            void UsePlayerList(vector <PlayerObj *> *a_PlayerList) { m_PlayerList = a_PlayerList; }
            void UseWeaponsList(WeaponsList* a_WeaponsList) { m_WeaponsList = a_WeaponsList; }
            void UsePhysicsSystem(PhysicsSystem* a_PhysicsSystem) { m_PhysicsSystem = a_PhysicsSystem; }

            GLfloat DistanceToPlayer(PlayerObj* a_Player);

            SDL_Surface* AccessLevelData() { return m_Level->animationSheet[0]->spriteTexture.imgF; }

            GLfloat CalculateFirePowerX();
            GLfloat CalculateFirePowerY();
            void CalculateFireTime();
            void SetupThrowingValues();

        protected:
            PlayerObj* a_EnemyPlayer;
            gp2d::Sprite* m_Level;
            WeaponsList* m_WeaponsList;
            PhysicsSystem* m_PhysicsSystem;
            vector <PlayerObj *> *m_PlayerList;
            PlayerObj* m_EnemyPlayer;
            bool m_TargetAquired;
            bool m_WeaponChosen;
            bool m_MaxHeightCalculated;
            bool m_InPosition;
            int m_ThinkingTime;
            GLfloat m_WeaponETA;
            GLfloat m_DistanceToEnemy;
            GLfloat m_ObstacleHeight;
            GLfloat m_DestinationX, m_DestinationY;
    };

    void AddAIPlayer(int PlayerID, GLfloat x, GLfloat y, bool Mirror2, GLfloat Scaling);
}

#endif
