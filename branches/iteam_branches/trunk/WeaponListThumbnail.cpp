#include "WeaponListThumbnail.h"

namespace iteam {
	WeaponListThumbnail::WeaponListThumbnail() {
		m_ReachedTarget = true; // have we moved to the correct place yet?
		int m_StartTicks = 0;
		int m_LastTicks = 0;
		int m_ID = 0;
	}

	void WeaponListThumbnail::DoBehaviours() {

		// move the thumbnail into position
		SetX ( CurveValueGLf ( m_DestinationX, GetX(), 5.0f ) );
		SetY ( CurveValueGLf ( m_DestinationY, GetY(), 5.0f ) );


	}


	void WeaponListThumbnail::MoveTo (
	    GLfloat a_X
	    , GLfloat a_Y
	) {
		m_DestinationX = a_X;
		m_DestinationY = a_Y;
	}

}
