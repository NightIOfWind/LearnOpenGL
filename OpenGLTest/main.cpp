#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.cpp"
#include <unistd.h>
#include <stdio.h>
using namespace std;
#define PATH_SIZE 255

void framebuffer_size_callback(GLFWwindow * window,int width,int height);
void processInput(GLFWwindow *window);

int main(int argc, const char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(800,600,"Learn OpenGL",NULL,NULL);
    if (window ==NULL)
    {
        std::cout << "Failed Creat GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout<< "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

//
//    char curPath[PATH_SIZE];
//    if (!getcwd(curPath, PATH_SIZE))
//    {
//        cout<<"Get path fail!"<<endl;
//    }
//    char vertexName[] = "vertexShader_1.glsl";
//    char fragmentName[] = "fragmentShader_1.glsl";
//    char *vertexPath = new char[strlen(vertexName),strlen(curPath)];
//    strcpy(vertexPath,curPath);
//    strcat(vertexPath,vertexName);
//    char *fragmentPath = new char[strlen(curPath),strlen(fragmentName)];
//    strcpy(fragmentPath,curPath);
//    strcat(fragmentPath,fragmentName);
    Shader ourShader("/Users/zhengjiangtao/LearnOpenGL/OpenGLTest/vertexShader_1.glsl","/Users/zhengjiangtao/LearnOpenGL/OpenGLTest/fragmentShader_1.glsl");
    float offset = 0.5f;
    ourShader.setFloat("xOffset", offset);

    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    unsigned int VBO,VAO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GL_FLOAT),0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float texCoords[]{
        0.0f,0.0f,
        1.0f,0.0f,
        0.5f,1.0f,
    };
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);

    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,3);
        //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
//    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
void framebuffer_size_callback(GLFWwindow * window,int width,int height)
{
    glViewport(0, 0, width, height);
}
