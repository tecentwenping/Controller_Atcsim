//���ļ���ſ�����ض���ı༭�����������¶���ı༭��

//����                                        �༭��
//����̨(Beacon)                        BeaconEditPacket
//�澯��(StcaArea)
//�͸���(MsawArea)
//������������(RestrictArea)
//ATS(ATS)
//�״����ä��(Radarrobe)
//��·(Course)


#ifndef _H_AIRSPACE_EDIT_PACKET_H
#define _H_AIRSPACE_EDIT_PACKET_H

#include "net_packet/serial_base.h"
#include "DataObj/dataobjs.h"
#include "edit_type.h"



//����̨�༭��
class BeaconEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(BeaconEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Beacon m_data;
private:
	//virtual void ReadFromBuffer(const char* pBuffer);
	//virtual void WriteToBuffer(char* pBuffer);
	//virtual int GetBufferSize();
	SERIALIZE_PACKET(m_edit_type & m_data);
};

class SectorEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SectorEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Sector m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�澯���༭��
class StcaAreaEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(StcaAreaEditPacket);
public:
	EDIT_TYPE m_edit_type;
	StcaArea m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//�͸���
class MsawAreaEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(MsawAreaEditPacket);
public:
	EDIT_TYPE m_edit_type;
	MsawArea m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//������������
class RestrictAreaEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RestrictAreaEditPacket);
public:
	EDIT_TYPE m_edit_type;
	RestrictArea m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  qnh����༭��
\details  
\author CX
\date 2013/07/10
*/
class QnhAreaEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(QnhAreaEditPacket);
public:
	EDIT_TYPE m_edit_type;
	QnhArea m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  �澯��������༭��
\details  
\author ZJ
\date 2013/07/16
*/
class InhibitoryAreaEditPacket : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(InhibitoryAreaEditPacket);
public:
	EDIT_TYPE m_edit_type;
	InhibitoryArea m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

//ATS�༭��
class ATSEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ATSEditPacket);
public:
	EDIT_TYPE m_edit_type;
	ATS m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  �״����ä���༭��
\details  
\author JZH
\date 2013/5/27
*/
class RadarrobeEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(RadarrobeEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Radarrobe m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  ��·�༭��
\details  
\author JZH
\date 2013/6/3
*/
class CourseEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CourseEditPacket);
public:
	EDIT_TYPE m_edit_type;
	Course m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};

/*!
\brief  �������༭��
\details  
\author JZH
\date 2013/6/19
*/
class SensorEditPacket: public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(SensorEditPacket);
public:
	EDIT_TYPE m_edit_type;
	SurveillanceSensor m_data;
private:
	SERIALIZE_PACKET(m_edit_type & m_data);
};
#endif