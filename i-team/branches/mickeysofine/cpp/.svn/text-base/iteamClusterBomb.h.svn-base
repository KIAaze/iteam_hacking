#ifndef iteamClusterBomb_H_INCLUDED
#define iteamClusterBomb_H_INCLUDED

#include "Weapon.h"
//=================================================================================
// Usage:
//
//     1. Copy this and the cpp file that goes with it
//     2. Rename the copies to the name of your new class
//     3. Add the newly created class to the weapons system
//        by adding the header at the top of weapons.cpp
//     4. declare the object as a new * to you weapon type
//        like so:
//          iteamClusterBomb* MyWeapon = new iteamClusterBomb;
//     5. add it to the WeaponList 'iteamWeapons', (look in InitWeapons()
//        for the grenade example).
//
//---------------------------------------------------------------------------------
//
//      That should be enough to include yo9ur weapon into the game,
//      but you must write the code of what happens in the virtual
//      functions.
//
// NOTE: Please keep to the convension of naming weapon classes iteam<ClassName>
//       e.g. iteamFooBar or iteamBigBangBaby
//
//       This will make it easy for us to see any weapons apart from the othe
//       modules.
//
//=================================================================================
namespace iteam {
     class WeaponComponent;

     class iteamClusterBomb : public Weapon {
         public:
            iteamClusterBomb();

            void DoBehaviours(
              const int collision = 0
            );

        // Not needed if your only firing one basic component that with have an angle and velocity
            // so delete if you dont need it as the base class Weapon implements that already
            virtual int Fire(
              PlayerObj *a_Player
            , GLfloat nx
            , GLfloat ny
            , GLfloat new_angle
            , GLfloat new_vel
            , GLfloat a_TriggerTime
            );

            GLfloat RandomAngle();
            GLfloat RandomVelocity();

            void FireCluster(
              GLfloat a_OriginX
            , GLfloat a_OriginY
            , GLfloat a_TriggerTime
            );

            void DoClusterBehaviours();


        protected:
            int m_ComponentToBeFired;
            int m_ClusterSize;
     };


}

#endif // ITEAMWEAPONNAME_H_INCLUDED
