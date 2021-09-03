#include "CResourceManager.h"

sf::Image *CResourceManager::GetImage(std::string _name)
{
    return m_images.at(_name);
}
void CResourceManager::LoadImage(std::string _name)
{
    sf::Image *out = new sf::Image();
    out->loadFromFile(FILEPATH + _name);
    m_images.try_emplace(_name, out);
}

std::map<std::string, sf::Image *> CResourceManager::m_images;