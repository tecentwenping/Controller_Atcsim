#include "totalbasedata.h"
#include "airport_data_objs.h"
#include "airspace_data_objs.h"
#include "assistance_data_objs.h"
TotalBaseData::TotalBaseData()
{

}

TotalBaseData::~TotalBaseData()
{

}

void TotalBaseData::ClearBaseData()
{
   
}

void TotalBaseData::SetBaseData( const AirportData& airportData )
{
   m_airportdata=airportData;
}

void TotalBaseData::SetBaseData( const std::vector<RunwayData>& vRunwayData )
{
   m_vcRunWayData=vRunwayData;
}

void TotalBaseData::SetBaseData( const std::vector<RoadData>& vRoadData )
{
   m_vcRoadData=vRoadData;
}

void TotalBaseData::SetBaseData( const std::vector<FixpointData>& vFixpointData )
{
   m_vcFixpointData=vFixpointData;
}

void TotalBaseData::SetBaseData( const std::vector<GateData>& vGateData )
{
  m_vcGateData=vGateData;
}

void TotalBaseData::SetBaseData( const std::vector<Tower>& vTowerData )
{
	m_vTower=vTowerData;

}

void TotalBaseData::SetBaseData( const std::vector<AirportModel>& vAirportmodelData )
{
	m_vAirportModel=vAirportmodelData;

}

void TotalBaseData::SetBaseData( const std::vector<AirportData>& vAirportData )
{
  m_vAirportData=vAirportData;
}

void TotalBaseData::SetBaseData( const std::vector<Star>& vStarData )
{
  m_vStar=vStarData;

}

void TotalBaseData::SetBaseData( const std::vector<Beacon>& vBeaconData )
{
   m_vBeaconData = vBeaconData;
}

void TotalBaseData::SetBaseData( const std::vector<Sector>& vSectorData )
{
	m_vSectorData = vSectorData;

}

void TotalBaseData::SetBaseData( const std::vector<RestrictArea>& vRestricAreaData )
{
	m_vRestricAreaData = vRestricAreaData;

}

void TotalBaseData::SetBaseData( const std::vector<Course>& vCourseData )
{
  m_vCourseData = vCourseData;
}

void TotalBaseData::SetBaseData( const std::vector<MsawArea>& vMsawAreaData )
{
	m_vMsawAreaData = vMsawAreaData;

}

std::vector<AirportData> & TotalBaseData::GetAirportDataVec()
{
   return m_vAirportData;
}

AirportData& TotalBaseData::GetAirportData()
{
  return m_vAirportData.at(0);
}

std::vector<RunwayData> & TotalBaseData::GetRunwayDataVec()
{
 return m_vcRunWayData;
}

std::vector<RoadData>& TotalBaseData::GetRoadDataVec()
{
	return m_vcRoadData;

}

std::vector<FixpointData>& TotalBaseData::GetFixpointDataVec()
{
   return m_vcFixpointData;
}

bool TotalBaseData::GetFixpointDataVec( int nID, FixpointData& fixpointdata )
{

	
		std::vector<FixpointData>::iterator iter = m_vcFixpointData.begin();
		for (; iter != m_vcFixpointData.end(); ++iter)
		{
			if (iter->GetFixpointID() == nID)
			{
				fixpointdata = *iter;
				return true;
			}
		}

	return false;
}

std::vector<GateData>& TotalBaseData::GetGateDataVec()
{
  return m_vcGateData;
}

std::vector<Tower>& TotalBaseData::GetTowerDataVec()
{
	return m_vTower;

}

std::vector<AirportModel>& TotalBaseData::GetAirportDataModelVec()
{
  return m_vAirportModel;
}

std::vector<Star>& TotalBaseData::GetStarDataVec()
{
 return m_vStar;
}

bool TotalBaseData::FindFixpointData( int nID, FixpointData& fixpointdata )
{
	std::vector<FixpointData>::iterator iter=m_vcFixpointData.begin();
	for(; iter != m_vcFixpointData.end(); ++iter)
	{
		if(iter->GetFixpointID() == nID)
		{
			fixpointdata = *iter;
			return true;
		}
	}
	return false;
}

bool TotalBaseData::FindRoadData( int nID, RoadData& roaddata )
{
	std::vector<RoadData>::iterator iter=m_vcRoadData.begin();
	for(; iter != m_vcRoadData.end(); ++iter)
	{
		if(iter->GetRoadID() == nID)
		{
			roaddata = *iter;
			return true;
		}
	}
	return false;

}

std::vector<Beacon>& TotalBaseData::GetBeaconVec()
{
   return m_vBeaconData;
}

void TotalBaseData::GetBeaconVec( int nID, Beacon &beacon )
{
	std::vector<Beacon>::iterator iter = m_vBeaconData.begin();
	for (; iter != m_vBeaconData.end(); ++iter)
	{
		Beacon &bcn = *iter;
		if (bcn.GetBeaconID() == nID)
		{
			beacon = *iter;
		}
	}

}

std::vector<Sector>& TotalBaseData::GetSectorVec()
{
return m_vSectorData;
}

std::vector<RestrictArea>& TotalBaseData::GetRestrictAreaVec()
{
 return m_vRestricAreaData;
}

std::vector<Course>& TotalBaseData::GetCourseVec()
{
	return m_vCourseData;

}

std::vector<MsawArea>& TotalBaseData::GetMsawAreaVec()
{
 return m_vMsawAreaData;
}

void  TotalBaseData::GetCylinderVec(int nID, std::vector<Cylinder>& vCylinder)
{

	vCylinder.clear();
	std::vector<Cylinder>::iterator iter = m_vecCylinder.begin();
	for(; iter != m_vecCylinder.end(); ++iter)
	{
		Cylinder &cldr = *iter;
		if(cldr.GetOwnID() == nID)
		{
			vCylinder.push_back(*iter);
		}
	}

}

void TotalBaseData::GetPointsData( int nID, std::vector<GlyphPt>& vGlyphPt )
{
	vGlyphPt.clear();
	std::vector<CylinderGlyph> v_cg;
	GetCylinderGlyphData(nID,v_cg);
	std::vector<CylinderGlyph>::iterator iter_cg = v_cg.begin();
	for(int sequence = 0; iter_cg != v_cg.end(); ++ iter_cg, ++ sequence)
	{
		GlyphPt temp_gp;
		Beacon temp_beacon;
		FixpointData temp_fp;
		GlyphPt gp;
		int gp_id = GetGlyphPtIDFromSequence(sequence,v_cg);
		GetGlyphPtData(gp_id,gp);
		switch(gp.GetPointType())
		{
		case 0://Beacon
			GetBeaconVec(gp.GetPointID(),temp_beacon);
			temp_gp.SetLongtitude(temp_beacon.GetLongitude());
			temp_gp.SetLatitude(temp_beacon.GetLatitude());
			temp_gp.SetHeight(temp_beacon.GetHeight());
			vGlyphPt.push_back(temp_gp);
			break;
		case 1://FixPoint
			GetFixpointDataVec(gp.GetPointID(),temp_fp);
			temp_gp.SetLongtitude(temp_fp.GetX());
			temp_gp.SetLatitude(temp_fp.GetY());
			temp_gp.SetHeight(temp_fp.GetZ());
			vGlyphPt.push_back(temp_gp);
			break;

		}
	}

}

void TotalBaseData::GetCylinderGlyphData( int nID, std::vector<CylinderGlyph> &vCylinderGlyph )
{
   vCylinderGlyph.clear();
   std::vector<CylinderGlyph>::iterator iter = m_vecCylinderGlyph.begin();
   for(; iter != m_vecCylinderGlyph.end(); ++ iter)
   {
	   CylinderGlyph &cg = *iter;
	   if(cg.GetCylinderID() == nID)
	   {
		   vCylinderGlyph.push_back(*iter);
	   }
   }
}
int TotalBaseData::GetGlyphPtIDFromSequence(int sequence, std::vector<CylinderGlyph> &vCylinderGlyph)
{
	int retValue = -1;
	
		std::vector<CylinderGlyph>::iterator iter = vCylinderGlyph.begin();
		for (; iter != vCylinderGlyph.end(); ++iter)
		{
			CylinderGlyph &cg = *(iter);
			if (cg.GetSequence() == sequence)
			{
				retValue = cg.GetGlyphPtID();
			}
		}
	return retValue;
}
void TotalBaseData::GetGlyphPtData(int nID, GlyphPt &glyphPt)
{

		std::vector<GlyphPt>::iterator iter = m_vecGlyphPt.begin();
		for (; iter != m_vecGlyphPt.end(); ++iter)
		{
			GlyphPt &gp = *iter;
			if (gp.GetGlyphPtID() == nID)
			{
				glyphPt = *iter;
			}
		}
	
}