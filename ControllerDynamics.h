#pragma once

#include "SystemDef.h"
#include <iostream>


sysDef(ControlDynamics)
bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->transform && e->rigidbody && e->controller;
}

void update(Entity *e)
{
	if (core(Input).getKeyDown(e->controller->up))
	{
		e->rigidbody->addForce(e->transform->up() * e->controller->speed);
	}

	if (core(Input).getKeyDown(e->controller->left))
	{
		e->rigidbody->addTorque(e->controller->torque * 1);
	}
	if (core(Input).getKeyDown(e->controller->right))
	{
		e->rigidbody->addTorque(e->controller->torque * -1);
	}
	auto &ref = e->controller;

	if (core(Input).getKeyDown(e->controller->fire) && ref->m_delay < ref->m_timer)
	{
		core(Factory).MakeBullet( e->transform, e->collider->faction, 1000);

		ref->m_timer = 0;
	}
	else ref->m_timer += core(Time).getDeltaTime();
}



sysEndDef 