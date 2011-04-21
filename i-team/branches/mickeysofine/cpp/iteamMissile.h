#ifndef ITEAMWEAPONNAME_H_INCLUDED
#define ITEAMWEAPONNAME_H_INCLUDED

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
//          iteamMissile* MyWeapon = new iteamMissile;
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
 class iteamMissile : public Weapon {
     public:
        iteamMissile();

        void DoBehaviours(
          const int collision = 0
        );
 };


}

#endif // ITEAMWEAPONNAME_H_INCLUDED
