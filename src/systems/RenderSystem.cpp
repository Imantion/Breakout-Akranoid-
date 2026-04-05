#include "RenderSystem.hpp"

#include <ranges>
#include <algorithm>
namespace Breakout
{

void RenderSystem::BeginFrame(sf::RenderWindow& window)
{
    window.clear(sf::Color(30, 30, 46));
}

void RenderSystem::EndFrame(sf::RenderWindow& window)
{
    window.display();
}

void RenderSystem::DrawActor(sf::RenderWindow& window, const Actor& actor)
{
    actor.Draw(window);
}

void RenderSystem::DrawBricks(sf::RenderWindow& window, const std::vector<Brick>& bricks)
{
    if (bricks.empty())
        return;

    const sf::Texture& brickTex = bricks.front().GetSprite().getTexture();
    auto texSize = brickTex.getSize();
    float tu = static_cast<float>(texSize.x);
    float tv = static_cast<float>(texSize.y);

    int aliveCount = std::ranges::count_if(bricks, [](const Brick& b) { return b.IsAlive(); });
    sf::VertexArray brickBatch{sf::PrimitiveType::Triangles};
    brickBatch.resize(aliveCount * 6); // 6 vertices per brick

    int index = 0;
    for (const auto& brick : bricks)
    {
        if (!brick.IsAlive())
            continue;

        auto pos   = brick.GetPosition();
        float w    = brick.GetWidth();
        float h    = brick.GetHeight();
        auto color = brick.GetColor();

        brickBatch[index++] = sf::Vertex{.position = {pos.x,     pos.y},     .color = color, .texCoords = {0.0f, 0.0f}};
        brickBatch[index++] = sf::Vertex{.position = {pos.x + w, pos.y},     .color = color, .texCoords = {tu,   0.0f}};
        brickBatch[index++] = sf::Vertex{.position = {pos.x + w, pos.y + h}, .color = color, .texCoords = {tu,   tv}};

        brickBatch[index++] = sf::Vertex{.position = {pos.x,     pos.y},     .color = color, .texCoords = {0.0f, 0.0f}};
        brickBatch[index++] = sf::Vertex{.position = {pos.x + w, pos.y + h}, .color = color, .texCoords = {tu,   tv}};
        brickBatch[index++] = sf::Vertex{.position = {pos.x,     pos.y + h}, .color = color, .texCoords = {0.0f, tv}};
    }

    sf::RenderStates states(&brickTex);
    window.draw(brickBatch, states);
}

void RenderSystem::DrawLabel(sf::RenderWindow& window, const Label& label)
{
    label.Draw(window);
}

void RenderSystem::DrawButton(sf::RenderWindow& window, const Button& button)
{
    button.Draw(window);
}

} // namespace Breakout
