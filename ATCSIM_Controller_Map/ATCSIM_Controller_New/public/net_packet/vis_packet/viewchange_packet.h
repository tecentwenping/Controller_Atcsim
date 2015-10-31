#pragma once
#include "serial_base.h"
#include "public/site_info.h"
#include "Serialization/wserialize.h"

class ViewChangePacket :public CSerial_Base
{
	PKT_DECLARE_DYNCREATE(ViewChangePacket);
public:
	int m_iMovingObjID;
	double m_dX;
	double m_dY;
	double m_dZ;
	double m_dH;
	double m_dP;
	double m_dR;
private:
	SERIALIZE_PACKET(m_iMovingObjID & m_dX & m_dY & m_dZ & m_dH & m_dP & m_dR);
};