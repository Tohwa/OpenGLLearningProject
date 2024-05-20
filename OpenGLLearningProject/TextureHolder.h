#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include <vector>
#include <string>

struct TextureHolder {

#pragma region sun
    std::vector<std::string> sunTextures
    {
        "../Textures/2k_sun.jpg"
    };
#pragma endregion

#pragma region mercury
    std::vector<std::string> mercuryTextures
    {
        "../Textures/2k_mercury.jpg"
    };
#pragma endregion
    
#pragma region venus
    std::vector<std::string> venusTextures
    {
        "../Textures/2k_venus_surface.jpg"
    };
#pragma endregion

#pragma region earth
    std::vector<std::string> earthTextures
    {
        "../Textures/2k_earth_daymap.jpg",
        "../Textures/2k_earth_clouds.jpg"
    };
#pragma endregion

#pragma region mars
    std::vector<std::string> marsTextures
    {
        "../Textures/2k_mars.jpg"
    };
#pragma endregion

#pragma region jupiter
    std::vector<std::string> jupiterTextures
    {
        "../Textures/2k_jupiter.jpg"
    };
#pragma endregion

#pragma region saturn
    std::vector<std::string> saturnTextures
    {
        "../Textures/2k_saturn.jpg"
    };
#pragma endregion

#pragma region uranus
    std::vector<std::string> uranusTextures
    {
        "../Textures/2k_uranus.jpg"
    };
#pragma endregion

#pragma region neptune
    std::vector<std::string> neptuneTextures
    {
        "../Textures/2k_neptune.jpg"
    };
#pragma endregion   
};

#endif // !TEXTUREHOLDER_H
