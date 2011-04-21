#ifndef _WeaponLIST_H
#define _WeaponLIST_H



namespace iteam {

	class Weapon;
	class WeaponComponent;
	class WeaponListThumbnail;

	/*!
        class WeaponList

        Usage:

        You only need one of these per turn-based game as it will manage
        all firing from player turns for you.

        define a new Weapon by deriving a new class from Weapon and use the
        Add method below to include it in the available Weapons list.
    */

	class WeaponsList {
		public:
			WeaponsList();

			~WeaponsList();

			int SizeCount() { return NumberOfWeapons; }

			void Add(Weapon* a_Weapon);

			void UpdateWeaponThumbs(void);

			void DoWeaponBehaviours();

			int GetTriggerTime(const int CurrentWeapon);

			void IncrementTriggerTime(int WeaponID, const GLfloat a_Increment);
			void DecrementTriggerTime(int WeaponID, const GLfloat a_Increment);
			Weapon* AccessWeapon(int i) { return m_Weapons[i]; }

		private:
			vector <Weapon*> m_Weapons;
			vector <gp2d::Sprite *> m_WeaponThumbnails;
			GLfloat m_ThumbnailX, m_ThumbnailY;
			GLfloat m_ThumbWidth, m_ThumbHeight; // values are scalars not actual height and width
			GLfloat m_ThumbnailPadding;
			int NumberOfWeapons;
			GLfloat WeaponStrength;
			GLfloat WeaponAngle;
	};

	extern WeaponsList* iteamWeapons;

} // end namespace

#endif
