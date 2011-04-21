#ifndef _GP_THREAD_H_
#define _GP_THREAD_H_

#include "core.hpp"
#include "exception.hpp"

#include <string>
#include <SDL/SDL.h>

/*! \namespace gp
    \brief The namespace used for gamepower.
*/
namespace gp {

/**
 * The GPThread class enables you to create a thread within the GP framework.
 * The 'backbone' of this GPThread relies on functions supplied by SDL. To use
 * threads, you simply subclass this class, and override the pure virtual
 * function run(). The code within run() will be the threaded code.
 *
 * Because the run() function is pure virtual, this class cannot be used without
 * being subclassed.
 *
 * @author krpors
 */
class GPThread {
private:

    /// The name of the thread. May be empty.
    std::string m_name;

    /// The SDL_Thread struct pointer.
    SDL_Thread* m_thread;

    /// Indication whether the thread is started and has not yet finished
    /// execution.
    gpBool m_running;

    /**
     * This static function is actually the 'callback' function used as the
     * first parameter in the SDL_CreateThread() function:
     *
     * SDL_CreateThread(int (void*)(), void* parameters);
     *
     * The first parameter used there is actually a pointer to this static
     * function!. The parameter `threadPtr' is _always_ a pointer to the
     * GPThread which is started.
     *
     * @param threadPtr The pointer to the GPThread which is being started.
     */
    static gpInt32 registerThread(void* threadPtr);

public:

    /**
     * Constructor for the GPThread.
     */
    GPThread();

    /**
     * Creates a thread with a name attached to it (for identification purposes).
     *
     * @param name The name of the thread.
     */
    GPThread(std::string name);

    /**
     * Virtual destructor. When this object is deleted, it will forcefully stop
     * the current running thread. In SDL terms: SDL_KillThread().
     *
     * @see stop()
     */
    virtual ~GPThread();

    /**
     * Creates and starts the thread. This will implicitly invoke the pure
     * virtual run() function in subclasses.
     */
    void start() throw (GPException);

    /**
     * Forcefully kill the thread, if running.
     */
    void stop();

    /**
     * Waits for a thread to finish.
     */
    void waitForFinish();

    /**
     * Gets the current thread ID as a signed 32 bit integer. If no thread was
     * running, return -1.
     *
     * @return The thread ID when running, or -1 when not running.
     */
    gpUint32 getID() const;

    /**
     * Returns whether the thread is running.
     *
     * @return true if running, false if otherwise.
     */
    gpBool isRunning() const;

    /**
     * Sets the name of the thread.
     *
     * @param name The name to identify this thread.
     */
    void setName(std::string name);

    /**
     * Gets the name of the thread.
     *
     * @return The name identifying this thread.
     */
    std::string getName() const;

    /**
     * This pure virtual function is the thread worker. When subclassed,
     * override this function to implement functionality for the thread.
     */
    virtual void run() = 0;
};

}

#endif
