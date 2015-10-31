#ifndef CGLYPHUPDATER_H
#define CGLYPHUPDATER_H 
#include <QObject>

class CGlyphUpdater:public QObject
{
     Q_OBJECT

public:
	CGlyphUpdater();
	~CGlyphUpdater();
public:
	void UpdateTrace();
private slots:
		void UpdateAircraftTraceSlot(int iTraceID);
		void UpdateAircraftTraceSlot_1();

private:
	int m_iTraceID;
	int m_iCount;
	
};

#endif // CGLYPHUPDATER_H
