#include "Light.h"

// Initialize the Light component with the given shader.
// This method retrieves the locations of the light-related uniform variables from the shader.
void Light::Initialize(SShader* _shader)
{
    m_shader = _shader; // Store the reference to the shader

    // Retrieve the locations of the uniform variables in the shader
    m_posID = glGetUniformLocation(m_shader->id, "light.position");
    m_ambientID = glGetUniformLocation(m_shader->id, "light.ambient");
    m_diffID = glGetUniformLocation(m_shader->id, "light.diffuse");
    m_specID = glGetUniformLocation(m_shader->id, "light.specular");

    m_attConst = glGetUniformLocation(m_shader->id, "light.attConst");
    m_attLinear = glGetUniformLocation(m_shader->id, "light.attLin");
    m_attQuad = glGetUniformLocation(m_shader->id, "light.attQuad");
}

// Apply the light settings to the shader.
// This method sets the values of the light-related uniform variables in the shader.
void Light::Draw()
{
    m_shader->Use(); // Activate the shader

    // Set the values for the light's uniform variables
    glUniform3fv(m_posID, 1, &position.x); // Set light position
    glUniform3fv(m_ambientID, 1, &ambient.x); // Set ambient color
    glUniform3fv(m_diffID, 1, &diffuse.x); // Set diffuse color
    glUniform3fv(m_specID, 1, &specular.x); // Set specular color

    // Set the values for the attenuation uniform variables
    glUniform1fv(m_attConst, 1, &attenuationConst); // Set constant attenuation
    glUniform1fv(m_attLinear, 1, &attenuationLinear); // Set linear attenuation
    glUniform1fv(m_attQuad, 1, &attenuationQuad); // Set quadratic attenuation
}