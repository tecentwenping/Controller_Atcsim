#ifndef _WNDSTYPE_H
#define _WNDSTYPE_H

//���ļ���Ҫ�������崰�ڵ�����
//���ڵ���������������ʶ�𴰿ڵı�ʶ
typedef enum euWndsType
{
	WND_ALL     = 0,   //���д���
	WND_MAINMAP,
	WND_CHILDMAP,
	WND_STRIP,
	WND_SETUP,
	WND_INFO,
	WND_QNH,
	WND_STCA,
	WND_DAIW,
	WND_MSAW,
	WND_MIL,
	WND_RWY,
	WND_RAM,
	WND_CLAM,
	WND_SHOT_POINT,
	WND_RVSM_AREA,

	//////////////////////////////////////////////////////////////////////////
	//begin ����Աϯλ����
	CONTROLLER_TOPWND,
	CONTROLLER_BOTTOMWND,
	SETTINGWND,
	FPLLISTWND,  
	MAPSETTINGWND,
	FPLWND,
	HOLDWND,
	GATEQUERYWND,
    WAITLISTWND,
	SECTORALLOCATEWND,
	HOLDSETTINGWND,
	ALARMWND,
	SYSTEMINFOWND,
	LABELRIGHTMENU, // �����Ҽ��˵�
	LABELDATAEDIT,  // ���������ı��༭
	CFLSETTINGWND,  // �Ҽ�CFL���ô���
    WND_RADTAG, //Rad Tag Wnd    
	WND_TAGLIST, // Tag List Wnd
    SECTORFILTERWND,//�������˴���	
	STRIPCONFIGRATIONSETUPWND,
	WND_SECTOR, // ����ѡ�񴰿�
	ALARMSOUNDWND, //�澯�������ô���
	WND_COASTLIST, //ä���б�
	WND_CONNECT,   //��������״̬����
	//end
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//begin ����ϯλ����
	PILOT_BOTTOMWND,
	PILOT_TOPWND,
	PILOT_CMDPANEL,
	PILOT_MAP_CMDWND,
	PILOT_INFO_CMDWND,
	PILOT_MAP_RESPONSEWND,
	PILOT_INFO_RESPONSEWND,
	PILOT_CURAIRCRAFTINFOWND,
	PILOT_CURVEHICLEINFOWND,
	PILOT_FPLLISTWND,
	PILOT_VEHICLELISTWND,
	PILOT_QUREYRESULTWND,
	PILOT_REPORTWND,
	PILOT_REPROTACKWND,
	PILOT_MOUSECMDWND,
	DEFINE_CMD,
	HOLDLIST,
	CANCELEDLIST,
	VEHICLELIST,
	HISTORYCMDWND,
	STRIPBAYWND,
	PILOTMAPWND,
	PILOTINFOWND,
	STATUSWND,
	PILOT_SECTORFILTERWND,
	PILOT_LABELFORMATSETWND,
	PILOT_MAILREPORT,
	PILOT_TITLE,
	PILOT_COLORSETTINGWND,
	PILOT_EXIT,
	PILOT_TAXWND,
	//end 
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//begin ��Աϯλ����
	SUPERVISOR_TOPWND,
	SUPERVISOR_BOTTOMWND,
	SUPERVISOR_EXERCISECTRLWND,
	SUPERVISOR_MAPSETTINGWND,
	SUPERVISOR_FPLLISTWND,
	SUPERVISOR_FPLWND,
	SUPERVISOR_GATEASSIGNWND,
	SUPERVISOR_LIGHTCTRL,
	SUPERVISOR_TIMEMODIFYWND,
	SUPERVISOR_WEATHERINFOWND,
	SUPERVISOR_ATCSETTINGWND,
	SUPERVISOR_MAILSENDWND,
	SUPERVISOR_ASSISTWND,
	//end 
	//////////////////////////////////////////////////////////////////////////

	WND_CMDWND,
	WND_SECONDMAP,
	WND_COLOR,
	WND_COLOR_SETTINGS,
	WND_SYS_SETTINGS,
	WND_FLYPLAN,
	WND_GLYPH_CREATOR,
	WND_ILS,
	WND_MAIL,
	WND_ENVCTRL,
	WND_AIRPORTENV,
	WND_RUNWAYENV,
	WND_VIEW,
	WND_EFFECT,
	WND_CLOUD,
	WND_MOTIONALSUBWND,
	WND_RADARSETTINGWND,
	WND_TLSETTING,
	WND_CREATEPLANE,
	WND_END
}WndsType;


//���崰�ڵĲ��ַ�ʽ����ʱ��������ģʽ
//����Ա 
//����
//��Ա
typedef enum euLayoutType
{
	LAYOUT_SUPERVISOR,
	LAYOUT_PILOT,
	LAYOUT_CONTROLLER,
}LayoutType;


#endif