#include "ParticleUpdaters.h"

//update cząsteczek w zależności od podłogi
void FloorUpdater::update(ParticleData *particles, float dt)
{
    //id ostaniej żywej cząsteczki
    size_t end_id = particles->alive_count;
    //dla każdej cząsteczki
    for (size_t i = 0; i < end_id; ++i)
    {
        //jeśli cząsteczka prazekracza poziom podłogi, ustaw poiom cząsteczki na poziomie podłogi
        if (particles->position.at(i).y < floor_level)
            particles->position.at(i).y = floor_level;
    }
}


void GravityUpdater::update(ParticleData *particles, float dt)
{
    size_t end_id = particles->alive_count;

    for (size_t i = 0; i < end_id; ++i)
        //dodaj wektor przyśpieszenia grawitacyjnego
        particles->acceleration.at(i) += gravity;
}

void EulerUpdater::update(ParticleData *particles, float dt)
{
    size_t end_id = particles->alive_count;
    for (size_t i = 0; i < end_id; ++i)
    {
        //do wektora prędkości dodaj wektor przyspieszenia pomnożony przez delta t
        particles->velocity.at(i) += particles->acceleration.at(i) * dt;
        //do wektora pozycji dodaj wektor prędkości pomnożony przez delta t
        particles->position.at(i) += particles->velocity.at(i) * dt;
        //reset wektoru przyśpiesznia
        particles->acceleration.at(i) = ofVec3f(0.f);
    }
}

//update czasu dla cząstek
void TimeUpdater::update(ParticleData *particles, float dt)
{
    size_t end_id = particles->alive_count;
    for (size_t i = 0; i < end_id; ++i)
    {
        //update czasu dla i-tej cząstki
        particles->time.at(i).x -= dt;
        particles->time.at(i).z = particles->time.at(i).x * particles->time.at(i).y;
        //czy czas dla i-tej cząstki wyczerpał się
        if (particles->time.at(i).x <= 0)
        {
            //tak, to "kill" tą cząstkę
            particles->kill(i);
            //update id ostatniej żywej cząstki
            end_id = particles->alive_count < particles->count ? particles->alive_count : particles->count;
        }
    }
}


void TimeColorUpdater::update(ParticleData *particles, float dt)
{

    size_t end_id = particles->alive_count;
    for (size_t i = 0; i < end_id; ++i)
        //update koloru dla i-tej cząstki na podstawie jej czasu
        particles->color.at(i).a = particles->time.at(i).z * 250.f;
}


