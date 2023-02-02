#pragma once

#include "ParticleGenerators.h"

class RainEmitter : public ParticleEmitter
{
public:
    RainEmitter(float emit_rate, ofVec3f origin, float radius);
};

class FireEmitter : public ParticleEmitter
{
public:
    FireEmitter(float emit_rate, ofVec3f origin, float radius);
};
