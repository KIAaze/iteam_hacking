#include "thread.hpp"

using namespace std;

namespace gp {

GPThread::GPThread() :
        m_name(""),
        m_thread(NULL),
        m_running(false) {
    /// in the constructor, initialize the basic thread to NULL first to prevent
    /// undefined behaviour of the value of m_thread.
}

GPThread::GPThread(string name) :
        m_name(name) {
}

GPThread::~GPThread() {
    /// forcefully delete the thread, if not NULL.
    if(m_thread != NULL) {
        stop();
    }
}

gpInt32 GPThread::registerThread(void* threadPtr) {
    GPThread* thread = reinterpret_cast<GPThread*>(threadPtr);
    if(thread == NULL) {
        /// Do not throw an exception here.
        cerr << "Thread was not created!" << endl;
        return -1;
    }

    thread->run();

    return 1; /// yeah.. what else? Nobody is listening for this value anyway.
}


void GPThread::start() throw (GPException) {
    /**
     * basically initializes and starting the thread by creating it using the
     * SDL_CreateThread function.
     *
     * If not already running, start it. We should and must not start a thread
     * twice in a GPThread object instance. To prevent this, check for the
     * boolean m_running and if the m_thread struct is NOT NULL.
     */
    if(!m_running && m_thread == NULL) {
        m_thread = SDL_CreateThread(GPThread::registerThread, this);
        if(m_thread == NULL) {
            string err = "Unable to create thread";
            if(!getName().empty()) {
                err += " `" + getName() + "'"; /// append name, if given
            }

            throw GPException(err, SDL_GetError());
        }

        m_running = true;

        clog << "Thread (ID ";
        clog << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'"; /// append the name, if given
        }
        clog << ") started" << endl;;

    }
}



void GPThread::stop() {
    if(m_running && m_thread != NULL) {
        clog << "Thread (ID ";
        clog << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'"; /// append the name, if given
        }
        clog << ") killed" << endl;

        /// FORCEFULLY kill it, without checking for return values... not that
        /// we do that, anyway... TODO: possible fixing needed?
        SDL_KillThread(m_thread);

        m_running = false; /// mark as stopped.
    }
}

void GPThread::waitForFinish() {
    if(m_running && m_thread != NULL) {
        clog << "Waiting for thread (ID " << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'";
        }
        clog << ") to finish" << endl;

        /// actually wait for the thread to finish, here
        SDL_WaitThread(m_thread, NULL);

        clog << "Thread (ID " << getID();
        if(!getName().empty()) {
            clog << " - `" << getName() << "'";
        }
        clog << ") finished" << endl;
    }
}

gpBool GPThread::isRunning() const {
    return m_running;
}

gpUint32 GPThread::getID() const {
    if(m_thread != NULL && isRunning()) {
        return SDL_GetThreadID(m_thread);
    } else {
        return 0;
    }
}

void GPThread::setName(string name) {
    m_name = name;
}

string GPThread::getName() const {
    return m_name;
}

}
