#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

namespace iteam {

#define EXPLOSION_FRAMES 16

	class Explosion : public gp2d::Sprite	{
		public:
			bool Active;
			int CurrentFrame;
			unsigned int startTicks;
		public:
			int GetCurrentFrame ( void );
			Explosion();
			Explosion( const char texture[], int w=1, int h=1, GLfloat Blastradius=60.0 );
			Explosion( gp2d::Texture* tex, int w=1, int h=1, GLfloat Blastradius=60.0 );
//			~Explosion();
// 			int DoBehaviour();
	};
	void AddExplosion ( Texture* tex, GLfloat x, GLfloat y, GLfloat Blastradius=60.0 );
	void ProccessExplosions ( void );
	extern map <int,iteam::Explosion> ExplosionsList;

	//TODO: Put this as a virtual function in the class from which weapons will be derived. ;)
	int GenericDestroyTerrain(Sprite* a_Surf, GLfloat a_X, GLfloat a_Y, GLfloat a_BlastRadius, GLfloat a_Explosion_halo_width);
}

#endif
