#include "core.hpp"
#include "sprite.hpp"

namespace gp {

GPSprite::GPSprite() :
    m_alpha(1.0f),
    m_anim_currentFrame(0),
    m_anim_currentSequence(0),
    m_anim_loop(true),
    m_anim_backwards(false),
    m_currentTexture(NULL) {

    setWidth(0.0f);
    setHeight(0.0f);
}

GPSprite::GPSprite(GPTexture* texture) :
    m_alpha(1.0f),
    m_anim_currentFrame(0),
    m_anim_currentSequence(0),
    m_anim_loop(true),
    m_anim_backwards(false),
    m_currentTexture(NULL) {

    addTexture(texture);

    /// just to have the rotation be around the center of the image by default
    /// (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_currentTexture->getWidth() / 2.0, -m_currentTexture->getHeight() / 2.0, 0);

    /**
     * TODO: Figure out how to create a default "1-frame-animation-sequence"
     * for static sprites.
     */
    std::vector<GPRect> omg;
    GPRect oo;
    oo.x = 0; oo.w = 1;
    oo.y = 0; oo.h = 1;
    omg.push_back(oo);
    m_animSequences[0] = omg;
}

GPSprite::GPSprite(std::string filename) :
    m_alpha(1.0f),
    m_anim_currentFrame(0),
    m_anim_currentSequence(0),
    m_anim_loop(true),
    m_anim_backwards(false),
    m_currentTexture(NULL) {

    addTexture(new GPTexture(filename));

    /// just to have the rotation be around the center of the image by default
    /// (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_currentTexture->getWidth() / 2.0, -m_currentTexture->getHeight() / 2.0, 0);

    /**
     * TODO: Figure out how to create a default "1-frame-animation-sequence"
     * for static sprites.
     */
    std::vector<GPRect> omg;
    GPRect oo;
    oo.x = 0; oo.w = 1;
    oo.y = 0; oo.h = 1;
    omg.push_back(oo);
    m_animSequences[0] = omg;
}

int GPSprite::addTexture(GPTexture* texture) {
    m_textures.push_back(texture);
    m_currentTexture = m_textures[m_textures.size()-1];

    setWidth(m_currentTexture->getWidth());
    setHeight(m_currentTexture->getHeight());

    /// Just to have the rotation be around the center of the image by default
    /// (TODO: will need to be adapted for spritesheets)
    this->setRotCenter(m_currentTexture->getWidth() / 2.0, -m_currentTexture->getHeight() / 2.0, 0);
    return m_textures.size()-1;
}

void GPSprite::useTexture(gpUint32 value) {
    if(value >= 0 && value <= m_textures.size() - 1) {
        m_currentTexture = m_textures[value];
    }
}

GPSprite::~GPSprite() {
    /// not much to delete here by default, especially not the
    /// GPTexture instance, because it can be used by other sprites.
}

GPTexture* GPSprite::getTexture() const {
    return m_currentTexture;
}

gpInt32 GPSprite::createAnim(gpInt32 framesWidth, gpInt32 framesHeight, gpInt32 orgx, gpInt32 orgy, gpInt32 width, gpInt32 height) {
    std::vector<GPRect> m_animRects;

    for(int fy = 0; fy <= framesHeight; fy++) {
        for(int fx = 0; fx <= framesWidth; fx++) {
            GPRect rect;

            rect.x = static_cast<gpFloat>(orgx + (fx * width)) / m_currentTexture->getSurface()->w;
            rect.y = static_cast<gpFloat>(orgy + (fy * height)) / m_currentTexture->getSurface()->h;
            rect.w = (static_cast<gpFloat>(orgx + (fx * width)) + static_cast<gpFloat>(width)) / m_currentTexture->getSurface()->w;
            rect.h = (static_cast<gpFloat>(orgy + (fy * height)) + static_cast<gpFloat>(height)) / m_currentTexture->getSurface()->h;

            m_animRects.push_back(rect);
        }
    }

    m_animSequences[0] = m_animRects;

    return 0;
}

void GPSprite::draw() {
    GLfloat x1, y1, x2, y2;
    gpBool isPowerOfTwo = getTexture()->isPowerOfTwo();
    GLenum textureMode = isPowerOfTwo ? GL_TEXTURE_2D : GL_TEXTURE_RECTANGLE_NV;

    /// If the texture is POT, then use GL_TEXTURE_2D, else, use the other one.
    glEnable(textureMode);

    /// blending function, used to make alpha parts transparent or some sort.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    /// enable alpha
    glAlphaFunc(GL_GREATER, 0.1f);
    glEnable(GL_ALPHA_TEST);
    glBindTexture(textureMode, m_currentTexture->getId()); /// make sure we use the
    glDisable(GL_POLYGON_SMOOTH);                   /// correct texture ID.

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(getX(), getY(), getZ());

    glRotatef(getRotation_X(), 1.0f, 0.0f, 0.0f);
    glRotatef(getRotation_Y(), 0.0f, 1.0f, 0.0f);
    glRotatef(getRotation_Z(), 0.0f, 0.0f, 1.0f);

    x1 = 0; x2 = 0;
    y1 = 0; y2 = 0;

    glBegin(GL_QUADS);
        glColor4f(1.0f, 1.0f, 1.0f, m_alpha); /// Set the sprite's alpha (PNG)

        /**
         * The following texture coordinate mappings look retarded. This is
         * because SDL flips the textures, vertically.
         *
         * Vertices:      Texture coordinates:
         *   1--4               2--3
         *   |  |               |  |
         *   2--3               1--4
         */

        if (isPowerOfTwo){
            x1 = (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].x + (m_currentTexture->getTextureOffsetX());
            y1 = (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].y + (m_currentTexture->getTextureOffsetY());
            x2 = (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].w + (m_currentTexture->getTextureRepeatX()-1.0f);
            y2 = (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].h + (m_currentTexture->getTextureRepeatY()-1.0f);
        } else {
            x1 = ( (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].x + (m_currentTexture->getTextureOffsetX())      ) * m_currentTexture->getSurface()->w;
            y1 = ( (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].y + (m_currentTexture->getTextureOffsetY())      ) * m_currentTexture->getSurface()->h;
            x2 = ( (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].w + (m_currentTexture->getTextureRepeatX()-1.0f) ) * m_currentTexture->getSurface()->w;
            y2 = ( (m_animSequences[m_anim_currentSequence])[m_anim_currentFrame].h + (m_currentTexture->getTextureRepeatY()-1.0f) ) * m_currentTexture->getSurface()->h;
        }

        glTexCoord2f(x1, y1); glVertex3f(getScale_X()*0, getScale_Y()*0, getScale_Z()*getZ());
        glTexCoord2f(x1, y2); glVertex3f(getScale_X()*0, getScale_Y()*(-getHeight()), getScale_Z()*getZ());
        glTexCoord2f(x2, y2); glVertex3f(getScale_X()*getWidth(), getScale_Y()*(-getHeight()), getScale_Z()*getZ());
        glTexCoord2f(x2, y1); glVertex3f(getScale_X()*getWidth(), getScale_Y()*0, getScale_Z()*getZ());

    glEnd();

    glDisable(textureMode);
    glDisable(GL_BLEND);
}


void GPSprite::setAlpha(GLfloat alpha) {
    m_alpha = alpha;
}

GLfloat GPSprite::getAlpha() const {
    return m_alpha;
}

}
