#include "GUI.h"

GUI::GUI(Player *_p1, Player *_p2,float _w,float _h)
{	
	w = _w;
	h = _h;

	p1 = _p1;
	p2 = _p2;

	size_livesH = 30;
	size_livesW = 30;

	size_pointsH = 30;
	size_pointsW = 30;

	initTextures();

	p1_points = nullptr;
	p2_points = nullptr;

	for (short i = 0; i < 3; i++)
	{
		p1_lives[i] = p2_lives[i] = nullptr;
	}
}

GUI::~GUI()
{
	for (short i = 0; i < 3; i++)
	{
		delete p1_lives[i];
		delete p2_lives[i];
	}

	TextureLoader::freeTexture(live_texture);
	TextureLoader::freeTexture(empty_live_texture);

	for (short i = 0; i < 9; i++)
	{
		TextureLoader::freeTexture(p1_textures_points[i]);
		TextureLoader::freeTexture(p2_textures_points[i]);
	}
}

void GUI::initTextures()
{
	live_texture = TextureLoader::getTexture("resources/textures/live1.png");
	empty_live_texture = TextureLoader::getTexture("resources/textures/emptyLive.png");
	
	p1_textures_points[0] = TextureLoader::getTexture("resources/textures/numbers/p2_0.png");
	p1_textures_points[1] = TextureLoader::getTexture("resources/textures/numbers/p2_1.png");
	p1_textures_points[2] = TextureLoader::getTexture("resources/textures/numbers/p2_2.png");
	p1_textures_points[3] = TextureLoader::getTexture("resources/textures/numbers/p2_3.png");
	p1_textures_points[4] = TextureLoader::getTexture("resources/textures/numbers/p2_4.png");
	p1_textures_points[5] = TextureLoader::getTexture("resources/textures/numbers/p2_5.png");
	p1_textures_points[6] = TextureLoader::getTexture("resources/textures/numbers/p2_6.png");
	p1_textures_points[7] = TextureLoader::getTexture("resources/textures/numbers/p2_7.png");
	p1_textures_points[8] = TextureLoader::getTexture("resources/textures/numbers/p2_8.png");	
	p1_textures_points[9] = TextureLoader::getTexture("resources/textures/numbers/p2_9.png");

	p2_textures_points[0] = TextureLoader::getTexture("resources/textures/numbers/p1_0.png");
	p2_textures_points[1] = TextureLoader::getTexture("resources/textures/numbers/p1_1.png");
	p2_textures_points[2] = TextureLoader::getTexture("resources/textures/numbers/p1_2.png");
	p2_textures_points[3] = TextureLoader::getTexture("resources/textures/numbers/p1_3.png");
	p2_textures_points[4] = TextureLoader::getTexture("resources/textures/numbers/p1_4.png");
	p2_textures_points[5] = TextureLoader::getTexture("resources/textures/numbers/p1_5.png");
	p2_textures_points[6] = TextureLoader::getTexture("resources/textures/numbers/p1_6.png");
	p2_textures_points[7] = TextureLoader::getTexture("resources/textures/numbers/p1_7.png");
	p2_textures_points[8] = TextureLoader::getTexture("resources/textures/numbers/p1_8.png");
	p2_textures_points[9] = TextureLoader::getTexture("resources/textures/numbers/p1_9.png");
}

void GUI::setLivesSize(float _w, float _h)
{
	size_livesH = _h;
	size_livesW = _w;
}

void GUI::setPointsSize(float _w, float _h)
{
	size_pointsW = _w;
	size_pointsH = _h;

}

void GUI::initPoints()
{
	p1_points = new Sprite(size_pointsW, size_pointsH, (w / 2) - size_pointsW, 0, STATIC);
	p1_points->setTextureMode(STATIC_TEXTURE);
	p1_points->setTexture(p1_textures_points[0]);

	p2_points = new Sprite(size_pointsW, size_pointsH, (w / 2), 0, STATIC);
	p2_points->setTextureMode(STATIC_TEXTURE);
	p2_points->setTexture(p1_textures_points[0]);
}

void GUI::initLives()
{
	float y = 0;

	float _w = w - size_livesW;

	for (short x = 0,i = 0; x < p1->getLives() * size_livesW; x+=size_livesW,i++)
	{
		p1_lives[i] = new Sprite(size_livesW, size_livesH, x, y, STATIC);
		p1_lives[i]->setTextureMode(STATIC_TEXTURE);
		p1_lives[i]->setTexture(live_texture);

		p2_lives[i] = new Sprite(size_livesW, size_livesH, _w - x, y, STATIC);
		p2_lives[i]->setTextureMode(STATIC_TEXTURE);
		p2_lives[i]->setTexture(live_texture);
	}
}

void GUI::restart()
{	
	p1_points->setTexture(p1_textures_points[0]);
	p2_points->setTexture(p2_textures_points[0]);

	for (short i = 0; i < p1->getLives(); i++)
	{
		p1_lives[i]->setTexture(live_texture);
		p2_lives[i]->setTexture(live_texture);
	}
}

void GUI::initGUI()
{
	initLives();
	initPoints();
}

void GUI::drawPoints()
{	
	if (p1_points == nullptr) return;

	p1_points->setTexture(p1_textures_points[p1->getPoints()]);
	p2_points->setTexture(p2_textures_points[p2->getPoints()]);

	p1_points->draw();
	p2_points->draw();
}

void GUI::drawLives()
{
	//draw player 1 lives

	if (p1_lives[0] == nullptr) return;

	for (short i = 0; i < p1->getLives(); i++)
	{
		p1_lives[i]->draw();
	}
	for (short i = p1->getLives(); i < 3; i++)
	{
		p1_lives[i]->setTexture(empty_live_texture);
		p1_lives[i]->draw();
	}

	//draw player 2 lives

	for (short i = 0; i < p2->getLives(); i++)
	{
		p2_lives[i]->draw();
	}
	for (short i = p2->getLives(); i < 3; i++)
	{
		p2_lives[i]->setTexture(empty_live_texture);
		p2_lives[i]->draw();
	}
}

void GUI::draw()
{
	drawLives();
	drawPoints();
}