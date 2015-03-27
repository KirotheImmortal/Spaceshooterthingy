#pragma once

#include "SystemDef.h"

sysDef(DynamicCollisionResponse)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->rigidbody && e->collider && e->transform;
}

void update(Entity *e)
{
	for each(auto o in e->collider->contacts)
		if (condition(o) && e->factoryIndex < o->factoryIndex)
		{

			auto &v1	= e->rigidbody->velocity;
			auto &v2	= o->rigidbody->velocity;
			auto m1		= e->rigidbody->mass;
			auto m2		= o->rigidbody->mass;
			//std::cout << e->factoryIndex << " " << i << std::endl;
			vec3 v2f, v1f;

			v2f = ((v1 *-2 * m2) + v2*(m1 - m2)) * (1 / (-m2 - m1));
			v1f = v1 + v2 - v2f;

			v1 = v1f;
			v2 = v2f;

			if (e->collider->isBullet == 0 && o->collider->isBullet == 1)
				e->rigidbody->addTorque(500);
			else if (e->collider->isBullet == 1 && o->collider->isBullet == 0)
				e->rigidbody->addTorque(500);

			//core(Factory).FreeEntity(e);
			 if (o->collider->isBullet == 1 && e->collider->isBullet == 1)
			{
				core(Factory).FreeEntity(o);
				core(Factory).FreeEntity(e);
			}
			else if (e->collider->isBullet == 1)
				core(Factory).FreeEntity(e);
		

			else if (o->collider->isBullet == 1)
				core(Factory).FreeEntity(o);
			


		}



	;
}


sysEndDef