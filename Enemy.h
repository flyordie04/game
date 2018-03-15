//Enemy.h
#pragma once
#include "entity.h"
#include <vector>

using namespace std;

class Enemy :
	public Entity,Transformable
{
public:
	Enemy(bool = true);
	~Enemy(void);

	virtual void setColor(Color=Color::White);

	void generate(int ile, int = 0,int y=0);
	void del(int index);

	void update();
	Vector2f getPoint(int index,int it);
	
	int getSize();
	int getSize(int index);
	

	bool isEmpty();

private:
	Color m_color;

	struct Asteroid
	{
		Vector2f speed;
		ConvexShape shape;
		bool big;
	};

	vector <Asteroid> m_Enemy;
	virtual void draw(sf::RenderTarget &target,sf::RenderStates states) const;
};