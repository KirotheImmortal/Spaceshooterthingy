#pragma once

#include "cmathutils.h"
#include "Component.h"

compDef(Rigidbody)

	vec3 velocity, force;
	float drag, mass, torq, angleMove;

	Rigidbody() : velocity(vec3Zero()),
				  force(vec3Zero()),
				  drag(10), mass(1), torq(0), angleMove(0){ }

	void addForce(vec3 const &a_force) {  force = force + a_force * 50;  }
	void addTorque(float a_torque)     {  torq = torq + a_torque * 50; }


compEndDef