#ifndef CSendFlyPlanToRDP_H
#define CSendFlyPlanToRDP_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CSendFlyPlanToRDP
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/25
  ����  ����:  ���ļ���������CSendFlyPlanToRDP������������Ƿ��ͷ��мƻ���RDP
  ����  ����:   
**************************************************************************/

#include <QObject>
#include <QUdpSocket>
#include <vector>

class CSendFlyPlanToRDP : public QObject
{
	Q_OBJECT

public:
	CSendFlyPlanToRDP();
	~CSendFlyPlanToRDP();
	private slots:
		void slot_SendFlyPlanToRDP();
		void slot_StartSendFlyPlanToRDP();
private:
	QUdpSocket *m_UdpSendFlyPlanToRDPSocket;//��RDP���ͷ��мƻ���UDP�׽���
	static const int SENDFLYPLANPORT = 9903; //���ͷ��мƻ�UDP�˿ڣ����͵�Ŀ�ĵ���RDP
	int m_iCount;
	
};

#endif // CSendFlyPlanToRDP_H
