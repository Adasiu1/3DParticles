#pragma once

#include "ParticleSystem.h"
#include "ParticleEmitter.h"
#include "ParticleGenerators.h"
#include "ParticleUpdaters.h"

class ofApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
    float floor_level;
	ofTime time;
	ofEasyCam camera;
	ParticleSystem particle_system{10000};
};
