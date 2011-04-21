#include "globals.h"
// ====================== GLOBALS =============================

namespace iteam	{
	
vector <iteam::IT_Weapon> WeaponsList;

GLfloat WeaponStrenght = 500.0;
GLfloat WeaponAngle = 90;
// ====================== WEAPONS =============================

weapon::weapon()	{
	// initialise the weapon
}

void weapon::SetBeginPosition(GLfloat nx, GLfloat ny )	{
	x = nx;
	y = ny;
	accel_x = 0;
	accel_y = 0;
	//angle = new_angle;
	//cout << "[WEAPONS COORDS] x = " << x << " y = " << y << " angle = " << angle << "\n";
}

void weapon::SetAcceleration(GLfloat new_accel, GLfloat new_angle)	{
	// apply a force for to the accelleration of the 
	GLfloat wrap_test;
	acceleration = new_accel;
	wrap_test = fire_angle + new_angle;
	// seeing as floats can go greater than 
	if(wrap_test > 360) {	// does the adding of these two angle wrap over 360 then turn is back within a 360 range value
		fire_angle = (fire_angle + new_angle) - 360;
	}
	if(wrap_test < 0)	{ 	// does if go less than 1? then turn it positive again
		fire_angle = (fire_angle + new_angle) + 360;
	}
	accel_x = acceleration * (GLfloat) cos(new_angle*M_PI/180);
	accel_y = acceleration * (GLfloat) sin(new_angle*PI/180) * -1;
	//cout << "accel_x = " << accel_x << "\n";
	//cout << "accel_y = " << accel_y << "\n";
	//cout << "angle = " << new_angle << "\n";
	vel_x = 0; vel_y = 0;
}

void weapon::CaclulateVelocity(void)	{
	
	vel_x += accel_x;
	vel_y += accel_y;
	/*
	cout << "====================== Calculate Velocity ====================\n";
	
	cout << "Velocity X = " << vel_x << "\n";
	cout << "Velocity Y = " << vel_y << "\n";
	cout << "accel_x = " << accel_x << "\n";
	cout << "accel_y = " << accel_y << "\n";
	
	cout << "====================== END  ============================\n";
	*/
	accel_x = 0;
	accel_y = 0;
	accel_y += IT_GRAVITY;
	//this->accel_x += IT_FRICTION;
}

void weapon::MoveMe(void)	{
	int newTicks;
	GLfloat advance_x, advance_y;
	CaclulateVelocity();
	newTicks =  iteam::Timer[0].GetTicks() - LastTicks;
	LastTicks = iteam::Timer[0].GetTicks();
	advance_x = GetDelta(vel_x, newTicks);
	advance_y = GetDelta(vel_y, newTicks);
	//cout << "Adv_x = " << advance_x << "\n";
	//cout << "Adv_y = " << advance_y << "\n";
	//cout << "Ticks are " << iteam::Timer[0].GetTicks() << "\n";
	x += advance_x;
	y += advance_y;
	
	if (CollisionPixel(this,&Level[0],0,0)) {
		x -= advance_x;
		y -= advance_y;
		advance_x = advance_x / newTicks;
		advance_y = advance_y / newTicks;
		vel_y = vel_y * -1; // flip the velocity in the opposite direction
		if(IsPhysical)	{
			// remove some of the bounce - commonly know as restitution coificiant think XD
			vel_y = vel_y * Elasticity; 
			
		}
		while(!CollisionPixel(this,&Level[0],0,0)) { // as long as there isnt a collision
				y += advance_y; // move the player downwards 1 pixel
				x += advance_x;
		}
	}
}


// ==================== WEAPON CLUSTERS =========================

void AddWeaponTypeToWeaponList(int TypeID)	{
	// add this weapon to the cluster
	WeaponsList.push_back(IT_Weapon()); 	// add a new weapon type to the weapons list
	WeaponsList[WeaponsList.size()-1].TypeID = TypeID;
	WeaponsList[WeaponsList.size()-1].Active = false;
}

void AddComponent(int WeaponID, int TypeID, const char texture[], bool IsPhysical, bool Bounces, GLfloat BlastRadius, GLfloat Elasticity)	{
	
	WeaponsList[TypeID].components.push_back(weapon());	// add a new component to the weapons type
	//cout << "[WEAPONS] Adding texture\n";
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Load(texture);
	//cout << "[WEAPONS] Added texture " << texture << "\n";
	// set the main values for this conponent
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].WeaponID = WeaponID;
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Visible = false;
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].IsPhysical = IsPhysical;
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].BlastRadius = BlastRadius;
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Bounces = Bounces;
	WeaponsList[ TypeID ].components[ WeaponsList[ TypeID ].components.size()-1 ].Elasticity = Elasticity;
}

// ==================== WEAPON FUNCTIONS ========================

int FireWeapon(int TypeID, GLfloat nx, GLfloat ny, GLfloat new_angle, GLfloat new_accel)	{
	// Set the angle to fire it at
	int i;
	WeaponsList[TypeID].Active = true;
	//cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
	//cout << "[WEAPONS] x = " << nx << " y = " << ny << " angle= " << new_angle << " accel = " << new_accel << "\n";
	for(i=0; i < WeaponsList[TypeID].components.size(); i++)	{
		// cout << "[FIRE WEAPON] TypeID = " << TypeID << "\n";
		WeaponsList[TypeID].components[ i ].SetBeginPosition( nx, ny);
		WeaponsList[TypeID].components[ i ].SetAcceleration(new_accel, new_angle);
		WeaponsList[TypeID].components[ i ].LastTicks = iteam::Timer[0].GetTicks();
		
	}		
	return(0);
}

// ==================== TEST FUNCTIONS ============================

void Test_Init(void)	{
	AddWeaponTypeToWeaponList(IT_WT_GRENADE);
	cout << "[WEAPONS] Added weapon type\n";
	AddComponent(IT_WC_GRENADE, IT_WT_GRENADE, "data/weapons/grenade.png", true, false, (GLfloat) 20.0, (GLfloat) 0.80);
	cout << "[WEAPONS] Added component\n";
}

void Test_Fire(GLfloat angle)	{
	
	int retval = FireWeapon( IT_WT_GRENADE, Player[CurPlayer].x, Player[CurPlayer].y, angle, WeaponStrenght );
}

// ==================== 

void UpdatePhysicalObjects(void)	{
	// update any active weapons
	int i,j;
	// cout << "[WEAPON PHYSICS] WeaponList is " << WeaponsList.size() << " items long\n";
	for(i=0; i < WeaponsList.size(); i++)	{	// loop through each weapon in list and test if its active
		// cout << "[WEAPON PHYSICS] Weapon " << i << " searched\n";
		if(WeaponsList[i].Active == true)	{	// seems to be active so process the componets
			for(j=0; j < WeaponsList[i].components.size(); j++)	{ // move each component
				// cout << "[WEAPON PHYSICS] Weapon " << i << " is active\n";
				WeaponsList[i].components[j].CaclulateVelocity();
				WeaponsList[i].components[j].MoveMe();
				Cam.Begin();
				WeaponsList[i].components[j].Draw();
				//cout << "[WEAPON PHYSICS] x = " << WeaponsList[i].components[j].x << " y = " << WeaponsList[i].components[j].y << "\n";
			}
		}
	}
	// this may include any players eventually as all moving things 
	// in the scene will be reacting to gravity etc.
	
}



} // namespace iteam closed
