#include "CResourceManager.h"

std::map<std::string, sf::Image*> CResourceManager::m_images;

std::map<std::string, sf::Font*> CResourceManager::m_fonts;

/// <summary>
/// Return image by name
/// <para>Author: Nerys</para>
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
sf::Image *CResourceManager::GetImage(std::string _name)
{
    if (m_images.find(_name) != m_images.end()) return m_images.at(_name);
    else {
        std::cerr << "\nWARNING: <CResourceManager::GetFont> image " << _name << " does not exist.\n";
        return nullptr;
    }
}

/// <summary>
/// Loads image into map
/// <para>Author: Nerys</para>
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_name"></param>
void CResourceManager::LoadImage(std::string _name)
{
    sf::Image *out = new sf::Image();
    if (!out->loadFromFile(GRAPHICS_FILEPATH + _name)) {
        std::cerr << "\nWARNING: <CResourceManager::LoadFont> image " << _name << " does not exist.\n";
        return;
    }
    m_images.try_emplace(_name, out);
}

/// <summary>
/// Gets font by name
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_name"></param>
/// <returns></returns>
sf::Font* CResourceManager::GetFont(std::string _name)
{
    if (m_fonts.find(_name) != m_fonts.end()) return m_fonts.at(_name);
    else {
        std::cerr << "\nWARNING: <CResourceManager::GetFont> font " << _name << " does not exist.\n";
        return nullptr;
    }
}

/// <summary>
/// Loads font into map
/// <para>Author: Keane</para>
/// </summary>
/// <param name="_name"></param>
void CResourceManager::LoadFont(std::string _name)
{
    sf::Font* out = new sf::Font();
    if (!out->loadFromFile(FONTS_FILEPATH + _name)) {
        std::cerr << "\nWARNING: <CResourceManager::LoadFont> font " << _name << " does not exist.\n";
        return;
    }
    m_fonts.try_emplace(_name, out);
}