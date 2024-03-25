#include "window/emu_window.h"

void framebuffer_size_callback(GLFWwindow* w, int width, int height)
{
    glViewport(0, 0, width, height);
}

// *****

unsigned int EmuWindow::SCR_WIDTH = 800;
unsigned int EmuWindow::SCR_HEIGHT = 600;

EmuWindow::EmuWindow() {
    this->init();
}

EmuWindow::~EmuWindow() {
    glfwTerminate();
}

int EmuWindow::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OlifreGB", NULL, NULL);
    if (this->window == NULL)
    {
        glfwTerminate();
        throw std::invalid_argument( "Failed to create GLFW window" );
    }
    glfwMakeContextCurrent(this->window);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::invalid_argument( "Failed to initialize GLAD" );
    }
}

void EmuWindow::runWindow() {
    while (!glfwWindowShouldClose(this->window))
    {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void EmuWindow::processInput()
{
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
}