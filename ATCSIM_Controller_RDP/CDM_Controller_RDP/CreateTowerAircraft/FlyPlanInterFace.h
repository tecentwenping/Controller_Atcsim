#ifndef CFlyPlanInterFace_H
#define CFlyPlanInterFace_H
/**************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ���ѧ�չ�ʵ����
  ����  ����: CFlyPlanInterFace
  ����  �ߡ�: ����ƽ
  ����  ����:1.0
  ��������ڡ�:2014/12/25
  ����  ����:  ���ļ���������CFlyPlanInterFace���ǹ��ڷ��мƻ�һϵ�в����Ľӿڷ�װ
  ����  ����:   
**************************************************************************/

#include <QObject>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <QThread>
#include <QObject>
class CGetFlyPlanFromDB;
class CSendFlyPlanToRDP;
typedef boost::shared_ptr<CGetFlyPlanFromDB> CGetFlyPlanFromDBPtr;
typedef boost::shared_ptr<CSendFlyPlanToRDP> CSendFlyPlanToRDPPtr;

class CFlyPlanInterFace : public QObject
{
	Q_OBJECT

public:
	CFlyPlanInterFace();
	~CFlyPlanInterFace();
private:
	void    myInitGetFlyPlanFunc();//��ʼ����ȡ���мƻ��ĺ���
private:
	CGetFlyPlanFromDBPtr  m_pGetFlyPlanFromDB;
	CSendFlyPlanToRDPPtr  m_pSendFlyPlanToRDP;
	
};

#endif // CFlyPlanInterFace_H
