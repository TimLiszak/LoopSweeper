#include "StdAfx.h"
#include "InstrumentManager.h"

CInstrumentManager* CInstrumentManager::pInstance = NULL;

CInstrumentManager::CInstrumentManager()
{
	InstrumentNames.push_back("Piano");
	InstrumentNames.push_back("RockKit");
	InstrumentNames.push_back("Classic-808");
	InstrumentNames.push_back("Glockenspiel");
	InstrumentNames.push_back("Anderson Guitar Clean");
	
	for (unsigned int i = 0; i < InstrumentNames.size(); i++)
	{
		Instruments.push_back(new CInstrument(InstrumentNames[i]));
	}
}

vector<string> CInstrumentManager::GetInstrumentNames()
{
	return InstrumentNames;
}

CInstrument* CInstrumentManager::GetInstrument(int InstrumentId)
{
	return Instruments[InstrumentId];
}
