unit HPSocketSDKUnit;

interface

uses
    Winapi.Windows;

type
    PInteger = ^Integer;
    PUShort = ^USHORT;

    // Ӧ�ó���״̬
    EnAppState =
    (
        ST_STARTING, ST_STARTED, ST_STOPING, ST_STOPED
    );

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
    En_HP_ServerError = (HP_SE_OK = 0, // �ɹ�
      HP_SE_ILLEGAL_STATE = 1, // ��ǰ״̬���������
      HP_SE_INVALID_PARAM = 2, // �Ƿ�����
      HP_SE_SOCKET_CREATE = 3, // �������� SOCKET ʧ��
      HP_SE_SOCKET_BIND = 4, // �󶨼�����ַʧ��
      HP_SE_SOCKET_PREPARE = 5, // ���ü��� SOCKET ʧ��
      HP_SE_SOCKET_LISTEN = 6, // ��������ʧ��
      HP_SE_CP_CREATE = 7, // ������ɶ˿�ʧ��
      HP_SE_WORKER_THREAD_CREATE = 8, // ���������߳�ʧ��
      HP_SE_DETECT_THREAD_CREATE = 9, // ��������߳�ʧ��
      HP_SE_SOCKE_ATTACH_TO_CP = 10 // ���� SOCKET �󶨵���ɶ˿�ʧ��
      );

    { ************************************************************************
      ���ƣ������������
      ������Start() / Stop() ����ִ��ʧ��ʱ����ͨ�� GetLastError() ��ȡ�������
      ************************************************************************ }
    En_HP_ClientError = (HP_CE_OK = 0, // �ɹ�
      HP_CE_ILLEGAL_STATE = 1, // ��ǰ״̬���������
      HP_CE_INVALID_PARAM = 2, // �Ƿ�����
      HP_CE_SOCKET_CREATE_FAIL = 3, // ���� Client Socket ʧ��
      HP_CE_SOCKET_PREPARE_FAIL = 4, // ���� Client Socket ʧ��
      HP_CE_CONNECT_SERVER_FAIL = 5, // ���ӷ�����ʧ��
      HP_CE_WORKER_CREATE_FAIL = 6, // ���������߳�ʧ��
      HP_CE_DETECTOR_CREATE_FAIL = 7, // ��������߳�ʧ��
      HP_CE_NETWORK_ERROR = 8, // �������
      HP_CE_DATA_PROC_ERROR = 9 // ���ݴ������
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
    HP_FN_OnError = function(dwConnID: DWORD; enOperation: En_HP_SocketOperation; iErrorCode: Integer) : En_HP_HandleResult; stdcall;

    // ����˻ص�����
    HP_FN_OnPrepareListen = function(soListen: Pointer) : En_HP_HandleResult; stdcall;
    // ���Ϊ TCP ���ӣ�pClientΪ SOCKET ��������Ϊ UDP ���ӣ�pClientΪ SOCKADDR_IN ָ�룻
    HP_FN_OnAccept = function(dwConnID: DWORD; pClient: Pointer) : En_HP_HandleResult; stdcall;
    HP_FN_OnServerShutdown = function(): En_HP_HandleResult; stdcall;

    // �ͻ��˻ص�����
    HP_FN_OnPrepareConnect = function(dwConnID: DWORD; socket: Pointer) : En_HP_HandleResult; stdcall;
    HP_FN_OnConnect = function(dwConnID: DWORD): En_HP_HandleResult; stdcall;

const
    HPSocketDLL = 'HPSocket4C_U.dll';

    // ���� HP_TcpPullServerListener ����
    function Create_HP_TcpServerListener(): Pointer; stdcall; external HPSocketDLL;

    // ���� HP_TcpServer ����
    function Create_HP_TcpServer(pListener: Pointer): Pointer; stdcall; external HPSocketDLL;

    {/*
    * ���ƣ�����ͨ�����
    * ���������������ͨ�������������ɺ�ɿ�ʼ���տͻ������Ӳ��շ�����
    *
    * ������		pszBindAddress	-- ������ַ
    *			usPort			-- �����˿�
    * ����ֵ��	TRUE	-- �ɹ�
    *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
    */}
    function HP_Server_Start(pServer: Pointer; pszBindAddress: PWideChar; usPort: USHORT):Boolean; stdcall; external HPSocketDLL;

    {/*
    * ���ƣ��ر�ͨ�����
    * �������رշ����ͨ��������ر���ɺ�Ͽ����пͻ������Ӳ��ͷ�������Դ
    *
    * ������
    * ����ֵ��	TRUE	-- �ɹ�
    *			FALSE	-- ʧ�ܣ���ͨ�� GetLastError() ��ȡ�������
    */}
    function HP_Server_Stop(pServer: Pointer):Boolean; stdcall; external HPSocketDLL;

    {/*
    * ���ƣ���������
    * �������û�ͨ���÷�����ָ���ͻ��˷�������
    *
    * ������		dwConnID	-- ���� ID
    *			pBuffer		-- �������ݻ�����
    *			iLength		-- �������ݳ���
    * ����ֵ��	TRUE	-- �ɹ�
    *			FALSE	-- ʧ��
    */}
    function HP_Server_Send(pServer: Pointer; dwConnID:DWORD; const pBuffer: Pointer; iLength: Integer):Boolean; stdcall; external HPSocketDLL;


    {/*
    * ���ƣ��Ͽ�����
    * �������Ͽ���ĳ���ͻ��˵�����
    *
    * ������		dwConnID	-- ���� ID
    *			bForce		-- �Ƿ�ǿ�ƶϿ�����
    * ����ֵ��	TRUE	-- �ɹ�
    *			FALSE	-- ʧ��
    */}
    function HP_Server_Disconnect(pServer: Pointer; dwConnID: DWORD; bForce: DWORD):Boolean; stdcall; external HPSocketDLL;


    // ��ȡĳ���ͻ������ӵĵ�ַ��Ϣ
    function  HP_Server_GetClientAddress(pServer: Pointer; dwConnID: DWORD; lpszAddress: PWideChar; piAddressLen: PInteger; pusPort: PUShort):Boolean; stdcall; external HPSocketDLL;

    // ��ȡ���һ��ʧ�ܲ����Ĵ������
    function  HP_Server_GetLastError(pServer:Pointer):Integer;stdcall;external HPSocketDLL;

    // ��ȡ���һ��ʧ�ܲ����Ĵ�������
    function  HP_Server_GetLastErrorDesc(pServer:Pointer) : PWideChar;stdcall;external HPSocketDLL;

    // ���� HP_TcpServer ����
    procedure Destroy_HP_TcpServer(pServer: Pointer); stdcall;external HPSocketDLL;

    // ���� HP_TcpClient ����
    procedure Destroy_HP_TcpClient(pClient: Pointer); stdcall;external HPSocketDLL;

    // ���� HP_TcpServerListener ����
    procedure Destroy_HP_TcpServerListener(pServer: Pointer); stdcall;external HPSocketDLL;

    // ���� HP_TcpClientListener ����
    procedure Destroy_HP_TcpClientListener(pClient: Pointer); stdcall;external HPSocketDLL;


    { ***************************** Server �ص��������÷��� ***************************** }

      procedure HP_Set_FN_Server_OnPrepareListen(pListener: Pointer; fn: HP_FN_OnPrepareListen);stdcall;external HPSocketDLL;
      procedure HP_Set_FN_Server_OnAccept(pListener: Pointer; fn: HP_FN_OnAccept); stdcall; external HPSocketDLL;
      procedure HP_Set_FN_Server_OnSend(pListener: Pointer; fn: HP_FN_OnSend); stdcall; external HPSocketDLL;
      procedure HP_Set_FN_Server_OnReceive(pListener: Pointer; fn: HP_FN_OnReceive); stdcall; external HPSocketDLL;
      procedure HP_Set_FN_Server_OnClose(pListener: Pointer; fn: HP_FN_OnClose); stdcall; external HPSocketDLL;
      procedure HP_Set_FN_Server_OnError(pListener: Pointer; fn: HP_FN_OnError); stdcall; external HPSocketDLL;
      procedure HP_Set_FN_Server_OnServerShutdown(pListener: Pointer; fn: HP_FN_OnServerShutdown); stdcall;external HPSocketDLL;

    { ********************************************************************************** }

implementation


end.
