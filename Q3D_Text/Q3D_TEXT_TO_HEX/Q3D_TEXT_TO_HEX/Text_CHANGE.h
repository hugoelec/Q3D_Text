#pragma once
#ifndef Text_CHANGE_h
#define Text_CHANGE_h
#include "windows.h"
#include <fstream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#include <cmath>			//同等"math.h"
#include<cstring>
#include "conio.h"
#include <strsafe.h>
#include <iostream>
using namespace std;
#include <process.h>

#include<fstream>
#include"string.h"
#include <strsafe.h>

class Text_CHANGE
{
public:

	Text_CHANGE();
	~Text_CHANGE();

	char *c_big5;
	char *c_utf8;
	wchar_t *w_Unicode;

	DWORD big5_to_Unicode_len(char c[] , bool flag);
	DWORD Unicode_to_big5_len(wchar_t w[] , bool flag);
	DWORD utf8_to_Unicode_len(char c[] , bool flag);
	DWORD Unicode_to_utf8_len(wchar_t w[] , bool flag);

	void big5_to_Unicode(char c[] , wchar_t w[] , int length);
	void Unicode_to_big5(wchar_t w[] , char c[] , int length);
	void utf8_to_Unicode(char c[] , wchar_t w[] , int length);
	void Unicode_to_utf8(wchar_t w[] , char c[] , int length);

	void close();

private:
	DWORD b5_uni_len;
	DWORD uni_b5_len;
	DWORD u8_uni_len;
	DWORD uni_u8_len;
};

Text_CHANGE::Text_CHANGE()
{
	c_big5 = NULL;
	c_utf8 = NULL;
	w_Unicode = NULL;

	b5_uni_len = 0;
	uni_b5_len = 0;
	u8_uni_len = 0;
	uni_u8_len = 0;
}

Text_CHANGE::~Text_CHANGE()
{
	delete []c_big5;
	delete []c_utf8;
	delete []w_Unicode;
	c_big5 = NULL;
	c_utf8 = NULL;
	w_Unicode = NULL;
}

DWORD Text_CHANGE::big5_to_Unicode_len(char c[] , bool flag = true)
{
	b5_uni_len = MultiByteToWideChar ( CP_ACP , 0 , c , -1 , NULL , 0 ) ;

	if(flag)
	{
		delete []w_Unicode;
		w_Unicode = new wchar_t[b5_uni_len];
		
	}

	return b5_uni_len;
}

DWORD Text_CHANGE::Unicode_to_big5_len(wchar_t w[] , bool flag = true)
{
	uni_b5_len = WideCharToMultiByte ( CP_OEMCP , 0 , w , -1 , NULL , 0 , NULL , NULL);

	if(flag)
	{
		delete []c_big5;
		c_big5 = new char[uni_b5_len];
	}

	return uni_b5_len;
}

DWORD Text_CHANGE::utf8_to_Unicode_len(char c[] , bool flag = true)
{
	u8_uni_len = MultiByteToWideChar ( CP_UTF8 , 0 , c , -1 , NULL , 0 ) ;

	if(flag)
	{
		delete []w_Unicode;
		w_Unicode = new wchar_t[u8_uni_len];
	}

	return u8_uni_len;
}

DWORD Text_CHANGE::Unicode_to_utf8_len(wchar_t w[] , bool flag = true)
{
	uni_u8_len = WideCharToMultiByte ( CP_UTF8 , 0 , w , -1 , NULL , 0 , NULL , NULL );

	if(flag)
	{
		delete []c_utf8;
		c_utf8 = new char[uni_u8_len];
	}

	return uni_u8_len;
}

void Text_CHANGE::big5_to_Unicode(char c[], wchar_t w[] , int length = -1)
{
	if(length < 0)
	{
		length = b5_uni_len;
	}
	MultiByteToWideChar( CP_ACP , 0 , c , -1 , w , length );
}

void Text_CHANGE::Unicode_to_big5(wchar_t w[], char c[], int length = -1)
{
	if(length < 0)
	{
		length = uni_b5_len;
	}
	WideCharToMultiByte ( CP_OEMCP , 0 , w , -1 , c , length , NULL , NULL );
}

void Text_CHANGE::utf8_to_Unicode(char c[], wchar_t w[], int length = -1)
{
	if(length < 0)
	{
		length = u8_uni_len;
	}
	MultiByteToWideChar( CP_UTF8 , 0 , c , -1 , w , length );
}

void Text_CHANGE::Unicode_to_utf8(wchar_t w[], char c[], int length = -1)
{
	if(length < 0)
	{
		length = uni_u8_len;
	}
	WideCharToMultiByte ( CP_UTF8 , 0 , w , -1 , c , length , NULL , NULL );
}

void Text_CHANGE::close()
{
	delete []c_big5;
	delete []c_utf8;
	delete []w_Unicode;
	c_big5 = NULL;
	c_utf8 = NULL;
	w_Unicode = NULL;
}

#endif

//strncpy_s用法
//char dst[5];
//strncpy_s(dst, 5, "a long string", _TRUNCATE);

//example
//
//Text_CHANGE TC;
//void main()
//{
//	TC.c_big5 = new char[10];
//	strncpy(TC.c_big5 , "啊" , 9/*n-1*/);
//	cout<<TC.c_big5<<endl;
//
//	//for(int i = 0 ; TC.c_big5[ i ] != 0 ; i++)
//	//{
//	//	printf("%d = %x\n" , i , (byte)TC.c_big5[i]);
//	//}
//
//	//////////
//	//big5->Unicode
//
//	/*int len = */TC.big5_to_Unicode_len(TC.c_big5);	//因為由char轉成wchar_t...所以無論是否中文都為1....包含最後的0字元...所以是n+1
//	//TC.w_Unicode = new wchar_t[len];	//除非在查詢所需長度時,第二參數設定為false~不然會自動創建記憶體
//
//	TC.big5_to_Unicode( TC.c_big5 , TC.w_Unicode);
//
//	//for(int i = 0 ; TC.w_Unicode[i] != 0 ; i++)
//	//{
//	////	printf("%d = %x\n" , i , TC.w_Unicode[i]);
//	//	DWORD buf = TC.w_Unicode[i];
//	//	printf("%d = %x\n" , i , buf%256 );		//後兩位
//	//	printf("%d = %x\n" , i , buf/256 );		//前兩位
//	//}
//
//	///////////
//	//Uicode -> big5
//	TC.Unicode_to_big5_len(TC.w_Unicode);	//同上big5轉Unicode...除非第二參數設定false...不然會自動建立記憶體...
//
//	TC.Unicode_to_big5(TC.w_Unicode , TC.c_big5 );
//
//	/*for(int i = 0 ; TC.c_big5[ i ] != 0 ; i++)
//	{
//		printf("%d = %x\n" , i , (byte)TC.c_big5[i]);
//	}*/
//
//	///////////
//	//Unicode -> utf8
//	TC.Unicode_to_utf8_len(TC.w_Unicode);	//同上big5轉Unicode...除非第二參數設定false...不然會自動建立記憶體...非英文~數字~普遍符號者~~所佔用空間為2~3
//
//	TC.Unicode_to_utf8( TC.w_Unicode , TC.c_utf8 );
//
//	/*for(int i = 0 ; TC.c_utf8[ i ] != 0 ; i++)
//	{
//		printf("%d = %x\n" , i , (byte)TC.c_utf8[i]);
//	}*/
//
//	//////////
//	//utf8 -> Unicode
//	TC.utf8_to_Unicode_len(TC.c_utf8);
//
//	TC.utf8_to_Unicode( TC.c_utf8 , TC.w_Unicode );	//同上big5轉Unicode...除非第二參數設定false...不然會自動建立記憶體...
//
//	for(int i = 0 ; TC.w_Unicode[i] != 0 ; i++)
//	{
//	//	printf("%d = %x\n" , i , TC.w_Unicode[i]);
//		DWORD buf = TC.w_Unicode[i];
//		printf("%d = %x\n" , i , buf%256 );		//後兩位
//		printf("%d = %x\n" , i , buf/256 );		//前兩位
//	}
//	TC.close();
//}