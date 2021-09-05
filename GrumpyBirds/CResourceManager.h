#ifndef CRESOURCEMANAGER_H
#define CRESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Font.hpp>
#include <map>
#include <iostream>

#define FILEPATH "Resources/Graphics/"

/// <summary>
/// Resource manager class
/// <para>Author: Nerys</para>
/// </summary>
class CResourceManager
{
public:
    static sf::Image *GetImage(std::string _name);
    static void LoadImage(std::string _name);

private:
    static std::map<std::string, sf::Image *> m_images;
};

#endif