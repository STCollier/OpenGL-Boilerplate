#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>


struct Window window;

static void _sizeCallback() {
    int width, height;
    glfwGetWindowSize(window.self, &width, &height);

    glViewport(0, 0, width, height);
}

static void _keyboardCallback() {
    if (glfwGetKey(window.self, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.self, 1);
}

void window_create(const char* title, int width, int height) {
    window.title = title;
    window.width = width;
    window.height = height;

    window.dt = 0.0f;
    window.lastFrame = 0.0f;
  
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window.self = glfwCreateWindow(window.width, window.height, window.title, NULL, NULL);

    if (window.self == NULL) {
        printf("Failed to create GLFW window");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window.self);

    // Load all OpenGL function pointers with Glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        printf("Failed to initialize GLAD");
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetFramebufferSizeCallback(window.self, _sizeCallback);
    glfwSetKeyCallback(window.self, _keyboardCallback);
}

void window_destroy() {
    glfwDestroyWindow(window.self);
    glfwTerminate();
}

void window_update() {
    float currentFrame = glfwGetTime();
    window.dt = currentFrame - window.lastFrame;
    window.lastFrame = currentFrame;

    // Render
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}