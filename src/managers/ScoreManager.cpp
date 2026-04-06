#include "managers/ScoreManager.hpp"
#include "core/Constants.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <numeric>

namespace Breakout
{

void ScoreManager::Load(const std::string& path)
{
    m_Scores.clear();

    std::ifstream file(path);
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::istringstream stream(line);
        ScoreEntry entry;
        if (stream >> entry.levelIndex >> entry.name >> entry.score)
            m_Scores.push_back(std::move(entry));
    }

    _sortAndTrim();
}

void ScoreManager::Save(const std::string& path) const
{
    std::ofstream file(path);
    if (!file.is_open())
        return;

    for (const auto& entry : m_Scores)
        file << entry.levelIndex << " " << entry.name << " " << entry.score << "\n";
}

void ScoreManager::AddScore(int levelIndex, const std::string& name, int score)
{
    m_Scores.push_back({levelIndex, name, score});
    _sortAndTrim();
}

int ScoreManager::GetBestScore(int levelIndex) const
{
    for (const auto& entry : m_Scores)
    {
        if (entry.levelIndex == levelIndex)
            return entry.score;
    }
    return 0;
}

int ScoreManager::GetBestTotalScore() const
{
    if (m_Scores.empty())
        return 0;

    return m_Scores.front().score;
}

int ScoreManager::GetTotalScore() const
{
    return std::accumulate(m_Scores.begin(), m_Scores.end(), 0,
        [](int sum, const ScoreEntry& entry) { return sum + entry.score; });
}

const std::vector<ScoreEntry>& ScoreManager::GetScores() const
{
    return m_Scores;
}

void ScoreManager::_sortAndTrim()
{
    std::sort(m_Scores.begin(), m_Scores.end(),
        [](const ScoreEntry& a, const ScoreEntry& b) { return a.score > b.score; });

    if (static_cast<int>(m_Scores.size()) > g_MaxScoreEntries)
        m_Scores.resize(g_MaxScoreEntries);
}

} // namespace Breakout
