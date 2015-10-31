//此文件中定义辅助相关的对象类，包括以下对象：

//航路点     RoutePt


#ifndef _H_ASSISTANCE_DATA_OBJS_H
#define _H_ASSISTANCE_DATA_OBJS_H
#include "DataObj.h"
#include <public/boost/boost/shared_ptr.hpp>
#include <public/boost/boost/make_shared.hpp>

/*----------------图元------------------- */
class GlyphPt : public DataObj
{
public:
	GlyphPt(void);
	~GlyphPt(void);

	int GetId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	GlyphPt(const GlyphPt &glyphPt);
	GlyphPt& operator=(const GlyphPt& glyphPt);

	//Set 方法
	void SetGlyphPtID(int iGlyphID);
	void SetGlyphPtName(std::string strGlyphName);
	void SetPointType(int iType);
	void SetPointID(int iID);
	void SetProcessMode(int iProcessMode);
	void SetArcInfoID(int iDetailID);
	void SetLatitude(double dLatitude);
	void SetLongtitude(double dLongtitude);
	void SetHeight(double dHeight);

	//Get方法
	int GetGlyphPtID();
	std::string GetGlyphPtName();
	int GetPointType();
	int GetPointID();
	double GetLongtitude();
	double GetLatitude();
	double GetHeight();
	int GetProcessMode();
	int GetArcInfoID();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iGlyphPtID & m_strGlyphPtName & m_iPointType & m_iPointID 
			& m_iProcessMode & m_iArcInfoID & m_dLatitude 
			& m_dLongtitude & m_dHeight;
	}

private:
	int m_iGlyphPtID;                /*图元ID*/
	std::string m_strGlyphPtName;    /*图元名称*/ 
	int m_iPointType;				/*0-m_iPointID为导航台ID；1-m_iPointID为固定点ID；2-忽略m_iPointID，取临时点信息*/
	int m_iPointID;					/*m_iPointType所表示类型点的ID*/
	int m_iProcessMode;				/*0-显示处理模式；1-核心处理模式*/
	int m_iArcInfoID;               /*图元详细信息ID*/
	double m_dLatitude;				/*临时点的纬度*/
	double m_dLongtitude;			/*临时点的经度*/
	double m_dHeight;				/*临时点的高度*/
};

/*-------------图元详细信息------------------- */
class GlyphPtArcInfo : public DataObj
{
public:
	GlyphPtArcInfo(void);
	~GlyphPtArcInfo(void);

	int GetId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	GlyphPtArcInfo(const GlyphPtArcInfo &glyphPtArcInfo);
	GlyphPtArcInfo& operator=(const GlyphPtArcInfo& glyphPtArcInfo);

	//Set 方法
	void SetArcInfoID(int iArcInfoID);
	void SetTopLongitude(double dTopLongitude);
	void SetTopLatitude(double dTopLatitude);
	void SetBottomLongitude(double dBottomLongitude);
	void SetBottomLatitude(double dBottomLatitude);
	void SetStartAngle(double dStartAngle);
	void SetEndAngle(double dEndAngle);
	void SetRotateAngle(double dRotateAngle);

	//Get方法
	int  GetArcInfoID();
	double GetTopLongitude();
	double GetTopLatitude();
	double GetBottomLongitude();
	double GetBottomLatitude();
	double GetStartAngle();
	double GetEndAngle();
	double GetRotateAngle();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iArcInfoID & m_dTopLongitude & m_dTopLatitude & m_dBottomLongitude 
			& m_dBottomLatitude & m_dStartAngle & m_dEndAngle 
			& m_dRotateAngle;
	}

private:
	int m_iArcInfoID;         /*图元信息ID*/
	double m_dTopLongitude;		  /*左上角经度*/
	double m_dTopLatitude;        /*左上角纬度*/
	double m_dBottomLongitude;    /*右下角经度*/
	double m_dBottomLatitude;     /*右下角纬度*/
	double m_dStartAngle;         /*开始弧度*/
	double m_dEndAngle;           /*结束弧度*/
	double m_dRotateAngle;        /*旋转角度*/
};


/*-------------空间图元关联表------------------- */
class CylinderGlyph : public DataObj
{
public:
	CylinderGlyph(void);
	~CylinderGlyph(void);

	//拷贝、赋值函数
	CylinderGlyph(const CylinderGlyph &cylinderGlyph);
	CylinderGlyph& operator=(const CylinderGlyph& cylinderGlyph);

	//Set 方法
	void SetCylinderID(int iCylinderID);
	void SetGlyphPtID(int iGlyphPtID);
	void SetSequence(int iSequence);

	//Get方法
	int GetCylinderID();
	int GetGlyphPtID();
	int GetSequence();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCylinderID & m_iGlyphPtID & m_iSequence;
	}

private:
	int m_iCylinderID;      /*柱面ID*/
	int m_iGlyphPtID;   /*扇区图元ID*/
	int m_iSequence;        /*序号*/

};


/*----------------- 柱面 ------------------- */
class Cylinder : public DataObj
{
public:
	Cylinder(void);
	~Cylinder(void);

	int GetId();
	string GetDisplayLabel();

	//拷贝、赋值函数
	Cylinder(const Cylinder &cylinder);
	Cylinder& operator=(const Cylinder& cylinder);

	//Set 方法
	void SetCylinderID(int iCylinderID);
	void SetCylinderName(std::string strCylinderName);
	void SetBottomLevel(double dBottomLevel);
	void SetTopLevel(double dTopLevel);
	void SetOwnType(int iType);
	void SetOwnID(int iID);

	//Get方法
	int GetCylinderID();
	std::string GetCylinderName();
	double GetBottomLevel();
	double GetTopLevel();
	int GetOwnType();
	int GetOwnID();

	//序列化方法
	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCylinderID & m_strCylinderName & m_dBottomLevel & m_dTopLevel & m_iOwnType & m_iOwnID;
	}

private:
	int m_iCylinderID;                 /*柱面ID*/
	std::string  m_strCylinderName;    /*柱面名称*/ 
	double m_dBottomLevel;             /*柱面下界*/
	double m_dTopLevel;                /*柱面上界*/
	int m_iOwnType;
	int m_iOwnID;
};



enum ENUM_ROUTEPT_OWNER_TYPE
{
	ROUTEPT_OWNER_TYPE_NONE = 0,

	ROUTEPT_OWNER_TYPE_SID,        //离场
	ROUTEPT_OWNER_TYPE_STAR,       //进场
	ROUTEPT_OWNER_TYPE_MISS,       //复飞
	ROUTEPT_OWNER_TYPE_COURSE,     //航路
	ROUTEPT_OWNER_TYPE_FLYPLAN,    //飞行计划
	ROUTEPT_OWNER_TYPE_ATS         //ATS
};

enum ENUM_ROUTEPT_TYPE
{
	ROUTEPT_TYPE_NONE = 0,

	//普通航路点(普通航路点也有可能是临时点、导航台点)
	ROUTEPT_TYPE_NORMAL_TEMP,         //临时点，数据库中没有表存放点的信息
	ROUTEPT_TYPE_NORMAL_BEACON,       //导航台点， 导航台表

	//特殊航路点
	ROUTEPT_TYPE_SPECIAL_SID,          //离场程序
	ROUTEPT_TYPE_SPECIAL_STAR,         //进场程序
	ROUTEPT_TYPE_SPECIAL_MISS,         //复飞程序
	ROUTEPT_TYPE_SPECIAL_ATS,          //ATS
	ROUTEPT_TYPE_SPECIAL_COURSE        //航路
};

//过台类型
enum ENUM_ROUTEPT_LEG_TYPE
{
	ROUTEPT_DIRECT_TO_FIX = 0,	//过台		
	ROUTEPT_COURSE_TO_FIX,	//切台
	ROUTEPT_RADIUS_TO_FIX,	//飞圆
	ROUTEPT_TRACK_TO_FIX	//飞弧后切回航路压线飞点
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

	//拷贝、赋值函数
	RoutePt(const RoutePt &routePt);
	RoutePt& operator=(const RoutePt& routePt);

	//boost序列化
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
	//数据库使用
	int                      m_iID;               //唯一标识一条记录ID，DB内部使用
	ENUM_ROUTEPT_OWNER_TYPE  m_eOwnerType;        //航路点Owner类型（参考ENUM_ROUTEPT_OWNER_TYPE定义）
	int                      m_iOwnerID;          //航路点OwnerID，如：
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_NONE时，   忽略m_iOwnerID。
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_SID时，    m_iOwnerID为离场程序ID
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_STAR时，   m_iOwnerID为进场程序的ID
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_COURSE时， m_iOwnerID为航路的ID
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_ATS时，    m_iOwnerID为ATA的ID
	//m_iOwnerType 等于ROUTEPT_OWNER_TYPE_FLYPLAN时，m_iOwnerID为飞行计划ID
	int                      m_iSequence;         //该航路点在OwnerID中的顺序


	//其他席位使用
	ENUM_ROUTEPT_TYPE   	 m_eRoutePtType; 	  //航路点类型（参考ENUM_ROUTEPT_TYPE定义）
	int                      m_iRoutePtID;        //航路点ID
	/*取值依据m_iRoutePtType的值不同而不同：
	ROUTEPT_TYPE_NORMAL_TEMP，          m_iRoutePtID值为<= 0
	ROUTEPT_TYPE_NORMAL_BEACON          m_iRoutePtID为导航台表中某一导航台的ID
	ROUTEPT_TYPE_SPECIAL_SID            m_iRoutePtID为SID表中某一SID的ID
	ROUTEPT_TYPE_SPECIAL_STAR           m_iRoutePtID为STAR表中某一STAR的ID
	ROUTEPT_TYPE_SPECIAL_MISS           m_iRoutePtID为MISS表中某一MISS的ID
	ROUTEPT_TYPE_SPECIAL_ATS            m_iRoutePtID为ATS表中某一ATS的ID*/
	string                   m_strRoutePtName;    //航路点名称（取值对应于m_iRoutePtID的取值，当m_iRoutePtID <=0 时，取值为空）
	double		             m_dLatitude;          //飞机出现的纬度（单位：弧度）
	double		             m_dLongtitude;	       //飞机出现的经度（单位：弧度）
	double		             m_dAltitude;	      //过台高度（标准海压高度，单位：米）（注意：如果是标准进离场程序，A/B/CD型的飞机过台高度不同）(ATS，复飞程序没有过台高度)
	ENUM_ROUTEPT_LEG_TYPE	 m_eLegType;	      //过台类型
	double		             m_dRadius;	          //飞弧半径（过台类型为RADIUS_TO_FIX时有效，单位：米）
	bool		             m_bClockWise;	      //飞弧方向（过台类型为RADIUS_TO_FIX时有效）

	//以下为标准离场程序SID特有
	double		                 m_dGrade;		//坡度
	bool						m_bSpiralTurnMode;	//转弯模式(是否盘旋上升)
	ENUM_ROUTEPT_TURN_DIRECTION  m_eTurnDirt; 	//转弯方向


	//标准进场程序STAR特有


	//复飞程序MISS特有



};




#endif   //_H_ASSISTANCE_DATA_OBJS_H