#pragma once

#include "Brick.hpp"

#include <vector>

namespace Breakout
{

class DestructibleBrick : public Brick
{
public:
    DestructibleBrick(std::vector<const sf::Texture*> textures, sf::Vector2f position,
                      float width, float height, int colorIndex, int hp);

    void OnHit() override;
    bool IsDestructible() const override;

    int GetHp()    const;
    int GetMaxHp() const;

private:
    void _updateTexture();

    int                             m_Hp;
    int                             m_MaxHp;
    std::vector<const sf::Texture*> m_HpTextures;
};

} // namespace Breakout
