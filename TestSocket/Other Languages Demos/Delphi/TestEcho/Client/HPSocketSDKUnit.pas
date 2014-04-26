unit HPSocketSDKUnit;

interface

uses
    Winapi.Windows;

type
    PInteger = ^Integer;
    PUShort = ^USHORT;

    // Ӧ�ó���״̬
    EnAppState = (ST_STARTING, ST_STARTED, ST_STOPING, ST_STOPED);

    { *****************************************************************************************************/
      /******************************************** �����ࡢ�ӿ� ********************************************/
      /*****************************************************************************************************/

      /************************************************************************
      ���ƣ�ͨ���������״̬
      ������Ӧ�ó������ͨ��ͨ������� GetState() ������ȡ�����ǰ����״̬
      ************************************************************************ }
    En_HP_ServiceState = (HP_SS_STARTING = 0, // ��������
      HP_SS_STARTED = 1, // �Ѿ�����
      HP_SS_STOPING = 2, // ����ֹͣ
      HP_SS_STOPED = 3 // �Ѿ�����
      );

    { ************************************************************************
      ���ƣ�Socket ��������
      ������Ӧ�ó���� OnErrror() �¼���ͨ���ò�����ʶ�����ֲ������µĴ���
      ************************************************************************ }
    En_HP_SocketOperation = (HP_SO_UNKNOWN = 0, // Unknown
      HP_SO_ACCEPT = 1, // Acccept
      HP_SO_CONNECT = 2, // Connnect
      HP_SO_SEND = 3, // Send
      HP_SO_RECEIVE = 4 // Receive
      );

    { ************************************************************************
      ���ƣ��¼�֪ͨ������
      �������¼�֪ͨ�ķ���ֵ����ͬ�ķ���ֵ��Ӱ��ͨ������ĺ�����Ϊ
      ************************************************************************ }
    En_HP_HandleResult = (HP_HR_OK = 0, // �ɹ�
      HP_HR_IGNORE = 1, // ����
      HP_HR_ERROR = 2 // ����
      );

    { ************************************************************************
      ���ƣ������������
      ������Start() / Stop() ����ִ��ʧ��ʱ����ͨ�� GetLastError() ��ȡ�������
      ************************************************************************ }
    En_HP_SocketError = (HP_SE_OK = 0, // �ɹ�
      HP_SE_ILLEGAL_STATE = 1, // ��ǰ״̬���������
      HP_SE_INVALID_PARAM = 2, // �Ƿ�����
      HP_SE_SOCKET_CREATE = 3, // ���� SOCKET ʧ��
      HP_SE_SOCKET_BIND = 4, // �� SOCKET ʧ��
      HP_SE_SOCKET_PREPARE = 5, // ���� SOCKET ʧ��
      HP_SE_SOCKET_LISTEN = 6, // ���� SOCKET ʧ��
      HP_SE_CP_CREATE = 7, // ������ɶ˿�ʧ��
      HP_SE_WORKER_THREAD_CREATE = 8, // ���������߳�ʧ��
      HP_SE_DETECT_THREAD_CREATE = 9, // ��������߳�ʧ��
      HP_SE_SOCKE_ATTACH_TO_CP = 10, // ����ɶ˿�ʧ��
      HP_SE_CONNECT_SERVER = 11, // ���ӷ�����ʧ��
      HP_SE_NETWORK = 12, // �������
      HP_SE_DATA_PROC = 13, // ���ݴ������
      HP_SE_DATA_SEND = 14 // ���ݷ���ʧ��
      );

    { ************************************************************************
      ���ƣ�����ץȡ���
      ����������ץȡ�����ķ���ֵ
      ************************************************************************ }
    En_HP_FetchResult = (HP_FR_OK = 0, // �ɹ�
      HP_FR_LENGTH_TOO_LONG = 1, // ץȡ���ȹ���
      HP_FR_DATA_NOT_FOUND = 2 // �Ҳ��� ConnID ��Ӧ������
      );

    { **************************************************** }

    // �����ص�����
    HP_FN_OnSend = function(dwConnID: DWORD; const pData: Pointer; iLength: Integer): En_HP_HandleResult; stdcall;
    HP_FN_OnReceive = function(dwConnID: DWORD; const pData: Pointer; iLength: Integer): En_HP_HandleResult; stdcall;
    HP_FN_OnClose = function(dwConnID: DWORD): En_HP_HandleResult; stdcall;
    HP_FN_OnError = function(dwConnID: DWORD; enOperation: En_HP_SocketOperation; iErrorCode: Integer): En_HP_HandleResult; stdcall;

    // ����˻ص�����
    HP_FN_OnPrepareListen = function(soListen: Pointer): En_HP_HandleResult; stdcall;
    // ���Ϊ TCP ���ӣ�pClientΪ SOCKET ��������Ϊ UDP ���ӣ�pClientΪ SOCKADDR_IN ָ�룻
    HP_FN_OnAccept = function(dwConnID: DWORD; pClient: Pointer): En_HP_HandleResult; stdcall;
    HP_FN_OnServerShutdown = function(): En_HP_HandleResult; stdcall;

    // �ͻ��˻ص�����
    HP_FN_OnPrepareConnect = function(dwConnID: DWORD; socket: Pointer): En_HP_HandleResult; stdcall;
    HP_FN_OnConnect = function(dwConnID: DWORD): En_HP_HandleResult; stdcall;

const
    HPSocketDLL = 'HPSocket4C_U.dll';

    // ���� HP_TcpPullServerListener ����
function Create_HP_TcpServerListener(): Pointer; stdcall; external HPSocketDLL;

// ���� HP_TcpServer ����
function Create_HP_TcpServer(pListener: Pointer): Pointer; stdcall; external HPSocketDLL;

{ /*
  * ���ƣ�����ͨ�����
  * ���������������ͨ�������������ɺ�ɿ�ʼ���տͻ������Ӳ��շ�����
  *
  * ������		pszBindAddress	-- ������ַ
  *			usPort			-- �����˿�
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
  */ }
function HP_Server_Start(pServer: Pointer; pszBindAddress: PWideChar; usPort: USHORT): Boolean; stdcall; external HPSocketDLL;

{ /*
  * ���ƣ��ر�ͨ�����
  * �������رշ����ͨ��������ر���ɺ�Ͽ����пͻ������Ӳ��ͷ�������Դ
  *
  * ������
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
  */ }
function HP_Server_Stop(pServer: Pointer): Boolean; stdcall; external HPSocketDLL;

{ /*
  * ���ƣ��Ͽ�����
  * �������Ͽ���ĳ���ͻ��˵�����
  *
  * ������		dwConnID	-- ���� ID
  *			bForce		-- �Ƿ�ǿ�ƶϿ�����
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ��
  */ }
function HP_Server_Disconnect(pServer: Pointer; dwConnID: DWORD; bForce: Boolean): Boolean; stdcall; external HPSocketDLL;

// ��ȡĳ���ͻ������ӵĵ�ַ��Ϣ
function HP_Server_GetRemoteAddress(pServer: Pointer; dwConnID: DWORD; lpszAddress: PWideChar; piAddressLen: PInteger; pusPort: PUShort): Boolean; stdcall;
  external HPSocketDLL;

// ��ȡ���һ��ʧ�ܲ����Ĵ������
function HP_Server_GetLastError(pServer: Pointer): Integer; stdcall; external HPSocketDLL;

// ��ȡ���һ��ʧ�ܲ����Ĵ�������
function HP_Server_GetLastErrorDesc(pServer: Pointer): PWideChar; stdcall; external HPSocketDLL;

// ���� HP_TcpServer ����
procedure Destroy_HP_TcpServer(pServer: Pointer); stdcall; external HPSocketDLL;

// ���� HP_TcpClient ����
procedure Destroy_HP_TcpClient(pClient: Pointer); stdcall; external HPSocketDLL;

// ���� HP_TcpServerListener ����
procedure Destroy_HP_TcpServerListener(pServer: Pointer); stdcall; external HPSocketDLL;

// ���� HP_TcpClientListener ����
procedure Destroy_HP_TcpClientListener(pClient: Pointer); stdcall; external HPSocketDLL;

{ ***************************** Server �ص��������÷��� ***************************** }

procedure HP_Set_FN_Server_OnPrepareListen(pListener: Pointer; fn: HP_FN_OnPrepareListen); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnAccept(pListener: Pointer; fn: HP_FN_OnAccept); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnSend(pListener: Pointer; fn: HP_FN_OnSend); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnReceive(pListener: Pointer; fn: HP_FN_OnReceive); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnClose(pListener: Pointer; fn: HP_FN_OnClose); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnError(pListener: Pointer; fn: HP_FN_OnError); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Server_OnServerShutdown(pListener: Pointer; fn: HP_FN_OnServerShutdown); stdcall; external HPSocketDLL;

{ ********************************************************************************** }

{ ***************************** Client ����������� *****************************/

  /*
  * ���ƣ�����ͨ�����
  * �����������ͻ���ͨ����������ӷ���ˣ�������ɺ�ɿ�ʼ�շ�����
  *
  * ������		pszRemoteAddress	-- ����˵�ַ
  *			usPort				-- ����˶˿�
  *			bAsyncConnect		-- �Ƿ�����첽 Connnect
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
  * }
function HP_Client_Start(pClient: Pointer; pszRemoteAddress: PWideChar; usPort: USHORT; bAsyncConnect: Boolean): Boolean; stdcall; external HPSocketDLL;

{ /*
  * ���ƣ��ر�ͨ�����
  * �������رտͻ���ͨ��������ر���ɺ�Ͽ������˵����Ӳ��ͷ�������Դ
  *
  * ������
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
  */ }
function HP_Client_Stop(pClient: Pointer): Boolean; stdcall; external HPSocketDLL;

{ /*
  * ���ƣ���������
  * �������û�ͨ���÷��������˷�������
  *
  * ������		dwConnID	-- ���� ID������������Ŀǰ�ò�����δʹ�ã�
  *			pBuffer		-- �������ݻ�����
  *			iLength		-- �������ݳ���
  * ����ֵ��	TRUE	-- �ɹ�
  *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
  */ }
function HP_Client_Send(pClient: Pointer; const pBuffer: Pointer; iLength: Integer): Boolean; stdcall; external HPSocketDLL;


// ��ȡ���һ��ʧ�ܲ����Ĵ������
function HP_Client_GetLastError(pServer: Pointer): Integer; stdcall; external HPSocketDLL;

// ��ȡ���һ��ʧ�ܲ����Ĵ�������
function HP_Client_GetLastErrorDesc(pServer: Pointer): PWideChar; stdcall; external HPSocketDLL;

// ���� HP_TcpClientListener ����
function Create_HP_TcpClientListener(): Pointer; stdcall; external HPSocketDLL;

// ���� HP_TcpClient ����
function Create_HP_TcpClient(pListener: Pointer): Pointer; stdcall; external HPSocketDLL;

// ��ȡ�������������� ID
function HP_Client_GetConnectionID(pClient: Pointer): DWORD; stdcall; external HPSocketDLL;

{ /***************************** Client �ص��������÷��� *****************************/ }
procedure HP_Set_FN_Client_OnPrepareConnect(pListener: Pointer; fn: HP_FN_OnPrepareConnect); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Client_OnConnect(pListener: Pointer; fn: HP_FN_OnConnect); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Client_OnSend(pListener: Pointer; fn: HP_FN_OnSend); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Client_OnReceive(pListener: Pointer; fn: HP_FN_OnReceive); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Client_OnClose(pListener: Pointer; fn: HP_FN_OnClose); stdcall; external HPSocketDLL;
procedure HP_Set_FN_Client_OnError(pListener: Pointer; fn: HP_FN_OnError); stdcall; external HPSocketDLL;
{ /**************************************************************************/ }

implementation

end.
