#include "CResourceManager.h"

std::map<std::string, sf::Image*> CResourceManager::m_images;

std::map<std::string, sf::Font*> CResourceManager::m_fonts;

sf::Image *CResourceManager::GetImage(std::string _name)
{
    return m_images.at(_name);
}
void CResourceManager::LoadImage(std::string _name)
{
    sf::Image *out = new sf::Image();
    out->loadFromFile(GRAPHICS_FILEPATH + _name);
    m_images.try_emplace(_name, out);
}

sf::Font* CResourceManager::GetFont(std::string _name)
{
    return m_fonts.at(_name);
}

void CResourceManager::LoadFont(std::string _name)
{
    sf::Font* out = new sf::Font();
    out->loadFromFile(FONTS_FILEPATH + _name);
    m_fonts.try_emplace(_name, out);
}