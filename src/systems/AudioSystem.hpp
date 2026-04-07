#pragma once

#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <vector>
#include "utils/robin_hood.hpp"

namespace Breakout
{

class AudioSystem
{
public:
    void LoadAll(const std::string& directory);

    void PlaySound(const std::string& name);
    void PlayMusic(const std::string& filepath, bool loop = true);
    void StopMusic();

    void SetMusicVolume(float volume);
    void SetSoundVolume(float volume);

    void SubscribeToEvents();

private:
    robin_hood::unordered_map<std::string, sf::SoundBuffer> m_Buffers;
    std::vector<sf::Sound>     m_SoundPool;
    std::unique_ptr<sf::Music> m_Music;
    float m_MusicVolume;
    float m_SoundVolume;
};

} // namespace Breakout
