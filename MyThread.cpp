#include "MyThread.h"
//默认在创建线程类的时候创建一个新线程
CMyThread* CMyThread::CreateThreadObj(BOOL bCreate/* = TRUE*/)
{
	CMyThread *pThis = new CMyThread();
	pThis->m_hThread = NULL;
	pThis->m_dwThreadID = 0;
	if (bCreate)
	{
		pThis->CreateThread(NULL, 0, 0);
	}

	return pThis;
}
//该函数由用户主动调用，以销毁线程对象
void CMyThread::DeleteThreadObj()
{
	::ExitThread(OBJECT_IS_VOER);
	if (NULL != m_hThread)
	{
		CloseHandle(m_hThread);
	}

	delete this;
}

void CMyThread::InitThread()
{
	printf("ThreadClass对象[A:0x%08x]线程[H:0x%08x ID:0x%x]初始化\n", this, m_hThread, m_dwThreadID);
}

void CMyThread::Run(LPVOID lpParam)
{
	printf("ThreadClass对象[A:0x%08x]线程[H:0x%08x ID:0x%x]运行\n",this,m_hThread,m_dwThreadID);
}

void CMyThread::ExitThread()
{
	//线程结束后调用该函数
	printf("ThreadClass对象[A:0x%08x]线程[H:0x%08x ID:0x%x]退出\n",this,m_hThread,m_dwThreadID);
	CloseHandle(m_hThread);
	delete this;
}

DWORD CMyThread::CreateThread(LPSECURITY_ATTRIBUTES lpsa, DWORD cbStack, DWORD fdwCreate)
{
	typedef DWORD (WINAPI *LPTHREAD_START_ADDRESS)(LPVOID);
	typedef DWORD (WINAPI CMyThread::*PCLASS_PROC)(LPVOID);
	PCLASS_PROC pThreadProc = &CMyThread::ThreadProc;
	m_hThread = ::CreateThread(lpsa, cbStack, *(LPTHREAD_START_ADDRESS*)(&pThreadProc), this, fdwCreate, &m_dwThreadID);
	return (NULL != m_hThread) ? -1 : 0;
}

DWORD WINAPI CMyThread::ThreadProc(LPVOID lpParam)
{
	InitThread();
	Run(lpParam);
	ExitThread();
	return 0;
}

HANDLE CMyThread::GetThreadHandle()
{
	return m_hThread;
}
