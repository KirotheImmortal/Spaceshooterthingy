#pragma once
#include "Component.h"
#include "ccollisionutils.h"
#include <list>

compDef(Collider)

int faction;
int isBullet;
Shape shape;

std::list<Entity *> contacts;

Collider() : faction(0), isBullet(0) {};



compEndDef
