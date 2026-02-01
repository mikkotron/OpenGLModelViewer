#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

//Array of cordinates for the triangle vertices sqrt(3) is for equilateral triangle shape . each line is (x, y, z)
GLfloat vertices[] =
{       //coordinates           //colors
   -0.5f,  0.0f,  0.5f,    0.83f,0.70f,0.44f,   0.0f, 0.0f, // base
   -0.5f,  0.0f, -0.5f,    0.83f,0.70f,0.44f,   5.0f, 0.0f, // base
    0.5f,  0.0f, -0.5f,    0.83f,0.70f,0.44f,   0.0f, 0.0f, // base
    0.5f,  0.0f,  0.5f,    0.83f,0.70f,0.44f,   5.0f, 0.0f, // base
    0.0f,  0.8f,  0.0f,    0.92f,0.86f,0.76f,   2.5f, 5.0f  // apex
    

};

// order how to draw the vertices
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};


// Cordinets of verticies 2D: origin in the middle of the window X pointing to the right and Y pointing up. Cordinates are normalised right most -1 left most 1. Highest part of screen 1 Lowest part -1.
int main()
{
    glfwInit();// initialising glfw

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// telling which version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // which profile we are using


    //Create a GLFWidnow object of 800 by 800pixels giving it a name
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGLModelViewer", NULL, NULL);
    
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
    glViewport(0, 0, width, height);



    Shader shaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    //links to VBO and VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

  
    //Texture

    Texture popCat("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    popCat.texUnit(shaderProgram, "text0", 0);

  

    //enables depth buffer so it renders all the sides of the model
    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // main while loop
    while (!glfwWindowShouldClose(window))
    {
        //background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //Clean back buffer and depth buffer and assign new color in it
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //telling which shader program we use
        shaderProgram.Activate();
        float crntFrame = (float)glfwGetTime();
        deltaTime = crntFrame - lastFrame;
        lastFrame = crntFrame;

        camera.Inputs(window, deltaTime);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        
        //Binding the texture
        popCat.Bind();
        //Bind the VAO so OpenGL knows to use it
        VAO1.Bind();
        //drawing, number of indices, data tyoe of indices, index of indices
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        //swapping back buffer with the front buffer // front is what currently is visible back is where we draw
        glfwSwapBuffers(window);

        //take care of all glfw events
        glfwPollEvents();
    }

    //deleteing the objects 
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();
    
    glfwDestroyWindow(window);// need to destory window and terminate glfw before program ends
    glfwTerminate();
    return 0;
}