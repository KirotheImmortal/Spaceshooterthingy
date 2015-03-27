#pragma once

#include "SystemDef.h"


sysDef(LifetimeDecay)

bool init(){ return true; }
bool term(){ return true; }

bool condition(Entity *e)
{
	return e->active && e->transform && e->lifetime;
}

void update(Entity *e)
{
	
	if (e->lifetime->timer > e->lifetime->life)
	{
		core(Factory).FreeEntity(e);
	}
	else e->lifetime->timer += core(Time).getDeltaTime();
	
}


sysEndDef