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
	c->SetFloat(-1);	//ex : ���N�Ҧ���Ʊ��W
	if(a && b)
	{
		Text_CHANGE TC;
		char get_buf[10] = {0} , set_buf[10] = {0};	//�إߤj�p10��array

		StringCbCopy(get_buf , 9 , a->GetString());	//���Ĥ@���}�����

	//	c->SetFloat( (float)strlen(get_buf) );

		TC.big5_to_Unicode_len( get_buf );		//�Φ��쪺�j�p�Ыطs���O����j�p�w�ǳƦs��unicode�����

		TC.big5_to_Unicode( get_buf , TC.w_Unicode);	//�N����নunicode

		string ss = "";		//�إߤ@�ӪŦr��

		for(int i = 0 ; TC.w_Unicode[i] != 0 ; i++)
		{
			DWORD buf = TC.w_Unicode[i];

			int bb = buf/256;

			sprintf_s(set_buf , 9 , bb > 15 ? "%x" : "0%x" , bb);	//�N���ର16�i��

			ss += set_buf;	//�N��Ƭ���

			bb = buf%256;

			sprintf_s(set_buf , 9 , bb > 15 ? "%x" : "0%x" , bb);	//�D���嬰���byte...�ҥH���ⵧ��ƭn�ন16�i��

			ss += set_buf;	//�N��ưO��
		}

		//ss += "\r\n";

		//TC.Unicode_to_utf8_len(TC.w_Unicode);

		//TC.Unicode_to_utf8( TC.w_Unicode , TC.c_utf8 );

		//for(int i = 0 ; TC.c_utf8[ i ] != 0 ; i++)
		//{
		//	sprintf_s(set_buf , 9 , "%x" , (byte)TC.c_utf8[i] );

		//	ss += set_buf;
		//}

		b->SetString(ss.c_str());	//�N�r��e�^Q3D
	}
}

