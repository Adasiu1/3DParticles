#include "ParticleEmitter.h"

namespace common
{
//definicja generatorów czasu, koloru i pozycji dla SnowfallEmitter i FireEmitter
    auto short_time_generator = std::make_shared<TimeGenerator>(2, 4);
    auto long_time_generator = std::make_shared<TimeGenerator>(6, 12);
    auto random_color_generator = std::make_shared<RandomColorGenerator>();
}

//child do ParticleEmitter
RainEmitter::RainEmitter(float emit_rate, ofVec3f origin, float radius) : ParticleEmitter(emit_rate, origin)
{
    //generator czasu dla długiego czasu życia cząstki
    addGenerator(common::long_time_generator);

    //generator losowego koloru dla cząstek o kolorach od błękitnego do białego
    addGenerator(std::make_shared<RandomColorGenerator>(ofColor(0, 0, 250)));

    //generator pozycji cząstek w postaci cylindra o środku origin i promieniu radius
    addGenerator(std::make_shared<CylinderPositionGenerator>(origin, radius, 0));

    //generator prędkości dla cząstek, które nie poruszają się w żadnym kierunku
    addGenerator(std::make_shared<VelocityGenerator>(ofVec3f(20), ofVec3f(-20)));
}

//child po klasie ParticleEmitter
FireEmitter::FireEmitter(float emit_rate, ofVec3f origin, float radius) : ParticleEmitter(emit_rate, origin)
{
    addGenerator(common::short_time_generator);
    addGenerator(std::make_shared<RandomColorGenerator>(ofColor(255, 0, 0), ofColor(255, 255, 0)));
    addGenerator(std::make_shared<CylinderPositionGenerator>(origin, radius, 0));
    addGenerator(std::make_shared<VelocityGenerator>(ofVec3f(0, 60, 0), ofVec3f(0, 60, 0)));
}
