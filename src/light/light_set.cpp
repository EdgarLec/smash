#include "Include.hpp"
#include "light.hpp"

Light::Light()
{
    // state.blendMode = sf::BlendAlpha;
    state.blendMode = sf::BlendAdd;
    state.shader = NULL;
    arr_vrtx = new sf::VertexArray();
    sf::RenderStates tmp;
    tmp.blendMode = state.blendMode;
    state.shader = state.shader;


    arr_vrtx->setPrimitiveType(sf::TriangleFan);
    angles = new dir_t[320 * 240];
    buffer = new dir_t[320 * 240];
}

Light::~Light()
{
    delete angles;
    delete buffer;
}