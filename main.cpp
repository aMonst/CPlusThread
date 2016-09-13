#include "MyThread.h"

int _tmain(int argc, TCHAR *argv[])
{
	CMyThread *pThread = CMyThread::CreateThreadObj();
	WaitForSingleObject(pThread->GetThreadHandle(), INFINITE);
	pThread->DeleteThreadObj();
	return 0;
}
