// Array_Buffer.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Q3D_TEXT_TO_HEX.h"

ChannelType channelType;
	
extern "C" __declspec( dllexport ) ChannelType* __cdecl GetType() {
	ZeroMemory(channelType.name, 80);
	StringCbCopy(channelType.name,  79, Q3D_TEXT_TO_HEX_NAME); 
	channelType.version			= Q3D_TEXT_TO_HEX_VERSION;
	channelType.guid			= Q3D_TEXT_TO_HEX_GUID;
	channelType.baseguid		= Q3D_TEXT_TO_HEX_GUID;
	channelType.minimumEdition 	= EDITION_LEVEL_ALL;		// All Quest3D Editions

	return &channelType;
}

Q3D_TEXT_TO_HEXDLL_EXPORTS

Q3D_TEXT_TO_HEX::Q3D_TEXT_TO_HEX() {
	SetChannelName(Q3D_TEXT_TO_HEX_NAME);
	//TODO: Add construction logic here
	SetChildCreationCount(0);
	ChildCreation child[7];

	child[0].channelType.guid	= STRING_GUID;
	StringCbCopy(child[0].channelType.name,79, STRING_NAME);
	child[0].requestLink		= 0;
	child[0].initialize		= false;
	StringCbCopy(child[0].name,79, "Text");
	SetChildCreateType(child[0], 0);

	child[1].channelType.guid	= STRING_GUID;
	StringCbCopy(child[1].channelType.name,79, STRING_NAME);
	child[1].requestLink		= 1;
	child[1].initialize		= false;
	StringCbCopy(child[1].name,79, "HEX");
	SetChildCreateType(child[1], 1);

	child[2].channelType.guid	= FLOAT_CHANNEL_GUID;
	strcpy(child[2].channelType.name, FLOAT_CHANNEL_NAME);
	child[2].requestLink		= 2;
	child[2].initialize		= false;
	StringCbCopy(child[2].name,79, "TX");
	SetChildCreateType(child[2], 2);
}

Q3D_TEXT_TO_HEX::~Q3D_TEXT_TO_HEX()
{
	//TODO:: Add destruction logic here
}


// Overlodaed save channel
bool Q3D_TEXT_TO_HEX::SaveChannel(A3dFileSaver& saver) {
	if(!A3d_Channel::SaveChannel(saver))
		return false;
	//TODO: Add your logic to save persistent data here
	return true;
}

bool Q3D_TEXT_TO_HEX::LoadChannel(A3dFileLoader& loader, A3d_ChannelGroup *group) {
	if(!A3d_Channel::LoadChannel(loader, group))
		return false;
	//TODO: Add your logic to load persistent data here
	return true;
}

void Q3D_TEXT_TO_HEX::DoDependencyInit(A3d_List* currentDependList) {
	//Include Visual Studio 2005 runtime libraries	
	AddDLLDepend("MSVCR80.DLL", currentDependList);
	AddDLLDepend("MSVCP80.DLL", currentDependList);
	AddDLLDepend("MSVCM80.DLL", currentDependList);
	AddDLLDepend("Microsoft.VC80.CRT.manifest", currentDependList);
}

void Q3D_TEXT_TO_HEX::CallChannel()
{
	//TODO: Add call channel logic here
	Aco_StringChannel* a = (Aco_StringChannel*)GetChild(0);
	Aco_StringChannel* b = (Aco_StringChannel*)GetChild(1);
	Aco_FloatChannel* c = (Aco_FloatChannel*)GetChild(2);
	c->SetFloat(-1);	//ex : 未將所有資料接上
	if(a && b)
	{
		Text_CHANGE TC;
		char get_buf[10] = {0} , set_buf[10] = {0};	//建立大小10的array

		StringCbCopy(get_buf , 9 , a->GetString());	//收第一隻腳的資料

	//	c->SetFloat( (float)strlen(get_buf) );

		TC.big5_to_Unicode_len( get_buf );		//用收到的大小創建新的記憶體大小已準備存放unicode的資料

		TC.big5_to_Unicode( get_buf , TC.w_Unicode);	//將資料轉成unicode

		string ss = "";		//建立一個空字串

		for(int i = 0 ; TC.w_Unicode[i] != 0 ; i++)
		{
			DWORD buf = TC.w_Unicode[i];

			int bb = buf/256;

			sprintf_s(set_buf , 9 , bb > 15 ? "%x" : "0%x" , bb);	//將值轉為16進位

			ss += set_buf;	//將資料紀錄

			bb = buf%256;

			sprintf_s(set_buf , 9 , bb > 15 ? "%x" : "0%x" , bb);	//非中文為兩個byte...所以有兩筆資料要轉成16進位

			ss += set_buf;	//將資料記錄
		}

		//ss += "\r\n";

		//TC.Unicode_to_utf8_len(TC.w_Unicode);

		//TC.Unicode_to_utf8( TC.w_Unicode , TC.c_utf8 );

		//for(int i = 0 ; TC.c_utf8[ i ] != 0 ; i++)
		//{
		//	sprintf_s(set_buf , 9 , "%x" , (byte)TC.c_utf8[i] );

		//	ss += set_buf;
		//}

		b->SetString(ss.c_str());	//將字串送回Q3D
	}
}

