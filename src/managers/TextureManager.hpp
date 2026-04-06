#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>

namespace Breakout
{

class TextureManager
{
public:
    void LoadAll(const std::string& directory);

    const sf::Texture& GetTexture(const std::string& name) const;

private:
    std::unordered_map<std::string, sf::Texture> m_Textures;
};

} // namespace Breakout
