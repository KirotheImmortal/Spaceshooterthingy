#pragma once

#include "SystemDef.h"


sysDef(CollisionRender)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->collider && e->transform;
}

void update(Entity *e)
{
	vec4 c;
	c.x = c.y = c.z = c.w = 1;
	

	if (!e->collider->contacts.empty())
		c.y = c.z = 0;

	e->collider->shape.origin = e->transform->globalPosition();
	Asset::instance().drawShape(e->collider->shape, c);


	
}

sysEndDef