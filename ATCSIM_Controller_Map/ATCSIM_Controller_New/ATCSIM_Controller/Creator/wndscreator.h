#ifndef WNDSCREATOR_H
#define WNDSCREATOR_H

#include <QWidget>
#include <boost/shared_ptr.hpp>
class CWndsManager;
class WndsCreator 
{
	

public:
	WndsCreator(QWidget *pMainWindow);
	WndsCreator(boost::shared_ptr<CWndsManager> pWndsManager,QWidget* pMainWindow);
	virtual ~WndsCreator();
public:
	virtual void InitAppWnds()=0;
protected:
	QWidget * m_pMainWindow;
	boost::shared_ptr<CWndsManager> m_pWndsManager;
	
};

#endif // WNDSCREATOR_H
