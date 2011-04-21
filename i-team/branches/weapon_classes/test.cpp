//
// C++ Implementation: test
//
// Description: 
//
//
// Author:  <>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <typeinfo>

using namespace std;

class _Sprite
{
                public:
                        bool Active;
                        int CurrentFrame;
                        unsigned int startTicks;
                        virtual int Update(){cout<<"_Sprite Update"<<endl;return(0);};
                        virtual int Render(){cout<<"_Sprite Render"<<endl;return(0);};
                        virtual ~_Sprite(){cout<<"_Sprite destructor called"<<endl;}
};

typedef map <int,_Sprite*> _SpriteMap;

class _Explosion : public _Sprite
{
                public:
                        bool Active;
                        int CurrentFrame;
                        unsigned int startTicks;
                        int Update(){cout<<"_Explosion Update"<<endl;return(0);};
                        int Render(){cout<<"_Explosion Render"<<endl;return(0);};
                        ~_Explosion(){cout<<"_Explosion destructor called"<<endl;}
};

class _Player : public _Sprite
{
                public:
                        bool Active;
                        int CurrentFrame;
                        unsigned int startTicks;
                        int Update(){cout<<"_Player Update"<<endl;return(0);};
                        int Render(){cout<<"_Player Render"<<endl;return(0);};
                        ~_Player(){cout<<"_Player destructor called"<<endl;}
};

class _Weapon : public _Sprite
{
                public:
                        bool Active;
                        int CurrentFrame;
                        unsigned int startTicks;
                        char *name;
                        int Update(){cout<<"_Weapon Update"<<endl;return(0);};
                        int Render(){cout<<"_Weapon Render"<<endl;return(0);};
                        ~_Weapon(){cout<<"_Weapon destructor called"<<endl;}
};

int GetUnusedMapNumber(map <int, _Sprite*> &a_map)
{
	int N;
	if ( a_map.empty() ) N=0;
	else N= ( a_map.rbegin() )->first+1;
	return(N);
}

int Add_Sprite(_SpriteMap &a_map)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=new _Sprite();
	return(N);
}
int Add_Explosion(_SpriteMap &a_map)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=new _Explosion();
	return(N);
}
int Add_Player(_SpriteMap &a_map)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=new _Player();
	return(N);
}
int Add_Weapon(_SpriteMap &a_map)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=new _Weapon();
	return(N);
}
int Add(_SpriteMap &a_map, _Sprite* obj)
{
	int N=GetUnusedMapNumber(a_map);
	a_map[N]=obj;
	return(N);
}
int Remove(_SpriteMap &a_map, _SpriteMap::iterator i)
{
	int N=( *i ).first;
	delete ( *i ).second;
	a_map.erase(i);
	return(N);
}

int ProcessAll(_SpriteMap &a_map)
{
	int N=0;
	for ( _SpriteMap::iterator i=a_map.begin(); i!=a_map.end(); i++ )
	{
		cout<<"\nobjet "<<typeid (*(( *i ).second)).name()<<":\n"<<endl;
		int remove=( *i ).second->Update();
		( *i ).second->Render();
		if(remove) Remove(a_map,i);
		N++;
	}
	return(N);
}

int Clear_SpriteMap(_SpriteMap &a_map)
{
	int N=0;
	for ( _SpriteMap::iterator i=a_map.begin(); i!=a_map.end(); i++ )
	{
		Remove(a_map,i);
		N++;
	}
	return(N);
}

int main(void)
{
	cout<<"==============="<<endl;
	_Sprite* ptrBase[4];
	ptrBase[0]=new _Sprite();
	ptrBase[1]=new _Explosion();
	ptrBase[2]=new _Player();
	ptrBase[3]=new _Weapon();

	for(int i=0;i<4;i++)
	{
		cout<<"\nobjet "<<typeid (*ptrBase[i]).name()<<":\n"<<endl;
		ptrBase[i]->Update();
		ptrBase[i]->Render();
		delete ptrBase[i];
	}
	cout<<"==============="<<endl;

	_SpriteMap supermap;
	cout<<GetUnusedMapNumber(supermap)<<endl;

	Add_Sprite(supermap);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add_Explosion(supermap);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add_Player(supermap);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add_Weapon(supermap);
	cout<<GetUnusedMapNumber(supermap)<<endl;

	Add(supermap, new _Sprite);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add(supermap, new _Explosion);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add(supermap, new _Player);
	cout<<GetUnusedMapNumber(supermap)<<endl;
	Add(supermap, new _Weapon);
	cout<<GetUnusedMapNumber(supermap)<<endl;

	ProcessAll(supermap);
	Clear_SpriteMap(supermap);

	cout<<"==============="<<endl;
	map <int, int> testmap;
	int N=4;
	for(int i=0;i<N;i++) testmap[i]=i;
	for(int j=0;j<N;j++)
	{
		cout<<"-->loop "<<j<<endl;
		for ( map<int,int>::iterator i=testmap.begin(); i!=testmap.end(); i++ )
		{
			cout<<"("<<(*i).first<<","<<(*i).second<<")"<<endl;
			if(j==0) testmap.erase(0);
			if(j==1) testmap[N]=N;
			if(j==2) testmap[0]=0;
		}
	}
	cout<<"==============="<<endl;

	return(0);
}
