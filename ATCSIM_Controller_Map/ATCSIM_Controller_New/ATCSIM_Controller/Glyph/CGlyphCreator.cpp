#include "CGlyphCreator.h"
#include "airspace_data_objs.h"
#include "airport_data_objs.h"
#include "wrunwayglyph.h"
#include "wunclosedlineglyph.h"
#include "wnavpointglyph.h"
#include "wgateglyph.h"
#include "getdatafromdb.h"
#include "coordinate.h"
#include "totalbasedata.h"
#include "wpainter.h"
#include "wqtpainter.h"
#include "WndsManager.h"
#include "CSimMap.h"
#include "CMapView.h"
#include "wlonglatglyph.h"
#include "wcontrlareaglyph.h"
#include "wworldpoint.h"
#include "AircraftTrace.h"
#include "waircraftglyph.h"
#include "wlabelformat.h"
#include "CLabelManager.h"
#include "wfontmetrics.h"
#include "wtelemeterglyph.h"
#include "AircraftInfo.h"
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include "wglyphidentity.h "
#include "CGlyphManager.h"
#include "WSysInfoGlyph.h"
#include "MainApp.h"
#include "DataOperator/ControllerGetAirPortData.h"
#include <boost/foreach.hpp>
#include <math.h>

#include <QThread>

//////////////////////////////////////////////////////////////////////////
#include "Manager/DataManager.h"
#include "DataOperator/TotalAircraftTrace.h"
#include "Wnds/CSimMap.h"
#include "Manager/MapManager.h"
#define towstring boost::lexical_cast<std::wstring>
boost::shared_mutex g_sm;//互斥对象

static const std::wstring PLUS_2(L"++");
static const std::wstring PLUS_3(L"+++");

static const std::wstring ARRAY_LEFT(1, 0x2190);
static const std::wstring ARRAY_UP(1, 0x2191);
static const std::wstring ARRAY_RIGHT(1, 0x2192);
static const std::wstring ARRAY_DOWN(1, 0x2193);
static const WSizeF EMPTY_SIZE;
static const std::wstring EMPTY_WSTR;

static const WColor BLACK(0, 0, 0);
static const WColor RED(255, 0, 0);
static const WColor YELLOW(255, 255, 0);
static const WColor DEFCOLOR(0, 255, 255);
static const WColor WHITE(255,255,255);
static const size_t MAX_CHARS = 10;

CGlyphCreator::CGlyphCreator()
{
	
}

CGlyphCreator::CGlyphCreator( GlyphManagerPtr pGlyphManager,CoordinatePtr pCoordinate,SimMapPtr pSimMap )
:m_pGlyphManager(pGlyphManager)
,m_pCoordinate(pCoordinate)
,m_pSimMap(pSimMap)
{
	m_pDataBase			= NULL;
	m_pGetDataFromDB	= NULL;
	m_pGetDataFromDB = new GetDataFromDB;
	m_pDataBase = new TotalBaseData;
    m_pCurTraces = NULL;
}

CGlyphCreator::~CGlyphCreator()
{
	if(m_pGetDataFromDB != NULL)
	{
		delete m_pGetDataFromDB;
		m_pGetDataFromDB = NULL;
	}
	if(!m_hmTraces.empty())
	{
		ClearTraces();
	}
}

void CGlyphCreator::InitAirspaceGlyph()
{
    
}

void CGlyphCreator::InitMapGlyph()
{
	//获取机场数据
  GetBaseDataFromDB();
  //画机场
  InitCoordinate();
  InitRunwayGlyph();
  InitTaxinglineGlyph();
  InitFixpointGlyph();
  InitGateGlyph();
  InitSysInfoGlyph();
  //初始化空域
  InitNAVPointGlyph();
  InitSectorGlyph();
  InitRestricAreaGlyph();//禁区限制区
  //InitRouteGlyph();//空中航路
  InitMsawAreaGlyph();//最低引导扇区

}
void CGlyphCreator::InitCoordinate()
{

	double dCenterX =  m_pDataBase->GetAirportData().GetCenterPointLongitude();
	double dCenterY = m_pDataBase->GetAirportData().GetCenterPointLatitude();
	if(m_pCoordinate)
	{
		m_pCoordinate->SetCenterPos(dCenterX,dCenterY);
	}
	//AddLongLatInfo()
}

void CGlyphCreator::InitRunwayGlyph()
{
	std::vector<RunwayData> vRunwayData;
	vRunwayData=m_pDataBase->GetRunwayDataVec();
	std::vector<RunwayData>::iterator Iter=vRunwayData.begin();
	WGlyphIdentity glyphIdentity;
	for(;Iter!= vRunwayData.end();++Iter)
	{
		RunwayData rd=*Iter;
		WRunwayGlyph* runwayGlyph=new WRunwayGlyph;
		WRunwayItemData& d=*runwayGlyph->data();
		d.m_line.setLine(rd.GetStartX(),rd.GetStartY(),rd.GetEndX(),rd.GetEndY());
		d.m_angle=rd.GetHeading();
		d.m_size.setWidth(rd.GetWidth());
		d.m_size.setHeight(rd.GetHeight());
		glyphIdentity.m_nLayerID=0;
		glyphIdentity.strName=rd.GetRunwayName();
		m_pGlyphManager->AddGlyph(GLYPH_RUNWAY,glyphIdentity,runwayGlyph);
		m_pSimMap->AddItemToMapScene(runwayGlyph,GLYPH_RUNWAY);
	}
}
void CGlyphCreator::InitTaxinglineGlyph()
{
	std::vector<RoadData> vRoadData;
	vRoadData = m_pDataBase->GetRoadDataVec();
	std::vector<RoadData>::iterator Iter = vRoadData.begin();
	for(;  Iter != vRoadData.end(); ++ Iter)
	{
		WUnclosedLineGlyph* TaxGlyph = new WUnclosedLineGlyph;
		WUnclosedLineItemData* pData = TaxGlyph->data();
		std::vector<WPointF> vPoints;
		vPoints.clear();
		WPointF point;
		WGlyphIdentity pIdentity;
		std::vector<boost::shared_ptr<RoadFixpointData> >::iterator IterRoadPoint=Iter->GetFixpoints().begin();
		for(; IterRoadPoint != Iter->GetFixpoints().end(); ++ IterRoadPoint)
		{
			FixpointData fixpointdata;
			bool bFind = m_pDataBase->FindFixpointData((*IterRoadPoint)->GetFixpointID(),fixpointdata);
			if(bFind)
			{
				point.setXY(fixpointdata.GetX(),fixpointdata.GetY());
				vPoints.push_back(point);
			}
		}
		pData->polyline = vPoints;
		pIdentity.m_nLayerID = 0;
		pIdentity.strName = Iter->GetRoadName();
		pData->m_sName = Iter->GetRoadName();
		m_pGlyphManager->AddGlyph(GLYPH_TAXLINE,pIdentity,TaxGlyph);
		m_pSimMap->AddItemToMapScene(TaxGlyph,GLYPH_TAXLINE);
	}
}

void CGlyphCreator::InitFixpointGlyph()
{
	std::vector<FixpointData> vFixpointData;
	vFixpointData = m_pDataBase->GetFixpointDataVec();
	std::vector<FixpointData>::iterator iter=vFixpointData.begin();
	WGlyphIdentity pIdentity;
	for(; iter != vFixpointData.end(); ++iter)
	{
		WNavPointGlyph *pNavPointGlyph = new WNavPointGlyph;
		WNavPointItemData* npd = pNavPointGlyph->data();

		npd->m_pos = WPointF(iter->GetX(), iter->GetY());
		npd->m_text = iter->GetFixpointName();
		npd->m_navType = 0;

		pIdentity.m_nLayerID = 0;
		pIdentity.strName = iter->GetFixpointName();
			m_pGlyphManager->AddGlyph(GLYPH_NAVPOINT,pIdentity,pNavPointGlyph);
		m_pSimMap->AddItemToMapScene(pNavPointGlyph, GLYPH_NAVPOINT);
	}
}

void CGlyphCreator::InitGateGlyph()
{
	std::vector<GateData> vGateData;
	vGateData = m_pDataBase->GetGateDataVec();
	std::vector<GateData>::iterator iter = vGateData.begin();
	WGlyphIdentity pIdentity;
	for(; iter != vGateData.end(); ++iter)
	{
		WGateGlyph* pGateGlyph = new WGateGlyph;
		pGateGlyph->setSelectable(false);
		WGateItemData* ndata = pGateGlyph->data();
		std::vector<GateItemData> vGateItemData;

		std::vector<WPointF> vPoints;
		vPoints.clear();
		WPointF point;
		GateItemData itemData;

		RoadData roadData;
		bool bFindRoad = m_pDataBase->FindRoadData(iter->GetRoadID(), roadData);
		if(bFindRoad)
		{
			std::vector<boost::shared_ptr<RoadFixpointData> >::iterator iterRoadPoint = roadData.GetFixpoints().begin();
			for(; iterRoadPoint != roadData.GetFixpoints().end(); ++iterRoadPoint)
			{
				FixpointData fixpointdata;
				bool bFindPoint = m_pDataBase->FindFixpointData((*iterRoadPoint)->GetFixpointID(),fixpointdata);
				if(bFindPoint)
				{
					itemData.m_name = fixpointdata.GetFixpointName();
					itemData.m_navType = fixpointdata.GetFixpointType();
					vGateItemData.push_back(itemData);
					point.setXY(fixpointdata.GetX(),fixpointdata.GetY());
					vPoints.push_back(point);

				}
			}
			ndata->polyline = vPoints;
			ndata->m_vItemDatas = vGateItemData;
			pIdentity.m_nLayerID = 0;
			pIdentity.strName = iter->GetGateName();
			m_pGlyphManager->AddGlyph(GLYPH_GATE, pIdentity, pGateGlyph);
			m_pSimMap->AddItemToMapScene(pGateGlyph, GLYPH_GATE);
		}
	}


}

void CGlyphCreator::GetBaseDataFromDB()
{

	//从数据库查询数据，存放在对象m_pDataBase的空间中
	m_pGetDataFromDB->QueryDataFromDB();
	m_pDataBase = m_pGetDataFromDB->GetTotalBaseData();
	//m_pDataBase = theApp::instance().GetControllerAirportDataPtr().get()->GetAirPortData();

}

void CGlyphCreator::UpdateMouseCoordinate( double x, double y )
{
	double dLongitude = 0.00;
	double dLatitude = 0.00;
	WWorldPointF point = m_pSimMap->GetMainMapView()->mapToScene(WWorldPointF(x,y));
	m_pCoordinate->ConvertXY2LongLat(point.x(),point.y(),dLongitude,dLatitude);

	WSysInfoGlyph* pGlyph = NULL;
	m_pGlyphManager->GetGlyph(GLYPH_SYSINFO,"SysInfo",&pGlyph);
	if(pGlyph)
	{
		WSysInfoItemData &d = *(pGlyph->data());
		char szTemp[100]={0};
		sprintf_s(szTemp,"Longitude:%.16f",dLongitude);
		d.m_strLongitude = szTemp;
		sprintf_s(szTemp,"Latitude: %.16f",dLatitude);
		d.m_strLatitude = szTemp;
	}
}

void CGlyphCreator::AddLongLatInfo( const WWorldPointF& pointF )
{
	double dLongitude,dLatitude;
	int iLongDegree,iLongCent,iLongSec,iLatDegree,iLatCent,iLatSec;
	WWorldPointF point = m_pSimMap->GetMainMapView()->mapToScene(pointF);
	m_pCoordinate->ConvertXY2LongLat(point.x(),point.y(),dLongitude,dLatitude);
	dLongitude *= (180/M_PI);
	dLatitude *= (180/M_PI);
	iLongDegree = (int)dLongitude;
	iLongCent = (int)(((double)(dLongitude-iLongDegree))*60);
	iLongSec=(int)(((((double)(dLongitude-iLongDegree))*60)-iLongCent)*60);
	iLatDegree=(int)dLatitude;
	iLatCent=(int)(((double)(dLatitude-iLatDegree))*60);
	iLatSec=(int)(((((double)(dLatitude-iLatDegree))*60)-iLatCent)*60);

	QString str = QString("%1%2%3N %4%5%6E").arg(iLatDegree, 2, 10, QLatin1Char('0')).arg\
		(iLatCent, 2, 10, QLatin1Char('0')).arg(iLatSec, 2, 10, QLatin1Char('0')).arg\
		(iLongDegree, 3, 10, QLatin1Char('0')).arg(iLongCent, 2, 10, QLatin1Char('0')).arg\
		(iLongSec, 2, 10, QLatin1Char('0'));

	WLongLatGlyph* longlatGlyph = new WLongLatGlyph;
	WLongLatItemData& d = *longlatGlyph->data();
	d.m_strText = str.toStdString();
	d.m_point = point;

	std::vector<WLongLatGlyph*> vTmpGlyph;
	m_pGlyphManager->GetGlyph(GLYPH_LONGLAT, vTmpGlyph);
	d.m_index = vTmpGlyph.size();

	if (vTmpGlyph.size() >= g_max_longlat_num)
	{
		d.m_index = g_max_longlat_num -1;
		BOOST_FOREACH(WLongLatGlyph *pGlyph, vTmpGlyph)
		{
			if (pGlyph->data()->m_index == 0)
			{
				m_pGlyphManager->RemoveGlyph(GLYPH_LONGLAT,pGlyph);
				m_pSimMap->RemoveItemFromMapScene(pGlyph, GLYPH_LONGLAT);
			}
			else
			{
				pGlyph->data()->m_index -= 1;
			}
		}
	}
	m_pGlyphManager->AddGlyph(GLYPH_LONGLAT, longlatGlyph);
	m_pSimMap->AddItemToMapScene(longlatGlyph, GLYPH_LONGLAT);


   
}

void CGlyphCreator::DeleteLonLatInfo( const WWorldPointF& pointF )
{

}

void CGlyphCreator::DeleteAllLongLatInfos()
{

}

void CGlyphCreator::InitSysInfoGlyph()
{
 WSysInfoGlyph *pGlyph = new WSysInfoGlyph;
 m_pSimMap->AddItemToMapScene(pGlyph,GLYPH_SYSINFO);
 WGlyphIdentity pIdentity;
 pIdentity.m_nLayerID = 0;
 pIdentity.strName = "SysInfo";
 m_pGlyphManager->AddGlyph(GLYPH_SYSINFO,pIdentity,pGlyph);
 pGlyph->setVisible(true);

}

void CGlyphCreator::InitNAVPointGlyph()
{
	double dMapX = 0;//坐标转换用(转换后的相对坐标，单位：m)
	double dMapY = 0;

	WGlyphIdentity pIdentity;
	std::vector<Beacon> vBeacon;
	vBeacon = m_pDataBase->GetBeaconVec(); 
	//多点形状的绘制
	std::vector<Beacon>::iterator iter = vBeacon.begin();
	for(int i = 0; iter != vBeacon.end(); ++iter,++i )
	{
		WNavPointGlyph *pNavPointGlyph = new WNavPointGlyph;
		WNavPointItemData *npd = pNavPointGlyph->data();
		//经纬度转换为以跑道为中心的相对世界坐标
		m_pCoordinate->ConvertLongLat2XY(iter->GetLongitude(),iter->GetLatitude(),dMapX,dMapY);

		npd->m_pos = WPointF(dMapX,dMapY);
		npd->m_text = iter->GetBeaconName();
		if( 1 == i%8)
		{
			++i;
		}
		npd->m_navType = i%8;
		pIdentity.m_nLayerID = 0;
		pIdentity.strName = iter->GetBeaconName();
		m_pGlyphManager->AddGlyph(GLYPH_AIRNAVPOINT,pIdentity,pNavPointGlyph);
		m_pSimMap->AddItemToMapScene(pNavPointGlyph,GLYPH_AIRNAVPOINT);
	}
}

void CGlyphCreator::InitSectorGlyph()
{

    //初始化扇区数据
	WGlyphIdentity pIdentity;
	pIdentity.m_nLayerID = 0;
	
	//坐标转换使用
	double dMapx = 0;
	double dMapY = 0;
	std::vector<Sector> vSector;//扇区
	std::vector<Cylinder> vCylinder;//柱面（一个扇区由多个柱面构成）
	std::vector<GlyphPt> vGlyphPt;//柱面多边形上面的点
	vSector = m_pDataBase->GetSectorVec();
	std::vector<Sector>::iterator iter = vSector.begin();
	for(; iter != vSector.end(); ++iter)
	{
		Sector &sector = *iter;
		m_pDataBase->GetCylinderVec(sector.GetSectorID(),vCylinder);
		std::vector<Cylinder>::iterator iter_cylinder = vCylinder.begin();
		for(; iter_cylinder != vCylinder.end(); ++ iter_cylinder)
		{
			Cylinder &cldr = *iter_cylinder;
			m_pDataBase->GetPointsData(cldr.GetCylinderID(),vGlyphPt);
			std::vector<GlyphPt>::iterator iter_glyph = vGlyphPt.begin();
			//添加管制区域
			WControlAreaGlyph *pControlGlyph = new WControlAreaGlyph;
			WControlAreaItemData *pControlAreaData = pControlGlyph->data();
			pControlAreaData->brush.setColor(WColor(100,100,0,100));
			pControlAreaData->brush.setStyle(Ws::SolidPattern);
			std::vector<WWorldPointT<double> > vPoint;
			for(; iter_glyph != vGlyphPt.end(); ++ iter_glyph)
			{
				GlyphPt &gp = *iter_glyph;
				//经纬度转换为以跑道为中心的相对世界坐标
				m_pCoordinate->ConvertLongLat2XY(gp.GetLongtitude(),gp.GetLatitude(),dMapx,dMapY);
				vPoint.push_back(WWorldPointT<double>(dMapx,dMapY));
			}
			pControlAreaData->polygon = WWorldPolygonF(vPoint);
			pIdentity.strName = cldr.GetCylinderName();
			m_pGlyphManager->AddGlyph(GLYPH_SECTOR,pIdentity,pControlGlyph);
			m_pSimMap->AddItemToMapScene(pControlGlyph,GLYPH_SECTOR);
		}
	}
}
void CGlyphCreator::InitRestricAreaGlyph()
{
	WGlyphIdentity pIdentity;
	pIdentity.m_nLayerID = 0;

	double dMapX = 0;
	double dMapY = 0;
	std::vector<RestrictArea> vArea;
	vArea = m_pDataBase->GetRestrictAreaVec();
	std::vector<RestrictArea>::iterator iter = vArea.begin();
	for(; iter != vArea.end(); ++iter)
	{
		WControlAreaGlyph *pGlyph = new WControlAreaGlyph;
		WControlAreaItemData *pData = pGlyph->data();
		pData->brush.setColor(WColor(100,100,0,100));
		pData->brush.setStyle(Ws::SolidPattern);

		std::vector<WPointF> vPoints;
		std::vector<boost::shared_ptr<PointPosition> >::iterator iter_point = iter->m_vRestrictAreaPoint.begin();
		for(; iter_point != iter->m_vRestrictAreaPoint.end(); ++ iter_point)
		{
			m_pCoordinate->ConvertLongLat2XY((*iter_point)->m_dLongtitude,(*iter_point)->m_dLatitude,dMapX,dMapY);
			vPoints.push_back(WPointF(dMapX,dMapY));

		}
		pData->polygon = vPoints;
		pIdentity.strName = iter->m_strRestrictAreaName;
		m_pGlyphManager->AddGlyph(GLYPH_RESTRICTAREA,pIdentity,pGlyph);
		m_pSimMap->AddItemToMapScene(pGlyph,GLYPH_RESTRICTAREA);
	}

}

void CGlyphCreator::InitRouteGlyph()
{
	WGlyphIdentity pIdentity;
	pIdentity.m_nLayerID = 0;

	double dMapX = 0;
	double dMapY = 0;

	std::vector<Course> vCourse;
	vCourse = m_pDataBase->GetCourseVec();
	std::vector<Course>::iterator iter =vCourse.begin();
	for(; iter != vCourse.end(); ++ iter)
	{
		WUnclosedLineGlyph *pGlyph = new WUnclosedLineGlyph;
		WUnclosedLineItemData *pData = pGlyph->data();

		std::vector<WPointF> vPoints;
		std::vector<boost::shared_ptr<RoutePt> >::iterator iter_point = iter->m_vecRoutePt.begin();
		for(; iter_point != iter->m_vecRoutePt.end(); ++iter_point)
		{
			m_pCoordinate->ConvertLongLat2XY((*iter_point)->m_dLongtitude,(*iter_point)->m_dLatitude,dMapX,dMapY);
			vPoints.push_back(WPointF(dMapX,dMapY));
		}
		pData->m_color = WColor(0,255,0);
		pData->polyline = WWorldPolylineF(vPoints);
		pIdentity.strName = iter->m_strCourseName;
		m_pGlyphManager->AddGlyph(GLYPH_AIRSPACEROUTE,pIdentity,pGlyph);
		m_pSimMap->AddItemToMapScene(pGlyph,GLYPH_AIRSPACEROUTE);

	}

}

void CGlyphCreator::InitMsawAreaGlyph()
{
	WGlyphIdentity pIdentity;
	pIdentity.m_nLayerID = 0;

	double dMapX = 0;//坐标转换用（转换后的相对坐标，单位：m）
	double dMapY = 0;

	std::vector<MsawArea> vArea;
	vArea = m_pDataBase->GetMsawAreaVec();
	std::vector<MsawArea>::iterator iter = vArea.begin();
	for (; iter != vArea.end(); ++iter)
	{
		WControlAreaGlyph* pGlyph = new WControlAreaGlyph;
		WControlAreaItemData* pData = pGlyph->data();
		pData->brush.setColor(WColor(100, 100, 0, 100));
		pData->brush.setStyle(Ws::SolidPattern);

		std::vector<WPointF> vPoints;
		std::vector<boost::shared_ptr<PointPosition> >::iterator iTerPoint = iter->m_vMsawAreaPoint.begin();
		for (; iTerPoint != iter->m_vMsawAreaPoint.end(); ++iTerPoint)
		{
			//经纬度转换为以跑道为中心的相对世界坐标
			m_pCoordinate->ConvertLongLat2XY((*iTerPoint)->m_dLongtitude, (*iTerPoint)->m_dLatitude, dMapX, dMapY);
			vPoints.push_back(WPointF(dMapX, dMapY));
		}

		//判断点数据是否为空，如为空，打印数据为空的日志
		if (vPoints.empty())
		{
			std::string str = iter->m_strMsawAreaName;
			str = str + "数据为空";
			//LOG(LOG_LEVEL_WARN, str);
		}
		pData->polygon = vPoints;
		pIdentity.strName = iter->m_strMsawAreaName;
		m_pGlyphManager->AddGlyph(GLYPH_MSAWAREA, pIdentity, pGlyph);
		m_pSimMap->AddItemToMapScene(pGlyph, GLYPH_MSAWAREA);
	}


}

void CGlyphCreator::InitSingleAircraftGlyph( AircraftTrace* pTrace )
{
	//new一个飞机对象
    WAircraftGlyph* aircraftGlyph = new WAircraftGlyph;

	//设置飞机的基本属性
	WAircraftItemData& d = *aircraftGlyph->data();
	d.m_penLine.setColor(WColor(0,255,0));
	d.m_penBounding.setColor(WColor(255,0,0));
	d.m_penBoundingSel.setColor(WColor(255,255,0));

	WPointF point(pTrace->m_fAbsX,pTrace->m_fAbsY);//飞机当前的绝对位置

    d.m_pos.setXY(point.x(),point.y());
	d.m_boundingRect.setRect(.0,.0,.0,.0);
	d.m_iId = pTrace->m_nTraceID;

	//WLabelFormateFactory是标牌工厂，负责生产标牌
	const WLabelFormat* format = WLabelFormatFactory::Instance().GetFormat(WLabelFormatFactory::normal_plan);
	//给指定航迹添加标牌格式
	CLabelManager::Instance().AddLabel(aircraftGlyph,*format);
	aircraftGlyph->setLabelLine(50,300);

	//处理字体的类
	const WFontMetrics metrics(WAircraftGlyph::getLabelFont());
	const double DX = metrics.averageCharWidth();//计算字符的平均宽度
	const double HEIGHT = metrics.height();//计算字体的高度

	//标牌中的具体块对象
	WLabelFields& fields = *CLabelManager::Instance().GetFields(aircraftGlyph);//获得指定航迹的标牌数组
	WLabelField* fd = 0;
	fd = &fields[WLabelFields::cfl];//cfl的含义：许可飞行高度，公制时10米为单位，显示4字符，英制时100英尺为单位，显示3字符，不足前补0
	fd->SetText( boost::lexical_cast<std::wstring>(""));
	fd->SetSize(WSizeF(DX * 10,2));

	fd = &fields[WLabelFields::label_data];//用户输入的自由文本
	fd->SetText(boost::lexical_cast<std::wstring>(""));
	fd->SetSize(WSizeF(DX * 10, 2));

	//将新航迹加入到地图中
	WGlyphIdentity pIdentity;
	pIdentity.m_nLayerID = 0;
	pIdentity.m_nTraceID = pTrace->m_nTraceID;
	pIdentity.strName = pTrace->m_strName;
	m_pGlyphManager->AddGlyph(GLYPH_AIRCRAFT,pIdentity,aircraftGlyph);
	m_pSimMap->AddItemToMapScene(aircraftGlyph,GLYPH_AIRCRAFT);
	UpdateTrace(aircraftGlyph,pTrace);
}
void CGlyphCreator::UpdateTrace(WAircraftGlyph* aircraftGlyph,AircraftTrace *pTrace)
{
	const WFontMetrics metrics(WAircraftGlyph::getLabelFont());
	const double DX = metrics.averageCharWidth();
	const double HEIGHT = metrics.height();
	const double WIDTH = DX * MAX_CHARS;
	g_sm.lock();
	AircraftTrace* aircraftTrace = pTrace;
	switch(aircraftTrace->m_eCurSignalType)
	{
	case  SIGNAL_NONE:
		aircraftGlyph->data()->m_eSymbolType = SYMBOL_INVALID;
		break;
	case  SIGNAL_PRIMARY:
		aircraftGlyph->data()->m_eSymbolType = SYMBOL_PRIMARY;
		break;
	case  SIGNAL_SECONDARY:
		aircraftGlyph->data()->m_eSymbolType = SYMBOL_SECONDARY;
		break;
	case SIGNAL_COMBINED:
		aircraftGlyph->data()->m_eSymbolType = SYMBOL_COMBINED;
		break;
	}
	//AircraftInfo *aircraftData = aircraftTrace->m_pAcftInfo;
	//bool bWarn = false;
	WLabelFields& fields = *CLabelManager::Instance().GetFields(aircraftGlyph);
	//if (aircraftData)
 //    {
	//	//label flash
	//	if (0 < pTrace->m_iCount && pTrace->m_iCount < 5)
	//	{
	//		if (0 == pTrace->m_iCount % 2)
	//		{
	//			CLabelManager::Instance().SetLogicFlags(aircraftGlyph, CLabelManager::coupling | CLabelManager::jurisdiction);
	//		}
	//		else
	//		{
	//			CLabelManager::Instance().SetLogicFlags(aircraftGlyph, CLabelManager::coupling | CLabelManager::flash);
	//		}
	//	}
	//	else
	//	{
	//		CLabelManager::Instance().SetLogicFlags(aircraftGlyph, CLabelManager::coupling | CLabelManager::jurisdiction);
	//	}
	//	UpdateLabel_AircraftInfo(fields, aircraftData);
	//}
	//else
	//{
		CLabelManager::Instance().SetLogicFlags(aircraftGlyph, CLabelManager::no_jurisdiciton);
	//}
	//动态处理标牌格式
	CLabelManager::Instance().LogicProcFormat(aircraftGlyph);
	//update trace info
	UpdateLabel_TraceInfo(aircraftGlyph, fields, aircraftTrace);
	g_sm.unlock();
	theApp::instance().GetMapMangerPtr().get()->GetSimMapPtr().get()->UpdateMap();
}

void CGlyphCreator::UpdateLabel_AircraftInfo( WLabelFields& fields, AircraftInfo* pAcftInfo )
{
	const WFontMetrics metrics(WAircraftGlyph::getLabelFont());
	const double DX = metrics.averageCharWidth();
	const double HEIGHT = metrics.height();
	WLabelField* fd = 0;

	//尾流，1个字符，H=high M=medium L=light
	fd = &fields[WLabelFields::w]; 
	fd->SetSize(WSizeF(DX, HEIGHT));
	fd->SetText(towstring(pAcftInfo->GetTurbo().c_str()));

	//降落机场，最多4字符
	fd = &fields[WLabelFields::ades]; 
	fd->SetText(towstring(pAcftInfo->GetArrAerodrome().c_str()));
	fd->SetSize(WSizeF(DX * 4, HEIGHT));

	//机型，最多4字符
	fd = &fields[WLabelFields::typ]; 
	fd->SetText(towstring(pAcftInfo->GetAcftType().c_str()));
	fd->SetSize(WSizeF(DX * 4, HEIGHT));
}

void CGlyphCreator::UpdateLabel_TraceInfo( WAircraftGlyph* aircraftGlyph, WLabelFields& fields,  AircraftTrace* pTraceInfo )
{
	const WFontMetrics metrics(WAircraftGlyph::getLabelFont());
	const double DX = metrics.averageCharWidth();
	const double HEIGHT = metrics.height();
	WLabelField* fd = 0;
	char szTmp[10] = {0};
	int nLength = 0;
	//飞机标示符
	fd = &fields[WLabelFields::acid];
	sprintf_s(szTmp,"%s",pTraceInfo->m_strName.c_str());
	fd->SetText(towstring(szTmp));
	nLength = strlen(szTmp);
	fd->SetSize(WSizeF(DX*nLength,HEIGHT));
	//SSR代码，4个字符
	fd = &fields[WLabelFields::moda];
	fd->SetText(towstring(pTraceInfo->m_strSSR.c_str()));
	fd->SetSize(WSizeF(DX*4,HEIGHT));
	//显示高度
	fd = &fields[WLabelFields::mcl];
	fd->SetSize(WSizeF(DX*4,HEIGHT));
	int mcl_height = pTraceInfo->m_nAttitude;
	//if)*/
	 if (pTraceInfo->m_euAltitudeType == ALTTYPE_QNH)//海压高度
	{
		//mcl_height = /*计算QNH校正高度*/mcl_height;
		//高度前面加字母A
		fd->SetText((boost::wformat(L"A%03d") % (mcl_height % 1000)).str());
	}
	else if (pTraceInfo->m_euAltitudeType == ALTTYPE_QFE) //场压高度
	{
		// 		mcl_height = /*计算QNH校正高度*/mcl_height;
		//高度前面加字母A
		fd->SetText((boost::wformat(L"H%03d") % (mcl_height % 1000)).str());
	}
	else
	{
		if (/*公制*/true)
		{
			//公制时10米为单位，显示4字符，不足前补0
			//mcl_height转换成公制，(m+n / 2) / n为对n“四舍五入”之意，下同
			//fd->SetText((boost::wformat(L"%04d") % ((mcl_height + 5) / 10 % 10000)).str());

			int nHeight = (mcl_height + 5) / 10;
			sprintf(szTmp, "%04d", nHeight);
			fd->SetText(towstring(szTmp));

		}
		else /*英制*/ 
		{
			//英制时100英尺为单位，显示3字符，不足前补0
			//mcl_height转换成英制
			fd->SetText((boost::wformat(L"%03d") % ((mcl_height + 50) / 100 % 1000)).str());
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//
	fd = &fields[WLabelFields::indicator]; //高度指示，向上的箭头表示爬升，向下的箭头表示下降，水平箭头表示平飞，旁路模式不显示
	fd->SetSize(WSizeF(DX, HEIGHT));
	unsigned char ch = pTraceInfo->m_byAtt;
	switch(ch)
	{
	case 0:
		{
			fd->SetText(ARRAY_RIGHT);
		}
		break;
	case 1:
		{
			fd->SetText(ARRAY_UP);
		}
		break;
	case 2:
		{
			fd->SetText(ARRAY_DOWN);
		}
		break;
	default:
		{
			fd->SetText(EMPTY_WSTR);
		}
		break;
	}
	//////////////////////////////////////////////////////////////////////////
	//gas
	fd = &fields[WLabelFields::gs]; //地速，公制时10km/h为单位，显示3位数字，英制时，以10knm/h为单位，显示2位数字
	fd->SetSize(WSizeF(DX * 4, HEIGHT));
	int gs_speed = static_cast<int>(pTraceInfo->m_dGAS);

	if (/*公制*/true)
	{
		//公制时10km/h为单位，显示3位数字，如果GS > 1994km/h，则显示+++
		//gs_speed转换到公制
		//fd->SetText((gs_speed > 1994) ? PLUS_3 : ((boost::wformat(L"%03d") % ((gs_speed + 5) / 10 % 1000))).str());
		sprintf(szTmp, "%03d ", gs_speed);
		fd->SetText(towstring(szTmp));

	}
	else /*英制*/
	{
		//英制时10knm/h为单位，显示2位数字，如果GS > 994knm/h，则显示++
		//gs_speed转换到英制
		fd->SetText((gs_speed > 994) ? PLUS_2 : ((boost::wformat(L"%02d") % ((gs_speed + 5) / 10 % 100))).str());
	}

	//////////////////////////////////////////////////////////////////////////
	//航向
	fd = &fields[WLabelFields::hdg]; //地速，公制时10km/h为单位，显示3位数字，英制时，以10knm/h为单位，显示2位数字
	fd->SetSize(WSizeF(DX * 4, HEIGHT));
	int heading = static_cast<int>(pTraceInfo->m_dHeading);

	if (/*公制*/true)
	{

		//gs_speed转换到公制
		//fd->SetText((heading > 1994) ? PLUS_3 : ((boost::wformat(L"%03d") % ((heading) % 1000))).str());
		sprintf(szTmp, "%03d ", heading);
		fd->SetText(towstring(szTmp));
	}
	else /*英制*/
	{
		//gs_speed转换到英制
		fd->SetText((heading > 994) ? PLUS_2 : ((boost::wformat(L"%02d") % ((heading) % 100))).str());
	}

	fd = &fields[WLabelFields::label_data];
	fd->SetText(towstring(""));
	fd->SetCharN(10);
//////////////////////////////////////////////////////////////////////////
	WAircraftItemData& d = *aircraftGlyph->data();
	WPointF point(pTraceInfo->m_fAbsX, pTraceInfo->m_fAbsY);
	/*WPointF offset(point.x() - d.m_pos.x(), point.y() - d.m_pos.y());
	WPointF labelPos = d.m_boundingRect.bottomLeft();

	WRectF rect_org = d.m_boundingRect;*/
	CLabelManager::Instance().UpdateLabel(aircraftGlyph);

	d.m_pos      = point; //server传的数据不是经纬度，暂时无需转换
	d.m_PRLPos   = pTraceInfo->m_wPRLPos;
  //  d.m_vHistory = &pTraceInfo->m_vHistoryPos;

	aircraftGlyph->data()->m_bShowBounding = true;
	aircraftGlyph->data()->m_nHeading = heading;
}

void CGlyphCreator::UpdateTelemeterLine( WAircraftGlyph* gly )
{
	std::vector<WGraphicsItem*> v;
	m_pGlyphManager->GetGlyph(GLYPH_TELEMETER, v);
	if (!v.empty())
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			WTelemeterGlyph* telemeterGly = dynamic_cast<WTelemeterGlyph*>(v[i]);
			if (telemeterGly)
			{
				WTelemeterGlyph::data_type& d = *(telemeterGly->data());
				WAircraftGlyph::data_type& d2 = *(gly->data());
				if (d.m_startTraceId == d2.m_iId)
				{
					d.m_line.setP1(d2.m_pos);
				}

				if (d.m_endTraceId == d2.m_iId)
				{
					d.m_line.setP2(d2.m_pos);
				}
			}
		}
	}
}

void CGlyphCreator::UpdateSingleAircraftTrace( AircraftTrace* pTrace )
{

	SetCurAircraftTrace(pTrace->m_nTraceID);
	if(! m_pSimMap || !pTrace)
	{
		return;
	}
	WAircraftGlyph* aircraft = NULL;
	m_pGlyphManager->GetGlyph(GLYPH_AIRCRAFT,pTrace->m_nTraceID,&aircraft);
	//图元不存在则创建
	if(NULL == aircraft)
	{
		InitSingleAircraftGlyph(pTrace);
	}
	else
	{
		bool isHideAcft = pTrace->m_bHide;
		aircraft->data()->m_bShowAcft = !isHideAcft;
		if(!isHideAcft)
		{
          UpdateTrace(aircraft,pTrace);
		}
	}
}

void CGlyphCreator::UpdateSingleAircraftPRLPos( std::string& strName,WPointF& point )
{
   WAircraftGlyph* aircraft = NULL;
   m_pGlyphManager->GetGlyph(GLYPH_AIRCRAFT,strName,&aircraft);
   if(aircraft)
   {
	   aircraft->data()->m_PRLPos = point;
   }

}
//////////////////////////////////////////////////////////////////////////
void CGlyphCreator::InitSomeAircraft()
{
	const size_t aircraftCount =  10;
	double rate = 300000;
	double s = rate * aircraftCount;
	int l = sqrt(s);
	int r = l / 2;
	for (size_t i = 0; i < aircraftCount; ++i)
	{
	AircraftTrace *trace  =  new AircraftTrace();
	trace->m_nTraceID = i;
	trace->m_fAbsX = rand() % l - r;
	trace->m_fAbsY = rand() % l - r;
	trace->m_dHeading = 100;
	trace->m_dGAS = 90;
	//theApp::instance().GetDataManagerPtr().get()->GetTotalAircraftTraceInstance()->UpdateAircraftTrace<AircraftTrace>(i,&trace);
	SetAircraftTrace(i,trace);
	}
}

AircraftTrace* CGlyphCreator::GetAircraftTrace( int nTraceNo )
{
	hmFplTraces::iterator iter = m_hmTraces.find(nTraceNo);
	if(iter != m_hmTraces.end())
	{
		return iter->second;
	}
	return NULL;
   
}

void CGlyphCreator::ClearTraces()
{
	BOOST_FOREACH(hmFplTraces::value_type& value, m_hmTraces)
	{
		if (value.second != NULL)
		{
			delete value.second;
			value.second = NULL;
		}
	}
	m_hmTraces.clear();
	m_pCurTraces = NULL;
}

void CGlyphCreator::SetCurAircraftTrace( int iTraceID )
{
	if(-1 == iTraceID)
	{
		m_pCurTraces = NULL;
	}
	else
	{
		m_pCurTraces = GetAircraftTrace(iTraceID);
	}
}

