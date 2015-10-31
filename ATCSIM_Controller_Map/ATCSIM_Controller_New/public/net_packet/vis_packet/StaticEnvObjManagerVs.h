//// by  wmq 2010.3.5  环境包

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
	ENV_OBJ_TYPE	m_eObjType;		//类型
	int    m_eCloudType;//云类型
	int                        m_iLevel;
	int						m_ObjID; 
	bool						m_bIsDelete;					//是否删除
	double					m_dPosX;						//位置
	double					m_dPosY;
	double					m_dPosZ;
	double					m_dSize;						//用于辐射雾的大小范围信息
	double					m_dLength;                //只适用施工区域，表示长度
	double					m_dWidth;                 //只适用施工区域，表示宽度
	double                 m_dHeading;             //只适用施工区域，表示朝向
private:
	SERIALIZE_PACKET(m_eObjType & m_eCloudType & m_iLevel &m_ObjID & m_bIsDelete & m_dPosX & m_dPosY
		& m_dPosZ & m_dSize & m_dLength & m_dWidth &m_dHeading);
};


#endif
