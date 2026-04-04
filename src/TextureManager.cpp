#include "TextureManager.hpp"

#include <filesystem>
#include <stdexcept>

namespace Breakout
{

void TextureManager::LoadAll(const std::string& directory)
{
    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (!entry.is_regular_file())
            continue;

        auto ext = entry.path().extension().string();
        if (ext != ".png" && ext != ".jpg" && ext != ".jpeg" && ext != ".bmp")
            continue;

        std::string key = entry.path().stem().string();
        sf::Texture texture(entry.path().string());
        m_Textures.emplace(std::move(key), std::move(texture));
    }
}

const sf::Texture& TextureManager::GetTexture(const std::string& name) const
{
    auto it = m_Textures.find(name);
    if (it == m_Textures.end())
        throw std::runtime_error("Texture not found: " + name);

    return it->second;
}

} // namespace Breakout
