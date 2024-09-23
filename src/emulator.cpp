#include "emulator.h"

// ******************************
// ******************************
// ******************************

Emulator::Emulator() {
    this->gameboy = new GB();
    
    this->initWindow();
}
Emulator::~Emulator() {
    delete this->gameboy;
    glfwTerminate();
}

// ******************************
// ******************************
// ******************************

void Emulator::loadRom(const char* rom) {
    this->cartridge = new Cartridge(rom);

    this->cartridge->printCartridgeData();
}

void Emulator::run() {
    while (!glfwWindowShouldClose(this->window))
    {
        processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
}

void Emulator::tick() {
    this->gameboy->run();
}

// ******************************
// ******************************
// ******************************

void framebuffer_size_callback(GLFWwindow* w, int width, int height)
{
    glViewport(0, 0, width, height);
}

// *****

unsigned int Emulator::SCR_WIDTH = 800;
unsigned int Emulator::SCR_HEIGHT = 600;

int Emulator::initWindow()
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

void Emulator::processInput()
{
    if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window, true);
    if(glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS)
       this->tick();
}
