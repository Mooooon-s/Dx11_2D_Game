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
		Resources::Load<AudioClip>(L"Buy", L"..\\Resources\\Sound\\BUY.ogg");
		Resources::Load<AudioClip>(L"Chomp", L"..\\Resources\\Sound\\chomp.wav");
		Resources::Load<AudioClip>(L"Waring", L"..\\Resources\\Sound\\AWOOGA.ogg");
		Resources::Load<AudioClip>(L"Hit_Sound", L"..\\Resources\\Sound\\zap.wav");
		Resources::Load<AudioClip>(L"Buzzer", L"..\\Resources\\Sound\\BUZZER.ogg");
		Resources::Load<AudioClip>(L"Bubble", L"..\\Resources\\Sound\\BUBBLES.ogg");
		Resources::Load<AudioClip>(L"Menu_Music", L"..\\Resources\\music\\Menu.mp3");
		Resources::Load<AudioClip>(L"DropFood", L"..\\Resources\\Sound\\DROPFOOD.ogg");
		Resources::Load<AudioClip>(L"Alien_music", L"..\\Resources\\music\\Alien.mp3");
		Resources::Load<AudioClip>(L"ButtonSound_Buy",L"..\\Resources\\Sound\\BUY.ogg");
		Resources::Load<AudioClip>(L"TitleBackground", L"..\\Resources\\music\\Title-Screen.wav");
		Resources::Load<AudioClip>(L"Stage_BackGround_Music", L"..\\Resources\\music\\Insaniq2.mp3");
	}
	void MnSoundManager::SoundPlay(const std::wstring sound)
	{
		Resources::Find<Mn::AudioClip>(sound)->Play();
	}
	void MnSoundManager::SoundStop(const std::wstring sound)
	{
		Resources::Find<Mn::AudioClip>(sound)->Stop();
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
