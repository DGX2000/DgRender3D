#include "freecamera.h"

#include <glm/gtc/matrix_transform.hpp>

FreeCamera::FreeCamera(const glm::vec3& position)
    : position(position)
{

}

void FreeCamera::computeTransformationMatrix() const
{
    auto cameraUp = glm::vec3(0.0F, 1.0F, 0.0F);

    auto viewingDirection = glm::vec4(0.0F, 0.0F, -1.0F, 0.0F);
    auto panningMatrix = glm::rotate(glm::mat4(1.0F), pan, glm::vec3(0.0F, 1.0F, 0.0F));
    viewingDirection = panningMatrix * viewingDirection;

    auto target = position + glm::vec3(viewingDirection.x, viewingDirection.y, viewingDirection.z);

    cachedTransformation = perspectiveTransformation * glm::lookAt(position, target, cameraUp);
}

void FreeCamera::move(const glm::vec3 &displacement)
{
    // TODO: Make movement relative to pan angle
    position += displacement;
    cachedTransformation.reset();
}

void FreeCamera::rotate(float amount)
{
    pan += amount;
    cachedTransformation.reset();
}
