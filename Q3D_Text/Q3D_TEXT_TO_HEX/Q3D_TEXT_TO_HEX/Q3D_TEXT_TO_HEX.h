#pragma once

#ifdef Q3D_TEXT_TO_HEX_EXPORTS
#define Q3D_TEXT_TO_HEX_API __declspec(dllexport)
#else
#define Q3D_TEXT_TO_HEX_API __declspec(dllimport)
#endif

#include "Aco_String.h"

#include"Q3D.h"
#include"Text_CHANGE.h"


#define Q3D_TEXT_TO_HEX_NAME		"Q3D_TEXT_TO_HEX"
#define Q3D_TEXT_TO_HEX_VERSION		1

//{4A559EE8-B188-423F-80DA-C54F6C573ABF}
static const GUID Q3D_TEXT_TO_HEX_GUID = { 0x4A559EE8, 0xB188, 0x423F, { 0x80, 0xDA, 0xC5, 0x4F, 0x6C, 0x57, 0x3A, 0xBF } };

class Q3D_TEXT_TO_HEX_API Q3D_TEXT_TO_HEX: public A3d_Channel
{
public:
	Q3D_TEXT_TO_HEX();
	virtual ~Q3D_TEXT_TO_HEX();

	
	// Save persistent channel data in channel group
	virtual bool			SaveChannel(A3dFileSaver& saver);
	// Load persistent channel data from channel group
	virtual bool			LoadChannel(A3dFileLoader& loader, A3d_ChannelGroup *group);

	// Add needed dependencies for publishing
	virtual void			DoDependencyInit(A3d_List* currentDependList);

	//CallChannel function invoked by the engine
	virtual void 			CallChannel();
protected:

};

// Leave rest of header file intact!
#define Q3D_TEXT_TO_HEXDLL_EXPORTS extern "C" { \
__declspec(dllexport) DllInterface * __cdecl InitDLL() \
{ \
	return new Q3D_TEXT_TO_HEX; \
} \
}

