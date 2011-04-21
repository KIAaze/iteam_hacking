/*! \file iteam_maths.h
\brief Mathematical functions

various maths & pysics functions
*/

#ifndef IT_MATH_H
#define IT_MATH_H
#include "globals.h"
#include <cmath>

#define PI 3.14159265

/*! \brief Converts degrees to radians. */
GLfloat deg2rad ( GLfloat a_deg );

/*! \brief Converts radians to degrees. */
GLfloat rad2deg ( GLfloat a_rad );

/*! \brief Makes sure the angle stays in [0;360[. */
GLfloat limit_angle ( GLfloat angle );

/*! \brief Initialize random seed. */
void init_rand();

/*! \brief Returns a random number between min and max using a uniform distribution. Originally created to add an error to the shots calculated by the AI.*/
GLfloat rand_uniform ( GLfloat min, GLfloat max );

/*! \brief Calculates the "reflection" vec(Vp) of the velocity vector vec(V) on the slope vec(T). Returns 0 if vec(T)=0.*/
int T_reflect_vector ( double Tx, double Ty, double Vx, double Vy, GLfloat &Vpx, GLfloat &Vpy );

/*! \brief Calculates the "reflection" vec(Vp) of the velocity vector vec(V) on the normal vec(N). Returns 0 if vec(N)=0.*/
int N_reflect_vector ( double Nx, double Ny, double Vx, double Vy, GLfloat &Vpx, GLfloat &Vpy );

bool NormalReflectVector ( const GLfloat a_Nx, const GLfloat a_Ny, gp2d::Sprite* spr );

/*! \brief Returns the distance between two 2d points (x1,y1) and (x2,y2).*/
GLfloat DistanceBetween ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );

/*! \brief Returns the angle between two 2d vectors (x1,y1) and (x2,y2).*/
GLfloat AngleBetweenObjects ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) ;

#endif
