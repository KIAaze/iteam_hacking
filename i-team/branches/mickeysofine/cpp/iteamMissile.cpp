#include "globals.h"
#include "iteamMissile.h"

namespace iteam {



    iteamMissile::iteamMissile() : Weapon()
    {
        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */

        // Add one basic grenade component, you could add more if you need to
        // but this is a grenade so it only needs one
       Add(
	   IT_WT_MISSILE
	, "data/weapons/missile.png"
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

    void iteamMissile::DoBehaviours(
      const int collision // = 0
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
            if(l_Component->collision) {
            // yes ... Fire in the hole!
                l_Component->BlastObjects();
                l_Component->DestroyTerrain();
                l_Component->SetInactive();
                m_PhysicsSystem->RemoveOneObject();
                m_Active = false;
                m_Player->HasFired = false;
                l_Component->collision = false;
            } else {
                // Nope so update seconds counter above Weapon
                l_Component->orientate();
                sprintf(l_Component->AccessName(), "%d", 1 + (component[0]->GetTriggerTime() - l_Ticks) / 1000 );


            }
        }
    }

}
