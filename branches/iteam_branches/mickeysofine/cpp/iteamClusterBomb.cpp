#include "globals.h"
#include "iteamClusterBomb.h"
#include "iteam_maths.h"

namespace iteam {



    iteamClusterBomb::iteamClusterBomb() : Weapon()
    {
        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */
        m_ClusterSize = 5;
        // Add one basic grenade component, you could add more if you need to
        // but this is a grenade so it only needs one
       Add(
           IT_WT_CLUSTERBOMB
        , "data/weapons/cluster_bomb.png"
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

        // create the small components for the cluster bomb
        for(int i = 1; i < m_ClusterSize; i++)  {
            Add(
               IT_WT_CLUSTERBOMB
            , "data/weapons/cluster_bomb.png"
            , true
            , true
            , (GLfloat) IT_WT_GRENADE_BLAST_RADIUS * 0.5
            , IT_WT_GRENADE_BLAST_FACTOR
            , IT_WT_GRENADE_BLAST_DAMAGE
            , (GLfloat) 0.8
            , 3
            , false
            , (GLfloat) 0.75 // half the size of the main bomb
            );
        }

        m_ComponentToBeFired = 0;

    }

    void iteamClusterBomb::DoBehaviours(
      const int collision // = 0
    )
    {



        /*

        NOTE: here is an example of the basic setup of a grenade
              you should create your own graphics etc for these,
              but these settings will work if your just debugging

        */
        if(m_Active)  {
            WeaponComponent* l_Component =  component[0];
            int l_Ticks = Timer[0].GetTicks() - l_Component->GetStartTicks();
    // is it time to explode yet?

            if(ComponentTriggered(l_Component)) {
            // yes ... Fire in the hole!
                m_ComponentToBeFired++;
                FireCluster(
                  l_Component->GetX()
                , l_Component->GetY()
                , l_Component->GetTriggerTime()
                );

            } else {
                // Nope so update seconds counter above Weapon

                sprintf(l_Component->AccessName(), "%d", 1 + (component[0]->GetTriggerTime() - l_Ticks) / 1000 );
                if( m_ComponentToBeFired > 0 )  {
                    DoClusterBehaviours();
                }
            }
        }
    }

    // NOTE:
    // 		You can delete this Fire() member function if you are only firing one component with an angle and velocity
    // 		This is because the code already exists as part of the base class 'Weapon', so there is no need to re-invent the wheel
    //  REMEBER:
    // 		If he above if true delete this AND the declaration from the class iteamClusterBomb.h

    int iteamClusterBomb::Fire(
      PlayerObj *a_Player
    , GLfloat nx
    , GLfloat ny
    , GLfloat new_angle
    , GLfloat new_vel
    , GLfloat a_TriggerTime
    )
    {

        m_Player = a_Player;

        WeaponComponent* l_Component = component[ 0 ];

        l_Component->Fire(
                  nx
                , ny
                , new_angle
                , new_vel
                , a_TriggerTime
                );
        l_Component->SetActive();
        m_PhysicsSystem->AddObject(l_Component);
        m_Active = true;

        return(0);
    }

    GLfloat iteamClusterBomb::RandomAngle()
    {
        return rand_uniform(30, 150);
    }

    GLfloat iteamClusterBomb::RandomVelocity()
    {
        return rand_uniform(4, 10) * m_PhysicsSystem->OneMeterInPixels();
    }

    void iteamClusterBomb::FireCluster(
      GLfloat a_OriginX
    , GLfloat a_OriginY
    , GLfloat a_TriggerTime
    )
    {
        for(int i = 1; i < m_ClusterSize; i++)  {
            WeaponComponent* l_Component = component[i];
            l_Component->Fire(
                  a_OriginX
                , a_OriginY
                , RandomAngle()
                , RandomVelocity()
                , a_TriggerTime / 1000
                );
            m_ComponentToBeFired++;
            l_Component->SetActive();
            m_PhysicsSystem->AddObject(l_Component);
        }
    }

    void iteamClusterBomb::DoClusterBehaviours()
    {
        for(int i = 1; i < m_ClusterSize; i++)  {
            WeaponComponent* l_Component = component[i];
            if(ComponentTriggered(l_Component)) {
                m_ComponentToBeFired--;
                l_Component->SetInactive();
                if(m_ComponentToBeFired == 1)   {
                    m_Active = false;
                    m_Player->HasFired = false;
                    m_ComponentToBeFired = 0;
                }

            }
        }
    }


}
