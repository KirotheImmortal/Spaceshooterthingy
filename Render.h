#pragma once
#include "Component.h"

compDef(Render)

std::string shader, texture, mesh;
float frame = 0, frameRate = 1;

compEndDef