#pragma once

#include "SystemDef.h"

sysDef(StaticCollisionResponse)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{	
	return e->active && e->collider;
}

bool specialCondition(Entity *e, Entity *o)
{
	return e->rigidbody && !o->rigidbody || !e->rigidbody && o->rigidbody;
}

bool bulletCheck(Entity *e)
{
	return e->collider->isBullet == 1;
}

void collisionMath(Entity *e, vec3 N)
{
	vec3 V		= e->rigidbody->velocity;
	vec3 negV	= { -V.x, -V.y, -V.z };
	vec3 P = N * vec3Dot(negV, N);

	e->rigidbody->velocity = (P * 2) + V;

	if (bulletCheck(e))
	{
		e->collider->faction = 3;
		e->render->mesh = "Bullet3";
	}
}

void update(Entity *e)
{
	for each(auto o in e->collider->contacts)
		if (condition(o) && specialCondition(e, o) && e->factoryIndex < o->factoryIndex)
		{
			vec3 N;

			if (!o->rigidbody)
			{//////////////////anything hitting a plane//////////////////////////////////////
				if (o->collider->shape.type == Shape::ePlane)
				{
				
					N = o->collider->shape.plane.normal;
					collisionMath(e, N);
			
				}
				/////////////////////////////////Circle hitting static circle//////////////////////////////////
				if (e->collider->shape.type == Shape::eCircle && o->collider->shape.type == Shape::eCircle)
				{
					 N = normal((e->collider->shape.position + e->transform->position()) - (o->collider->shape.position + o->transform->position()));
					 collisionMath(e, N);

				}


				/////////////if a rect is hitting a static circle////////////////////////////
				else if (o->collider->shape.type == Shape::eRect && e->collider->shape.type == Shape::eCircle)
				{
					vec3 rmin = o->collider->shape.rect.min + o->transform->position();
					vec3 rmax = o->collider->shape.rect.max + o->transform->position();

					vec3 cpos = e->collider->shape.circle.position + e->transform->position();


					int x = clamp(rmin.x, cpos.x, rmax.x);
					int y = clamp(rmin.y, cpos.y, rmax.y);

					if (x == rmin.x) // -1 , 0
					{
						N.x = -1;
						N.y = N.z = 0;
					}

					else if (x == rmax.x) // <  1 , 0> rht
					{
						N.x = 1;
						N.y = N.z = 0;
					}
					else if (y == rmin.y) // <  0 ,-1> top
					{
						N.y = -1;
						N.x = N.z = 0;
					}
					else if (y == rmin.y) // <  0 , 1> bot
					{
						N.y = 1;
						N.x = N.z = 0;
					}
					collisionMath(e, N);

				}

				
			}

			else if (!e->rigidbody)
			{
				////////////////////////anything hitting a plane////////////////////
				if (e->collider->shape.type == Shape::ePlane)
				{
					N = e->collider->shape.plane.normal;
					collisionMath(o, N);
				}
				//////////////////////////////////circle hitting circle//////////////////////////////////////
				else if (e->collider->shape.type == Shape::eCircle && o->collider->shape.type == Shape::eCircle)
				{
					 N = normal((o->collider->shape.position + o->transform->position()) -( e->collider->shape.position + e->transform->position()));
					 collisionMath(o, N);
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
				//////////////////////////////////////////////////////////////////////////////
				else if (e->collider->shape.type == Shape::eRect && o->collider->shape.type == Shape::eCircle)
				{
					vec3 rmin = e->collider->shape.rect.min + e->transform->position();
					vec3 rmax = e->collider->shape.rect.max + e->transform->position();
				 
					vec3 cpos = o->collider->shape.circle.position + o->transform->position();
					

					int x = clamp(rmin.x, cpos.x, rmax.x);
					int y = clamp(rmin.y, cpos.y, rmax.y);

					if (x == rmin.x) // -1 , 0
					{
						N.x = -1;
						N.y = N.z = 0;
					}

					else if (x == rmax.x) // <  1 , 0> rht
					{
						N.x = 1;
						N.y = N.z = 0;
					}
					else if (y == rmin.y) // <  0 ,-1> top
					{
						N.y = -1;
						N.x = N.z = 0;
					}
					else if (y == rmin.y) // <  0 , 1> bot
					{
						N.y = 1;
						N.x = N.z = 0;
					}
					 collisionMath(o, N);

				}


			}
		}
		
}

sysEndDef

