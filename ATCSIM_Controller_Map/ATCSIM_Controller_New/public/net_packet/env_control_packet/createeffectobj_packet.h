#pragma once
#include "serial_base.h"
#include "public/site_info.h"
#include "Serialization/wserialize.h"
#include "public/BaseTypeDefine/PublicTypeDefine.h"

struct ST_3GPOINT
{
	double m_dX;
	double m_dY;
	double m_dZ;

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_dX & m_dY & m_dZ;
	}
};

class CreateEffectObjPacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(CreateEffectObjPacket);
public:
	int                      m_iObjID;       //������ЧID
	std::string              m_sObjName;     //���������֣�
	ENUM_OBJ_TYPE            m_eAnimalType;  //�������ͣ�
	std::vector<ST_3GPOINT>  m_vPoint;        //�����˶�����
	ST_3GPOINT               m_startPoint;    // �����ʼλ��  
	bool                     m_bCreate;       //trueΪ������ falseΪɾ��
private:
	SERIALIZE_PACKET(m_iObjID & m_sObjName & m_eAnimalType & m_vPoint & m_startPoint & m_bCreate);
};