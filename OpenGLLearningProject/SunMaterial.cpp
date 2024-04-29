#include "SunMaterial.h"

const int SunMaterial::Initialize(GameObject& _gameObject)
{
    m_shader = SShader("LitVertex.glsl","LitFragment.glsl");
    _gameObject.m_shader = &m_shader;

    
    return 0;
}

const int SunMaterial::Update()
{
    return 0;
}

const int SunMaterial::Draw()
{
    return 0;
}

void SunMaterial::Finalize()
{
}
