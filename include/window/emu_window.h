#ifndef EMU_WINDOW_H
#define EMU_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class EmuWindow {
private:
    GLFWwindow* window;
    static unsigned int SCR_WIDTH;
    static unsigned int SCR_HEIGHT;

    int init();
    void processInput();

public:
    EmuWindow();
    ~EmuWindow();
    
    void runWindow();

};


#endif // EMU_WINDOW_H