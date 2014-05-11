/*
 * Copyright: JessMA Open Source (ldcsaa@gmail.com)
 *
 * Version	: 3.2.1
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Project	: https://github.com/ldcsaa
 * Blog		: http://www.cnblogs.com/ldcsaa
 * Wiki		: http://www.oschina.net/p/hp-socket
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#pragma once

#include <winsock2.h>

/************************************************************************
���ƣ����� ID ��������
������Ӧ�ó�����԰� CONNID ����Ϊֻ����Ҫ�����ͣ��磺ULONG / ULONGLONG��
************************************************************************/
typedef ULONG_PTR	CONNID;

/*****************************************************************************************************/
/******************************************** �����ࡢ�ӿ� ********************************************/
/*****************************************************************************************************/

/************************************************************************
���ƣ�ͨ���������״̬
������Ӧ�ó������ͨ��ͨ������� GetState() ������ȡ�����ǰ����״̬
************************************************************************/
enum EnServiceState
{
	SS_STARTING	= 0,	// ��������
	SS_STARTED	= 1,	// �Ѿ�����
	SS_STOPING	= 2,	// ����ֹͣ
	SS_STOPED	= 3,	// �Ѿ�����
};

/************************************************************************
���ƣ�Socket ��������
������Ӧ�ó���� OnErrror() �¼���ͨ���ò�����ʶ�����ֲ������µĴ���
************************************************************************/
enum EnSocketOperation
{
	SO_UNKNOWN	= 0,	// Unknown
	SO_ACCEPT	= 1,	// Acccept
	SO_CONNECT	= 2,	// Connect
	SO_SEND		= 3,	// Send
	SO_RECEIVE	= 4,	// Receive
};

/************************************************************************
���ƣ��¼�֪ͨ������
�������¼�֪ͨ�ķ���ֵ����ͬ�ķ���ֵ��Ӱ��ͨ������ĺ�����Ϊ
************************************************************************/
enum EnHandleResult
{
	HR_OK		= 0,	// �ɹ�
	HR_IGNORE	= 1,	// ����
	HR_ERROR	= 2,	// ����
};

/************************************************************************
���ƣ�����ץȡ���
����������ץȡ�����ķ���ֵ
************************************************************************/
enum EnFetchResult
{
	FR_OK				= 0,	// �ɹ�
	FR_LENGTH_TOO_LONG	= 1,	// ץȡ���ȹ���
	FR_DATA_NOT_FOUND	= 2,	// �Ҳ��� ConnID ��Ӧ������
};

/************************************************************************
���ƣ����ݷ��Ͳ���
������Server ����� Agent ��������ݷ��Ͳ���

* ���ģʽ��Ĭ�ϣ�	�������Ѷ�����Ͳ��������������һ���ͣ����Ӵ���Ч��
* ��ȫģʽ			�������Ѷ�����Ͳ��������������һ���ͣ������ƴ����ٶȣ����⻺�������
* ֱ��ģʽ			����ÿһ�����Ͳ�����ֱ��Ͷ�ݣ������ڸ��ز��ߵ�Ҫ��ʵʱ�Խϸߵĳ���

************************************************************************/
enum EnSendPolicy
{
	SP_PACK				= 0,	// ���ģʽ��Ĭ�ϣ�
	SP_SAFE				= 1,	// ��ȫģʽ
	SP_DIRECT			= 2,	// ֱ��ģʽ
};

/************************************************************************
���ƣ������������
��������� Start() / Stop() ����ִ��ʧ��ʱ����ͨ�� GetLastError() ��ȡ�������
************************************************************************/
enum EnSocketError
{
	SE_OK						= NO_ERROR,	// �ɹ�
	SE_ILLEGAL_STATE			= 1,		// ��ǰ״̬���������
	SE_INVALID_PARAM			= 2,		// �Ƿ�����
	SE_SOCKET_CREATE			= 3,		// ���� SOCKET ʧ��
	SE_SOCKET_BIND				= 4,		// �� SOCKET ʧ��
	SE_SOCKET_PREPARE			= 5,		// ���� SOCKET ʧ��
	SE_SOCKET_LISTEN			= 6,		// ���� SOCKET ʧ��
	SE_CP_CREATE				= 7,		// ������ɶ˿�ʧ��
	SE_WORKER_THREAD_CREATE		= 8,		// ���������߳�ʧ��
	SE_DETECT_THREAD_CREATE		= 9,		// ��������߳�ʧ��
	SE_SOCKE_ATTACH_TO_CP		= 10,		// ����ɶ˿�ʧ��
	SE_CONNECT_SERVER			= 11,		// ���ӷ�����ʧ��
	SE_NETWORK					= 12,		// �������
	SE_DATA_PROC				= 13,		// ���ݴ������
	SE_DATA_SEND				= 14,		// ���ݷ���ʧ��
};

/************************************************************************
���ƣ�Socket ���������ӿ�
�������������˺Ϳͻ��� Socket �������Ĺ�����Ϣ
************************************************************************/
class ISocketListener
{
public:

	/*
	* ���ƣ��ѷ�������֪ͨ
	* �������ɹ��������ݺ�Socket ���������յ���֪ͨ
	*		
	* ������		dwConnID	-- ���� ID
	*			pData		-- �ѷ������ݻ�����
	*			iLength		-- �ѷ������ݳ���
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ��֪ͨ�������� HR_ERROR������ģʽ���������Դ���
	*/
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)					= 0;

	/*
	* ���ƣ��ѽ�������֪ͨ��PUSH ģ�ͣ�
	* ���������� PUSH ģ�͵� Socket ͨ��������ɹ��������ݺ��� Socket ���������͸�֪ͨ
	*		
	* ������		dwConnID	-- ���� ID
	*			pData		-- �ѽ������ݻ�����
	*			iLength		-- �ѽ������ݳ���
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ���� OnError() �¼�ʱ�䲢�ر�����
	*/
	virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)				= 0;

	/*
	* ���ƣ����ݵ���֪ͨ��PULL ģ�ͣ�
	* ���������� PULL ģ�͵� Socket ͨ��������ɹ��������ݺ��� Socket ���������͸�֪ͨ
	*		
	* ������		dwConnID	-- ���� ID
	*			iLength		-- �ѽ������ݳ���
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ���� OnError() �¼�ʱ�䲢�ر�����
	*/
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)									= 0;

	/*
	* ���ƣ��ѹر�����֪ͨ
	* �����������ر����Ӻ�Socket ���������յ���֪ͨ
	*		
	* ������		dwConnID -- ���� ID
	* ����ֵ��	���Է���ֵ
	*/
	virtual EnHandleResult OnClose(CONNID dwConnID)													= 0;

	/*
	* ���ƣ�ͨ�Ŵ���֪ͨ
	* ������ͨ�ŷ��������Socket ���������յ���֪ͨ�����ر�����
	*		
	* ������		dwConnID	-- ���� ID
	*			enOperation	-- Socket ��������
	*			iErrorCode	-- �������
	* ����ֵ��	���Է���ֵ
	*/
	virtual EnHandleResult OnError(CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)	= 0;

public:
	virtual ~ISocketListener() {}
};

/************************************************************************
���ƣ������ Socket �������ӿ�
�������������� Socket �������������¼�֪ͨ
************************************************************************/
class IServerListener : public ISocketListener
{
public:

	/*
	* ���ƣ�׼������֪ͨ
	* ������ͨ�ŷ�����������ʱ���ڼ��� Socket ������ɲ���ʼִ�м���ǰ��Socket ����
	*		�����յ���֪ͨ��������������֪ͨ��������ִ�� Socket ѡ�����õȶ��⹤��
	*		
	* ������		soListen	-- ���� Socket
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ��ֹ����ͨ�ŷ������
	*/
	virtual EnHandleResult OnPrepareListen(SOCKET soListen)				= 0;

	/*
	* ���ƣ��ر�ͨ�����֪ͨ
	* ������ͨ������ر�ʱ��Socket ���������յ���֪ͨ
	*		
	* ������	
	* ����ֵ�����Է���ֵ
	*/
	virtual EnHandleResult OnServerShutdown()							= 0;
};

/************************************************************************
���ƣ�TCP ����� Socket �������ӿ�
���������� TCP ����� Socket �������������¼�֪ͨ
************************************************************************/
class ITcpServerListener : public IServerListener
{
public:

	/*
	* ���ƣ���������֪ͨ
	* ���������յ��ͻ�����������ʱ��Socket ���������յ���֪ͨ��������������֪ͨ����
	*		����ִ�� Socket ѡ�����û�ܾ��ͻ������ӵȶ��⹤��
	*		
	* ������		dwConnID	-- ���� ID
	*			soClient	-- �ͻ��� Socket
	* ����ֵ��	HR_OK / HR_IGNORE	-- ��������
	*			HR_ERROR			-- �ܾ�����
	*/
	virtual EnHandleResult OnAccept(CONNID dwConnID, SOCKET soClient)	= 0;
};

/************************************************************************
���ƣ�PUSH ģ�ͷ���� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpServerListener : public ITcpServerListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareListen(SOCKET soListen)							{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(CONNID dwConnID, SOCKET soClient)				{return HR_IGNORE;}
	virtual EnHandleResult OnServerShutdown()										{return HR_IGNORE;}
};

/************************************************************************
���ƣ�PULL ģ�ͷ���� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpPullServerListener : public CTcpServerListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

/************************************************************************
���ƣ�UDP ����� Socket �������ӿ�
���������� UDP ����� Socket �������������¼�֪ͨ
************************************************************************/
class IUdpServerListener : public IServerListener
{
public:

	/*
	* ���ƣ���������֪ͨ
	* ���������յ��ͻ�����������ʱ��Socket ���������յ���֪ͨ��������������֪ͨ����
	*		����ִ�� Socket ѡ�����û�ܾ��ͻ������ӵȶ��⹤��
	*		
	* ������		dwConnID	-- ���� ID
	*			soClient	-- �ͻ��� Socket
	* ����ֵ��	HR_OK / HR_IGNORE	-- ��������
	*			HR_ERROR			-- �ܾ�����
	*/
	virtual EnHandleResult OnAccept(CONNID dwConnID, const SOCKADDR_IN* pSockAddr)	= 0;
};

/************************************************************************
���ƣ�UDP ����� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CUdpServerListener : public IUdpServerListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareListen(SOCKET soListen)							{return HR_IGNORE;}
	virtual EnHandleResult OnAccept(CONNID dwConnID, const SOCKADDR_IN* pSockAddr)	{return HR_IGNORE;}
	virtual EnHandleResult OnServerShutdown()										{return HR_IGNORE;}
};

/************************************************************************
���ƣ��ͻ��� Socket �������ӿ�
����������ͻ��� Socket �������������¼�֪ͨ
************************************************************************/
class IClientListener : public ISocketListener
{
public:

	/*
	* ���ƣ�׼������֪ͨ
	* ������ͨ�ſͻ����������ʱ���ڿͻ��� Socket ������ɲ���ʼִ������ǰ��Socket ����
	*		�����յ���֪ͨ��������������֪ͨ��������ִ�� Socket ѡ�����õȶ��⹤��
	*		
	* ������		dwConnID	-- ���� ID
	*			socket		-- �ͻ��� Socket
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ��ֹ����ͨ�ſͻ������
	*/
	virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)		= 0;

	/*
	* ���ƣ��������֪ͨ
	* �����������˳ɹ���������ʱ��Socket ���������յ���֪ͨ
	*		
	* ������		dwConnID	-- ���� ID
	* ����ֵ��	HR_OK / HR_IGNORE	-- ����ִ��
	*			HR_ERROR			-- ͬ�����ӣ���ֹ����ͨ�ſͻ������
	*								   �첽���ӣ��ر�����
	*/
	virtual EnHandleResult OnConnect(CONNID dwConnID)							= 0;
};

/************************************************************************
���ƣ�TCP �ͻ��� Socket �������ӿ�
���������� TCP �ͻ��� Socket �������������¼�֪ͨ
************************************************************************/
class ITcpClientListener : public IClientListener
{
};

/************************************************************************
���ƣ�PUSH ģ�Ϳͻ��� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpClientListener : public ITcpClientListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(CONNID dwConnID)								{return HR_IGNORE;}
};

/************************************************************************
���ƣ�PULL �ͻ��� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpPullClientListener : public CTcpClientListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

/************************************************************************
���ƣ�UDP �ͻ��� Socket �������ӿ�
���������� UDP �ͻ��� Socket �������������¼�֪ͨ
************************************************************************/
class IUdpClientListener : public IClientListener
{
};

/************************************************************************
���ƣ�UDP ���� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CUdpClientListener : public IUdpClientListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(CONNID dwConnID)								{return HR_IGNORE;}
};

/************************************************************************
���ƣ�ͨ�Ŵ��� Socket �������ӿ�
���������� ͨ�Ŵ��� Socket �������������¼�֪ͨ
************************************************************************/
class IAgentListener : public IClientListener
{
public:

	/*
	* ���ƣ��ر�ͨ�����֪ͨ
	* ������ͨ������ر�ʱ��Socket ���������յ���֪ͨ
	*		
	* ������	
	* ����ֵ�����Է���ֵ
	*/
	virtual EnHandleResult OnAgentShutdown()										= 0;
};

/************************************************************************
���ƣ�TCP ͨ�Ŵ��� Socket �������ӿ�
���������� TCP ͨ�Ŵ��� Socket �������������¼�֪ͨ
************************************************************************/
class ITcpAgentListener : public IAgentListener
{
};

/************************************************************************
���ƣ�PUSH ģ��ͨ�Ŵ��� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpAgentListener : public ITcpAgentListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)					{return HR_IGNORE;}
	virtual EnHandleResult OnSend(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
	virtual EnHandleResult OnPrepareConnect(CONNID dwConnID, SOCKET socket)			{return HR_IGNORE;}
	virtual EnHandleResult OnConnect(CONNID dwConnID)								{return HR_IGNORE;}
	virtual EnHandleResult OnAgentShutdown()										{return HR_IGNORE;}
};

/************************************************************************
���ƣ�PULL ͨ�Ŵ��� Socket �������������
����������ĳЩ�¼�֪ͨ��Ĭ�ϴ������������¼���
************************************************************************/
class CTcpPullAgentListener : public CTcpAgentListener
{
public:
	virtual EnHandleResult OnReceive(CONNID dwConnID, int iLength)						= 0;
	virtual EnHandleResult OnReceive(CONNID dwConnID, const BYTE* pData, int iLength)	{return HR_IGNORE;}
};

/************************************************************************
���ƣ����� Socket ����ӿ�
���������帴�� Socket ��������в������������Է��ʷ��������� Socket ���ͬʱ������ Socket ����
************************************************************************/
class IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

	/*
	* ���ƣ��ر�ͨ�����
	* �������ر�ͨ��������ر���ɺ�Ͽ��������Ӳ��ͷ�������Դ
	*		
	* ������	
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
	*/
	virtual BOOL Stop	()														= 0;

	/*
	* ���ƣ���������
	* �������û�ͨ���÷�����ָ�����ӷ�������
	*		
	* ������		dwConnID	-- ���� ID
	*			pBuffer		-- �������ݻ�����
	*			iLength		-- �������ݳ���
	*			iOffset		-- �������ݻ�����ָ��ƫ����
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� Windows API ���� ::GetLastError() ��ȡ Windows �������
	*/
	virtual BOOL Send	(CONNID dwConnID, const BYTE* pBuffer, int iLength, int iOffset = 0)	= 0;

	/*
	* ���ƣ��Ͽ�����
	* �������Ͽ�ĳ������
	*		
	* ������		dwConnID	-- ���� ID
	*			bForce		-- �Ƿ�ǿ�ƶϿ�����
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ��
	*/
	virtual BOOL Disconnect(CONNID dwConnID, BOOL bForce = TRUE)				= 0;

	/*
	* ���ƣ��Ͽ���ʱ����
	* �������Ͽ�����ָ��ʱ��������
	*		
	* ������		dwPeriod	-- ʱ�������룩
	*			bForce		-- �Ƿ�ǿ�ƶϿ�����
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ��
	*/
	virtual BOOL DisconnectLongConnections(DWORD dwPeriod, BOOL bForce = TRUE)	= 0;

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/*
	* ���ƣ��������ӵĸ�������
	* �������Ƿ�Ϊ���Ӱ󶨸������ݻ��߰�ʲô�������ݣ�����Ӧ�ó���ֻ�����
	*		
	* ������		dwConnID	-- ���� ID
	*			pv			-- ����
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���Ч������ ID��
	*/
	virtual BOOL SetConnectionExtra		(CONNID dwConnID, PVOID pExtra)			= 0;

	/*
	* ���ƣ���ȡ���ӵĸ�������
	* �������Ƿ�Ϊ���Ӱ󶨸������ݻ��߰�ʲô�������ݣ�����Ӧ�ó���ֻ�����
	*		
	* ������		dwConnID	-- ���� ID
	*			ppv			-- ����ָ��
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���Ч������ ID��
	*/
	virtual BOOL GetConnectionExtra			(CONNID dwConnID, PVOID* ppExtra)	= 0;

	/* ���ͨ������Ƿ������� */
	virtual BOOL HasStarted				()									= 0;
	/* �鿴ͨ�������ǰ״̬ */
	virtual EnServiceState GetState		()									= 0;
	/* ��ȡ������ */
	virtual DWORD GetConnectionCount	()									= 0;
	/* ��ȡĳ������ʱ�������룩 */
	virtual BOOL GetConnectPeriod	(CONNID dwConnID, DWORD& dwPeriod)		= 0;
	/* ��ȡĳ�����ӵ�Զ�̵�ַ��Ϣ */
	virtual BOOL GetRemoteAddress	(CONNID dwConnID, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)	= 0;
	/* ��ȡ���һ��ʧ�ܲ����Ĵ������ */
	virtual EnSocketError GetLastError	()									= 0;
	/* ��ȡ���һ��ʧ�ܲ����Ĵ������� */
	virtual LPCTSTR		GetLastErrorDesc()									= 0;
	/* ��ȡ������δ�������ݵĳ��� */
	virtual BOOL GetPendingDataLength	(CONNID dwConnID, int& iPending)	= 0;

	/* �������ݷ��Ͳ��� */
	virtual void SetSendPolicy				(EnSendPolicy enSendPolicy)		= 0;
	/* ���� Socket �����������ʱ�䣨���룬�������ڼ�� Socket ��������ܱ���ȡʹ�ã� */
	virtual void SetFreeSocketObjLockTime	(DWORD dwFreeSocketObjLockTime)	= 0;
	/* ���� Socket ����ش�С��ͨ������Ϊƽ���������������� 1/3 - 1/2�� */
	virtual void SetFreeSocketObjPool		(DWORD dwFreeSocketObjPool)		= 0;
	/* �����ڴ�黺��ش�С��ͨ������Ϊ Socket ����ش�С�� 2 - 3 ���� */
	virtual void SetFreeBufferObjPool		(DWORD dwFreeBufferObjPool)		= 0;
	/* ���� Socket ����ػ��շ�ֵ��ͨ������Ϊ Socket ����ش�С�� 3 ���� */
	virtual void SetFreeSocketObjHold		(DWORD dwFreeSocketObjHold)		= 0;
	/* �����ڴ�黺��ػ��շ�ֵ��ͨ������Ϊ�ڴ�黺��ش�С�� 3 ���� */
	virtual void SetFreeBufferObjHold		(DWORD dwFreeBufferObjHold)		= 0;
	/* ���ù����߳�������ͨ������Ϊ 2 * CPU + 2�� */
	virtual void SetWorkerThreadCount		(DWORD dwWorkerThreadCount)		= 0;
	/* ���ùر����ǰ�ȴ����ӹرյ��ʱ�ޣ����룬0 �򲻵ȴ��� */
	virtual void SetMaxShutdownWaitTime		(DWORD dwMaxShutdownWaitTime)	= 0;

	/* ��ȡ���ݷ��Ͳ��� */
	virtual EnSendPolicy GetSendPolicy		()	= 0;
	/* ��ȡ Socket �����������ʱ�� */
	virtual DWORD GetFreeSocketObjLockTime	()	= 0;
	/* ��ȡ Socket ����ش�С */
	virtual DWORD GetFreeSocketObjPool		()	= 0;
	/* ��ȡ�ڴ�黺��ش�С */
	virtual DWORD GetFreeBufferObjPool		()	= 0;
	/* ��ȡ Socket ����ػ��շ�ֵ */
	virtual DWORD GetFreeSocketObjHold		()	= 0;
	/* ��ȡ�ڴ�黺��ػ��շ�ֵ */
	virtual DWORD GetFreeBufferObjHold		()	= 0;
	/* ��ȡ�����߳����� */
	virtual DWORD GetWorkerThreadCount		()	= 0;
	/* ��ȡ�ر��齨ǰ�ȴ����ӹرյ��ʱ�� */
	virtual DWORD GetMaxShutdownWaitTime	()	= 0;

public:
	virtual ~IComplexSocket() {}
};

/************************************************************************
���ƣ�ͨ�ŷ��������ӿ�
����������ͨ�ŷ������������в������������Է��ʷ���
************************************************************************/
class IServer : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

	/*
	* ���ƣ�����ͨ�����
	* ���������������ͨ�������������ɺ�ɿ�ʼ���տͻ������Ӳ��շ�����
	*		
	* ������		pszBindAddress	-- ������ַ
	*			usPort			-- �����˿�
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
	*/
	virtual BOOL Start	(LPCTSTR pszBindAddress, USHORT usPort)								= 0;

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* ��ȡ���� Socket �ĵ�ַ��Ϣ */
	virtual BOOL GetListenAddress(LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)		= 0;
};

/************************************************************************
���ƣ�TCP ͨ�ŷ��������ӿ�
���������� TCP ͨ�ŷ������������в������������Է��ʷ���
************************************************************************/
class ITcpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* ���� Accept ԤͶ�� Socket ������ͨ������Ϊ�����߳����� 1 - 2 ���� */
	virtual void SetAcceptSocketCount	(DWORD dwAcceptSocketCount)		= 0;
	/* ����ͨ�����ݻ�������С������ƽ��ͨ�����ݰ���С�������ã�ͨ������Ϊ 1024 �ı����� */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	/* ���ü��� Socket �ĵȺ���д�С�����ݲ������������������ã� */
	virtual void SetSocketListenQueue	(DWORD dwSocketListenQueue)		= 0;
	/* ������������������룬0 �򲻷����������� */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	/* ��������ȷ�ϰ�����������룬0 ������������������������ɴ� [Ĭ�ϣ�WinXP 5 ��, Win7 10 ��] ��ⲻ������ȷ�ϰ�����Ϊ�Ѷ��ߣ� */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;

	/* ��ȡ Accept ԤͶ�� Socket ���� */
	virtual DWORD GetAcceptSocketCount	()	= 0;
	/* ��ȡͨ�����ݻ�������С */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* ��ȡ���� Socket �ĵȺ���д�С */
	virtual DWORD GetSocketListenQueue	()	= 0;
	/* ��ȡ���������� */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* ��ȡ��������� */
	virtual DWORD GetKeepAliveInterval	()	= 0;
};

/************************************************************************
���ƣ�UDP ͨ�ŷ��������ӿ�
���������� UDP ͨ�ŷ������������в������������Է��ʷ���
************************************************************************/
class IUdpServer : public IServer
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* �������ݱ�����󳤶ȣ������ھ����������²����� 1472 �ֽڣ��ڹ����������²����� 548 �ֽڣ� */
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)		= 0;
	/* ��ȡ���ݱ�����󳤶� */
	virtual DWORD GetMaxDatagramSize()								= 0;

	/* ���ü������Դ�����0 �򲻷��ͼ�������������������Դ�������Ϊ�Ѷ��ߣ� */
	virtual void SetDetectAttempts	(DWORD dwDetectAttempts)		= 0;
	/* ���ü������ͼ�����룬0 �����ͼ����� */
	virtual void SetDetectInterval	(DWORD dwDetectInterval)		= 0;
	/* ��ȡ���������� */
	virtual DWORD GetDetectAttempts	()								= 0;
	/* ��ȡ��������� */
	virtual DWORD GetDetectInterval	()								= 0;
};

/************************************************************************
���ƣ�ͨ�ſͻ�������ӿ�
����������ͨ�ſͻ�����������в������������Է��ʷ���
************************************************************************/
class IClient
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

	/*
	* ���ƣ�����ͨ�����
	* �����������ͻ���ͨ����������ӷ���ˣ�������ɺ�ɿ�ʼ�շ�����
	*		
	* ������		pszRemoteAddress	-- ����˵�ַ
	*			usPort				-- ����˶˿�
	*			bAsyncConnect		-- �Ƿ�����첽 Connect
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
	*/
	virtual BOOL Start	(LPCTSTR pszRemoteAddress, USHORT usPort, BOOL bAsyncConnect = FALSE)	= 0;

	/*
	* ���ƣ��ر�ͨ�����
	* �������رտͻ���ͨ��������ر���ɺ�Ͽ������˵����Ӳ��ͷ�������Դ
	*		
	* ������	
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
	*/
	virtual BOOL Stop	()																		= 0;

	/*
	* ���ƣ���������
	* �������û�ͨ���÷��������˷�������
	*		
	* ������		pBuffer		-- �������ݻ�����
	*			iLength		-- �������ݳ���
	*			iOffset		-- �������ݻ�����ָ��ƫ����
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� Windows API ���� ::GetLastError() ��ȡ Windows �������
	*/
	virtual BOOL Send	(const BYTE* pBuffer, int iLength, int iOffset = 0)						= 0;

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* ���ͨ������Ƿ������� */
	virtual BOOL HasStarted					()													= 0;
	/* �鿴ͨ�������ǰ״̬ */
	virtual EnServiceState	GetState		()													= 0;
	/* ��ȡ���һ��ʧ�ܲ����Ĵ������ */
	virtual EnSocketError	GetLastError	()													= 0;
	/* ��ȡ���һ��ʧ�ܲ����Ĵ������� */
	virtual LPCTSTR			GetLastErrorDesc()													= 0;
	/* ��ȡ�������������� ID */
	virtual CONNID			GetConnectionID	()													= 0;
	/* ��ȡ Client Socket �ĵ�ַ��Ϣ */
	virtual BOOL		GetLocalAddress	(LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)	= 0;
	/* ��ȡ������δ�������ݵĳ��� */
	virtual BOOL GetPendingDataLength	(int& iPending)											= 0;

	/* �����ڴ�黺��ش�С��ͨ������Ϊ -> PUSH ģ�ͣ�5 - 10��PULL ģ�ͣ�10 - 20 �� */
	virtual void SetFreeBufferPoolSize		(DWORD dwFreeBufferPoolSize)						= 0;
	/* �����ڴ�黺��ػ��շ�ֵ��ͨ������Ϊ�ڴ�黺��ش�С�� 3 ���� */
	virtual void SetFreeBufferPoolHold		(DWORD dwFreeBufferPoolHold)						= 0;

	/* ��ȡ�ڴ�黺��ش�С */
	virtual DWORD GetFreeBufferPoolSize		()													= 0;
	/* ��ȡ�ڴ�黺��ػ��շ�ֵ */
	virtual DWORD GetFreeBufferPoolHold		()													= 0;

public:
	virtual ~IClient() {}
};

/************************************************************************
���ƣ�TCP ͨ�ſͻ�������ӿ�
���������� TCP ͨ�ſͻ�����������в������������Է��ʷ���
************************************************************************/
class ITcpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/
	
	/* ����ͨ�����ݻ�������С������ƽ��ͨ�����ݰ���С�������ã�ͨ������Ϊ��(N * 1024) - sizeof(TBufferObj)�� */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)	= 0;
	/* ������������������룬0 �򲻷����������� */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)		= 0;
	/* ��������ȷ�ϰ�����������룬0 ������������������������ɴ� [Ĭ�ϣ�WinXP 5 ��, Win7 10 ��] ��ⲻ������ȷ�ϰ�����Ϊ�Ѷ��ߣ� */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)	= 0;

	/* ��ȡͨ�����ݻ�������С */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* ��ȡ���������� */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* ��ȡ��������� */
	virtual DWORD GetKeepAliveInterval	()	= 0;
};

/************************************************************************
���ƣ�UDP ͨ�ſͻ�������ӿ�
���������� UDP ͨ�ſͻ�����������в������������Է��ʷ���
************************************************************************/
class IUdpClient : public IClient
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* �������ݱ�����󳤶ȣ������ھ����������²����� 1472 �ֽڣ��ڹ����������²����� 548 �ֽڣ� */
	virtual void SetMaxDatagramSize	(DWORD dwMaxDatagramSize)		= 0;
	/* ��ȡ���ݱ�����󳤶� */
	virtual DWORD GetMaxDatagramSize()								= 0;

	/* ���ü������Դ�����0 �򲻷��ͼ�������������������Դ�������Ϊ�Ѷ��ߣ� */
	virtual void SetDetectAttempts	(DWORD dwDetectAttempts)		= 0;
	/* ���ü������ͼ�����룬0 �����ͼ����� */
	virtual void SetDetectInterval	(DWORD dwDetectInterval)		= 0;
	/* ��ȡ���������� */
	virtual DWORD GetDetectAttempts	()								= 0;
	/* ��ȡ��������� */
	virtual DWORD GetDetectInterval	()								= 0;
};

/************************************************************************
���ƣ�ͨ�Ŵ�������ӿ�
����������ͨ�Ŵ�����������в������������Է��ʷ������������������һ��ͬʱ���Ӷ���������Ŀͻ������
************************************************************************/
class IAgent : public IComplexSocket
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

	/*
	* ���ƣ�����ͨ�����
	* ����������ͨ�Ŵ��������������ɺ�ɿ�ʼ����Զ�̷�����
	*		
	* ������		pszBindAddress	-- ������ַ
	*			bAsyncConnect	-- �Ƿ�����첽 Connect
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
	*/
	virtual BOOL Start	(LPCTSTR pszBindAddress = nullptr, BOOL bAsyncConnect = TRUE)					= 0;

	/*
	* ���ƣ����ӷ�����
	* ���������ӷ����������ӳɹ��� IAgentListener ����յ� OnConnect() �¼�
	*		
	* ������		pszRemoteAddress	-- ����˵�ַ
	*			usPort				-- ����˶˿�
	*			pdwConnID			-- ���� ID��Ĭ�ϣ�nullptr������ȡ���� ID��
	* ����ֵ��	TRUE	-- �ɹ�
	*			FALSE	-- ʧ�ܣ���ͨ�� Windows API ���� ::GetLastError() ��ȡ Windows �������
	*/
	virtual BOOL Connect(LPCTSTR pszRemoteAddress, USHORT usPort, CONNID* pdwConnID = nullptr)			= 0;

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* ��ȡĳ�����ӵı��ص�ַ��Ϣ */
	virtual BOOL GetLocalAddress(CONNID dwConnID, LPTSTR lpszAddress, int& iAddressLen, USHORT& usPort)	= 0;
};

/************************************************************************
���ƣ�TCP ͨ�Ŵ�������ӿ�
���������� TCP ͨ�Ŵ�����������в������������Է��ʷ���
************************************************************************/
class ITcpAgent : public IAgent
{
public:

	/***********************************************************************/
	/***************************** ����������� *****************************/

public:

	/***********************************************************************/
	/***************************** ���Է��ʷ��� *****************************/

	/* �����Ƿ����õ�ַ���û��ƣ�Ĭ�ϣ������ã� */
	virtual void SetReuseAddress		(BOOL bReuseAddress)			= 0;
	/* ����Ƿ����õ�ַ���û��� */
	virtual BOOL IsReuseAddress			()								= 0;

	/* ����ͨ�����ݻ�������С������ƽ��ͨ�����ݰ���С�������ã�ͨ������Ϊ 1024 �ı����� */
	virtual void SetSocketBufferSize	(DWORD dwSocketBufferSize)		= 0;
	/* ������������������룬0 �򲻷����������� */
	virtual void SetKeepAliveTime		(DWORD dwKeepAliveTime)			= 0;
	/* ��������ȷ�ϰ�����������룬0 ������������������������ɴ� [Ĭ�ϣ�WinXP 5 ��, Win7 10 ��] ��ⲻ������ȷ�ϰ�����Ϊ�Ѷ��ߣ� */
	virtual void SetKeepAliveInterval	(DWORD dwKeepAliveInterval)		= 0;

	/* ��ȡͨ�����ݻ�������С */
	virtual DWORD GetSocketBufferSize	()	= 0;
	/* ��ȡ���������� */
	virtual DWORD GetKeepAliveTime		()	= 0;
	/* ��ȡ��������� */
	virtual DWORD GetKeepAliveInterval	()	= 0;
};

/************************************************************************
���ƣ�PULL ģ������ӿ�
���������� PULL ģ����������в�������
************************************************************************/
class IPullSocket
{
public:

	/*
	* ���ƣ�ץȡ����
	* �������û�ͨ���÷����� Socket �����ץȡ����
	*		
	* ������		dwConnID	-- ���� ID
	*			pBuffer		-- ����ץȡ������
	*			iLength		-- ץȡ���ݳ���
	* ����ֵ��	EnFetchResult
	*/
	virtual EnFetchResult Fetch	(CONNID dwConnID, BYTE* pData, int iLength)	= 0;

public:
	virtual ~IPullSocket() {}
};

/************************************************************************
���ƣ�TCP PULL ģ��ͨ�ŷ��������ӿ�
�������̳��� ITcpServer �� IPullSocket
************************************************************************/
class ITcpPullServer : public IPullSocket, public ITcpServer
{

};

/************************************************************************
���ƣ�TCP PULL ģ��ͨ�ſͻ�������ӿ�
�������̳��� ITcpClient �� IPullSocket
************************************************************************/
class ITcpPullClient : public IPullSocket, public ITcpClient
{

};

/************************************************************************
���ƣ�TCP PULL ģ�ʹ�������ӿ�
�������̳��� ITcpAgent �� IPullSocket
************************************************************************/
class ITcpPullAgent : public IPullSocket, public ITcpAgent
{

};
