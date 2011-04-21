/*! \file iteam_maths.cpp
\brief Mathematical functions

various maths & pysics functions
*/

#include "iteam_maths.h"
#include <iostream>
#include <cmath>

GLfloat deg2rad ( GLfloat a_deg ) {
	return ( a_deg*M_PI/180. );
}

GLfloat rad2deg ( GLfloat a_rad ) {
	return ( a_rad*180./M_PI );
}

GLfloat limit_angle ( GLfloat angle ) {
	while ( angle>=360 ) angle-=360.0;
	while ( angle<0 ) angle+=360.0;
	return ( angle );
}

void init_rand() {
	srand ( time ( NULL ) );
}

GLfloat rand_uniform ( GLfloat min, GLfloat max ) {
	return ( min+ ( max-min ) *rand() / ( GLfloat ) RAND_MAX );
}

int T_reflect_vector ( double Tx, double Ty, double Vx, double Vy, GLfloat &Vpx, GLfloat &Vpy ) {
	Vpx=0;Vpy=0;//default values
	double denom=Tx*Tx+Ty*Ty;
	if ( denom==0 ) return ( 0 );
	double k= ( Tx*Vx+Ty*Vy ) /denom;
	Vpx=2*k*Tx-Vx;
	Vpy=2*k*Ty-Vy;
	return ( 1 );
}

int N_reflect_vector ( double Nx, double Ny, double Vx, double Vy, GLfloat &Vpx, GLfloat &Vpy ) {
	Vpx=0;Vpy=0;//default values
	double denom=Nx*Nx+Ny*Ny;
	if ( denom==0 ) return ( 0 );
	double k=- ( Nx*Vx+Ny*Vy ) /denom;
	Vpx=2*k*Nx+Vx;
	Vpy=2*k*Ny+Vy;
	return ( 1 );
}

bool NormalReflectVector ( const GLfloat a_Nx, const GLfloat a_Ny, gp2d::Sprite* spr ) {
	GLfloat l_Vx = spr->GetVX();
	GLfloat l_Vy = spr->GetVY();

	GLfloat l_Denominator=a_Nx*a_Nx + a_Ny*a_Ny;
	if ( l_Denominator == 0 ) {
		return(false);//the normal vector is a zero vector. We can't use it.
	}
	double l_k= - ( a_Nx*l_Vx + a_Ny*l_Vy ) / l_Denominator;
	spr->SetVX ( 2 * l_k * a_Nx + l_Vx );
	spr->SetVY ( 2 * l_k * a_Ny + l_Vy );

	return ( true );
}

GLfloat DistanceBetween ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) 	{
	GLfloat x_lenght, y_lenght;
	x_lenght = x2 - x1;
	y_lenght = y2 - y1;
	return sqrt ( ( x_lenght * x_lenght ) + ( y_lenght * y_lenght ) );
}

GLfloat AngleBetweenObjects ( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) 	{


	GLfloat angle;
	angle=limit_angle ( rad2deg ( -atan2 ( y2-y1,x2-x1 ) ) );//-atan2 because of the current iteam standard angle
	cout << "angle = " << angle << endl;
	return angle;
}
