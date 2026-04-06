#pragma once

#include <string>
#include <vector>

namespace Breakout
{

struct ScoreEntry
{
    int         levelIndex;
    std::string name;
    int         score;
};

class ScoreManager
{
public:
    void Load(const std::string& path);
    void Save(const std::string& path) const;

    void AddScore(int levelIndex, const std::string& name, int score);

    int GetBestScore(int levelIndex) const;
    int GetBestTotalScore() const;
    int GetTotalScore() const;
    const std::vector<ScoreEntry>& GetScores() const;

private:
    void _sortAndTrim();

    std::vector<ScoreEntry> m_Scores;
};

} // namespace Breakout
