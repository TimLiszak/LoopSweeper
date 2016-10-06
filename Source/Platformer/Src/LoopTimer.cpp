#include "StdAfx.h"
#include "LoopTimer.h"
#include "Render2d.h"
#include "Workspace.h"
#include "Cell.h"

CLoopTimer::CLoopTimer(float InBeatsPerMinute, int InBeatsPerMeasure, int InNumMeasures)
{
	BeatsPerMinute = InBeatsPerMinute;
	BeatsPerMeasure = InBeatsPerMeasure;
	NumMeasures = InNumMeasures;
	CurrentTime = 0.0f;
	CurrentBeat = -1;
	CurrentEighth = -1;
	CurrentSixteenth = -1;
	CurrentMeasure = 0;
	bIsPlaying = false;
}

void CLoopTimer::Play()
{
	CurrentTime = 0.0f;
	CurrentBeat = 0;
	CurrentEighth = 0;
	CurrentSixteenth = 0;
	CurrentMeasure = 0;
	bIsPlaying = true;

	DoSixteenth();
	DoEighth();
	DoQuarter();
}

void CLoopTimer::Update(const FLOAT DeltaTime)
{
	if (!bIsPlaying)
		return;


	CurrentTime += DeltaTime;
	
	float SixteenthTime = 15.0f / BeatsPerMinute;
	if (CurrentTime >= SixteenthTime)
	{
		CurrentTime -= SixteenthTime;
		CurrentSixteenth++;

		if (CurrentSixteenth % 2 == 0)
		{
			CurrentEighth++;
			DoEighth();

			if (CurrentEighth % 2 == 0)
			{
				CurrentBeat++;

				if (CurrentBeat >= BeatsPerMeasure)
				{
					CurrentBeat = 0;
					CurrentEighth = 0;
					CurrentSixteenth = 0;
					CurrentMeasure++;
					CurrentMeasure %= NumMeasures;
				}

				DoQuarter();
			}
		}

		DoSixteenth();
	}
}

void CLoopTimer::DoSixteenth()
{
	for (std::vector<IBeatCallback*>::iterator it = BeatCallbacks.begin(); it != BeatCallbacks.end(); ++it)
	{
		(*it)->OnSixteenth(CurrentSixteenth, CurrentMeasure);
	}
}

void CLoopTimer::DoEighth()
{
	for (std::vector<IBeatCallback*>::iterator it = BeatCallbacks.begin(); it != BeatCallbacks.end(); ++it)
	{
		(*it)->OnEighth(CurrentEighth, CurrentMeasure);
	}
}

void CLoopTimer::DoQuarter()
{
	for (std::vector<IBeatCallback*>::iterator it = BeatCallbacks.begin(); it != BeatCallbacks.end(); ++it)
	{
		(*it)->OnQuarter(CurrentBeat, CurrentMeasure);
	}
}

void CLoopTimer::AddBeatCallback(IBeatCallback* Callback)
{
	BeatCallbacks.push_back(Callback);
}

float CLoopTimer::GetPercent()
{
	float SixteenthTime = 15.0f / BeatsPerMinute;
	float Beat = (((float)CurrentSixteenth + (CurrentTime / SixteenthTime)) * 0.25f) + (float)(CurrentMeasure * BeatsPerMeasure);
	float NumBeats = (float)(BeatsPerMeasure * NumMeasures);
	return Beat / NumBeats;
}
