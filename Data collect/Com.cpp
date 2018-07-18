#include "StdAfx.h"
#include "Com.h"



CCom::CCom()
{
	m_hCom = NULL;
}

BOOL CCom::OpenComm( CString strPort, int nBaudRate /*= 9600*/, int nParity/*= NOPARITY*/, int nByteSize /*= 8*/, int nStopBits /*= ONESTOPBIT*/ )
{
	m_hCom = CreateFile(strPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(INVALID_HANDLE_VALUE == m_hCom)
	{
		return FALSE;
	}

	DCB dcb;
	COMMTIMEOUTS timeouts = {
		100,
		1,
		2000,                                        //读串口超时时间值
		1,
		100	};
		GetCommState(m_hCom, &dcb);
		dcb.BaudRate = nBaudRate;
		dcb.Parity = nParity;
		dcb.ByteSize = nByteSize;
		dcb.StopBits = nStopBits;
		SetCommState(m_hCom, &dcb);
		SetupComm(m_hCom, 1024, 1024);
		SetCommTimeouts(m_hCom, &timeouts);
		return TRUE;
}

BOOL CCom::CloseComm()
{
	if (NULL != m_hCom)
	{
		CloseHandle(m_hCom);
		m_hCom = NULL;
	}
	return TRUE;
}

int CCom::ReadComm( void* pData, int nLength )
{
	try
	{
		DWORD dwReadNum = 0;
		ReadFile(m_hCom, pData, nLength, &dwReadNum, 0);
		return (int)dwReadNum;
	}
	catch(...)
	{
		return -1;
	}
}

int CCom::WriteComm( void* pData, int nLength )
{
	try
	{
		DWORD dwWriteNum = 0;
		WriteFile(m_hCom, pData, nLength, &dwWriteNum, 0);
		return (int)dwWriteNum;
	}
	catch (...)
	{
		return -1;
	}
}
