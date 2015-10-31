#include "wndscreator.h"
#include "WndsManager.h"



WndsCreator::WndsCreator( QWidget *pMainWindow )
:m_pMainWindow(pMainWindow)
{

}

WndsCreator::WndsCreator( boost::shared_ptr<CWndsManager> pWndsManager,QWidget* pMainWindow )
:m_pWndsManager(pWndsManager),m_pMainWindow(pMainWindow)
{

}

WndsCreator::~WndsCreator()
{

}
