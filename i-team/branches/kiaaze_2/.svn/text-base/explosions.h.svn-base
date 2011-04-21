#ifndef IT_EXPLOSIONS_H
#define IT_EXPLOSIONS_H

namespace iteam {
	
	#define EXPLOSION_FRAMES 16
	
	class explosion : public gp2d::Sprite	{
		public:
			bool Active;
			int CurrentFrame;
			unsigned int startTicks;
			int GetCurrentFrame(void);
	};
	void Init_Explosions(void);
	void AddExplosion(const char texture[]);
	void TriggerExplosion(GLfloat x, GLfloat y);
	void ProccessExplosions(void);
	void DrawExplosions(void);
	void CheckExplosionStatus(void);
	extern vector <iteam::explosion> ExplosionsList;
}

#endif
