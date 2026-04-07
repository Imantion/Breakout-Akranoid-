#include "DestructibleBrick.hpp"

#include <algorithm>

namespace Breakout
{

DestructibleBrick::DestructibleBrick(std::vector<const sf::Texture*> textures,
                                     sf::Vector2f position, float width, float height,
                                     int colorIndex, int hp)
    : Brick(EntityType::Destructible, *textures.at(0), position, width, height, colorIndex)
    , m_Hp(hp)
    , m_MaxHp(hp)
    , m_HpTextures(std::move(textures))
{
}

void DestructibleBrick::OnHit()
{
    m_Hp--;

    if (m_Hp <= 0)
    {
        Kill();
        return;
    }

    _updateTexture();
}

bool DestructibleBrick::IsDestructible() const
{
    return true;
}

int DestructibleBrick::GetHp() const
{
    return m_Hp;
}

int DestructibleBrick::GetMaxHp() const
{
    return m_MaxHp;
}

void DestructibleBrick::_updateTexture()
{
    int damageTaken = m_MaxHp - m_Hp;
    int texIndex = std::min(damageTaken, static_cast<int>(m_HpTextures.size()) - 1);

    if (texIndex >= 0 && texIndex < static_cast<int>(m_HpTextures.size()))
    {
        m_Sprite.setTexture(*m_HpTextures[texIndex], true);
        ScaleToFit();
        m_Sprite.setColor(m_Color);
    }
}

} // namespace Breakout
