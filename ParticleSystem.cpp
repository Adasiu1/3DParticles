#include "ParticleSystem.h"

void ParticleData::generate(size_t count)
{
    this->count = count;
    //wektory
    alive.resize(count, false);
    time.resize(count);
    color.resize(count);
    position.resize(count);
    velocity.resize(count);
    acceleration.resize(count);
}

void ParticleData::swap(size_t first, size_t second)
{
    time.at(first) = time.at(second);
    color.at(first) = color.at(second);
    position.at(first) = position.at(second);
    velocity.at(first) = velocity.at(second);
    acceleration.at(first) = acceleration.at(second);
}

//ustawienie danej cząstki jako nieaktywnej.
void ParticleData::kill(size_t index)
{
    alive.at(index) = false;
    swap(index, alive_count - 1); //przeniesienie tej cząstki na koniec wektora
    --alive_count; //zmniejszenie liczby cząstek aktywnych
}

//budzenie i dodawnie cząsteczek aktywnych
void ParticleData::wake(size_t index)
{
    alive.at(index) = true;
    ++alive_count;
}


void ParticleEmitter::emit(ParticleData *particles, float dt)
{
    //max liczba nowych cząsteczek
    size_t max_new_particles = size_t(dt * emit_rate);
    //index początkowy
    size_t start_id = particles->alive_count;
    //index końcowy
    size_t end_id = std::min(start_id + max_new_particles, particles->count - 1);

    //generowanie
    for (auto &generator : generators)
        generator->generate(particles, dt, start_id, end_id);
    //obudznie cząstek
    for (size_t i = start_id; i < end_id; ++i)
        particles->wake(i);
}

//dodanie generatora cząstek
void ParticleEmitter::addGenerator(std::shared_ptr<ParticleGenerator> generator)
{
    generators.push_back(generator);
}

//konstruktor systemu cząstek
ParticleSystem::ParticleSystem(size_t max_particle_count)
{
    particles.generate(max_particle_count);
}

void ParticleSystem::draw()
{
    //interowanie żywych cząstek
    for (size_t i = 0; i < particles.alive_count; ++i)
    {
        ofSetColor(particles.color.at(i));
        ofDrawSphere(particles.position.at(i), 1);
    }
}

void ParticleSystem::update(float dt)
{
    for (auto &emitter : emitters)
        emitter->emit(&particles, dt);

    for (auto &updater : updaters)
        updater->update(&particles, dt);
}

void ParticleSystem::addEmitter(std::shared_ptr<ParticleEmitter> emitter)
{
    emitters.push_back(emitter);
}

void ParticleSystem::addUpdater(std::shared_ptr<ParticleUpdater> updater)
{
    updaters.push_back(updater);
}
