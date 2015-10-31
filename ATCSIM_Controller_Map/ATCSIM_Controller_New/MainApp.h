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
	//将不同席位的不同实现放在主函数中进行创建，并设置CMainApp的指针
	void SetMainCallbackPtr(MainCallbackLogicPtr pCallback);
	void SetWndsMangerPtr(WndsMangerPtr pWndsManager);
	void SetMainWindowPtr(WMainWindowPtr pMainWindow);
	void SetWndsCreatorPtr(WndsCreatorPtr pWndsCreator);

	//初始化应用程序实例
	bool InitAppInstance();
	//退出程序
	void ExitApp();
	//当训练计划结束或重新开始时清空数据
	//该函数主要用于当停止某个训练计划后再开始另外的训练计划时，
	//要保证上一次的训练计划数据全部清空
	void ClearData();


public:
	WndsMangerPtr	GetWndsManagerPtr()const;
	MapMangerPtr	GetMapMangerPtr()const;
	WMainWindowPtr	GetWMainWindowPtr()const;
	DataManagerPtr  GetDataManagerPtr()const;
	NetManagerPtr	GetNetManagerPtr()const;
	TimerPtr		GetTimerPtr()const;

	//返回不同界面的回调操作
	MainCallbackLogicPtr	GetMainCallbackLogic()const;
	template<typename T>
	T *GetMainCallbackLogic()
	{
		return dynamic_cast<T*>()
	}
	//主要用于判断当前系统是否已经运行，如果没运行，则不能进行相应的操作
	bool IsRunning();

protected:
	/*********************************************************
	*函数名：InitWnds
	*函数功能：初始化窗体
	*变量：
	**********************************************************/
	void InitWnds();
	/*********************************************************
	*函数名：InitSimMap
	*函数功能：初始化地图
	*变量：
	**********************************************************/
	void InitSimMap();
	//初始化坐标
    void InitCoordinate();
	//初始化图元
	void InitGlyphs();

	void InitData();
	//初始化网络
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
//创建单件
typedef singleton_default<CMainApp> theApp;

#endif // MAINAPP_H
