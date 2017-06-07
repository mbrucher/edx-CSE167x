// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
  auto theta = glm::radians(degrees);

  return mat3() * std::cos(theta) + glm::outerProduct(axis,axis) * (1 - std::cos(theta)) + mat3(0, -axis.z, axis.y, axis.z, 0, -axis.x, -axis.y, axis.x, 0) * std::sin(theta);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
  mat3 rotation = rotate(degrees, glm::normalize(-up));
  eye = rotation * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 axis = glm::normalize(glm::cross(up, eye));
	mat3 rotation = rotate(degrees, axis);
	eye = rotation * eye;
	up = rotation * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
  return mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
