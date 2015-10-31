#ifndef WNDSMANAGER_H
#define WNDSMANAGER_H
#include "./boost/make_shared.hpp"
#include <map>
#include "wndsType.h"
#include "SimWnd.h"

using namespace boost;
class QWidget;
class WndsLayout;

class CWndsManager
{
public:
	CWndsManager();
	virtual ~CWndsManager();
public:
	//处理窗口的增删查
	template<typename T>
	T *GetSimWnd(WndsType type);//返回指定类型的窗口指针

	void ClearWndData(WndsType wndType);//清空窗口数据
	bool AddSimWnd(WndsType type, SimWnd* pWnd);
	bool DelSimWnd(WndsType type);
	void SetMainWnd(QWidget *pWnd);
	QWidget* GetMainWnd();

	//处理窗口布局
	void AddLayout(LayoutType type, shared_ptr<WndsLayout> pLayout);
	void UpdateLayout(LayoutType type = LAYOUT_SUPERVISOR);
protected:
	//查找指定类型的窗口
	bool FindSimWnd(WndsType wndType);
protected:
	QWidget * m_pMainWnd;//主窗口，用于放置主地图或其它布局窗口
	std::map<WndsType,SimWnd*> m_mpWidget;
	std::map<LayoutType,shared_ptr<WndsLayout>> m_mpLayout;
};
template<typename T>
T* CWndsManager::GetSimWnd(WndsType wndType)
{
	std::map<WndsType,SimWnd*>::iterator iter = m_mpWidget.find(wndType);
	if(iter != m_mpWidget.end())
	{
		return dynamic_cast<T*>(iter->second);
	}
	return NULL;
}
#endif // WNDSMANAGER_H
