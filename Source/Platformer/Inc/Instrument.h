#ifndef _INSTRUMENT_H_
#define _INSTRUMENT_H_

#include "GameEngine.h"
#include <map>

class CInstrument
{
public:
	CInstrument(string Directory);
	virtual ~CInstrument() {}

	virtual void PlaySound(string SoundName);
	virtual void StopSound(string SoundName);
	virtual vector<string> GetSoundNames();
	virtual map<unsigned int, string> GetCategories();

	static vector<string> GetNoteNames();

protected:
	string GetSoundFileName(string SoundName, float& outPitch);

	map<string, int> SoundMap;
	vector<string> SoundNames;
	vector<float> Frequencies;
	map<unsigned int, string> Categories;
	bool bIsNotes;

	static vector<string> NoteNames;
};

#endif