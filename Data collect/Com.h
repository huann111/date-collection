#pragma once

 
//串口通信类
class CCom 
{

public:
	CCom(void);
	BOOL OpenComm(CString strPort, int nBaudRate = 9600, int nParity= NOPARITY, int nByteSize = 8, int nStopBits = ONESTOPBIT);
	BOOL CloseComm();
	int ReadComm(void* pData, int nLength);
	int WriteComm(void* pData, int nLength);
	HANDLE GetHandle() const{ return m_hCom; }
	//HANDLE m_hCom;
private:
	HANDLE m_hCom;

};
