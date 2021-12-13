#ifndef FREECAMERA_H
#define FREECAMERA_H

#include "camera.h"

class FreeCamera : public Camera
{
public:
    FreeCamera(const glm::vec3& position);

    void computeTransformationMatrix() const override;

    void move(const glm::vec3& displacement);
    void rotate(float amount);

private:
    glm::vec3 position;
    float pan{0.0F};
};

#endif // FREECAMERA_H
