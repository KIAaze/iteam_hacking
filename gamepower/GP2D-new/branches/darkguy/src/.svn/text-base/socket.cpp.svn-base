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
						  - libsdl-net1.2-dev
                        * FreeType development libraries
                          - libfreetype6-dev

SOCKET CLASSES (version 0.0.1)
By Judo

MODIFICATIONS BY:
No one at the moment.
===================================================================================
CHANGELOG:

0.0.1:
-> First code release.
===================================================================================
*/
#include "gp2d.h"

namespace gp2d {
	
	TCPClientSocket::TCPClientSocket() {
		printDebug("New TCPClientSocket created");
		if (SDLNet_Init() < 0) {
			std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	TCPClientSocket::~TCPClientSocket() {
		printDebug("TCPClientSocket destroyed");
	}
	
	void TCPClientSocket::Connect(std::string hostname, int port) {
		printDebug("TCPClientSocket connection attempted");
		if (SDLNet_ResolveHost(&ip, &hostname[0], port) < 0) {
			std::cout << "SDLNet_ResolveHost: " << SDLNet_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
		if (!(socket = SDLNet_TCP_Open(&ip))) {
			std::cout << "SDLNet_TCP_Open: " << SDLNet_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	
	void TCPClientSocket::Send(std::string message) {
		printDebug("TCPClientSocket send attempted");
		message += "\r\n";
		if (SDLNet_TCP_Send(socket, &message[0], message.length() + 1) < message.length() + 1) {
			std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
		}
	}
	
	void TCPClientSocket::SendRaw(std::string message) {
		printDebug("TCPClientSocket raw send attempted");
		if (SDLNet_TCP_Send(socket, &message[0], message.length() + 1) < message.length() + 1) {
			std::cout << "SDLNet_TCP_Send: " << SDLNet_GetError() << std::endl;
		}
	}
	
	std::string TCPClientSocket::Receive() {
		printDebug("TCPClientSocket receive attempted");
		buffer.clear();
		if (SDLNet_TCP_Recv(socket, cbuffer, 1024) <= 0) {
			std::cout << "SDLNet_TCP_Recv: " << SDLNet_GetError() << std::endl;
		}
		else {
			buffer = cbuffer;
		}
		return buffer;
	}
	
	void TCPClientSocket::Close() {
		printDebug("TCPClientSocket close called");
		SDLNet_TCP_Close(socket);
		//~TCPClientSocket();
	}
};
	
