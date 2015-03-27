#pragma once


#include "Component.h"


compDef(Lifetime)

float timer, life;

Lifetime() : timer(0), life(.5) {}

compEndDef