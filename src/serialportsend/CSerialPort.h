#pragma once
#include <Windows.h>
#include <iostream>
/*
	����ͨ����
	�Դ��ڵĻ�������
*/
class CSerialPort
{
public:
	CSerialPort();
	~CSerialPort();
	CSerialPort(const CSerialPort& cs) = delete;
	const CSerialPort& operator=(const CSerialPort& cs) = delete;

	/** ��ʼ�����ں���
	*
	*  @param:  UINT portNo ���ڱ��,Ĭ��ֵΪ1,��COM1,ע��,������Ҫ����9
	*  @param:  UINT baud   ������,Ĭ��Ϊ115200//9600
	*  @param:  char parity �Ƿ������żУ��,'Y'��ʾ��Ҫ��żУ��,'N'��ʾ����Ҫ��żУ��
	*  @param:  UINT databits ����λ�ĸ���,Ĭ��ֵΪ8������λ
	*  @param:  UINT stopsbits ֹͣλʹ�ø�ʽ,Ĭ��ֵΪ1
	*  @param:  DWORD dwCommEvents Ĭ��ΪEV_RXCHAR,��ֻҪ�շ�����һ���ַ�,�����һ���¼�
	*  @return: bool  ��ʼ���Ƿ�ɹ�
	*  @note:   ��ʹ�����������ṩ�ĺ���ǰ,���ȵ��ñ��������д��ڵĳ�ʼ��
	*�����������������ṩ��һЩ���õĴ��ڲ�������,����Ҫ����������ϸ��DCB����,��ʹ�����غ���
	*                 ������������ʱ���Զ��رմ���,�������ִ�йرմ���
	*/

	bool InitPort(UINT  portNo = 1, UINT  baud = CBR_115200, char  parity = 'N', UINT  databits = 8, UINT  stopsbits = 1,
							DWORD dwCommEvents = EV_RXCHAR);

	/** ���ڳ�ʼ������
	*  �������ṩֱ�Ӹ���DCB�������ô��ڲ���
	*  @param:  UINT portNo
	*  @param:  const LPDCB & plDCB
	*  @return: bool  ��ʼ���Ƿ�ɹ�
	*  @note:   �������ṩ�û��Զ���ش��ڳ�ʼ������
	*/
	bool InitPort(UINT  portNo, const LPDCB& plDCB);

	/** ���������߳�
	*  �������߳���ɶԴ������ݵļ���,�������յ������ݴ�ӡ����Ļ���
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   ���߳��Ѿ����ڿ���״̬ʱ,����flase
	*/
	bool OpenListenThread();

	/** �رռ����߳�
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   ���ñ�������,�������ڵ��߳̽��ᱻ�ر�
	*/
	bool CloseListenTread();

	/** �򴮿�д����
	*  ���������е�����д�뵽����
	*  @param:  unsigned char * pData ָ����Ҫд�봮�ڵ����ݻ�����
	*  @param:  unsigned int length ��Ҫд������ݳ���
	*  @return: bool  �����Ƿ�ɹ�
	*  @note:   length��Ҫ����pData��ָ�򻺳����Ĵ�С
	*/
	bool WriteData (char* pData, unsigned int length);

	/** ��ȡ���ڻ������е��ֽ���
	*  @return: UINT  �����Ƿ�ɹ�
	*  @note:   �����ڻ�������������ʱ,����0
	*/
	UINT GetBytesInCOM();

	/** ��ȡ���ڽ��ջ�������һ���ֽڵ�����
	*  @param:  char & cRecved ��Ŷ�ȡ���ݵ��ַ�����
	*  @return: bool  ��ȡ�Ƿ�ɹ�
	*/
	bool ReadChar(char &cRecved);

	bool ReadData();

private:
	/** �򿪴���
	*  @param:  UINT portNo �����豸��
	*  @return: bool  ���Ƿ�ɹ�
	*/
	bool openPort(UINT  portNo);

	/** �رմ���
	*  @return: void  �����Ƿ�ɹ�
	*/
	void ClosePort();

	/** ���ڼ����߳�
	*  �������Դ��ڵ����ݺ���Ϣ
	*  @param:  void * pParam �̲߳���
	*  @return: UINT WINAPI �̷߳���ֵ
	*/
	static UINT WINAPI ListenThread(void* pParam);

private:
	HANDLE											m_hComm;												//!���ھ��
	static bool										s_bExit;													//!�߳��˳���־����
	volatile HANDLE								m_hListenThread;									//!�߳̾��
	CRITICAL_SECTION							m_csCommunicationSync;					 //!< �����������  
	std::string										m_strData;	
};

