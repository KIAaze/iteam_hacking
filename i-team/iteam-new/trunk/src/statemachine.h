#ifndef _ITEAM_STATEMACHINE_H
#define _ITEAM_STATEMACHINE_H
#include <GP2D/gp2d.h>
using namespace gp;

namespace game {

	class stateMachine {
		private:
			int m_state;
			int m_nextState;
		public:
			stateMachine();
			virtual ~stateMachine();
			
			virtual void run();

			int getState();
			void setNextState(int state);
			void setState(int state);
			void nextState();
	};

}
#endif
