//Enemy.cpp
#define M_PI 3.14159265358979323846
#include "Enemy.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

Enemy::Enemy(bool can)
{
	can_hurt_player = can;
}


Enemy::~Enemy(void)
{
}


void Enemy::setColor(Color c)
{
	m_color = c;
}


void Enemy::draw(RenderTarget &target, RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = NULL;
	
	for(int i=0;i<m_Enemy.size();i++)
	{
		target.draw(m_Enemy[i].shape,states);
	}
}


void Enemy::generate(int ile,int xg, int yg)
{
	int x,y;

	for(int i=0;i<ile;i++)
	{
		Asteroid ast;
		ast.big = false;

		if(xg==0 && yg==0)
		{
			if(rand()%10>4)ast.big=true; else ast.big=false;

			/*if(rand()%2 == 0)
			{
				x = -5;
				y = rand()%720;
			}
			else
			{
				x = rand()%1280;
				y = -5;
			}*/


			x = rand()%1280;
			y = 0;
		}
		int radius = 40;
		if(ast.big) radius*=1.5;

		//generowanie figury
		ConvexShape shape;
		shape.setPointCount((rand()%3)+5);

		int size = shape.getPointCount();
		
		for(int j=0;j<size;j++)
		{
			float alpha = rand()%(360/size)+j*(360/size);
			alpha=(alpha*M_PI)/180;
			shape.setPoint(j,Vector2f(x+cos(alpha)*radius,y+sin(alpha)*radius));
		}
		shape.setOrigin(shape.getPoint(0));
		
		shape.setOutlineColor(Color::White);
		shape.setFillColor(Color::Transparent);
		
		shape.setOutlineThickness(1);
		shape.setPosition(x,y);

		ast.shape = shape;
		
		//ustawianie prêdkoœci
		float vx,vy;

		vx = (rand()%4)/1.5f;
		vy = (rand()%4)/1.5f;

		if(vx==0) vx=1;
		if(vy==0) vy=1;

		ast.speed = Vector2f(0,vy);

		m_Enemy.push_back(ast);
	}
}


void Enemy::del(int it)
{
	for(int i=it;i<m_Enemy.size()-1;i++)
	{
		std::swap(m_Enemy[i],m_Enemy[i+1]);
	}

	m_Enemy.resize(m_Enemy.size()-1);
}


void Enemy::update()
{
	//wychodzenie poza krawedzie
	for(int i=0;i<m_Enemy.size();i++)
	{
		Vector2f pos = m_Enemy[i].shape.getPosition();
		
		//os x
		if(pos.x > 1295) //margines 15 pikseli
			m_Enemy[i].shape.setPosition(-10,pos.y);
		else if(pos.x < -15)
			m_Enemy[i].shape.setPosition(1290,pos.y);

		if(pos.y > 735)
			m_Enemy[i].shape.setPosition(pos.x,-10);
		else if(pos.y < -15)
			m_Enemy[i].shape.setPosition(pos.x,730);
	}

	//ruch jednostajny
	for(int i=0;i<m_Enemy.size();i++)
	{
		m_Enemy[i].shape.move(m_Enemy[i].speed);
	}
}


Vector2f Enemy::getPoint(int i,int it)
{
	return m_Enemy[i].shape.getTransform().transformPoint(m_Enemy[i].shape.getPoint(it));
}


int Enemy::getSize()
{
	return m_Enemy.size();
}


int Enemy::getSize(int index)
{
	return m_Enemy[index].shape.getPointCount();
}


bool Enemy::isEmpty()
{
	return m_Enemy.empty();
}