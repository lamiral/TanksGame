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
			collision();

			shader->use();
			shader->SetMatrix4fv("Ortho",Ortho);

			map->draw();
			player1->draw();
			player2->draw();
		}
	}
	else {
		Sleep(50000);
	}
}

void Application::restartGame()
{

}

void Application::checkGame()
{
	if (player1->getLives() <= 0)
	{
		restartGame();
	}

	if (player2->getLives() <= 0)
	{
		restartGame();
	}
}

void Application::key()
{	
	COLLISION_TYPE player1_collision = Collision::player_collision(player1, map);
	COLLISION_TYPE player2_collision = Collision::player_collision(player2, map);

	if		(inputManager->key_pressed(KEY_W))    {  if (player1_collision != UP_COLLISION && player1_collision != LEFT_COLLISION && player1_collision != RIGHT_COLLISION)			player1->move(KEY_W); }
	else if (inputManager->key_pressed(KEY_S))    {  if (player1_collision != DOWN_COLLISION && player1_collision != LEFT_COLLISION && player1_collision != RIGHT_COLLISION)		player1->move(KEY_S); }
	else if (inputManager->key_pressed(KEY_D))    {  if (player1_collision != RIGHT_COLLISION  && player1_collision != UP_COLLISION && player1_collision != DOWN_COLLISION)			player1->move(KEY_D); }
	else if (inputManager->key_pressed(KEY_A))    {  if (player1_collision != LEFT_COLLISION  && player1_collision != DOWN_COLLISION && player1_collision != UP_COLLISION)			player1->move(KEY_A); }
	else if (inputManager->key_pressed(KEY_LEFT_ALT)) { player1->instantiateShell((float)glfwGetTime()); }

	if		(inputManager->key_pressed(KEY_UP))   {	 if (player2_collision != UP_COLLISION && player2_collision != LEFT_COLLISION && player2_collision != RIGHT_COLLISION)			player2->move(KEY_W); }
	else if (inputManager->key_pressed(KEY_DOWN)) {  if (player2_collision != DOWN_COLLISION && player2_collision != LEFT_COLLISION && player2_collision != RIGHT_COLLISION)		player2->move(KEY_S); }
	else if (inputManager->key_pressed(KEY_RIGHT)){  if (player2_collision != RIGHT_COLLISION  && player2_collision != UP_COLLISION && player2_collision != DOWN_COLLISION)			player2->move(KEY_D); }
	else if (inputManager->key_pressed(KEY_LEFT)) {  if (player2_collision != LEFT_COLLISION  && player2_collision != DOWN_COLLISION && player2_collision != UP_COLLISION)			player2->move(KEY_A); }
	else if (inputManager->key_pressed(KEY_RIGHT_ALT)) { player2->instantiateShell((float)glfwGetTime()); }
	

}

void Application::collision()
{
	Collision::shell_collision(player1, player2, map);
}

void Application::initAppObjects()
{	
	shader = new Shader();
	shader->loadShaders("VertexShader.txt", "FragmentShader.txt", LOAD_FROM_FILE);

	map = new Map();
	MapLoader::loadMap(map, "resources/maps/map1.txt", MAP_SIZE, MAP_SIZE);

	player1 = new Player(100, 100, MAP_SIZE+15, MAP_SIZE+15,1);
	player1->setTexture("resources/textures/p1down.png");

	player2 = new Player(200, 200, MAP_SIZE+15, MAP_SIZE+15,2);
	player2->setTexture("resources/textures/p2down.png");

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