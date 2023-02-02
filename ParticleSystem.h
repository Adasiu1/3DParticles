#pragma once

#include "ofMain.h"

class ParticleData
{
public:
    ParticleData(){};

    void generate(size_t count);
    void kill(size_t index);
    void wake(size_t index);
    void swap(size_t first, size_t second);

    size_t count{0};
    size_t alive_count{0};
    std::vector<bool> alive;
    std::vector<ofVec3f> time;
    std::vector<ofColor> color;
    std::vector<ofVec3f> position;
    std::vector<ofVec3f> velocity;
    std::vector<ofVec3f> acceleration;
};


// funkcje wirtualkne//
class ParticleGenerator
{
public:
    ParticleGenerator(){};

    virtual void generate(ParticleData *particles, float dt, size_t start_id, size_t end_id) = 0;
};

class ParticleEmitter
{
public:
    ParticleEmitter(float emit_rate, ofVec3f origin) : emit_rate(emit_rate), origin(origin){};

    virtual void emit(ParticleData *particles, float dt);
    void addGenerator(std::shared_ptr<ParticleGenerator> generator);

    ofVec3f origin;
    float emit_rate;
    std::vector<std::shared_ptr<ParticleGenerator>> generators;
};

class ParticleUpdater
{
public:
    ParticleUpdater(){};

    virtual void update(ParticleData *particles, float dt) = 0;
};

class ParticleSystem
{
public:
    ParticleSystem(size_t max_particle_count);

    void draw();
    void update(float dt);

    void addEmitter(std::shared_ptr<ParticleEmitter> emitter);
    void addUpdater(std::shared_ptr<ParticleUpdater> updater);

    ParticleData particles;
    std::vector<std::shared_ptr<ParticleEmitter>> emitters;
    std::vector<std::shared_ptr<ParticleUpdater>> updaters;
};
