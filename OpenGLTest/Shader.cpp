#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class Shader{
public:
    unsigned int ID;
    Shader(const GLchar * vertexPath,const GLchar *fragmentPath)
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream,fShaderStream;
            //读取文件到数据流中
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            vShaderFile.close();
            fShaderFile.close();
            //数据流转化为string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(std::ifstream::failure e)
        {
            std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESS_READ"<<std::endl;
        }
        const char *vShaderCode = vertexCode.c_str();
        const char *fShaderCode = fragmentCode.c_str();
        unsigned int vertex,fragment;
        int success;
        char info[512];
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&vShaderCode,NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(vertex,512,NULL,info);
            std::cout<<"ERROR::SHADER::VERTEX::COMPILE_FAILED\n"<<info<<std::endl;
        }
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&fShaderCode,NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(fragment,512,NULL,info);
            std::cout<<"ERROR::SHADER::FRAGMENT::COMPILE_FAILED\n"<<info<<std::endl;
        }
        ID = glCreateProgram();
        glAttachShader(vertex,ID);
        glAttachShader(fragment,ID);
        glLinkProgram(ID);
        glGetProgramiv(ID,GL_COMPILE_STATUS,&success);
        if (!success)
        {
            glGetShaderInfoLog(ID,512,NULL,info);
            std::cout<<"ERROR::PROGRAM::LINK_ERROR::COMPILE_FAILED\n"<<info<<std::endl;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);

    }
    void use()
    {
        glUseProgram(ID);
    }
    void setBool(const std::string &name,bool value) const
    {
        glUniform1i(glGetUniformLocation(ID,name.c_str()),(int)value);
    }
    void setInt(const std::string &name,int value) const
    {
        glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
    }
    void setFloat(const std::string &name,float value) const
    {
        glUniform1i(glGetUniformLocation(ID,name.c_str()), value);
    }

};
#endif