#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <GL/glew.h>

#include <string>

#include "transform.h"

namespace ned {
class Shader {
 public:
  Shader(const std::string& filename);
  void bind(void);
  void update(const Transform& transform, const Camera& camera);
  virtual ~Shader();

 protected:
 private:
  static const unsigned int SHADER_COUNT = 2;
  static const unsigned int UNIFORM_COUNT = 3;
  void operator=(const Shader& shader) {}
  Shader(const Shader& shader) {}
  std::string load_shader(const std::string& filename);
  void check_shader_error(GLuint shader,
                          GLuint flag,
                          bool is_program,
                          const std::string& error_message);
  GLuint create_shader(const std::string text, unsigned int type);
  GLuint m_program;
  GLuint m_shaders[SHADER_COUNT];
  GLuint m_uniforms[UNIFORM_COUNT];
}
};  // namespace ned
#endif
