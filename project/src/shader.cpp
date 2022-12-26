#include "shader.h"

#include <fstream>
#include <iostream>

namespace ned {
Shader::Shader(const std::string& filename) {
  m_program = glCreateProgram();
  m_shaders[0] = create_shader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] =
      create_shader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

  for (unsigned int i = 0; i < SHADER_COUNT; ++i) {
    glAttachShader(m_program, m_shaders[i]);
  }

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");

  glLinkProgram(m_program);
  check_shader_error(m_program, GL_LINK_STATUS, true,
                     "Error linking shader program.");

  glValidate(m_program);
  check_shader_error(m_program, GL_VALIDATE_STATUS, true,
                     "Invalid shader program.");

  m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
  m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
  m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

Shader::~Shader() {
  for (unsigned int i = 0; i < SHADER_COUNT; ++i) {
    glDetachShader(m_program, m_shaders[i]);
    glDeleteShader(m_shaders[i]);
  }
  glDeleteProgram(m_program);
}

void Shader::bind() {
  glUseProgram(m_program);
}

void Shader::update(const Transform& transform, const Camera& camera) {
  glm::mat4 mvp = transform.get_mvp();
  glm::mat4 normal = transform.get_model();

  glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &mvp[0][0]);
  glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &normal[0][0]);
  glUniform3f(m_uniforms[2], 0.0f, 0.0f, 0.0f);
}

std::string Shader::load_shader(const std::string& filename) {
  std::ifstream file;
  file.open((filename).c_str());

  std::string output;
  std::string line;

  if (file.is_open()) {
    while (file.good()) {
      getline(file, line);
      output.append(line + "\n");
    }
  } else {
    fprintf(stderr, "Unable to load shader: %s \n", filename);
  }
  return output;
}

void Shader::check_shader_error(GLuint shader,
                                GLuint flag,
                                bool is_program,
                                const std::string& error_message) {
  GLint success = 0;
  GLchar error[1024] = {0};

  if (is_program) {
    glGetProgramiv(shader, flag, &success);
  } else {
    glGetShaderiv(shader, flag, &success);
  }

  if (success == GL_FALSE) {
    if (is_program) {
      glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
    } else {
      glGetShaderInfoLog(shader, sizeof(error), nullptr, error);
    }
    fprintf(stderr, "%s: %s\n", error_message, error);
  }
}

GLuint Shader::create_shader(const std::string text, unsigned int type) {
  GLuint shader = glCreateShader(type);

  if (shader == 0) {
    fprintf(stderr, "Error compiling shader type: %d\n", type);
  }

  const GLchar* p[1];
  p[0] = text.c_str();
  GLint lengths[1];
  lengths[0] = text.length();

  glShaderSource(shader, 1, p, lengths);
  glCompileShader(shader);

  check_shader_error(shader, GL_COMPILE_STATUS, false,
                     "Error compiling shader");

  return shader;
}
}  // namespace ned
