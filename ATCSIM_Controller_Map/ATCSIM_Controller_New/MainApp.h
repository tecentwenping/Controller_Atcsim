#ifndef MAINAPP_H
#define MAINAPP_H

#include <boost/pool/detail/singleton.hpp>
using boost::details::pool::singleton_default;
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>
#include <vector>
using namespace boost;
using namespace boost::signals2;
#include "EnumVarible.h"
class CWndsManager;
class CMainWindow;
class CMainCallBackLogic;
class CMapManager;
class WndsCreator;
class CDataManager;
class CNetManager;
class timer;
typedef boost::shared_ptr<CNetManager>  NetManagerPtr;
typedef boost::shared_ptr<CDataManager> DataManagerPtr;
typedef boost::shared_ptr<CMapManager> MapMangerPtr;
typedef boost::shared_ptr<CWndsManager> WndsMangerPtr;
typedef boost::shared_ptr<CMainCallBackLogic> MainCallbackLogicPtr;
typedef boost::shared_ptr<WndsCreator>  WndsCreatorPtr;
typedef CMainWindow*	WMainWindowPtr;
typedef boost::shared_ptr<timer>   TimerPtr;

#include <QThread>
class CMainApp
{
	

public:
	CMainApp();
	virtual ~CMainApp();
public:
	//����ͬϯλ�Ĳ�ͬʵ�ַ����������н��д�����������CMainApp��ָ��
	void SetMainCallbackPtr(MainCallbackLogicPtr pCallback);
	void SetWndsMangerPtr(WndsMangerPtr pWndsManager);
	void SetMainWindowPtr(WMainWindowPtr pMainWindow);
	void SetWndsCreatorPtr(WndsCreatorPtr pWndsCreator);

	//��ʼ��Ӧ�ó���ʵ��
	bool InitAppInstance();
	//�˳�����
	void ExitApp();
	//��ѵ���ƻ����������¿�ʼʱ�������
	//�ú�����Ҫ���ڵ�ֹͣĳ��ѵ���ƻ����ٿ�ʼ�����ѵ���ƻ�ʱ��
	//Ҫ��֤��һ�ε�ѵ���ƻ�����ȫ�����
	void ClearData();


public:
	WndsMangerPtr	GetWndsManagerPtr()const;
	MapMangerPtr	GetMapMangerPtr()const;
	WMainWindowPtr	GetWMainWindowPtr()const;
	DataManagerPtr  GetDataManagerPtr()const;
	NetManagerPtr	GetNetManagerPtr()const;
	TimerPtr		GetTimerPtr()const;

	//���ز�ͬ����Ļص�����
	MainCallbackLogicPtr	GetMainCallbackLogic()const;
	template<typename T>
	T *GetMainCallbackLogic()
	{
		return dynamic_cast<T*>()
	}
	//��Ҫ�����жϵ�ǰϵͳ�Ƿ��Ѿ����У����û���У����ܽ�����Ӧ�Ĳ���
	bool IsRunning();

protected:
	/*********************************************************
	*��������InitWnds
	*�������ܣ���ʼ������
	*������
	**********************************************************/
	void InitWnds();
	/*********************************************************
	*��������InitSimMap
	*�������ܣ���ʼ����ͼ
	*������
	**********************************************************/
	void InitSimMap();
	//��ʼ������
    void InitCoordinate();
	//��ʼ��ͼԪ
	void InitGlyphs();

	void InitData();
	//��ʼ������
	void InitNetWork();
private:
	WndsMangerPtr	m_pWndsManager;
	MapMangerPtr	m_pMapManager;
	WMainWindowPtr	m_pMainWindow;
	MainCallbackLogicPtr m_pMainCallback;
	WndsCreatorPtr	m_pWndsCreator;	
	RUNNING_STATUS	m_eStatus;
	TimerPtr        m_pTimer;
	//
	QThread			m_RecvAircraftTraceThread;
	DataManagerPtr	m_pDataManager;
	NetManagerPtr	m_pNetManager;
};
//��������
typedef singleton_default<CMainApp> theApp;

#endif // MAINAPP_H
