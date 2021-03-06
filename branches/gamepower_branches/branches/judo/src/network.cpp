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

#include "SDL_net.h"

#include "network.h"

namespace gp2d {


int GP2DStartReceive(GP2DBaseClientSocket* socket)
{
    socket->startReceive();
    return 0; // note that SDL_Threads require an int to return
}

int GP2DStopReceive(GP2DBaseClientSocket* socket)
{
    socket->stopReceive();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////
////    GP2DBaseClientSocket - Base class for TCP and UDP client sockets
////
////////////////////////////////////////////////////////////////////////////////

/* is any of this necessary? */

GP2DBaseClientSocket::GP2DBaseClientSocket() { }
GP2DBaseClientSocket::~GP2DBaseClientSocket() { }
void GP2DBaseClientSocket::receive() { }
void GP2DBaseClientSocket::startReceive()
{
    m_receiveThread = 
    SDL_CreateThread((int (*)(void *))GP2DStartReceive, &this);
}
void GP2DBaseClientSocket::stopReceive()
{
    SDL_WaitThread(m_receiveThread, NULL);
}

////////////////////////////////////////////////////////////////////////////////
////
////    GP2DCTCPClientSocket - TCP client-side socket
////
////////////////////////////////////////////////////////////////////////////////

GP2DTCPClientSocket::GP2DTCPClientSocket() {
    if (SDLNet_Init() < 0) {
        printf("GP2DTCPClientSocket::GP2DTCPClientSocket() SDLNet_Init(): %s", SDLNet_GetError());
    }
    socketSet = SDLNet_AllocSocketSet(1);
    if (!socketSet) {
        printf("GP2DTCPClientSocket::GP2DTCPClientSocket() SDLNetAllocSocketSet(): %s", SDLNet_GetError());
    }
    if (0 > SDLNet_TCP_AddSocket(socketSet, socket)) {
        printf("GP2DTCPClientSocket::GP2DTCPClientSocket() SDLNet_TCP_AddSocket(): %s", SDLNet_GetError());
    }
    currentState = false;
    amountToReceive = 1024;
}

GP2DTCPClientSocket::~GP2DTCPClientSocket() {
    SDLNet_FreeSocketSet(socketSet);
    socketSet = NULL; //just in case
}

void GP2DTCPClientSocket::receive() {
    while (currentState == true) {
        int socketState = SDLNet_CheckSockets(socketSet, 0);
        if (socketState < 0) {
            printf("GP2DTCPClientSocket::receive() SDLNet_CheckSockets(): %s", SDLNet_GetError());
            currentState = false;
        }
        if (socketState == 0) {
            currentState = true; //but no data received
        }
        if (isReady()) { //could possibly cause excessive CPU usage
            buffer = (char*) realloc(buffer, bufferSize + amountToReceive);

            if(!buffer) {
                free(buffer);
                buffer = NULL;
                bufferSize = 0;
                currentState = false;
            }

            int recvReturn = SDLNet_TCP_Recv(socket, buffer + bufferSize, amountToReceive);
            
            if(recvReturn <= 0)
            {
              free(buffer);
              buffer = NULL;
              bufferSize = 0;
              currentState = false;
            }
            bufferSize += recvReturn;
        currentState = true; // completed everything
        }
    }
}

bool GP2DTCPClientSocket::connect(const char* host, int port) {
    if (SDLNet_ResolveHost(&ipAddress, host, port) < 0) {
        printf("GP2DTCPClientSocket::connect() SDLNet_ResolveHost(): %s", SDLNet_GetError());
        return false;
    }
    SDL_Delay(500); //making sure ResolveHost finishes first
    if (!(socket = SDLNet_TCP_Open(&ipAddress))) {
        printf("GP2DTCPClientSocket::connect() SDLNet_TCP_Open(): %s", SDLNet_GetError());
        return false;
    }
    currentState = true;
    return true;
}

bool GP2DTCPClientSocket::close() {
    SDLNet_TCP_Close(socket);
    return false;
}


bool GP2DTCPClientSocket::sendBinary(const char* data, int size) {
    if (currentState == true) {
        if (size != SDLNet_TCP_Send(socket, (void*) data, size)) {
            printf("GP2DTCPClientSocket::sendBinary() SDLNet_TCP_Send(): %s", SDLNet_GetError());
            return false;
        }
    }
    return true;
}

bool GP2DTCPClientSocket::getBinary(char** data, unsigned int size) {
    if (currentState == true) {
        *data = 0;

        // Check for incoming data
        bool returnValue = receive();
        if(returnValue != true) {
            return false;
        }

        if(bufferSize < size) {
            return true;
        }

        // Allocate the string to return
        *data = (char*) malloc(size);

        memcpy(*data, buffer, size);

        if(size == bufferSize) {
            free(buffer);
            bufferSize = 0;
            return true;
        }

        // Suppress the string from our buffer
        char* newBuffer = (char* )malloc(bufferSize - size);
        memcpy(newBuffer, buffer + size, bufferSize - size);

        free(buffer);
        buffer = newBuffer;
        bufferSize -= size;
        return true;
    }
    return false;
}

bool GP2DTCPClientSocket::getString(char** string, char* terminator) {
    if (currentState == true) {
        *string = NULL;

        // Check for incoming data
        bool returnValue = receive();
        if(returnValue != true) {
            return false;
        }

        // Find the terminator
        int i = 0;
        char* pointer;
        int position;
        pointer = strstr(buffer, terminator);
        position = pointer - buffer; // This may raise a warning during compile, but I see no issue with it
	    
        if (buffer[i + strlen(terminator)] == '\0') { //if this really is the end of the string...

            i = i + strlen(terminator) - 1; //assuming the terminator is greater than one character, this will have i be the actual final position
            if( i == (int) bufferSize) {
                return true;
            }

            // Retrieve the string from the buffer
            returnValue = getBinary(string, i + 1);
            if(returnValue != 1) {
                return false;
            }

            // Add a NULL character at the end of the string
            *string = (char*) realloc(*string, i + 2);
            (*string)[i + 1] = '\0';
        }
    }
return true;
}

bool GP2DTCPClientSocket::sendString(const char* data) {
    return sendBinary(data, strlen(data));
}

bool GP2DTCPClientSocket::isReady() {
    SDL_Delay(50);
    if (SDLNet_SocketReady(socket) != 0) {
        return true;
    }
    else {
        return false;
    }
}

bool GP2DTCPClientSocket::isConnected() {
    return currentState;
}
    
void GP2DTCPClientSocket::setAmountToReceive(int newAmount) {
    amountToReceive = newAmount;
}

} // namespace gp2d
