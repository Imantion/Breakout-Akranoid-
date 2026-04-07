#include "BrickFactory.hpp"
#include "DestructibleBrick.hpp"
#include "InvulnerableBrick.hpp"
#include "core/Constants.hpp"
#include "core/Game.hpp"

namespace Breakout
{

std::unique_ptr<Brick> BrickFactory::CreateDestructible(sf::Vector2f position,
                                                        float width, float height,
                                                        int colorIndex, int hp)
{
    auto& texMgr = Game::Get()->GetTextureManager();

    std::vector<const sf::Texture*> textures;
    textures.push_back(&texMgr.GetTexture(g_TexBrick));

    if (hp >= g_CrackTextureMinHp)
        textures.push_back(&texMgr.GetTexture(g_TexBrickCracked));

    return std::make_unique<DestructibleBrick>(
        std::move(textures), position, width, height, colorIndex, hp);
}

std::unique_ptr<Brick> BrickFactory::CreateInvulnerable(sf::Vector2f position,
                                                        float width, float height,
                                                        int colorIndex)
{
    auto& texMgr = Game::Get()->GetTextureManager();

    return std::make_unique<InvulnerableBrick>(
        texMgr.GetTexture(g_TexBrickInvulnerable), position, width, height, colorIndex);
}

} // namespace Breakout
