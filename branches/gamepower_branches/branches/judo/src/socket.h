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

#ifndef _GP2D_SOCKET_H
#define _GP2D_SOCKET_H

#include "gp2d.h"

namespace gp2d {
	
	class TCPClientSocket {
		public:
			TCPClientSocket();
			~TCPClientSocket();
			
			IPaddress ip;
			TCPsocket socket;
			int port;
			std::string hostname;
			std::string buffer;
			char cbuffer[1024];

			void Connect(std::string, int);  // hostname, port
			void Close();
			std::string Receive();
			void Send(std::string);  // message to be sent
			void SendRaw(std::string); // same as above, does not add \r\n
		
	};
}

#endif
