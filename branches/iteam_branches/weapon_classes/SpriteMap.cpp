#include "SpriteMap.h"

#include <typeinfo>
#include <iostream>
using namespace std;
using namespace iteam;

int GetUnusedMapNumber(map <int, Sprite*> &a_map)
{
	int N;
	if ( a_map.empty() ) N=0;
	else N= ( a_map.rbegin() )->first+1;
	return(N);
}

int Add(SpriteMap &a_map, Sprite* obj)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=obj;
	return(N);
}

int Remove(SpriteMap &a_map, SpriteMap::iterator i)
{
	int N=( *i ).first;
	delete ( *i ).second;
	a_map.erase(i);
	return(N);
}

int ProcessAll(SpriteMap &a_map)
{
	int N=0;
	for ( SpriteMap::iterator i=a_map.begin(); i!=a_map.end(); i++ )
	{
// 		cout<<"\nobjet "<<typeid (*(( *i ).second)).name()<<":\n"<<endl;
		( *i ).second->Render(Cam);
		int remove=( *i ).second->DoBehaviour();
		( *i ).second->Update();
		if(remove) Remove(a_map,i);
		N++;
	}
	return(N);
}

int ClearSpriteMap(SpriteMap &a_map)
{
	int N=0;
	for ( SpriteMap::iterator i=a_map.begin(); i!=a_map.end(); i++ )
	{
		Remove(a_map,i);
		N++;
	}
	return(N);
}

bool CheckKey(SpriteMap &a_map, int key)
{
	for ( SpriteMap::iterator it=a_map.begin(); it!=a_map.end(); it++ )
	{
		if((*it).first==key) return(true);
	}
	return(false);
}
