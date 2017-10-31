#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <Windows.h>

#include "Player.h"
#include "Math.h"
#include "Log.h"
#include "Window.h"
#include "Shader.h"
#include "Sprite.h"
#include "Map.h"
#include "MapLoader.h"
#include "InputManager.h"

#define MAP_SIZE 30
#define PLAYER_SPEED 5

class Application
{
private:

	int w, h;

	Player *player1;
	Map *map;

	InputManager *inputManager;
	Window *window;
	Shader *shader;

	glm::mat4 Ortho;

	void clear();
	void initAppObjects();
	void initOrtho();
	void key();

	bool initGL();

public:

	Application(const char *title);
	~Application();

	void start();
};
#include "Application.h"

Application::Application(const char *title)
{	
	if (glfwInit() != GLFW_TRUE)
	{
		window = nullptr;
		return;
	}
	
	w = MAP_SIZE * MAP_SIZE;
	h = MAP_SIZE * MAP_SIZE;

	window = new Window(w, h, title);

	if (!initGL())
	{	
		window->deleteWindow();
		window = nullptr;
	}

	initAppObjects();
	initOrtho();
}

Application::~Application()
{
	delete window;
	delete map;
	delete shader;
	delete player1;
}

void Application::start()
{
	if (window)	{
		while (window->is_open())
		{
			clear();
			key();

			shader->use();
			shader->SetMatrix4fv("Ortho",Ortho);

			map->draw();
			player1->draw();
		}
	}
	else {
		Sleep(50000);
	}
}

void Application::key()
{
	if		(inputManager->key_pressed(KEY_W)) player1->move(KEY_W);
	else if (inputManager->key_pressed(KEY_A)) player1->move(KEY_A);
	else if (inputManager->key_pressed(KEY_D)) player1->move(KEY_D);
	else if (inputManager->key_pressed(KEY_S)) player1->move(KEY_S);
}

void Application::initAppObjects()
{
	shader = new Shader();
	shader->loadShaders("VertexShader.txt", "FragmentShader.txt", LOAD_FROM_FILE);

	map = new Map();
	MapLoader::loadMap(map, "resources/maps/map1.txt", MAP_SIZE, MAP_SIZE);

	player1 = new Player(100, 100, MAP_SIZE+30, MAP_SIZE+30);
	player1->setTexture("resources/textures/down.png");

	inputManager = new InputManager(window->getWindow());
}

void Application::initOrtho()
{
	glm::mat4 projection = glm::ortho(0.0f,(float)w,(float)h,0.0f,-1.0f,1.0f);
	glm::mat4 model = glm::mat4(1.0f);

	Ortho = projection * model;
}

void Application::clear()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Application::initGL()
{
	if (glewInit() != GLEW_OK)
	{
		Log::error("glew error");

		return false;
	}

	return true;
}
#include "InputManager.h"

bool InputManager::key_pressed(KEY_TYPE key)
{
	if (glfwGetKey(window, key) == GLFW_PRESS) return true;
	else									   return false;
}
#pragma once

#include <GLFW\glfw3.h>

enum KEY_TYPE
{
	KEY_W = GLFW_KEY_W,
	KEY_D = GLFW_KEY_D,
	KEY_A = GLFW_KEY_A,
	KEY_S = GLFW_KEY_S,
	KEY_ESCAPE = GLFW_KEY_ESCAPE
};

class InputManager
{
private:
	
	GLFWwindow *window;

public:

	InputManager(GLFWwindow *_window) : window(_window) {};

	bool key_pressed(KEY_TYPE key);
};
#include "Log.h"


void Log::error(const char *str)
{
	std::cout << "\nError : " << str << "\n" << std::endl;
}

void Log::info(const char *str)
{
	std::cout << "\nInfo : " << str << "\n" << std::endl;
}
#pragma once

#include <iostream>

class Log
{
public:

	static void error(const char *errorStrig);
	static void info(const char *errorStrig);
};
#include "Map.h"

void Map::draw()
{
	short size_sections = sections.size();

	for (short i = 0; i < size_sections; i++)
	{
		sections[i]->draw();
	}
}

#pragma once

#include <iostream>
#include <vector>
#include "Sprite.h"


class Map
{
public:

	std::vector<Sprite*> sections;

	void draw();
};
#include "MapLoader.h"

void MapLoader::loadMap(Map *map, const char *mapPath,int mapSize,int sectionSize)
{
	std::ifstream file(mapPath);

	if (!file.is_open())
	{
		Log::error("error map file");
		return;
	}

	std::string str;

	float x = 0.0f;
	float y = 0.0f;

	short m = 0;

	while (std::getline(file,str) && m < mapSize)
	{	
		x = 0.0f;
		for (short i = 0;i < str.size(); i++)
		{
			if (str[i] == WALL)
			{
				Sprite *sprite = new Sprite(sectionSize,sectionSize, x, y,STATIC);
				sprite->setTexture("resources/textures/wall.png");
				map->sections.push_back(sprite);
			}
			else if (str[i] == WATER)
			{
				Sprite *sprite = new Sprite(sectionSize, sectionSize, x, y, STATIC);
				sprite->setTexture("resources/textures/water.jpg");
				map->sections.push_back(sprite);
			}
			else if (str[i] == GRASS)
			{
				Sprite *sprite = new Sprite(sectionSize, sectionSize, x, y, STATIC);
				sprite->setTexture("resources/textures/grass.png");
				map->sections.push_back(sprite);
			}

			x += sectionSize;
		}
		m++;
		y += sectionSize;
	}
}
#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "TextureLoader.h"
#include "Sprite.h"
#include "Map.h"
#include "Log.h"

enum
{	
	WALL  = '#',
	WATER = '&',
	GRASS = '$'
};

class MapLoader
{
public:

	static void loadMap(Map *map,const char *mapPath,int mapSize,int sectionSize);
};
#pragma once

#include <glm\glm.hpp>
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

struct vertices
{
	float x, y, z;

	vertices(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};
	vertices(const vertices &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
};
#include "Player.h"

Player::Player(float _x,float _y,float _w,float _h)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	direction = 1;

	sprite = new Sprite(_w, _h, _x, _y, DYNAMIC);
}

Player::~Player()
{
	delete sprite;
}

void Player::setTexture(const char *pathTexture)
{
	sprite->setTexture(pathTexture);
}

void Player::draw()
{	
	sprite->x = this->x;
	sprite->y = this->y;

	sprite->draw();
}

void Player::move(KEY_TYPE key)
{
	if (key == KEY_W)
	{
		this->y -= PLAYER_SPEED;
		if (direction != UP)
		{
			this->direction = UP;
			this->setTexture("resources/textures/up.png");
		}
	}
	else if (key == KEY_S)
	{
		this->y += PLAYER_SPEED;
		if (this->direction != DOWN)
		{
			this->direction = DOWN;
			this->setTexture("resources/textures/down.png");
		}
	}
	else if (key == KEY_D)
	{
		this->x += PLAYER_SPEED;
		if (this->direction != RIGHT)
		{
			this->direction = RIGHT;
			this->setTexture("resources/textures/right.png");
		}
	}
	else if (key == KEY_A)
	{
		this->x -= PLAYER_SPEED;
		if (this->direction != LEFT)
		{
			this->direction = LEFT;
			this->setTexture("resources/textures/left.png");
		}
	}
}
#pragma once

#include "Sprite.h"
#include "InputManager.h"

enum DIRECTION
{
	UP = 0,
	DOWN = 1,
	RIGHT = 2,
	LEFT = 3
};

#define PLAYER_SPEED 5

class Player
{
private:
	
	Sprite *sprite;

	int lives;
	int points;

	void init();

public:
	
	int direction;
	float x, y,w,h;

	Player(float _x,float _y,float _w,float _h);
	~Player();

	void setTexture(const char *pathTexture);
	void draw();
	void move(KEY_TYPE key);
};
#include "Rect.h"

Rect::Rect(float _w, float _h, float _x, float _y,RECT_DRAW_TYPE _type_draw,RECT_TYPE _type_rect)
{	
	rect_type = _type_rect;
	draw_type = _type_draw;

	w = _w;
	h = _h;
	this->x = _x;
	this->y = _y;
	VAO = 0;

	init();
}

Rect::~Rect()
{
	glDeleteVertexArrays(1, &VAO);
}

void Rect::init()
{
	GLuint VBO, IBO;
	float z = 0.0f;

	if (draw_type == NON_TEXTURE)
	{
		float vertices[] =
		{
			this->x,this->y,z,
			this->x,this->y + h,z,
			this->x + w,this->y + h,z,
			this->x + w,this->y,z
		};

		unsigned int indices[] =
		{
			0,1,2,
			0,2,3
		};

		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		glBindVertexArray(0);
	}
	else if (draw_type == WITH_TEXTURE) {

		float vertices[] =
		{
			this->x,this->y,z,			0.0,0.0,
			this->x,this->y + h,z,		0.0,1.0,
			this->x + w,this->y + h,z,	1.0,1.0,
			this->x + w,this->y,z,		1.0,0.0
		};

		unsigned int indices[] =
		{
			0,1,2,
			0,2,3
		};

		glGenVertexArrays(1, &VAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &IBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));

		glBindVertexArray(0);
	}
}

void Rect::draw()
{	
	if (rect_type == DYNAMIC) init();
	glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
#pragma once

#include <GL\glew.h>

enum RECT_DRAW_TYPE{
	NON_TEXTURE,
	WITH_TEXTURE
};

enum RECT_TYPE
{
	DYNAMIC,
	STATIC
};

class Rect
{
private:

	GLuint VAO;

	float w, h;

	void init();

	RECT_DRAW_TYPE draw_type;
	RECT_TYPE      rect_type;

public:
	float x, y;

	Rect(float _w, float _h, float _x, float _y,RECT_DRAW_TYPE _type,RECT_TYPE type);
	~Rect();

	void draw();
};
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
#include "Sprite.h"

Sprite::Sprite(float _w,float _h,float _x,float _y,RECT_TYPE type)
{	
	w = _w;
	h = _h;
	x = _x;
	y = _y;

	rect = new Rect(_w, _h, _x, _y,WITH_TEXTURE,type);
}

Sprite::~Sprite()
{
	glDeleteTextures(1, &texture);
}

void Sprite::draw()
{	
	rect->x = this->x;
	rect->y = this->y;
	glBindTexture(GL_TEXTURE_2D, texture);
	rect->draw();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::setTexture(const char *pathTexture)
{
	texture = TextureLoader::getTexture(pathTexture);
}
#pragma once

#include "TextureLoader.h"
#include "Rect.h"

class Sprite
{
private:

	GLuint texture;
	Rect *rect;

public:

	float w, h, x, y;

	Sprite(float _w,float _h,float x,float y,RECT_TYPE type);
	~Sprite();

	void draw();
	void setTexture(const char *filepath);
};
#include "TextureLoader.h"

GLuint TextureLoader::getTexture(const char *pathTexture)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int w, h;
	unsigned char *image = SOIL_load_image(pathTexture, &w, &h, 0, SOIL_LOAD_RGB);

	if (!image)
	{
		Log::error("image error : ");

		return 0;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
#pragma once

#include <GL\glew.h>
#include <SOIL.h>
#include "Log.h"

class TextureLoader
{
public:

	static GLuint getTexture(const char *filepath);
};
#include "Window.h"

Window::Window(int _w, int _h, const char *title)
{
	w = _w;
	h = _h;

	window = glfwCreateWindow(w,h,title,NULL,NULL);

	if (!window)
	{
		Log::error("Window did not create");
		return;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
}

Window::~Window()
{	
	this->deleteWindow();
}

void Window::deleteWindow()
{
	if (window) {
		glfwTerminate();
		glfwDestroyWindow(window);
	}
}

bool Window::is_open()
{
	if (!window) return false;

	glfwPollEvents();
	glfwSwapBuffers(window);

	return !glfwWindowShouldClose(window);
}

GLFWwindow* Window::getWindow() const
{
	return window;
}
#pragma once

#include <GL/glew.h>
#include <GLFW\glfw3.h>

#include "Log.h"

class Window
{
private:

	GLFWwindow *window;
	int w, h;

public:
	
	Window(int w, int h, const char *title);
	~Window();

	void deleteWindow();

	bool is_open();

	GLFWwindow* getWindow() const;
};