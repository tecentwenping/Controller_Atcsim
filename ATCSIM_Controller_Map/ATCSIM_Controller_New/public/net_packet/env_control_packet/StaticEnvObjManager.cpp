#include "StaticEnvObjManager.h"
PKT_IMPLEMENT_DYNCREATE(StaticEnvObjManagerPacket);

StaticEnvObjManagerPacket::StaticEnvObjManagerPacket()
{
	m_eObjType=NONETYPE;
	m_eCloudType=0;
	m_iLevel=0;
	m_ObjID=0;
	m_bIsDelete=false;
	m_dPosX=0.0;
	m_dPosY=0.0;
	m_dPosZ=0.0;
	m_dSize=0.0;
	m_dLength=0.0;
	m_dWidth=0.0;
	m_dHeading=0.0;
}
