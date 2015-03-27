#pragma once
#include "SystemDef.h"

sysDef(CollisionRendering)
bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->transform && e->collider;
}

void update(Entity *e)
{
	vec4 color = {0,0,0,1};
	if (e->collider->faction == 1)
	color.x = 1;
	else
	color.z = 1;

	e->collider->shape.origin = e->transform->globalPosition();
	Asset::instance().drawShape(e->collider->shape, color);
}

sysEndDef
