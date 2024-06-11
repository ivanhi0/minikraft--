#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>

#include "../include/GL/glew.h"
#include "../include/GLFW/glfw3.h"
#pragma comment(lib, "include/GL/glew32.lib")
#pragma comment(lib, "include/GLFW/glfw3.lib")
#pragma comment(lib, "include/GLFW/glfw3dll.lib")
#pragma comment(lib, "include/GLFW/glfw3_mt.lib")
#pragma comment(lib, "OpenGL32.lib")
using namespace std;


Shader::Shader(unsigned int id) : id(id){

}

Shader::~Shader() {
	glDeleteProgram(id);
}

void Shader::use() {
	glUseProgram(id);
}

Shader* loadShader(string vertexFile, string fragmentFile) {
	// Read shader files
	string vertexCode;
	string fragmentCode;
	ifstream vShaderFile;
	ifstream fShaderFile;

	vShaderFile.exceptions(ifstream::badbit);
	fShaderFile.exceptions(ifstream::badbit);
	try {
		vShaderFile.open(vertexFile);
		fShaderFile.open(fragmentFile);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (ifstream::failure& e) {
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
		return nullptr;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		cerr << "SHADER::VERTEX: compilation failed\n";
		cerr << infoLog << endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		cerr << "SHADER::FRAGMENT: compilation failed\n";
		cerr << infoLog << endl;
		return nullptr;
	}

	// Shader Program
	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		cerr << "SHADER::PROGRAM: linking failed\n";
		cerr << infoLog << endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(id);
		return nullptr;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return new Shader(id);

}