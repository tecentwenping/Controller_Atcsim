#include "WndsManager.h"
#include "WndsLayout.h"
#include <utility>
CWndsManager::CWndsManager():m_pMainWnd(NULL)

{


}  

CWndsManager::~CWndsManager()
{

}

void CWndsManager::ClearWndData( WndsType wndType )
{
	//清空所有窗口数据
	if(WND_ALL == wndType)
	{
		std::map<WndsType,SimWnd*>::iterator iter = m_mpWidget.begin();
		for(; iter != m_mpWidget.end(); ++iter)
		{
			if(iter->second)
			{
				iter->second->ClearWndData();
			}

		}
	}
	//清空指定窗口的数据
	else
	{
		SimWnd* wndPtr = GetSimWnd<SimWnd>(wndType);
		if(wndPtr)
		{
			wndPtr->ClearWndData();
		}
	}

}

bool CWndsManager::AddSimWnd( WndsType type, SimWnd* pWnd )
{
	if(FindSimWnd(type))
	{
		return false;
	}
	m_mpWidget.insert(std::make_pair(type,pWnd));
	return true;

}

bool CWndsManager::DelSimWnd( WndsType type )
{
	std::map<WndsType,SimWnd*>::iterator iter = m_mpWidget.find(type);
	if(iter != m_mpWidget.end())
	{
		m_mpWidget.erase(iter);
		return true;
	}
    return false;

}

void CWndsManager::SetMainWnd( QWidget *pWnd )
{
   m_pMainWnd = pWnd;
}

QWidget* CWndsManager::GetMainWnd()
{
  return m_pMainWnd;
}


void CWndsManager::AddLayout( LayoutType type, shared_ptr<WndsLayout> pLayout )
{
  m_mpLayout.insert(std::make_pair(type,pLayout));
}

void CWndsManager::UpdateLayout( LayoutType type /*= LAYOUT_SUPERVISOR*/ )
{
	std::map<LayoutType,shared_ptr<WndsLayout> >::iterator iter = m_mpLayout.find(type);
	if(iter != m_mpLayout.end())
	{
		iter->second->Layout();
	}

}

bool CWndsManager::FindSimWnd( WndsType wndType )
{
	std::map<WndsType,SimWnd*>::iterator iter = m_mpWidget.find(wndType);
	if(iter != m_mpWidget.end())
	{
		return true;
	}
	return false;

}
