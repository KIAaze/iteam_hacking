//STOLEN FROM ROOT >B-D

#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <ocidl.h>
#include <olectl.h>
#else
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>
#include <X11/Xlib.h>

#if defined(R__AIX) || defined(R__SOLARIS)
#   include <sys/select.h>
#endif
#include <time.h>
#include <sys/time.h>
#endif

static const char *Credits[] = {
	"Adamorjames",
	"Aussie",
	"BackwardsDown",
	"Chi0",
	"Compwiz",
	"DarkGuy",
	"Doddi",
	"Jorgerosa",
	"JoshuaRL",
	"Judo",
	"Kevin Pors",
	"KIAaze",
	"L_darkness",
	"Luis Figueiredo",
	"Mickeysofine",
	"Xavieran",
	0
};

#ifdef WIN32
char* get_user_name() {
	char user_name[256];
	DWORD length = sizeof ( user_name );

	if ( GetUserName ( user_name, &length ) ) {
		char name[256];
		strcpy ( name, user_name );
		char *s = strchr ( name, ',' );
		if ( s ) *s = 0;
		return ( name );
	}
	else
		return ( "Susi" );
}
#else
char* get_user_name() {
	struct passwd *pwd = getpwuid ( getuid() );
	if ( pwd ) {
		char name[256];
		strcpy ( name, pwd->pw_gecos );
		char *s = strchr ( name, ',' );
		if ( s ) *s = 0;
		if ( strlen ( name ) )
			return ( name );
		else
			return ( pwd->pw_name );
	}
	else
		return ( "Susi" );
}
#endif

int DrawCredits() {
	printf ( "Credits:\n" );
	for ( int i=0;Credits && Credits[i];i++ ) printf ( "%s\n",Credits[i] );
	printf ( "\n" );

	//char name[256];
	printf ( "Extra special thanks go to %s,\n", get_user_name() );
	printf ( "one of our favorite users.\n" );

	return ( 0 );
}

int main ( void ) {
	DrawCredits();
	return ( 0 );
}
