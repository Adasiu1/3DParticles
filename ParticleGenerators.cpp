#include "ParticleGenerators.h"


//random czas życia cząsteczek
void TimeGenerator::generate(ParticleData *particles, float dt, size_t start_id, size_t end_id)
{
    for (size_t i = start_id; i < end_id; ++i)
    {
        //zakres życia cząsteczki
        float lifetime = ofRandom(min, max);
        particles->time.at(i) = ofVec3f(lifetime, 1.0f / lifetime, 0.f);
    }
}

void RandomColorGenerator::generate(ParticleData *particles, float dt, size_t start_id, size_t end_id)
{
    for (size_t i = start_id; i < end_id; ++i)
    {
        particles->color.at(i) = ofColor(
            ofRandom(min.r, max.r),
            ofRandom(min.g, max.g),
            ofRandom(min.b, max.b));
    }
}


//randomwoe pozycje cząsteczek w cylindrycznej przestrzeni
void CylinderPositionGenerator::generate(ParticleData *particles, float dt, size_t start_id, size_t end_id)
{
    for (size_t i = start_id; i < end_id; ++i)
    {
        //randomowey kąt nachylenia
        float theta = ofRandom(2 * PI);
        //randomowa odległość od środka cylindru
        float u = ofRandom(radius) + 70;
        float r = u > radius ? 2 - u : u;
        //współrzędne
        float x = origin.x + r * cos(theta);
        float y = origin.y + ofRandom(-height / 2, height);
        float z = origin.z + r * sin(theta);
        //ustaw pozycję cząsteczki
        particles->position.at(i) = ofVec3f(x, y, z);
    }
}

void VelocityGenerator::generate(ParticleData *particles, float dt, size_t start_id, size_t end_id)
{
    for (size_t i = start_id; i < end_id; ++i)
    {
        //randomowa prędkość cząteczki
        particles->velocity.at(i) = ofVec3f(
            ofRandom(min.x, max.x),
            ofRandom(min.y, max.y),
            ofRandom(min.z, max.z));
    }
}
