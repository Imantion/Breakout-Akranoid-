#include "BrickFactory.hpp"
#include "DestructibleBrick.hpp"
#include "InvulnerableBrick.hpp"
#include "Game.hpp"

namespace Breakout
{

std::unique_ptr<Brick> BrickFactory::CreateDestructible(sf::Vector2f position,
                                                        float width, float height,
                                                        int colorIndex, int hp)
{
    auto& texMgr = Game::Get()->GetTextureManager();

    std::vector<const sf::Texture*> textures;
    textures.push_back(&texMgr.GetTexture("brick"));

    if (hp >= 2)
        textures.push_back(&texMgr.GetTexture("brick_cracked"));

    return std::make_unique<DestructibleBrick>(
        std::move(textures), position, width, height, colorIndex, hp);
}

std::unique_ptr<Brick> BrickFactory::CreateInvulnerable(sf::Vector2f position,
                                                        float width, float height,
                                                        int colorIndex)
{
    auto& texMgr = Game::Get()->GetTextureManager();

    return std::make_unique<InvulnerableBrick>(
        texMgr.GetTexture("brick_invulnerable"), position, width, height, colorIndex);
}

} // namespace Breakout
