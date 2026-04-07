#include "systems/AudioSystem.hpp"
#include "core/Constants.hpp"
#include "core/Game.hpp"
#include "events/Events.hpp"

#include <filesystem>

namespace Breakout
{

void AudioSystem::LoadAll(const std::string& directory)
{
    m_MusicVolume = g_DefaultMusicVolume;
    m_SoundVolume = g_DefaultSoundVolume;

    if (!std::filesystem::exists(directory))
        return;

    for (const auto& entry : std::filesystem::directory_iterator(directory))
    {
        if (!entry.is_regular_file())
            continue;

        auto ext = entry.path().extension().string();
        if (ext != ".wav" && ext != ".ogg" && ext != ".flac")
            continue;

        std::string key = entry.path().stem().string();

        try
        {
            sf::SoundBuffer buffer(entry.path().string());
            m_Buffers.emplace(std::move(key), std::move(buffer));
        }
        catch (...)
        {
        }
    }
}

void AudioSystem::PlaySound(const std::string& name)
{
    auto it = m_Buffers.find(name);
    if (it == m_Buffers.end())
        return;

    for (auto& sound : m_SoundPool)
    {
        if (sound.getStatus() == sf::Sound::Status::Stopped)
        {
            sound.setBuffer(it->second);
            sound.setVolume(m_SoundVolume);
            sound.play();
            return;
        }
    }

    m_SoundPool.emplace_back(it->second);
    m_SoundPool.back().setVolume(m_SoundVolume);
    m_SoundPool.back().play();
}

void AudioSystem::PlayMusic(const std::string& filepath, bool loop)
{
    StopMusic();

    if (!std::filesystem::exists(filepath))
        return;

    m_Music = std::make_unique<sf::Music>(filepath);
    m_Music->setLooping(loop);
    m_Music->setVolume(m_MusicVolume);
    m_Music->play();
}

void AudioSystem::StopMusic()
{
    if (m_Music)
    {
        m_Music->stop();
        m_Music.reset();
    }
}

void AudioSystem::SetMusicVolume(float volume)
{
    m_MusicVolume = volume;
    if (m_Music)
        m_Music->setVolume(m_MusicVolume);
}

void AudioSystem::SetSoundVolume(float volume)
{
    m_SoundVolume = volume;
}

void AudioSystem::SubscribeToEvents()
{
    auto& bus = Game::Get()->GetEventBus();

    bus.Subscribe<BallHitBrickEvent>([this](const BallHitBrickEvent&)
    {
        PlaySound(g_SfxBrickHit);
    });

    bus.Subscribe<BallHitWallEvent>([this](const BallHitWallEvent&)
    {
        PlaySound(g_SfxWallHit);
    });

    bus.Subscribe<BallHitPaddleEvent>([this](const BallHitPaddleEvent&)
    {
        PlaySound(g_SfxPaddleHit);
    });

    bus.Subscribe<AbilityPickedUpEvent>([this](const AbilityPickedUpEvent&)
    {
        PlaySound(g_SfxAbilityPickup);
    });

    bus.Subscribe<BallLostEvent>([this](const BallLostEvent&)
    {
        PlaySound(g_SfxBallLost);
    });
}

} // namespace Breakout
