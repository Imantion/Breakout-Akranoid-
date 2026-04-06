#pragma once

#include "LevelData.hpp"
#include "entities/Brick.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Breakout
{

class LevelLoader
{
public:
    void LoadCampaign(const std::string& path);

    std::vector<std::unique_ptr<Brick>> LoadLevel(int index);

    bool HasNextLevel(int currentIndex) const;
    int  GetLevelCount() const;

private:
    static LevelData                           _parseLevel(const std::string& path);
    static std::vector<std::unique_ptr<Brick>> _createBricks(const LevelData& level);

    std::vector<std::string> m_Campaign;
    std::string              m_LevelsDirectory;
};

} // namespace Breakout
