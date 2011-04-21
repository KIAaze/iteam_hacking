#ifndef ITEAMGRENADE_H_INCLUDED
#define ITEAMGRENADE_H_INCLUDED

#include "Weapon.h"

namespace iteam {
 class iteamGrenade : public Weapon {
     public:
        iteamGrenade();

        void DoBehaviours(
          const int a_Collision = 0
        );

    protected:

 };


}

#endif // ITEAMGRENADE_H_INCLUDED
