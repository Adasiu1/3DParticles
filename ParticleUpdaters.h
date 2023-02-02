#pragma once

#include "ParticleSystem.h"

//aktualizacja pozycji przy uwzględnieniu podłogi
class FloorUpdater : public ParticleUpdater
{
public:
    //ustawienie podłogi na poziomi -1.0f

    FloorUpdater(float floor_level = -1.0f) : floor_level(floor_level), floor_color(ofColor(0, 0, 255)){};

    void update(ParticleData *particles, float dt) override;
    
    //wartość poziomu podłogi
    float floor_level;
    ofColor floor_color;
};

//aktualizacja pozycji względem grawitacji
class GravityUpdater : public ParticleUpdater
{
public:
    //wartość grawitacji
    GravityUpdater(ofVec3f gravity = ofVec3f(0, -9.81f, 0)) : gravity(gravity){};

    void update(ParticleData *particles, float dt) override;

    //wektor grawitacji
    ofVec3f gravity;
};

//aktualizacja pozycji z wykorzystaniem metody Eulera
class EulerUpdater : public ParticleUpdater
{
public:
    void update(ParticleData *particles, float dt) override;
};

class TimeUpdater : public ParticleUpdater
{
public:
    void update(ParticleData *particles, float dt) override;
};

//aktualziacaja koloru w zależności od czasu życia cząsteczki 
class TimeColorUpdater : public ParticleUpdater
{
public:
    void update(ParticleData *particles, float dt) override;

    ofColor min_color;
    ofColor max_color;
};
