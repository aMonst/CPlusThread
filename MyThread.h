#pragma once
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#define OBJECT_IS_VOER -1 //此种情况是由于线程对象生命周期结束
#define THREAD_IS_OVER -2 //线程结束，会主动销毁对象

class CMyThread
{
public:
	static CMyThread* CreateThreadObj(BOOL bCreate = TRUE);
	void DeleteThreadObj();
	virtual void InitThread();
	virtual void Run(LPVOID lpParam);
	virtual void ExitThread();
	HANDLE GetThreadHandle();
protected:
	DWORD WINAPI ThreadProc(LPVOID lpParam);
	DWORD CreateThread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, DWORD fdwCreate);
	CMyThread(){}
	virtual ~CMyThread(void){}
	void operator = (CMyThread& obj){}
	CMyThread(CMyThread& obj);
protected:
	HANDLE m_hThread;
	DWORD m_dwThreadID;
};
