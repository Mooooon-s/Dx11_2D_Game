#include "MnSoundManager.h"
#include "MnAudioClip.h"

namespace Mn {
	void MnSoundManager::Initialize()
	{
		Fmod::Initialize();
		LoadSound();
	}
	void MnSoundManager::LoadSound()
	{
		Resources::Load<Mn::AudioClip>(L"ButtonSound_Buy",L"..\\Resources\\Sound\\BUY.ogg");
		Resources::Load<Mn::AudioClip>(L"DropFood", L"..\\Resources\\Sound\\DROPFOOD.ogg");
		Resources::Load<AudioClip>(L"Waring", L"..\\Resources\\Sound\\AWOOGA.ogg");
		Resources::Load<AudioClip>(L"Alien_music", L"..\\Resources\\music\\Alien.mp3");
	}
	void MnSoundManager::SoundPlay(const std::wstring sound)
	{
		Resources::Find<Mn::AudioClip>(sound)->Play();
	}
	void MnSoundManager::SoundPlay(const std::wstring sound, float vol)
	{
		Resources::Find<Mn::AudioClip>(sound)->SoundPlay(vol);
	}
	void MnSoundManager::SoundPlay(const std::wstring sound, float vol, bool loop)
	{
		Resources::Find<Mn::AudioClip>(sound)->SoundPlay(vol, loop);
	}
	void MnSoundManager::SetVolum(const std::wstring sound,float volum)
	{
		Resources::Find<Mn::AudioClip>(sound)->SetVolum(volum);
	}
	bool MnSoundManager::IsPlaying(const std::wstring sound)
	{
		return Resources::Find<Mn::AudioClip>(sound)->IsPlaying();
	}
}
