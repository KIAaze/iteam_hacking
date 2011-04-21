#ifndef _GP2D_FRAMERATE_H
#define _GP2D_FRAMERATE_H
#include "gp2d.h"

namespace gp2d {

	class GP2DTimer	{
		private:
			bool started;
			bool paused;
			unsigned int startTicks;
			unsigned int pausedTicks;
		public:
			GP2DTimer();
			void start ( void );
			void stop ( void );
			void reset ();
			void pause ( void );
			void unpause ( void );
			int getTicks ( void );
			bool isStarted();
			bool isPaused();
	};

}

#endif
