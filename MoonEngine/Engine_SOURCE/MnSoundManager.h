#pragma once
#include "MoonEngine.h"
#include "MnFmod.h"
#include "MnResources.h"

namespace Mn {
	class MnSoundManager
	{
	private:
	public:
		static void Initialize();
		static void LoadSound();
		static void SoundPlay(const std::wstring sound);
		static void SoundPlay(const std::wstring sound,float vol);
		static void SoundPlay(const std::wstring sound,float vol,bool loop);
		static void SetVolum(const std::wstring sound,float volum);
		static bool IsPlaying(const std::wstring sound);
	};
}


