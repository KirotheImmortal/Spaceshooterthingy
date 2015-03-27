#pragma once
#include "SystemDef.h"

sysDef(RigidbodyDynamics)

bool init() { return true; }
bool term() { return true; }

bool condition(Entity *e)
{
	return e->active && e->rigidbody && e->transform;
}

void update(Entity *e)
{
	auto &pos = e->transform->position();
	float dt = core(Time).getDeltaTime();
	auto &vel = e->rigidbody->velocity;
	auto &force = e->rigidbody->force;
	auto &torq = e->rigidbody->torq;
	auto &mass = e->rigidbody->mass;
	auto &angleMove = e->rigidbody->angleMove;
	auto &drag = e->rigidbody->drag;
	
	e->transform->m_local = makeRotation(angleMove * dt)
								*e->transform->m_local
									*makeTranslation(vel * dt);


	//pos = pos + vel * dt;


	float a_damp = (angleMove *-1) * drag;
	float a_acc  = (torq + a_damp) * (1 / mass);
	
	vec3 damp = (vel * -1) * drag;
	vec3 acceleration = (force + damp) *(1 / mass);

	vel = vel + acceleration * dt;
	force = vec3Zero();
	angleMove = angleMove + a_acc * dt;
	torq = 0;

}
sysEndDef