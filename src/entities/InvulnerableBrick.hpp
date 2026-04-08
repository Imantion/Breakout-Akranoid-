#pragma once

#include "Brick.hpp"

namespace Breakout
{

class InvulnerableBrick : public Brick
{
public:
    InvulnerableBrick(const sf::Texture& texture, sf::Vector2f position,
                      float width, float height, int colorIndex);

    void OnHit(uuids::uuid hitWith) override;
    bool IsDestructible() const override;
};

} // namespace Breakout
