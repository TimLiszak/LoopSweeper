#include "StdAfx.h"
#include "Instrument.h"
#include "AudioDevice.h"

vector<string> CInstrument::NoteNames;

CInstrument::CInstrument(string Directory)
{
	HANDLE hFind;
	WIN32_FIND_DATA data;

	bIsNotes = true;

	string SearchDir = SOUND_DIRECTORY + Directory + string("\\*.WAV");
	hFind = FindFirstFile(SearchDir.c_str(), &data);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do 
		{
			string File = data.cFileName;
			string SoundName = File.substr(0, File.size() - 4);
			int SoundId = CAudioDevice::Get()->CreateSound(Directory + string("\\") + SoundName);
			SoundMap[SoundName] = SoundId;
			SoundNames.push_back(SoundName);

			try
			{
				int Note = stoi(SoundName);
				float Frequency = CAudioDevice::Get()->GetFrequency(Note);
				Frequencies.push_back(Frequency);
			}
			catch (...) 
			{ 
				bIsNotes = false;
			}


		} while (FindNextFile(hFind, &data));

		FindClose(hFind);
	}

	if (bIsNotes)
	{
		Categories[0] = "Octave 0";
		Categories[4] = "Octave 1";
		Categories[4 + 12 * 1] = "Octave 2";
		Categories[4 + 12 * 2] = "Octave 3";
		Categories[4 + 12 * 3] = "Octave 4";
		Categories[4 + 12 * 4] = "Octave 5";
		Categories[4 + 12 * 5] = "Octave 6";
		Categories[4 + 12 * 6] = "Octave 7";
	}
}	

vector<string> CInstrument::GetNoteNames()
{
	if (NoteNames.size() == 0)
	{
		vector<string> Notes;
		Notes.push_back("C");
		Notes.push_back("C#");
		Notes.push_back("D");
		Notes.push_back("D#");
		Notes.push_back("E");
		Notes.push_back("F");
		Notes.push_back("F#");
		Notes.push_back("G");
		Notes.push_back("G#");
		Notes.push_back("A");
		Notes.push_back("A#");
		Notes.push_back("B");

		NoteNames.push_back("G#0");
		NoteNames.push_back("A0");
		NoteNames.push_back("A#0");
		NoteNames.push_back("B0");

		int Octave = 1;
		while (Octave < 8)
		{
			for (string Note : Notes)
			{
				NoteNames.push_back(Note + std::to_string(Octave));

			}
			Octave++;
		}
	}
	return NoteNames;
}

map<unsigned int, string> CInstrument::GetCategories()
{
	return Categories;
}

void CInstrument::PlaySound(string SoundName)
{
	float Pitch = 1.0f;
	string Filename = GetSoundFileName(SoundName, Pitch);
	CAudioDevice::Get()->PlaySound(SoundMap[Filename], Pitch);
}

void CInstrument::StopSound(string SoundName)
{
	float Pitch = 1.0f;
	string Filename = GetSoundFileName(SoundName, Pitch);
	CAudioDevice::Get()->StopSound(SoundMap[Filename]);
}

string CInstrument::GetSoundFileName(string SoundName, float& outPitch)
{
	outPitch = 1.0f;
	if (bIsNotes)
	{
		int Note = -1;
		for (int i = 0; i < NoteNames.size(); i++)
		{
			if (SoundName == NoteNames[i])
			{
				Note = i;
				break;
			}
		}

		if (Note >= 0)
		{
			float DesiredFrequency = CAudioDevice::Get()->GetFrequency(Note);
			int SoundIndex = 0;
			float SoundFrequency = Frequencies[0];
			float CurrentDiff = abs(DesiredFrequency - SoundFrequency);
			for (int i = 1; i < Frequencies.size(); i++)
			{
				float Diff = abs(DesiredFrequency - Frequencies[i]);
				if (Diff < CurrentDiff)
				{
					CurrentDiff = Diff;
					SoundFrequency = Frequencies[i];
					SoundIndex = i;
				}
			}

			outPitch = DesiredFrequency / SoundFrequency;
			return SoundNames[SoundIndex];
		}
	}

	return SoundName;
}

vector<string> CInstrument::GetSoundNames()
{
	if (bIsNotes)
	{
		return GetNoteNames();
	}
	return SoundNames;
}
