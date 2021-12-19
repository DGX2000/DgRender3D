#ifndef DGRENDER3D_H
#define DGRENDER3D_H

#include <GL/glew.h>

#include "mesh.h"
#include "transformnode.h"
#include "meshnode.h"
#include "model.h"

#include "camera.h"
#include "freecamera.h"

#include "shader.h"
#include "texture.h"

class DgRender3D
{
public:
    DgRender3D() = delete;

    static void initialize()
    {
        glewInit();
        glEnable(GL_DEPTH_TEST);
    }

private:
};


#endif // DGRENDER3D_H
