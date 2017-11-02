#pragma once

#include "Player.h"
#include "Sprite.h"
#include "TextureLoader.h"

class GUI
{
private:

	GLuint live_texture;
	GLuint empty_live_texture;
	
	GLuint p1_textures_points[10];
	GLuint p2_textures_points[10];

	Sprite *p1_lives[3];
	Sprite *p2_lives[3];

	Sprite *p1_points;
	Sprite *p2_points;

	Player *p1;
	Player *p2;

	float size_livesW;
	float size_livesH;
	
	float size_pointsW;
	float size_pointsH;

	float w, h;

	void initTextures();
	void initLives();
	void initPoints();

	void drawLives();
	void drawPoints();

public:

	GUI(Player *p1, Player *p2,float w,float h);
	~GUI();

	void setLivesSize(float w, float h);
	void setPointsSize(float w, float h);

	void initGUI();

	void restart();

	void draw();
};