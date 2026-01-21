#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

// Cordinets of verticies 2D: origin in the middle of the window X pointing to the right and Y pointing up. Cordinates are normalised right most -1 left most 1. Highest part of screen 1 Lowest part -1.
int main()
{
    glfwInit();// initialising glfw

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// telling which version we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // which profile we are using


    //Array of cordinates for the triangle vertices sqrt(3) is for equilateral triangle shape . each line is (x, y, z)
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

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

    /////////
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // creating a value/reference to store our vertexshader in
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // feeding in the source code from the top
    glCompileShader(vertexShader); //gpu cant understand source code so compiing it to machine code

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); 
    glCompileShader(fragmentShader); 
    /////////

    //now wraping those 2 shaders to shader program

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader); // attaching shaders
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // wrap

    glDeleteShader(vertexShader); // deleteing the shaders
    glDeleteShader(fragmentShader);


    //information sending between gpu cpu is slow thats why its done in buffers big batches

    GLuint VAO, VBO; // reference integer for the buffer object


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); // creating a buffer object giving it value one becauase we create only 1 3D object
    //Binding = making certain object the current object when ever functions happen it modifies the current object the binding object

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); // binding it with GL array buffer because its the type for vertex buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //storing the vertices ref for type of buffer, total size of data in bytes, the data itself, specifying the usage of data STATIC vertices will be modified once and used many many times DRAW means we modify the vertices and wil be used to draw image on the screen
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);// Vertex attrib is a way of communicating to the vert shader from outside
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // ordering is extre ely important with the buffers and attributes
    glBindVertexArray(0);


    //Specify the color of the background 
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    //Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // swap the back buffer with the front buffer
    glfwSwapBuffers(window);

    // main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        //take care of all glfw events
        glfwPollEvents();
    }

    //deleteing the objects 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);// need to destory window and terminate glfw before program ends
    glfwTerminate();
    return 0;
}