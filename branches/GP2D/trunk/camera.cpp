#include "camera.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

namespace gp {

/**
 * Create!
 */
GPCamera::GPCamera() {
}

/**
 * Destroy!
 */
GPCamera::~GPCamera() {
}

/**
 * Sets the window associated to the camera
 */
void GPCamera::setWindow(GPWindow* window)
{
    m_window = window;
}

GPWindow* GPCamera::getWindow()
{
    return m_window;
}

/**
 * Set range.
 */
void GPCamera::setRange(gpDouble range) {
    m_range = range;
}

/**
 * Get range.
 */
gpDouble GPCamera::getRange() const {
    return m_range;
}

/**
 * Sets x, y positions.
 */
void GPCamera::setPosition(gpFloat x, gpFloat y) {
    m_posX = x;
    m_posY = y;
}

gpFloat GPCamera::getX() const {
    return m_posX;
}

gpFloat GPCamera::getY() const {
    return m_posY;
}

//==============================================================================

GPGameCamera::GPGameCamera() {
}

void GPGameCamera::updateCamera() {
    if(m_window == NULL) {
        throw GPException("No GPWindow instance found");
    } else {
        /// window can be not null, but still not created.
        if(!m_window->isCreated()) {
            throw GPException("GPWindow can not be allocated (is it created?)");
        }
        int height = m_window->getHeight();
        int width = m_window->getWidth();

        /// no division by zeroes, plx!
        if (height == 0) {
            height = 1;
        }

        /// the aspect ratio of the 'window'
        GLfloat aspectRatio = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);

        glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));

        /// make sure to change the projection matrix.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        if (width <= height) {
            glOrtho(-m_range, m_range,
                    -m_range / aspectRatio, m_range / aspectRatio,
                    -m_range, m_range);
        } else {
            glOrtho(-m_range * aspectRatio, m_range * aspectRatio,
                    -m_range, m_range,
                    -m_range, m_range);
        }

        /// this translates the orthographic projection to the desired x and y.
        /// don't know why exactly this works, but some website refer to it as
        /// 'working'.
        glTranslatef(-getX(), -getY(), 0.0f);
    }
}

//==============================================================================

GPGuiCamera::GPGuiCamera() throw (GPException) :
        m_rangeLeft(0),
        m_rangeRight(100),
        m_rangeTop(100),
        m_rangeBottom(0) {

}

void GPGuiCamera::updateCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
    glOrtho(m_rangeLeft, m_rangeRight, m_rangeBottom, m_rangeTop, -1.0, 1.0);
}

void GPGuiCamera::setDefaults() throw (GPException) {
    if(!m_window->isCreated()) {
        /// well, the window cannot be allocated. Be sure to notify the
        /// programmer by throwing an exception.
        throw GPException("GPWindow can not be allocated (is it created?)");
    }

    m_rangeLeft = 0;
    m_rangeRight = m_window->getWidth();
    m_rangeBottom = 0;
    m_rangeTop = m_window->getHeight();
}

//==============================================================================

GPDirector::GPDirector(GPGameCamera* gamecam, GPGuiCamera* guicam) :
        m_gamecam(gamecam),
        m_guicam(guicam),
        m_flag(true) {
}

GPDirector::~GPDirector() {
}

void GPDirector::useGameCamera() {
    if(!m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();

        m_gamecam->updateCamera();

        m_flag = false;
    }
}

void GPDirector::useGuiCamera() {
    if(m_flag) {
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();

        m_guicam->updateCamera();

        m_flag = true;
    }
}

GPGameCamera* GPDirector::getGameCamera() {
    return m_gamecam;
}

GPGuiCamera* GPDirector::getGuiCamera() {
    return m_guicam;
}

}
