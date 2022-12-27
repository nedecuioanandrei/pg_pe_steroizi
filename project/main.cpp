#include "src/camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <bits/stdc++.h>
#include "src/shader.h"
#include "src/mesh.h"
#include "src/camera.h"
#include "src/transform.h"

using namespace std;

const int w_width = 1280;
const int w_height = 720;
GLFWwindow* window = nullptr;

float get_tilt(const int l, const int x) {
    const int mid = l / 2;
    const int offset = x - mid;
    return -90.0f * offset / mid;
}


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
    
    Mesh pom("./objects/dead_tree2.obj");
    Shader shader("./shaders/test");
    double mouse_x, mouse_y;
    glfwGetCursorPos(window, &mouse_x, &mouse_y); 
    Camera camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)w_width/(float)w_height, 0.1f, 100.0f, mouse_x, mouse_y);
    Transform transform;

    float amt = 0.05;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
        shader.bind();
        shader.update(transform, camera);
        pom.Draw();      

        if (glfwGetKey(window, GLFW_KEY_A)) {
            camera.move_left(amt);
        }
        if (glfwGetKey(window, GLFW_KEY_D)) {
            camera.move_right(amt);
        }
        if (glfwGetKey(window, GLFW_KEY_W)) {
            camera.move_forward(amt);
        }
        if (glfwGetKey(window, GLFW_KEY_S)) {
            camera.move_backward(amt);
        }
        double x, y;
        cout << x << " " << y << " " << get_tilt(w_width, x) << " " << get_tilt(w_height, y) << endl;
        glfwGetCursorPos(window, &x, &y);
        camera.update_yaw(-get_tilt(w_width, x));
        camera.update_pitch(get_tilt(w_height, y));
        glfwSwapBuffers(window);        
    }
    glfwTerminate();
    return 0x0;
}
