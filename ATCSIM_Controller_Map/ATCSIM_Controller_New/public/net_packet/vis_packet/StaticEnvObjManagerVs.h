//// by  wmq 2010.3.5  ������

#ifndef _STATIC_ENV_OBJ_MANAGER_PACKETVS_H_
#define _STATIC_ENV_OBJ_MANAGER_PACKETVS_H_

#include "Serial_Base.h"
#include "public\BaseTypeDefine\EnvTypeDefine/EnvStruct.h"
#include "public\TowerTime\TowerTime.h"

#pragma warning(disable:4786)

class StaticEnvObjManagerPacketVs : public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(StaticEnvObjManagerPacketVs);
public: 	
	StaticEnvObjManagerPacketVs ();
	ENV_OBJ_TYPE	m_eObjType;		//����
	int    m_eCloudType;//������
	int                        m_iLevel;
	int						m_ObjID; 
	bool						m_bIsDelete;					//�Ƿ�ɾ��
	double					m_dPosX;						//λ��
	double					m_dPosY;
	double					m_dPosZ;
	double					m_dSize;						//���ڷ�����Ĵ�С��Χ��Ϣ
	double					m_dLength;                //ֻ����ʩ�����򣬱�ʾ����
	double					m_dWidth;                 //ֻ����ʩ�����򣬱�ʾ���
	double                 m_dHeading;             //ֻ����ʩ�����򣬱�ʾ����
private:
	SERIALIZE_PACKET(m_eObjType & m_eCloudType & m_iLevel &m_ObjID & m_bIsDelete & m_dPosX & m_dPosY
		& m_dPosZ & m_dSize & m_dLength & m_dWidth &m_dHeading);
};


#endif
