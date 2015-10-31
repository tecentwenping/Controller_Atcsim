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
	//�����ڵ���ɾ��
	template<typename T>
	T *GetSimWnd(WndsType type);//����ָ�����͵Ĵ���ָ��

	void ClearWndData(WndsType wndType);//��մ�������
	bool AddSimWnd(WndsType type, SimWnd* pWnd);
	bool DelSimWnd(WndsType type);
	void SetMainWnd(QWidget *pWnd);
	QWidget* GetMainWnd();

	//�����ڲ���
	void AddLayout(LayoutType type, shared_ptr<WndsLayout> pLayout);
	void UpdateLayout(LayoutType type = LAYOUT_SUPERVISOR);
protected:
	//����ָ�����͵Ĵ���
	bool FindSimWnd(WndsType wndType);
protected:
	QWidget * m_pMainWnd;//�����ڣ����ڷ�������ͼ���������ִ���
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
