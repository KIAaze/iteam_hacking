#include "globals.h"
#include "Weapon.h"
#include "iteamGrenade.h"

namespace iteam {



    iteamGrenade::iteamGrenade()
    {
        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */
        Add(
			  IT_WT_GRENADE
			, "data/weapons/grenade.png"
			, true
			, true
			, (GLfloat) IT_WT_GRENADE_BLAST_RADIUS
			, IT_WT_GRENADE_BLAST_FACTOR
			, IT_WT_GRENADE_BLAST_DAMAGE
			, (GLfloat) 0.8
			, 3
			, false
			, (GLfloat) 1
		);


    }

    void iteamGrenade::DoBehaviours(
      const int a_Collision // = 0
    )
    {
        WeaponComponent* l_Component =  component[0];
        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */
        if(m_Active)  {
            int l_Ticks = Timer[0].GetTicks() - l_Component->GetStartTicks();
        // is it time to explode yet?
            if(l_Ticks > l_Component->GetTriggerTime()) {
            // yes ... Fire in the hole!
                l_Component->BlastObjects();
                l_Component->DestroyTerrain();
                l_Component->SetInactive();
                m_PhysicsSystem->RemoveOneObject();
                m_Active = false;
                m_Player->HasFired = false;
            } else {
                // Nope so update seconds counter above Weapon

                sprintf(l_Component->AccessName(), "%d", 1 + (component[0]->GetTriggerTime() - l_Ticks) / 1000 );


            }
        }
    }

    // What no Fire?
    //
    // we dont need a fire function as weapon has a basic fire that fire component[0]
    // so we dont need to duplicate code!


}
