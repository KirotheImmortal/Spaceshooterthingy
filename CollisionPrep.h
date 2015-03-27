#pragma once

#include "SystemDef.h"
#include "cmathutils.h"
#include "ccollisionutils.h"



sysDef(CollisionPrep)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->collider;
}

void update(Entity *e)
{
	e->collider->contacts.clear();
}

sysEndDef