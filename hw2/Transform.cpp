// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include <cmath>

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& a) 
{
	auto theta = glm::radians(degrees);
	auto axis = glm::normalize(a);

	return mat3() * std::cos(theta) + glm::outerProduct(axis,axis) * (1 - std::cos(theta)) + mat3(0, -axis.z, axis.y, axis.z, 0, -axis.x, -axis.y, axis.x, 0) * std::sin(theta);
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
	mat3 rotation = rotate(degrees, glm::normalize(-up));
	eye = rotation * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	vec3 axis = glm::normalize(glm::cross(up, eye));
	mat3 rotation = rotate(degrees, axis);
	eye = rotation * eye;
	up = rotation * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
	vec3 w = glm::normalize(eye - center);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	return mat4(u.x, v.x, w.x, 0, u.y, v.y, w.y, 0, u.z, v.z, w.z, 0, -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	auto d = 1/std::tan(glm::radians(fovy) / 2);
    return mat4(d/aspect, 0, 0, 0,
		        0, d, 0, 0,
				0, 0, -(zFar + zNear) / (zFar - zNear), -1,
				0, 0, -(2*zFar*zNear) / (zFar - zNear), 0);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    return mat4(sx, 0, 0, 0,
		        0, sy, 0, 0,
				0, 0, sz, 0,
				0, 0, 0, 1);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    return mat4(1, 0, 0, 0,
		        0, 1, 0, 0,
				0, 0, 1, 0,
				tx, ty, tz, 1);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
