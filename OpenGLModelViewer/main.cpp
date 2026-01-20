#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

int main(void)
{
    glfwInit();// initialising glfw

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// telling which version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // which profile we are using

    //Create a GLFWidnow object of 800 by 800pixels giving it a name
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGLModelViewer", NULL, NULL);
    
    //if window fails to create terminate glfw and close program
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //introduce window to current context. context = workspace where drawing textures and buffers happen
    glfwMakeContextCurrent(window);

    // load glad
    gladLoadGL();


    // specifying viewport  goes from 0, 0 to 800 800
    glViewport(0, 0, 800, 800);
    //Specify the color of the background 
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // main while loop
    while (!glfwWindowShouldClose(window))
    {
        //take care of all glfw events
        glfwPollEvents();
    }

    glfwDestroyWindow(window);// need to destory window and terminate glfw before program ends
    glfwTerminate();
    return 0;
}