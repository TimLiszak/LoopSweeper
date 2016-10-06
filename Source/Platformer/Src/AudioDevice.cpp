#include "StdAfx.h"
#include "AudioDevice.h"

CAudioDevice* CAudioDevice::pInstance = NULL;

void CAudioDevice::Init()
{
	FMOD::System_Create(&AudioSystem);      // Create the main system object.
	AudioSystem->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
}

int CAudioDevice::CreateSound(string SoundFile)
{
	string Extension(".WAV");
	string Filename = SOUND_DIRECTORY + SoundFile + Extension;

	FMOD::Sound* sound = nullptr;
	AudioSystem->createSound(Filename.c_str(), FMOD_DEFAULT, 0, &sound);

	if (sound)
	{
		Sounds.push_back(sound);
		return Sounds.size() - 1;
	}
	return -1;
}

void CAudioDevice::PlaySound(int SoundId, float Pitch)
{
	if (SoundId < 0 || SoundId > (int)Sounds.size() || !Sounds[SoundId])
		return;

	FMOD::Channel* Channel = nullptr;
	AudioSystem->playSound(Sounds[SoundId], NULL, false, &Channel);
	Channel->setPitch(Pitch);

	Channels[SoundId] = Channel;
}

void CAudioDevice::StopSound(int SoundId)
{
	FMOD::Channel* Channel = Channels[SoundId];
	Channel->setVolume(0.0f);
	//Channel->setPaused(true);
}

void CAudioDevice::Update(const FLOAT DeltaTime)
{
	AudioSystem->update();
}

float CAudioDevice::GetFrequency(int Note)
{
	return pow(2.0f, ((float)Note - 49.0f) / 12.0f) * 440.0f;
}
