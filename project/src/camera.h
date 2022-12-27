#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/trigonometric.hpp>

struct Camera {
 public:
  Camera(const glm::vec3& pos,
         float fov,
         float aspect,
         float zNear,
         float zFar,
         float yaw,
         float pitch) {
    this->pos = pos;
    this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->projection = glm::perspective(fov, aspect, zNear, zFar);
    this->yaw = yaw;
    this-> pitch = pitch;
  } 
  
  void _update_forward() { 
    glm::vec3 ans = forward;
    ans.x = cos(glm::radians(this -> yaw)) * cos(glm::radians(this -> pitch));
    ans.y = sin(glm::radians(this -> pitch));
    ans.z = sin(glm::radians(this -> yaw)) * cos(glm::radians(this -> pitch));
    this -> forward = glm::normalize(ans);    
  }

  inline glm::mat4 get_view_projection() const {
    return projection * glm::lookAt(pos, pos + this -> forward, up);
  }

  void move_forward(float amt) { pos += forward * amt; }
    
  void move_backward(float amt) { pos -= forward * amt; }
  
  void move_right(float amt) { pos += glm::cross(up, forward) * amt; }
  
  void move_left(float amt) { pos -= glm::cross(up, forward) * amt; }   
    
  void update_yaw(float yaw) { 
    this -> yaw = yaw; 
    this->_update_forward();
  }

  void update_pitch(float pitch) { 
    this -> pitch = pitch; 
    this -> _update_forward();
  }

 protected:
 private:
  glm::mat4 projection;
  glm::vec3 pos;
  glm::vec3 forward;
  glm::vec3 up;
  float yaw;
  float pitch;
};
#endif
