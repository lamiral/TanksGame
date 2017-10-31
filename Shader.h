#pragma once

#include <GL\glew.h>
#include <fstream>
#include <sstream>

#include "Math.h"
#include "Log.h"

enum ERROR_TYPE{
	SHADER_ERROR,
	PROGRAM_ERROR,
};

enum LOAD_TYPE{
	LOAD_FROM_FILE,
	LOAD_FROM_STRING,
};

class Shader
{
private:

	GLuint vsShader, fsShader, program;

	void error(GLuint object, ERROR_TYPE type);
	void errorProgram(GLuint program);
	void errorShader(GLuint shader);

	void loadFromFile(const char *vsFilepath, const char *fsFilepath);
	void loadFromString(const char *vsStr, const char *fsStr);

	void initProgram(const char *vsSource, const char *fsSource);
	void createShaders(const char *vs, const char *fs);
	void createProgram();

	void deleteShader(GLuint shader);

public:

	Shader();
	~Shader();

	void loadShaders(const char *vs,const char *fs,LOAD_TYPE type);

	void use();
	void stop();

	void deleteProgram();

	GLuint getProgramId();

	//SetUniform

	void SetMatrix4fv(const char *uniName, glm::mat4 &Matrix);
};