#include "globals.h"
#include "Weapon.h"
#include "WeaponsList.h"
#include "WeaponComponent.h"

namespace iteam {


    // =======================================================================================================
	//
	// ======================================= Weapons list class ============================================
	//
	// =======================================================================================================



	WeaponsList::WeaponsList()
	{
		WeaponStrength = 500;
		WeaponAngle = 90;
		NumberOfWeapons = 0;

	}

	WeaponsList::~WeaponsList()
	{
		for(int i=0; i < NumberOfWeapons; i++)  {
			delete m_Weapons[i];
		}

	}



	void WeaponsList::UpdateWeaponThumbs(void)	{
		int i;

		/*for(i=0; i < NumberOfWeapons; i++)	{
		    Cam.Begin();
		    m_Weapons[i]->Move(
		      Cam.GetX() + - (VIEWPORT_WIDTH/2) + m_Weapons[i]->GetOffsetX()
		    , Cam.GetY() - (VIEWPORT_HEIGHT/2) + m_Weapons[i]->GetOffsetY()
		    );
		    m_Weapons[i]->Draw();
		}*/
	}

	void WeaponsList::Add(
	Weapon* a_Weapon
	)
	{
		// add this Weapon to the cluster


		a_Weapon->SetID(NumberOfWeapons);
		m_Weapons.push_back(a_Weapon);
		NumberOfWeapons++;


	}


	//use of this function unclear
	//FireWeapon might enough


	int WeaponsList::GetTriggerTime(
	const int CurrentWeapon
	)
	{
		int l_TriggerTime;
		for(int i=0; i < NumberOfWeapons; i++)  {
		    if(m_Weapons[i]->GetID() == CurrentWeapon) {
			l_TriggerTime = m_Weapons[i]->GetTriggerTime();
		    }
		}
		return l_TriggerTime;
	}

	void WeaponsList::IncrementTriggerTime(
	  int WeaponID
	, const GLfloat a_Increment
	)
	{
		int l_TriggerTime;
		for(int i = 0; i < NumberOfWeapons; i++)    {
		    if(WeaponID == m_Weapons[i]->GetID())   {
			m_Weapons[i]->IncrementTriggerTime(a_Increment);
		    }
		}
	}

	void WeaponsList::DecrementTriggerTime(
	  int WeaponID
	, const GLfloat a_Increment
	)
	{
		int l_TriggerTime;
		for(int i = 0; i < NumberOfWeapons; i++)    {
		    if(WeaponID == m_Weapons[i]->GetID())   {
			m_Weapons[i]->DecrementTriggerTime(a_Increment);
		    }
		}
	}

	void WeaponsList::DoWeaponBehaviours()
	{
	    Weapon* l_Weapon = 0;
        for(int i = 0; i < m_Weapons.size(); i++)   {
            l_Weapon = m_Weapons[i];
            if(l_Weapon->IsActive())  {
                    l_Weapon->DoBehaviours();
            }
        }
	}

} // end of namespace
