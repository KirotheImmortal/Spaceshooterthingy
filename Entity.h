
#pragma once

#include "Transform.h"
#include "Rigidbody.h"
#include "Render.h"
#include "Controller.h"
#include "Collider.h"
#include "Lifetime.h"
#include "TextRender.h"


#define entityFree(e)  do { \
						compFree(e, transform); \
						compFree(e, rigidbody); \
						compFree(e, render); \
						compFree(e, collider); \
						compFree(e, controller); \
						compFree(e, lifetime);  \
						compFree(e, textrender); \
						} while (0)


struct Entity
{
	bool active, added, removed;
	int factoryIndex;
	Transform	*transform;
	Rigidbody	*rigidbody;
	Render		*render;
	Controller	*controller;
	Collider	*collider;
	Lifetime	*lifetime;
	Text		*textrender;
	
	


	Entity(int UID) : factoryIndex(UID), active(false),
		transform(0),
		rigidbody(0),
		render(0),
		controller(0),
		collider(0),
		lifetime(0),
		textrender(0),
		added(false),
		removed(false) { }
};