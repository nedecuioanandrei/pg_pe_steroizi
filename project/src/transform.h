#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "camera.h"

namespace ned {
class Transform {
 public:
  Transform(const glm::vec3& pos = glm::vec3(),
            const glm::vec3& rot = glm::vec3(),
            const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));
  inline glm::mat4 get_model() const {
    glm::mat4 pos_mat = glm::translate(pos);
    glm::mat4 scale_mat = glm::scale(scale);
    glm::mat4 rot_x = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rot_y = glm::rotate(rot.y, glm::vec3(0.0, 1.0. 0.0));
    glm::mat4 rot_z = glm::rotate(rot.x, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 rot_mat = rot_x * rot_y * rot_z;
    return pos_mat * rot_mat * scale_mat;
  }
  inline glm::mat4 get_mvp(const Camera& camera) const {
    glm::mat4 vp = camera.get_view_projection();
    glm::mat4 m = get_model();
    return vp * m;
  }
  inline glm::vec3* get_pos() { return &pos; }
  inline glm::vec3* get_rot() { return &rot; }
  inline glm::vec3* get_scale() { return &scale; }
  inline void set_pos(glm::vec3& pos) { this->pos = pos; }
  inline void set_rot(glm::vec3& rot) { this->rot = rot; }
  inline void set_scale(glm::vec3& scale) { this->scale = scale; }

 protected:
 private:
  glm::vec3 pos;
  glm::vec3 rot;
  glm::vec3 scale;
};
};  // namespace ned
#endif
