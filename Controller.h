#pragma once
#include "Component.h"

compDef(Controller)

char left, right, up,  fire;
float speed = 50, torque = 1, m_delay, m_timer;

Controller() :  m_timer(0) {}

compEndDef
