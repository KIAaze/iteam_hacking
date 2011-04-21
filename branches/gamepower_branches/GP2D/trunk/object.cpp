#include "core.hpp"
#include "object.hpp"

namespace gp {

/**
 * GPObject constructor.
 */
GPObject::GPObject() {
    init();
}

GPObject::GPObject(float x, float y) {
    init();
    m_x = x;
    m_y = y;
}

GPObject::GPObject(float x, float y, float z) {
    init();
    m_x = x;
    m_y = y;
    m_z = z;
}

/**
 * Destroy the object. Virtual destructor.
 */
GPObject::~GPObject() {
}

/**
 * Do some initializing here of local class members.
 */
void GPObject::init() {
    m_x = 0.0f; /// initialize the coordinates and all that to 0.0f.
    m_y = 0.0f;
    m_z = 0.0f;
    m_x_scale = 1.0f;
    m_y_scale = 1.0f;
    m_z_scale = 1.0f;
    m_height = 0.0f;
    m_width = 0.0f;
    m_x_velocity = 0.0f;
    m_y_velocity = 0.0f;
    m_angle_X = 0.0f;
    m_angle_Y = 0.0f;
    m_angle_Z = 0.0f;
}

/**
 * Shitload of getters functions over here.
 */

float GPObject::getX() const {
    return m_x;
}
float GPObject::getY() const {
    return m_y;
}
float GPObject::getZ() const {
    return m_z;
}
float GPObject::getWidth() const {
    return m_width;
}
float GPObject::getHeight() const {
    return m_height;
}
gpFloat GPObject::getScale_X() const {
    return m_x_scale;
}
gpFloat GPObject::getScale_Y() const {
    return m_y_scale;
}
gpFloat GPObject::getScale_Z() const {
    return m_z_scale;
}
void GPObject::getScale(gpFloat& X, gpFloat& Y, gpFloat& Z) const {
    X=m_x_scale;
    Y=m_y_scale;
    Z=m_z_scale;
}
float GPObject::getVelocity_X() const {
    return m_x_velocity;
}
float GPObject::getVelocity_Y() const {
    return m_y_velocity;
}
float GPObject::getRotation_X() const {
    return m_angle_X;
}
float GPObject::getRotation_Y() const {
    return m_angle_Y;
}
float GPObject::getRotation_Z() const {
    return m_angle_Z;
}
float GPObject::getRotCenter_X() const {
    return m_RotCenter_X;
}
float GPObject::getRotCenter_Y() const {
    return m_RotCenter_Y;
}
float GPObject::getRotCenter_Z() const {
    return m_RotCenter_Z;
}

/**
 * Shitload of setter methods right here.
 */

void GPObject::setX(float x) {
    m_x = x;
}
void GPObject::setY(float y) {
    m_y = y;
}
void GPObject::setZ(float z) {
    m_z = z;
}
void GPObject::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}
void GPObject::setWidth(float w) {
    m_width = w;
}
void GPObject::setHeight(float h) {
    m_height = h;
}
void GPObject::setScale_X(float s) {
    m_x_scale = s;
}
void GPObject::setScale_Y(float s) {
    m_y_scale = s;
}
void GPObject::setScale_Z(float s) {
    m_z_scale = s;
}
void GPObject::setScale(float s) {
    m_x_scale=s;
    m_y_scale=s;
    m_z_scale=s;
}
void GPObject::setScale(gpFloat sX, gpFloat sY, gpFloat sZ) {
    m_x_scale=sX;
    m_y_scale=sY;
    m_z_scale=sZ;
}
void GPObject::setSize(float w, float h) {
    m_width = w;
    m_height = h;
}

void GPObject::setVelocity_X(float xvel) {
    m_x_velocity = xvel;
}
void GPObject::setVelocity_Y(float yvel) {
    m_y_velocity = yvel;
}
void GPObject::setRotation_X(float angle) {
    m_angle_X = angle;
}
void GPObject::setRotation_Y(float angle) {
    m_angle_Y = angle;
}
void GPObject::setRotation_Z(float angle) {
    m_angle_Z = angle;
}
void GPObject::setRotCenter_X(float a_X) {
    m_RotCenter_X = a_X;
}
void GPObject::setRotCenter_Y(float a_Y) {
    m_RotCenter_Y = a_Y;
}
void GPObject::setRotCenter_Z(float a_Z) {
    m_RotCenter_Z = a_Z;
}
void GPObject::setRotCenter(float a_x,float a_y,float a_z) {
    m_RotCenter_X = a_x;
    m_RotCenter_Y = a_y;
    m_RotCenter_Z = a_z;
}

}
