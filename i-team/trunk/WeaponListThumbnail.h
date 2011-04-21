#ifndef _WEAPONLISTTHUMBNAIL_H
#define _WEAPONLISTTHUMBNAIL_H

#include "globals.h"

namespace iteam {

	/*!
	    Class WeaponListThumbnail

	    Usage:

	    Used to maintin a list and display of available weapons during game
	    play.

	    The controller class is WeaponList which manages the placement and
	    rotation of the icons/thumbnails during the game

	*/

	class WeaponListThumbnail : public gp2d::Sprite {
		public:
			WeaponListThumbnail();
			virtual void DoBehaviours();
			void MoveTo ( GLfloat a_X, GLfloat a_Y );
			void SetID ( int a_ID ) { m_ID = a_ID; }
			int GetID() { return m_ID; }
		protected:
			bool m_ReachedTarget; // have we moved to the correct place yet?
			int m_StartTicks;
			int m_LastTicks;
			int m_ID;
			GLfloat m_DestinationX, m_DestinationY;
	};

}

#endif
