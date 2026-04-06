#include "LevelLoader.hpp"
#include "Constants.hpp"
#include "entities/BrickFactory.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Breakout
{

void LevelLoader::LoadCampaign(const std::string& path)
{
    m_LevelsDirectory = std::filesystem::path(path).parent_path().string();

    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open campaign file: " + path);

    m_Campaign.clear();
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        m_Campaign.push_back(line);
    }
}

std::vector<std::unique_ptr<Brick>> LevelLoader::LoadLevel(int index)
{
    const std::string& levelFile = m_Campaign.at(index);
    std::string levelPath = m_LevelsDirectory + "/" + levelFile;

    LevelData level = _parseLevel(levelPath);
    return _createBricks(level);
}

bool LevelLoader::HasNextLevel(int currentIndex) const
{
    return (currentIndex + 1) < static_cast<int>(m_Campaign.size());
}

int LevelLoader::GetLevelCount() const
{
    return static_cast<int>(m_Campaign.size());
}

LevelData LevelLoader::_parseLevel(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to open level file: " + path);

    LevelData level{};
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::istringstream stream(line);
        std::vector<BrickCell> row;
        std::string token;

        while (stream >> token)
        {
            BrickCell cell{};

            if (token == "x")
            {
                cell.isEmpty = true;
            }
            else if (token == "i")
            {
                cell.isInvulnerable = true;
            }
            else
            {
                cell.hp = std::stoi(token);
            }

            row.push_back(cell);
        }

        if (!row.empty())
        {
            if (level.columns == 0)
                level.columns = static_cast<int>(row.size());

            level.grid.push_back(std::move(row));
        }
    }

    level.rows = static_cast<int>(level.grid.size());
    return level;
}

std::vector<std::unique_ptr<Brick>> LevelLoader::_createBricks(const LevelData& level)
{
    float leftMargin = (g_WindowWidth -
        (level.columns * (g_BrickWidth + g_BrickPadding) - g_BrickPadding)) / 2.0f;

    std::vector<std::unique_ptr<Brick>> bricks;
    bricks.reserve(level.rows * level.columns);

    for (int row = 0; row < level.rows; ++row)
    {
        for (int col = 0; col < level.columns; ++col)
        {
            const auto& cell = level.grid[row][col];

            if (cell.isEmpty)
                continue;

            float x = leftMargin + col * (g_BrickWidth + g_BrickPadding);
            float y = g_BrickGridTopMargin + row * (g_BrickHeight + g_BrickPadding);
            auto pos = sf::Vector2f{x, y};

            if (cell.isInvulnerable)
                bricks.push_back(BrickFactory::CreateInvulnerable(pos, g_BrickWidth, g_BrickHeight, row));
            else
                bricks.push_back(BrickFactory::CreateDestructible(pos, g_BrickWidth, g_BrickHeight, row, cell.hp));
        }
    }

    return bricks;
}

} // namespace Breakout
