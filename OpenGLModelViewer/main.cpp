#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Array of cordinates for the triangle vertices sqrt(3) is for equilateral triangle shape . each line is (x, y, z)
GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Low left
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //low right
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, //up
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, // inner low

};

GLuint indices[] =
{
    0, 3, 5, //Lower left tri
    3, 2, 4, //Lower right tri
    5, 4, 1  // upper tri
};


// Cordinets of verticies 2D: origin in the middle of the window X pointing to the right and Y pointing up. Cordinates are normalised right most -1 left most 1. Highest part of screen 1 Lowest part -1.
int main()
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



    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));


    VAO1.LinkVBO(VBO1, 0);

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    

    

    // main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        //take care of all glfw events
        glfwPollEvents();
    }

    //deleteing the objects 
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    
    glfwDestroyWindow(window);// need to destory window and terminate glfw before program ends
    glfwTerminate();
    return 0;
}