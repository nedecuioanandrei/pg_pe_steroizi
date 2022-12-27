#include "src/camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
#include "src/shader.h"
#include "src/mesh.h"

using namespace std;

const int w_width = 1280;
const int w_height = 720;
GLFWwindow* window = nullptr;

signed main(int argc, char** argv)
{
    if (!glfwInit()) {
        fprintf(stderr, "Crapa");
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w_width, w_height, "PG_pe_steroizi", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Crapa");
        glfwTerminate();
        return 2;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();
    
    /*
     * Testing
     */
    Vertex vertices[] = {
            Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
            Vertex(glm::vec3(0, 0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
            Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, -1))
    };
    
    Vertex vertices[] = {
            Vertex(glm::vec3(-0.7, -0.7, 0), glm::vec2(1, 0), glm::vec3())
    };  
    
    unsigned int indices[] = {0, 1 ,2};

    Mesh mesh(
                    vertices, 
                    sizeof(vertices)/sizeof(vertices[0]),
                    indices,
                    sizeof(indices)/sizeof(indices[0]));
    Shader shader("./shaders/test");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        shader.bind();
        mesh.Draw();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0x0;
}
