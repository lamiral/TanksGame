#include "Shader.h"

Shader::Shader()
{
	vsShader = fsShader = program = 0;
}

Shader::~Shader()
{
	this->deleteProgram();
}

void Shader::loadShaders(const char *vs, const char *fs, LOAD_TYPE load_type)
{
	if (load_type == LOAD_FROM_FILE)		   loadFromFile(vs, fs);
	else if (load_type == LOAD_FROM_STRING)    loadFromString(vs, fs);
}

void Shader::loadFromFile(const char *vsPath, const char *fsPath)
{
	std::ifstream vsFile, fsFile;
	vsFile.open(vsPath);
	fsFile.open(fsPath);

	if (!vsFile.is_open()){
		Log::error("Vertex shader file did not find");
		return;
	}
	else if (!vsFile.is_open()){
		Log::error("Fragment shader file did not find");
		return;
	}

	std::stringstream vs_streamStr, fs_streamStr;
	std::string	vsStr, fsStr;

	vs_streamStr << vsFile.rdbuf();
	fs_streamStr << fsFile.rdbuf();

	vsStr = vs_streamStr.str();
	fsStr = fs_streamStr.str();

	const char *sourceVs = vsStr.c_str();
	const char *sourceFs = fsStr.c_str();

	initProgram(sourceVs, sourceFs);
}

void Shader::loadFromString(const char *vsStr, const char *fsStr)
{
	initProgram(vsStr, fsStr);
}

void Shader::initProgram(const char *vsSource, const char *fsSource)
{
	createShaders(vsSource, fsSource);
	createProgram();
}

void Shader::createShaders(const char *vsSource, const char *fsSource)
{
	vsShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vsShader, 1, &vsSource, NULL);
	glCompileShader(vsShader);

	fsShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsShader, 1, &fsSource, NULL);
	glCompileShader(fsShader);

	error(vsShader, SHADER_ERROR);
	error(fsShader, SHADER_ERROR);
}

void Shader::createProgram()
{
	program = glCreateProgram();

	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);

	glLinkProgram(program);

	error(program, PROGRAM_ERROR);
}

void Shader::error(GLuint object, ERROR_TYPE error_type)
{
	if (error_type == SHADER_ERROR)			errorShader(object);
	else if (error_type = PROGRAM_ERROR)	errorProgram(object);
}

void Shader::errorShader(GLuint shader)
{
	int compile_status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if (!compile_status)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		Log::error(buffer);
	}
}

void Shader::errorProgram(GLuint program)
{
	int	link_status = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &link_status);

	if (!link_status)
	{
		char buffer[512];
		glGetProgramInfoLog(program, 512, NULL, buffer);
		Log::error(buffer);
	}
}

void Shader::deleteProgram()
{
	deleteShader(vsShader);
	deleteShader(fsShader);
	this->stop();
	glDeleteProgram(program);
}

void Shader::deleteShader(GLuint shader)
{
	glDeleteShader(shader);
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::stop()
{
	glUseProgram(0);
}

GLuint Shader::getProgramId()
{
	return program;
}

//SetUniforms

void Shader::SetMatrix4fv(const char *uniName, glm::mat4 &Matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(program, uniName), 1, GL_FALSE, &Matrix[0][0]);
}