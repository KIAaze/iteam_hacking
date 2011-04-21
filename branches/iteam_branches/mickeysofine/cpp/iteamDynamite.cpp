#include "globals.h"
#include "iteamDynamite.h"

namespace iteam {



    iteamDynamite::iteamDynamite() : Weapon()
    {
        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */

        // Add one basic grenade component, you could add more if you need to
        // but this is a grenade so it only needs one
       Add(
	   IT_WT_DYNAMITE
	, "data/weapons/dynamite.png"
	, true
	, true
	, (GLfloat) IT_WT_GRENADE_BLAST_RADIUS
	, IT_WT_GRENADE_BLAST_FACTOR
	, IT_WT_GRENADE_BLAST_DAMAGE
	, (GLfloat) 0.1
	, 3
	, false
	, (GLfloat) 1
	);


    }

    void iteamDynamite::DoBehaviours(
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

    // NOTE:
    // 		You can delete this Fire() member function if you are only firing one component with an angle and velocity
    // 		This is because the code already exists as part of the base class 'Weapon', so there is no need to re-invent the wheel
    //  REMEBER:
    // 		If he above if true delete this AND the declaration from the class iteamDynamite.h

    int iteamDynamite::Fire(
      PlayerObj *a_Player
    , GLfloat nx
    , GLfloat ny
    , GLfloat new_angle
    , GLfloat new_vel
    , GLfloat a_TriggerTime
    )
    {
        //GLfloat l_GravityInPixels = m_PhysicsSystem->GetGravityInPixels();
        m_Player = a_Player;
        WeaponComponent* l_Component = component[0];
        l_Component->Fire(
                  nx
                , ny
                , 0
                , 0
                , a_TriggerTime
                );
        m_PhysicsSystem->AddObject(l_Component);
        m_Active = true;
        return(0);
    }

}
