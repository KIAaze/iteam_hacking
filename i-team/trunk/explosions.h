#ifndef IT_EXPLOSIONS_H
#define IT_EXPLOSIONS_H

namespace iteam {

#define EXPLOSION_FRAMES 16

	class explosion : public gp2d::Sprite	{
		public:
			bool Active;
			int CurrentFrame;
			unsigned int startTicks;
		public:
			int GetCurrentFrame ( void );
//			explosion();
//			~explosion();
	};
	void Init_Explosions ( void );
	void AddExplosion ( Texture* tex );
	void TriggerExplosion ( Texture* tex, GLfloat x, GLfloat y, GLfloat Blastradius=60.0 );
	void ProccessExplosions ( void );
	void DrawExplosions ( void );
	void CheckExplosionStatus ( void );
	extern map <int,iteam::explosion> ExplosionsList;
}

#endif
