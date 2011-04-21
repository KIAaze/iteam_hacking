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

        void SetTemporary(void) { Temporary = true; }
        bool IsTemporary() { return Temporary; }

        void SetDirection(const GLfloat a_Angle) { Directional = true; Angle = a_Angle; }
        bool IsIsDirectional() { return Directional; }

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

        void AddObject(gp2d::Sprite* spr);

        void AddImpulse(PhysicalImpulse* a_Impulse);

        const int SizeCount() { return m_NumObjectsInSystem; }

        void ProcessAllPhysicalObjects();

        const GLfloat GetGravity() { return m_Gravity; }
        const GLfloat GetGravityInPixels() { return m_GravityInPixels; }
        void SetGravity(const GLfloat a_Gravity) { m_Gravity = a_Gravity; }
        void IncreaseGravityBy(const GLfloat a_Gravity) { m_Gravity += a_Gravity; }
        void DecreaseGravityBy(const GLfloat a_Gravity) { m_Gravity -= a_Gravity; }

        const GLfloat GetFriction() { return m_Friction; }
        void SetFriction(const GLfloat a_Friction) { m_Friction = a_Friction; }
        void IncreaseFrictionBy(const GLfloat a_Friction) { m_Friction += a_Friction; }
        void DecreaseFrictionBy(const GLfloat a_Friction) { m_Friction += a_Friction; }

        const GLfloat CalulateEnviromentXAcceleration();
        const GLfloat CalulateEnviromentYAcceleration();

        const GLfloat OneMeterInPixels() { return m_OneMeterInPixels; }
        void SetWind(GLfloat a_Wind) { m_Wind = a_Wind; m_WindInPixels = m_Wind * m_OneMeterInPixels; }
        GLfloat GetWind() { return m_Wind; }
        GLfloat GetWindInPixels() { return m_WindInPixels; }

        void RemoveOneObject();
        ~PhysicsSystem();
      private:
        int m_NumObjectsInSystem;
        int m_ImpulseCount;
        int m_LastTicks;
        GLfloat m_GravityInPixels;
        GLfloat m_OneMeterInPixels; // scale of a meter in game units (pixels)
        GLfloat m_Wind;
        GLfloat m_WindInPixels;
        GLfloat m_Gravity;
        GLfloat m_Friction;
        gp2d::Sprite* m_PhysicalObjects[PHYSIC_MAX_OBJECTS];
        PhysicalImpulse* m_EnviromentalForces[PHYSIC_MAX_OBJECTS];

    };

    extern PhysicsSystem* iteamPhysics;


}
#endif
