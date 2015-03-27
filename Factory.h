#pragma once
#include "Core.h"
#include "Entity.h"
#include <cassert>


coreDef(Factory)

std::vector<Entity> m_entities;
std::vector<Entity> m_entitiesRemove;
std::vector<Entity> m_entitiesAdd;


Entity *newEntity()
{
	assert(m_entities.size() < m_entities.capacity());

	for (int i = 0; i < m_entities.size(); ++i)
		if (!m_entities[i].active && !m_entities[i].added)
		{
			m_entities[i].added = true;
			return &m_entities[i];

		}
	m_entities.push_back(Entity(m_entities.size()));
	m_entities.back().added = true;
	return &m_entities.back();

	//m_entitiesAdd.push_back(Entity(-1));
	//return &m_entitiesAdd.back();
}
bool init()
{
	m_entities.reserve(64);
	return true;
}

bool step()
{
	for (int i = 0; i < m_entities.size(); ++i)
	{

		if (m_entities[i].added)
		{
			m_entities[i].active = true;
			m_entities[i].added = false;
		}

		if (m_entities[i].removed)
		{

			m_entities[i].active = false;
			m_entities[i].removed = false;
			entityFree((&m_entities[i]));

		}

	}

	/*for (int i = 0; i < m_entitiesRemove.size(); ++i)
	{
		auto e = &m_entitiesRemove[i];
		entityFree(e);
	}
	auto newEntity = m_entitiesAdd.begin();
	for (auto entity = m_entities.begin(); entity != m_entities.end() &&
									 newEntity != m_entitiesAdd.end(); entity++)
		if (!entity->active)
		{
			newEntity->factoryIndex = entity->factoryIndex;
			*entity = *newEntity;
			newEntity++;
		}
	
	while (newEntity != m_entitiesAdd.end())
	{
		newEntity->factoryIndex = m_entities.size();
		m_entities.push_back(*newEntity);
		newEntity++;
	}

	m_entitiesAdd.clear();
	m_entitiesRemove.clear();*/
	return true;
}


bool term() { return true; }




public:


	std::vector<Entity> &getEntities() { return m_entities; }

	void FreeEntity(Entity *e)
	{
		e->removed = true;
	}

	void MakeBorders()
	{
		MakePlane(core(Window).width()  / 2, 0, 0, 1);
		MakePlane(0, 0, 1, 0);
		MakePlane(core(Window).width() / 2, core(Window).height(), 0, -1);
		MakePlane(core(Window).width(), core(Window).height() / 2, -1, 0);
	}

	Entity *drawText(std::string text, float x, float y, float w, float h)
	{
		Entity *Textmsg = newEntity();
		compMake(Textmsg, textrender);
		compMake(Textmsg, transform);

		Textmsg->transform->m_local = makeScale(vec3Make(w,h,0));
	
		Textmsg->textrender->text = text;

		Textmsg->transform->position().x = x;
		Textmsg->transform->position().y = y;
		return Textmsg;
	}

	Entity *MakeBackground()
	{
		Entity *back = newEntity();
		compMake(back, transform);
		compMake(back, render);

		back->transform->position().x = WINDOW_WIDTH / 2;
		back->transform->position().y = WINDOW_HEIGHT / 2;
		back->transform->position().z = 0;
		back->render->shader = "Texture";
		back->render->mesh = "back";
		back->render->texture = "Background";

		return back;

	}

	Entity *MakeBouble(float x, float y, float r)
	{
		Entity *bouble = newEntity();

		compMake(bouble, collider);
		compMake(bouble, transform);

		bouble->collider->shape = makeCircle(x, y, r);

		return bouble;

	}

	Entity *MakePlane(float x, float y, float normx, float normy)
	{

		Entity *wall = newEntity();


		compMake(wall, collider);
		compMake(wall, transform);


		wall->collider->shape = makePlane(0, 0, normx, normy);
		wall -> transform -> position().x = x;
		wall -> transform -> position().y = y;
		wall -> transform -> position().z = 0;


		return wall;

	}

	Entity *MakeTank(float x, float y, int faction)
	{
		Entity *tank = newEntity();
		Entity *turret = newEntity();
		

		compMake(tank, transform);
		compMake(tank, collider);
		compMake(tank, controller);
		compMake(tank, rigidbody);
		compMake(tank, render);

		compMake(turret, transform);
		compMake(turret, render);
		compMake(turret, collider);
		compMake(turret, rigidbody);
		compMake(turret, controller);
		
	

		tank->rigidbody->drag = 5;
		tank->rigidbody->mass = 10;
		tank->controller->speed = 100;
		tank->transform->position().x = x;
		tank->transform->position().y = y;
		tank->collider->shape = makeCircle(0, 0, 60);
		

		tank->collider->faction = faction;
		turret->collider->faction = faction;

		
		

		tank->render->shader	= "Texture";
		tank->render->texture	= "Spaceship";
		
		turret->render->shader	= "Texture";
		
		

		turret->transform->m_parent = tank->transform;
		turret->render->texture = "Cannon";
		turret->controller->m_delay = 1;


		switch (faction)
		{
		case 1:
			tank->controller->up		= 'W';
			tank->controller->left		= 'A';
			tank->controller->right		= 'D';
			turret->controller->left	= 'Q';
			turret->controller->right	= 'E';
			turret->controller->fire    = 'F';
			turret->render->mesh	= "cannon";
			tank->render->mesh		= "space";
			
			
			break;

		case 2:
			tank->controller->up		= 'I';
			tank->controller->left		= 'J';
			tank->controller->right		= 'L';
			turret->controller->left	= 'U';
			turret->controller->right	= 'O';
			turret->controller->fire	= ';';
			turret->render->mesh = "cannon2";
			tank->render->mesh = "space2";

			break;

		}
		
			

		

		return tank;
	}

	Entity *MakeBullet(Transform *source, int faction, float speed)
	{
		Entity *bullet = newEntity();
		compMake(bullet, transform);
		compMake(bullet, render);
		compMake(bullet, collider);
		compMake(bullet, rigidbody);
		compMake(bullet, lifetime);

		
		

		bullet->collider->isBullet = 1;

		bullet->rigidbody->drag = .05f;
		
		bullet->rigidbody->mass = 10;

		bullet->lifetime->life =  20;

		bullet->collider->shape = makeCircle(0, 0, 15);

		bullet->transform->m_local = source->m_global;

		bullet->collider->faction = faction;
		
		if (faction == 1)
		bullet->render->mesh = "Bullet1";
		else
		bullet->render->mesh = "Bullet2";

		bullet->render->shader = "Texture";
		bullet->render->texture = "Bullet";

		bullet->rigidbody->velocity = bullet->transform->up() * speed;
		
		return bullet;
		
	}




coreEndDef