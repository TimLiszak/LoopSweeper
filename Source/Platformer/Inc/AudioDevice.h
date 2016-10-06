#ifndef _AUDIODEVICE_H_
#define _AUDIODEVICE_H_

#include "GameEngine.h"
#include "Window.h"
#include "fmod.hpp"
#include <vector>
#include <string>
using namespace std;

class CAudioDevice
{
public:
	static CAudioDevice* Get()
	{
		if (!pInstance)
		{
			pInstance = new CAudioDevice();
		}
		return pInstance;
	}

	virtual ~CAudioDevice() {}

	virtual void Init();
	virtual void Update(const FLOAT DeltaTime);

	virtual int CreateSound(string SoundFile);
	virtual void PlaySound(int SoundId, float Pitch = 1.0f);
	virtual void StopSound(int SoundId);

	virtual float GetFrequency(int Note);

protected:
	CAudioDevice() : AudioSystem(nullptr) {}
	static CAudioDevice*		pInstance;
	class FMOD::System*			AudioSystem;

	vector<class FMOD::Sound*> Sounds;
	map<int, FMOD::Channel*> Channels;
};

#endif