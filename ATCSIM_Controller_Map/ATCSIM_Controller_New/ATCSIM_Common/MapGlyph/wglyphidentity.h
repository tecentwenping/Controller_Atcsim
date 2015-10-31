#ifndef _WGLYPHIDENTITY_H
#define _WGLYPHIDENTITY_H

#include <string>

//定义图元的类型，任何一种图元都必须有一种类型
//图层的枚举值决定了图层的高度
typedef enum euGlyphType
{
	GLYPH_NONE = -1,
	// [ 动目标层 ]
	GLYPH_AIRCRAFT,	 //航空器
	GLYPH_FRAME,	 //矩形框
	GLYPH_TELEMETER, //测距线
	GLYPH_VEHICLE,   //车辆
	// [ 动目标辅助层 ]
	GLYPH_LONGLAT,	//经纬度显示层
	GLYPH_TAXING,//地图简单操作动态滑行线
	GLYPH_DYNAMIC_ROUTE,//鼠标点击的飞行计划航路
	GLYPH_DRAG_AIRCRAFT,//稍后合并

	// [ 中间保留图层用于动态绘图 id: 10-100]
	GLYPH_RESERVE = 10,
	

	GLYPH_RUNWAY = 101,    //跑道
	GLYPH_NAVPOINT,  //导航台
	GLYPH_AIRNAVPOINT, //用于空中的导航台
	GLYPH_AIRLINE,   //航线
	GLYPH_ROUTE,     //飞行计划的航路
	GLYPH_LINKLINE,  //连接线
	GLYPH_TAXLINE,   //滑行线
	GLYPH_GATE,      //停机位
	GLYPH_CORRIDOR,  //空中走廊
	GLYPH_SECTOR,
	GLYPH_CONTROLLER,
	GLYPH_LANDFORM, //地形
	GLYPH_WEATHER_ENV_AREA, //气象环境区域
	GLYPH_MAINRING,		// 主距离环
	GLYPH_SECONDRING,	// 
	GLYPH_FROZEN,    //冻结框
	GLYPH_RING,      //距离环
	GLYPH_AZIMUTH,   //方位环
	GLYPH_SYSINFO,
	GLYPH_RESTRICTAREA, //禁区限制区
	GLYPH_MSAWAREA,     //最低引导扇区
	GLYPH_AIRSPACEROUTE,//空中航路
	GLYPH_CLOUD,
	GLYPH_BACKGROUND,// [ 背景层 ]

	GLYPH_END //!!! the end
}GlyphType;


//标识图元属性
class WGlyphIdentity
{
public:
	WGlyphIdentity(){};
	virtual ~WGlyphIdentity(){};
public:
	std::string strName;
	int  m_nLayerID;
	int  m_nTraceID;
};


//标识飞机图元
class WAcftGlyphIdentity:public WGlyphIdentity
{
public:
	WAcftGlyphIdentity(){};
	~WAcftGlyphIdentity(){};
public:
	int m_nSSR;
};


#endif