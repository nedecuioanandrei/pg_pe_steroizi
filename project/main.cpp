#include "src/camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0x0;
}
