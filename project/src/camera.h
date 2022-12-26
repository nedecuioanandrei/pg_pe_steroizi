#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace ned {
    class Camera {
        private:
                Camera(
                                const glm::vec3& pos,
                                float fov,
                                float aspect,
                                float zNear,
                                float zfar
                                );
                inline glm::mat4 get_view_projection() const {
                    return projection * glm::lookAt(pos, pos + forward, up);
                }
        protected:
        private:
                glm::mat4 projection;
                glm::vec3 pos;
                glm::vec3 forward;
                glm::vec3 up;
    }; 
};
#endif
