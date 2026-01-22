#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>


#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

//Array of cordinates for the triangle vertices sqrt(3) is for equilateral triangle shape . each line is (x, y, z)
GLfloat vertices[] =
{       //coordinates                               //colors
   -0.5f, -0.5f, 0.0f,     1.0f, 0.0f,  0.0f,  0.0f, 0.0f,//Low left corn
   -0.5f,  0.5f, 0.0f,     0.0f, 1.0f,  0.0f,  0.0f, 1.0f,//up left corn
    0.5f,  0.5f, 0.0f,     0.0f, 0.0f,  1.0f,  1.0f, 1.0f,//up right corn
    0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,  1.0f, 0.0f//low left corn
    

};

GLuint indices[] =
{
    0, 2, 1, // upper triangle
    0, 3, 2 // lower triangle
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

    //links to VBO and VAO
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    //Texture

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("pop_cat.png", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    //float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);


    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
    shaderProgram.Activate();
    glUniform1i(tex0Uni, 0);

    // main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        //take care of all glfw events
        glfwPollEvents();
    }

    //deleteing the objects 
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    glDeleteTextures(1, &texture);
    shaderProgram.Delete();
    
    glfwDestroyWindow(window);// need to destory window and terminate glfw before program ends
    glfwTerminate();
    return 0;
}