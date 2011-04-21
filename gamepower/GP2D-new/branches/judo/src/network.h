/*
	This file is part of GamePower 2D.

    GamePower 2D is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    GamePower 2D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GamePower 2D; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

===================================================================================
GAMEPOWER 2D ENGINE
===================================================================================
This engine requires:	* OpenGL/Mesa development libraries
								* C compiler (gcc 4.2 used)
								* SDL development libraries
								  - libsdl1.2-dev
                          - libsdl-image1.2-dev
                          - libsdl-mixer1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

NETWORK FUNCTIONS (version 0.0.1)
By Judo
*/

#ifndef _GP2D_NETWORK_H
#define _GP2D_NETWORK_H

#include "core.h"

//#include "net2/net2.h"
//#include "net2/fastevents.h"
//#include "net2/SDLUtils.h"

#include <cstdio>
#include <string>

#include "SDL_net.h"

namespace gp2d {

class GP2DBaseClientSocket; // don't mind me, just prototyping myself

////////////////////////////////////////////////////////////////////////////////
////
////   Utility functions - begin and end receive functions
////
////////////////////////////////////////////////////////////////////////////////

int GP2DStartReceive(GP2DBaseClientSocket &socket);
int GP2DStopReceive(GP2DBaseClientSocket &socket);


////////////////////////////////////////////////////////////////////////////////
////
////    GP2DBaseClientSocket - Base class for TCP and UDP client sockets
////
////////////////////////////////////////////////////////////////////////////////

class GP2DBaseClientSocket {

public:

    GP2DBaseClientSocket();
    ~GP2DBaseClientSocket();

    virtual void receive();
    virtual void startReceive();
    virtual void stopReceive();

private:

    SDL_Thread* m_receiveThread;

};


////////////////////////////////////////////////////////////////////////////////
////
////    GP2DCTCPClientSocket - TCP client-side socket
////
////////////////////////////////////////////////////////////////////////////////

class GP2DTCPClientSocket : public GP2DBaseClientSocket {

public:

    GP2DTCPClientSocket();
    ~GP2DTCPClientSocket();

    bool connect(const char* host, int port);
    bool close();

    bool sendString(const char* data);
    bool sendBinary(const char* data, int size);

    bool getString(char** data, char* terminator);
    bool getBinary(char** data, unsigned int size);

    bool isReady();
    bool isConnected();
    void setAmountToReceive(int newAmount);

    void receive();

private:

    SDLNet_SocketSet socketSet;
    char* hostame;
	IPaddress ipAddress;
	TCPsocket socket;
	char* buffer;
    unsigned int bufferSize;
    int amountToReceive;
    bool currentState;

};

class GP2DTCPServerSocket {

public:

private:

};

class GP2DUDPClientSocket {

public:

private:

};

class GP2DUDPServerSocket {

public:

private:

};

} // namespace gp2d


#endif

