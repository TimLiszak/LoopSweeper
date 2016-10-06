#ifndef _INSTRUMENTMANAGER_H_
#define _INSTRUMENTMANAGER_H_

#include "GameEngine.h"
#include "Instrument.h"
#include <vector>
#include <string>
using namespace std;

class CInstrumentManager
{
public:
	static CInstrumentManager* Get()
	{
		if (!pInstance)
		{
			pInstance = new CInstrumentManager();
		}
		return pInstance;
	}

	virtual ~CInstrumentManager() {}

	vector<string> GetInstrumentNames();
	CInstrument* GetInstrument(int InstrumentId);

protected:
	CInstrumentManager();
	static CInstrumentManager*		pInstance;

	vector<string> InstrumentNames;
	vector<CInstrument*> Instruments;

};

#endif