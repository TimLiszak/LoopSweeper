#ifndef _LOOPTIMER_H_
#define _LOOPTIMER_H_

#include "GameEngine.h"
#include "Window.h"

class IBeatCallback
{
public:
	virtual void	OnQuarter(int Quarter, int Measure) {};
	virtual void	OnEighth(int Eighth, int Measure) {};
	virtual void	OnSixteenth(int Sixteenth, int Measure) {};
};

class CLoopTimer
{
public:
	CLoopTimer(float InBeatsPerMinute, int InBeatsPerMeasure, int InNumMeasures);
	virtual ~CLoopTimer() {}

	virtual void Update(const FLOAT DeltaTime);
	virtual void Play();

	virtual void AddBeatCallback(IBeatCallback* Callback);

	virtual float GetPercent();

protected:
	bool bIsPlaying;

	float BeatsPerMinute;
	int BeatsPerMeasure;
	int NumMeasures;

	float CurrentTime;
	int CurrentSixteenth;
	int CurrentEighth;
	int CurrentBeat;
	int CurrentMeasure;

	std::vector<IBeatCallback*> BeatCallbacks;

	void DoSixteenth();
	void DoEighth();
	void DoQuarter();

public:
	inline float GetBeatsPerMinute() const { return BeatsPerMinute; }
	inline int GetBeatsPerMeasure() const { return BeatsPerMeasure; }
	inline int GetNumMeasures() const { return NumMeasures; }
};

#endif