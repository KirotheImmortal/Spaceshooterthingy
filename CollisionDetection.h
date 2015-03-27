#pragma once

#include "SystemDef.h"
#include <cmath>
#include "ccollisionutils.h"



sysDef(CollisionDetection)

bool init() { return true; }
bool term() { return true; }

bool isCollidingFunction(Entity *a, Entity *b)
{
	a->collider->shape.origin = a->transform->globalPosition();
	b->collider->shape.origin = b->transform->globalPosition();

	return ShapeVsShape(a->collider->shape, b->collider->shape) >= 0;
}

bool condition(Entity *e)
{
	return e->active && e->collider && e->transform;
}

//bool isCollidingFunction(Entity *a, Entity b )
//{
//	auto &a_ref = a->transform->globalPosition();
//	auto &b_ref = b.transform->globalPosition();
//	float ax = a_ref.x;
//	float ay = a_ref.y;
//	float bx = b_ref.x;
//	float by = b_ref.y;
//
//	float sum = a->collider->radius + b.collider->radius;
//	float dis = sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay));
//
//	return sum > dis;
//}

void update(Entity *e)
{
	auto &ents = core(Factory).getEntities();

	for (int i = e->factoryIndex + 1; i < ents.size(); ++i)
		if (condition(&ents[i]) && e->collider->faction != ents[i].collider->faction
			&& isCollidingFunction(e, &ents[i]))

		{

			e->collider->contacts.push_front(&ents[i]);
			(&ents[i])->collider->contacts.push_front(e);



			//auto &v1 = e->rigidbody->velocity;
			//auto &v2 = ents[i].rigidbody->velocity;
			//auto m1 = e->rigidbody->mass;
			//auto m2 = ents[i].rigidbody->mass;
			////std::cout << e->factoryIndex << " " << i << std::endl;
			//vec3 v2f, v1f;

			//v2f = ((v1 *- 2 * m2) + v2*(m1 - m2)) * (1 / (-m2 - m1));
			//v1f = v1 + v2 - v2f;

			//v1 = v1f;
			//v2 = v2f;



			//if (e->factoryIndex < 3)
			//core(Factory).FreeEntity(e);

			////if (!&ents[i].collider)
			////if (&ents[i].render->mesh == "Bullet1" || &ents[i].render->mesh == "Bullet2"
			//if (i < 3)
			//core(Factory).FreeEntity(&ents[i]);


		}
}



sysEndDef