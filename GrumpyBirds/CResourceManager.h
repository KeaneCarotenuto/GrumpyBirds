#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <map>
#include <iostream>

#define GRAPHICS_FILEPATH "Resources/Graphics/"
#define FONTS_FILEPATH "Resources/Fonts/"

/// <summary>
/// Resource manager class
/// <para>Author: Nerys</para>
/// <para>Author: Keane</para>
/// </summary>
class CResourceManager
{
public:
    static sf::Image *GetImage(std::string _name);
    static void LoadImage(std::string _name);

    static sf::Font* GetFont(std::string _name);
    static void LoadFont(std::string _name);

private:
    static std::map<std::string, sf::Image *> m_images;

    static std::map<std::string, sf::Font *> m_fonts;
};

#endif