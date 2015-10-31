//���ļ��ж��帨����صĶ����࣬�������¶���

//��·��     RoutePt


#ifndef _H_ASSISTANCE_DATA_OBJS_H
#define _H_ASSISTANCE_DATA_OBJS_H
#include "DataObj.h"
#include <public/boost/boost/shared_ptr.hpp>
#include <public/boost/boost/make_shared.hpp>

/*----------------ͼԪ------------------- */
class GlyphPt : public DataObj
{
public:
	GlyphPt(void);
	~GlyphPt(void);

	int GetId();
	string GetDisplayLabel();

	//��������ֵ����
	GlyphPt(const GlyphPt &glyphPt);
	GlyphPt& operator=(const GlyphPt& glyphPt);

	//Set ����
	void SetGlyphPtID(int iGlyphID);
	void SetGlyphPtName(std::string strGlyphName);
	void SetPointType(int iType);
	void SetPointID(int iID);
	void SetProcessMode(int iProcessMode);
	void SetArcInfoID(int iDetailID);
	void SetLatitude(double dLatitude);
	void SetLongtitude(double dLongtitude);
	void SetHeight(double dHeight);

	//Get����
	int GetGlyphPtID();
	std::string GetGlyphPtName();
	int GetPointType();
	int GetPointID();
	double GetLongtitude();
	double GetLatitude();
	double GetHeight();
	int GetProcessMode();
	int GetArcInfoID();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iGlyphPtID & m_strGlyphPtName & m_iPointType & m_iPointID 
			& m_iProcessMode & m_iArcInfoID & m_dLatitude 
			& m_dLongtitude & m_dHeight;
	}

private:
	int m_iGlyphPtID;                /*ͼԪID*/
	std::string m_strGlyphPtName;    /*ͼԪ����*/ 
	int m_iPointType;				/*0-m_iPointIDΪ����̨ID��1-m_iPointIDΪ�̶���ID��2-����m_iPointID��ȡ��ʱ����Ϣ*/
	int m_iPointID;					/*m_iPointType����ʾ���͵��ID*/
	int m_iProcessMode;				/*0-��ʾ����ģʽ��1-���Ĵ���ģʽ*/
	int m_iArcInfoID;               /*ͼԪ��ϸ��ϢID*/
	double m_dLatitude;				/*��ʱ���γ��*/
	double m_dLongtitude;			/*��ʱ��ľ���*/
	double m_dHeight;				/*��ʱ��ĸ߶�*/
};

/*-------------ͼԪ��ϸ��Ϣ------------------- */
class GlyphPtArcInfo : public DataObj
{
public:
	GlyphPtArcInfo(void);
	~GlyphPtArcInfo(void);

	int GetId();
	string GetDisplayLabel();

	//��������ֵ����
	GlyphPtArcInfo(const GlyphPtArcInfo &glyphPtArcInfo);
	GlyphPtArcInfo& operator=(const GlyphPtArcInfo& glyphPtArcInfo);

	//Set ����
	void SetArcInfoID(int iArcInfoID);
	void SetTopLongitude(double dTopLongitude);
	void SetTopLatitude(double dTopLatitude);
	void SetBottomLongitude(double dBottomLongitude);
	void SetBottomLatitude(double dBottomLatitude);
	void SetStartAngle(double dStartAngle);
	void SetEndAngle(double dEndAngle);
	void SetRotateAngle(double dRotateAngle);

	//Get����
	int  GetArcInfoID();
	double GetTopLongitude();
	double GetTopLatitude();
	double GetBottomLongitude();
	double GetBottomLatitude();
	double GetStartAngle();
	double GetEndAngle();
	double GetRotateAngle();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iArcInfoID & m_dTopLongitude & m_dTopLatitude & m_dBottomLongitude 
			& m_dBottomLatitude & m_dStartAngle & m_dEndAngle 
			& m_dRotateAngle;
	}

private:
	int m_iArcInfoID;         /*ͼԪ��ϢID*/
	double m_dTopLongitude;		  /*���ϽǾ���*/
	double m_dTopLatitude;        /*���Ͻ�γ��*/
	double m_dBottomLongitude;    /*���½Ǿ���*/
	double m_dBottomLatitude;     /*���½�γ��*/
	double m_dStartAngle;         /*��ʼ����*/
	double m_dEndAngle;           /*��������*/
	double m_dRotateAngle;        /*��ת�Ƕ�*/
};


/*-------------�ռ�ͼԪ������------------------- */
class CylinderGlyph : public DataObj
{
public:
	CylinderGlyph(void);
	~CylinderGlyph(void);

	//��������ֵ����
	CylinderGlyph(const CylinderGlyph &cylinderGlyph);
	CylinderGlyph& operator=(const CylinderGlyph& cylinderGlyph);

	//Set ����
	void SetCylinderID(int iCylinderID);
	void SetGlyphPtID(int iGlyphPtID);
	void SetSequence(int iSequence);

	//Get����
	int GetCylinderID();
	int GetGlyphPtID();
	int GetSequence();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCylinderID & m_iGlyphPtID & m_iSequence;
	}

private:
	int m_iCylinderID;      /*����ID*/
	int m_iGlyphPtID;   /*����ͼԪID*/
	int m_iSequence;        /*���*/

};


/*----------------- ���� ------------------- */
class Cylinder : public DataObj
{
public:
	Cylinder(void);
	~Cylinder(void);

	int GetId();
	string GetDisplayLabel();

	//��������ֵ����
	Cylinder(const Cylinder &cylinder);
	Cylinder& operator=(const Cylinder& cylinder);

	//Set ����
	void SetCylinderID(int iCylinderID);
	void SetCylinderName(std::string strCylinderName);
	void SetBottomLevel(double dBottomLevel);
	void SetTopLevel(double dTopLevel);
	void SetOwnType(int iType);
	void SetOwnID(int iID);

	//Get����
	int GetCylinderID();
	std::string GetCylinderName();
	double GetBottomLevel();
	double GetTopLevel();
	int GetOwnType();
	int GetOwnID();

	//���л�����
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCylinderID & m_strCylinderName & m_dBottomLevel & m_dTopLevel & m_iOwnType & m_iOwnID;
	}

private:
	int m_iCylinderID;                 /*����ID*/
	std::string  m_strCylinderName;    /*��������*/ 
	double m_dBottomLevel;             /*�����½�*/
	double m_dTopLevel;                /*�����Ͻ�*/
	int m_iOwnType;
	int m_iOwnID;
};



enum ENUM_ROUTEPT_OWNER_TYPE
{
	ROUTEPT_OWNER_TYPE_NONE = 0,

	ROUTEPT_OWNER_TYPE_SID,        //�볡
	ROUTEPT_OWNER_TYPE_STAR,       //����
	ROUTEPT_OWNER_TYPE_MISS,       //����
	ROUTEPT_OWNER_TYPE_COURSE,     //��·
	ROUTEPT_OWNER_TYPE_FLYPLAN,    //���мƻ�
	ROUTEPT_OWNER_TYPE_ATS         //ATS
};

enum ENUM_ROUTEPT_TYPE
{
	ROUTEPT_TYPE_NONE = 0,

	//��ͨ��·��(��ͨ��·��Ҳ�п�������ʱ�㡢����̨��)
	ROUTEPT_TYPE_NORMAL_TEMP,         //��ʱ�㣬���ݿ���û�б��ŵ����Ϣ
	ROUTEPT_TYPE_NORMAL_BEACON,       //����̨�㣬 ����̨��

	//���⺽·��
	ROUTEPT_TYPE_SPECIAL_SID,          //�볡����
	ROUTEPT_TYPE_SPECIAL_STAR,         //��������
	ROUTEPT_TYPE_SPECIAL_MISS,         //���ɳ���
	ROUTEPT_TYPE_SPECIAL_ATS,          //ATS
	ROUTEPT_TYPE_SPECIAL_COURSE        //��·
};

//��̨����
enum ENUM_ROUTEPT_LEG_TYPE
{
	ROUTEPT_DIRECT_TO_FIX = 0,	//��̨		
	ROUTEPT_COURSE_TO_FIX,	//��̨
	ROUTEPT_RADIUS_TO_FIX,	//��Բ
	ROUTEPT_TRACK_TO_FIX	//�ɻ����лغ�·ѹ�߷ɵ�
};

// enum ENUM_ROUTEPT_TURN_MODE
// {
// 	ROUTEPT_TURN_MODE_NONE = 0,
// 	ROUTEPT_TURN_MODE_SPIRAL,
// };

enum ENUM_ROUTEPT_TURN_DIRECTION
{
	ROUTEPT_TURN_DIRECTION_NONE = 0,
	ROUTEPT_TURN_DIRECTION_LEFT,
	ROUTEPT_TURN_DIRECTION_RIGHT,
	ROUTEPT_TURN_DIRECTION_HOLD

};

class RoutePt : public DataObj
{
public:
	RoutePt();
	~RoutePt();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();
	void SetSequence(int iSeq);
	int GetSequence();

	//��������ֵ����
	RoutePt(const RoutePt &routePt);
	RoutePt& operator=(const RoutePt& routePt);

	//boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iID & m_eOwnerType & m_iOwnerID & m_iSequence 
			& m_iRoutePtID & m_strRoutePtName & m_eRoutePtType 
			& m_dLatitude & m_dLongtitude & m_dAltitude & m_eLegType 
			& m_dRadius & m_bClockWise & m_dGrade & m_bSpiralTurnMode 
			& m_eTurnDirt;
	}

public:
	//���ݿ�ʹ��
	int                      m_iID;               //Ψһ��ʶһ����¼ID��DB�ڲ�ʹ��
	ENUM_ROUTEPT_OWNER_TYPE  m_eOwnerType;        //��·��Owner���ͣ��ο�ENUM_ROUTEPT_OWNER_TYPE���壩
	int                      m_iOwnerID;          //��·��OwnerID���磺
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_NONEʱ��   ����m_iOwnerID��
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_SIDʱ��    m_iOwnerIDΪ�볡����ID
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_STARʱ��   m_iOwnerIDΪ���������ID
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_COURSEʱ�� m_iOwnerIDΪ��·��ID
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_ATSʱ��    m_iOwnerIDΪATA��ID
	//m_iOwnerType ����ROUTEPT_OWNER_TYPE_FLYPLANʱ��m_iOwnerIDΪ���мƻ�ID
	int                      m_iSequence;         //�ú�·����OwnerID�е�˳��


	//����ϯλʹ��
	ENUM_ROUTEPT_TYPE   	 m_eRoutePtType; 	  //��·�����ͣ��ο�ENUM_ROUTEPT_TYPE���壩
	int                      m_iRoutePtID;        //��·��ID
	/*ȡֵ����m_iRoutePtType��ֵ��ͬ����ͬ��
	ROUTEPT_TYPE_NORMAL_TEMP��          m_iRoutePtIDֵΪ<= 0
	ROUTEPT_TYPE_NORMAL_BEACON          m_iRoutePtIDΪ����̨����ĳһ����̨��ID
	ROUTEPT_TYPE_SPECIAL_SID            m_iRoutePtIDΪSID����ĳһSID��ID
	ROUTEPT_TYPE_SPECIAL_STAR           m_iRoutePtIDΪSTAR����ĳһSTAR��ID
	ROUTEPT_TYPE_SPECIAL_MISS           m_iRoutePtIDΪMISS����ĳһMISS��ID
	ROUTEPT_TYPE_SPECIAL_ATS            m_iRoutePtIDΪATS����ĳһATS��ID*/
	string                   m_strRoutePtName;    //��·�����ƣ�ȡֵ��Ӧ��m_iRoutePtID��ȡֵ����m_iRoutePtID <=0 ʱ��ȡֵΪ�գ�
	double		             m_dLatitude;          //�ɻ����ֵ�γ�ȣ���λ�����ȣ�
	double		             m_dLongtitude;	       //�ɻ����ֵľ��ȣ���λ�����ȣ�
	double		             m_dAltitude;	      //��̨�߶ȣ���׼��ѹ�߶ȣ���λ���ף���ע�⣺����Ǳ�׼���볡����A/B/CD�͵ķɻ���̨�߶Ȳ�ͬ��(ATS�����ɳ���û�й�̨�߶�)
	ENUM_ROUTEPT_LEG_TYPE	 m_eLegType;	      //��̨����
	double		             m_dRadius;	          //�ɻ��뾶����̨����ΪRADIUS_TO_FIXʱ��Ч����λ���ף�
	bool		             m_bClockWise;	      //�ɻ����򣨹�̨����ΪRADIUS_TO_FIXʱ��Ч��

	//����Ϊ��׼�볡����SID����
	double		                 m_dGrade;		//�¶�
	bool						m_bSpiralTurnMode;	//ת��ģʽ(�Ƿ���������)
	ENUM_ROUTEPT_TURN_DIRECTION  m_eTurnDirt; 	//ת�䷽��


	//��׼��������STAR����


	//���ɳ���MISS����



};




#endif   //_H_ASSISTANCE_DATA_OBJS_H