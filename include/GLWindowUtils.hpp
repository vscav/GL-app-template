#pragma once
#ifndef _GLWindowUtils_HPP_
#define _GLWindowUtils_HPP_

#include <GL/glew.h>

// Useful class for updating OpenGL state, such as alpha blending, depth testing, etc.
class GLWindowUtils
{
private:
    bool m_cullingBackFace = false;
    bool m_inWireframe = false;
    bool m_isAlphaBlending = false;
    bool m_additiveBlending = false;
    bool m_antialiasing = false;
    bool m_depthTesting = false;

public:
    GLWindowUtils() = default;
    ~GLWindowUtils() = default;

    void antialias(bool enable);

    void enableAlphaBlending();

    void enableAdditiveBlending();

    void disableBlending();

    void enableDepthTesting(bool enable);

    void cullBackFaces(bool cull);

    void goWireframe(bool goWireframe);
};

#endif /* _GLWindowUtils_HPP_ */