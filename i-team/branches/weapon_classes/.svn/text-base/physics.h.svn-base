/*! \file physics.h
\brief Physics engine

Used to process movement of physical objects.
*/

#ifndef IT_PHYSICS_H
#define IT_PHYSICS_H

#include "library_h/gp2d.h"
#include <vector>

using namespace gp2d;
using namespace std;

namespace iteam {
	// a character is define as 2 meters high which means
	// each character is about 54px so 1m = 27 pixels
	// real gravity is 9.81m per second or 9.81 * 27 pixels per second = 265px (rounded up)

#define MetersToPixels(m) (int)(m * 27)
#define PixelsToMeters(p) (p / 27)
#define PS_GRAVITY 265
#define PS_SUBDEVIDE_VALUE 3
#define PHYSIC_MAX_OBJECTS 256

	class PhysicalImpulse {
		public:
			PhysicalImpulse();

			void SetTemporary ( void ) { Temporary = true; }
			bool IsTemporary() { return Temporary; }

			void SetDirection ( const GLfloat a_Angle ) { Directional = true; Angle = a_Angle; }
			bool IsDirectional() { return Directional; }

		private:
			GLfloat x;
			GLfloat y;
			GLfloat Range;
			GLfloat Angle;
			bool Temporary;
			bool Directional;
	};

	class PhysicsSystem {
		public:
			PhysicsSystem();

			int Reset();
			int Step();

			int AddObject ( gp2d::Sprite* spr );
			void RemoveObject(int id);

			void AddImpulse ( PhysicalImpulse* a_Impulse );

			const int SizeCount() { return m_NumObjectsInSystem; }

			void ProcessAllPhysicalObjects();
			int UpdateObject(Sprite* a_obj);

			const GLfloat GetGravity() { return m_Gravity; }
			const GLfloat GetGravityInPixels() { return m_GravityInPixels; }
			void SetGravity ( const GLfloat a_Gravity ) { m_Gravity = a_Gravity; }
			void IncreaseGravityBy ( const GLfloat a_Gravity ) { m_Gravity += a_Gravity; }
			void DecreaseGravityBy ( const GLfloat a_Gravity ) { m_Gravity -= a_Gravity; }

			const GLfloat GetFriction() { return m_Friction; }
			void SetFriction ( const GLfloat a_Friction ) { m_Friction = a_Friction; }
			void IncreaseFrictionBy ( const GLfloat a_Friction ) { m_Friction += a_Friction; }
			void DecreaseFrictionBy ( const GLfloat a_Friction ) { m_Friction += a_Friction; }

			const GLfloat CalulateEnvironmentXAcceleration();
			const GLfloat CalulateEnvironmentYAcceleration();

			const GLfloat OneMeterInPixels() { return m_OneMeterInPixels; }
			void SetWind ( GLfloat a_Wind ) { m_Wind = a_Wind; m_WindInPixels = m_Wind * m_OneMeterInPixels; }
			GLfloat GetWind() { return m_Wind; }
			GLfloat GetWindInPixels() { return m_WindInPixels; }

			~PhysicsSystem();
		private:
			int m_ImpulseCount;
			int m_LastTicks;
			int m_DeltaTime;

			GLfloat m_OneMeterInPixels; // scale of a meter in game units (pixels) [ 27 pixels in this implementation but might be different in other games]
			GLfloat m_Wind;
			GLfloat m_WindInPixels;
			GLfloat m_Gravity;// actual gravity times 2 (it seems faster than normal gravity somehow
			GLfloat m_GravityInPixels; // establish the actual game units measurements
			GLfloat m_Friction;

			int m_NumObjectsInSystem;
// 			gp2d::Sprite* m_PhysicalObjects[PHYSIC_MAX_OBJECTS];
			map <int,gp2d::Sprite*> m_PhysicalObjects;

			PhysicalImpulse* m_EnvironmentalForces[PHYSIC_MAX_OBJECTS];

	};

	extern PhysicsSystem* iteamPhysics;

}

#endif
