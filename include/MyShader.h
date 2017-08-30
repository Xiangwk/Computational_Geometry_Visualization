#ifndef MYSHADER_H_
#define MYSHADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <gl/glew.h>  //这是为了包含所有必要的opengl头文件

class Shader
{
public:
	//程序对象
	GLuint program;
	//构造函数
	Shader(const GLchar *vert_path, const GLchar *frag_path);
};

Shader::Shader(const GLchar *vert_path, const GLchar *frag_path)
{
	std::string vertex_shader_str;
	std::string fragment_shader_str;
	std::ifstream vert_file;
	std::ifstream frag_file;

	vert_file.exceptions(std::ifstream::badbit);
	frag_file.exceptions(std::ifstream::badbit);
	try
	{
		vert_file.open(vert_path);
		frag_file.open(frag_path);
		std::stringstream vert_stream, frag_stream;
		vert_stream << vert_file.rdbuf();
		frag_stream << frag_file.rdbuf();
		vert_file.close();
		frag_file.close();
		vertex_shader_str = vert_stream.str();
		fragment_shader_str = frag_stream.str();
	}
	catch (std::ifstream::failure erro)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	//着色器源代码
	const GLchar *vert_shader_source = vertex_shader_str.c_str();
	const GLchar *frag_shader_source = fragment_shader_str.c_str();

	GLuint vertex_shader;
	GLint success;
	GLchar info_log[512];
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vert_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	GLuint fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &frag_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//链接着色器
	this->program = glCreateProgram();
	glAttachShader(this->program, vertex_shader);
	glAttachShader(this->program, fragment_shader);
	glLinkProgram(this->program);
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

#endif