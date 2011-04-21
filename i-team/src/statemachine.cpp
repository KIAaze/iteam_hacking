#include "statemachine.h"
using namespace std;
using namespace gp2d;

namespace game {

stateMachine::stateMachine(){
	m_state = 0;
	m_nextState = 0;
}
stateMachine::~stateMachine(){}

int stateMachine::getState()
{
	return m_state;
}

void stateMachine::setNextState(int state)
{
	m_nextState = state;
}

void stateMachine::setState(int state)
{
	m_state = state;
}

void stateMachine::nextState()
{
	m_state = m_nextState;
}

void stateMachine::run(){}

}
