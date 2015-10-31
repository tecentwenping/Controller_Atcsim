#include "AircraftTrace.h"
#include "AircraftInfo.h"
#include "Manager/DataManager.h"
#include <boost/make_shared.hpp>
#include "Interface/theApp.h"
//#include "public/ControllerAcftInfo.h"
double AircraftTrace::PI =  3.14159265358979323846;
AircraftTrace::AircraftTrace():m_nTraceID(-1), m_nAttitude(0),
m_dHeading(0.0), m_fAbsX(0.0), m_fAbsY(0.0), m_byAtt(1),
m_strName(""), m_strSSR(""), eStateType(PublicDataStruct::STATE_NONE),
m_wPRLPos(0, 0), m_fPRLTime(3.0), m_nHistoryNum(10),
m_eCurSignalType(PublicDataStruct::SIGNAL_COMBINED),m_bShowLabel(true), 
m_bHide(false), m_iCount(-1)
{
	//m_vHistoryPos.reserve(5000);
}


AircraftTrace::~AircraftTrace()
{

}

void AircraftTrace::ComputeMapXY()
{
	//double dx = 0.00;
	//double dy = 0.00;
	//theApp::instance().GetMapManagerPtr()->GetMapCoordinatePtr()->\
	//	ConvertLongLat2XY(m_dLongitude, m_dLatitude, dx, dy);

	//m_fAbsX = static_cast<float>(dx);
	//m_fAbsY = static_cast<float>(dy);
}


void AircraftTrace::ComputPRLPos()
{
}    

void AircraftTrace::ComputPRLPos( int iTraceID )
{
	//���ȸ��ݺ���Ų��ҹ켣��
	QStringList pathPointList;
	theData::instance().GetPathPoint(iTraceID,pathPointList);
	if(pathPointList.empty())
	{
		return;
	}
	//��Ϊ�յ�QStringList��ŵ���һϵ�е�
	PublicDataStruct::AircraftPos temp;
	std::map<int,std::vector<WPointF> > aircraftTraceMap;//��Ž�����ĺ�����
	// std::vector<WPointF> vTracePos;
	// vTracePos.reserve(5000);
	MapFixPoint mpFixPoint;
	double dX_0 = 0.0,dY_0 = 0.0,dX_1 = 0.0,dY_1 = 0.0;
	theData::instance().GetMapFixPoint(mpFixPoint);



	///////////////////////////////////////////////////////////////
	std::deque<WPointF> dTracePos;
	dTracePos.resize(5000);
	///////////////////////////////////////////////////////////////
	 for(int i = 1; i != pathPointList.size()-1; ++i)
		{
			
			int j = i+1;
			MapFixPoint::iterator ForIter = mpFixPoint.find(pathPointList.at(i).toStdString());
			MapFixPoint::iterator BackIter = mpFixPoint.find(pathPointList.at(j).toStdString());
			//���ǰ�������
			if(ForIter != mpFixPoint.end())
			{
				dX_0 = ForIter->second.GetFixPointX();
				dY_0 = ForIter->second.GetFixPointY();
			}
			//��ú�������
			if(BackIter != mpFixPoint.end())
			{
				dX_1 = BackIter->second.GetFixPointX();
				dY_1 = BackIter->second.GetFixPointY();
			}
			/*///////////////////////////////
			//			1         ���
			//			1        /|
			//			1 root  / |dTmpty
			//			1      /  |
			//			1     /   |
			//			1     ----- dTmpx
			//			1    ǰ��
			//			|  dTmpx/root = t/s
			//			///////////////////////////////*/
			double           dTmpx = 0.0;
			double           dTmpty = 0.0;
			double           root = 0.0;
			dTmpx  = dX_1 - dX_0;      /* the x different per 4s.*///dong 05.3.1
			dTmpty = dY_1 - dY_0;      /* the y different per 4s.*/
			root  = sqrt(dTmpx*dTmpx + dTmpty*dTmpty);
			if (root<1e-10)
			{
				root = 1.0;
			}
			//�洢������ֵ��
			double dCurX = dX_0;//��ֵ����x����
			double dCurY = dY_0;//��ֵ�յ��y����
			double	dS = double(2*(29*10/36));//һ��ʱ�������ƶ��ľ���
			int pointCount = root/dS;//��ֵ��ĸ���
			//vTracePos.push_back(WPointF(dX_0,dY_0));//������

			dTracePos.push_back(WPointF(dX_0,dY_0));
			if(0 == pointCount)
				continue;
			for(int k = 0; k != pointCount; ++k)
			{
				dCurX += dS*(dTmpx/root);//�˶�dTemps������x���ƫ��
				dCurY += dS*(dTmpty/root);//�˶�dTemps������y���ƫ��
				//vTracePos.push_back(WPointF(dCurX,dCurY));

				dTracePos.push_back(WPointF(dCurX,dCurY));
			}
			 //vTracePos.push_back(WPointF(dX_1,dY_1));//����յ�

			 dTracePos.push_back(WPointF(dX_1,dY_1));
		}
	// theApp::instance().GetDataManagerPtr()->SetTracePoint(iTraceID,vTracePos);

	 theApp::instance().GetDataManagerPtr()->SetAircraftTracePoint1(iTraceID,dTracePos);
}

void AircraftTrace::SetPRLTime(const float fTime)
{
	double dTmpX = 0;
	double dTmpY = 0;
	dTmpX = (m_wPRLPos.x() - m_fAbsX) * fTime / m_fPRLTime;
	dTmpY = (m_wPRLPos.y() - m_fAbsY) * fTime / m_fPRLTime;
	m_wPRLPos.setX(m_fAbsX + dTmpX);
	m_wPRLPos.setY(m_fAbsY + dTmpY);
	m_fPRLTime = fTime;
}

/**
\brief     SetHistoryNum
\Access    public 
\param     const int nHistoryNum
\retval    void
\remark		//TODO @hxl ��ǰ��ʷ�������ǰ�������num���洢���ǰ�������num����ʾ   
*/
void AircraftTrace::SetHistoryNum( const int nHistoryNum )
{
	m_nHistoryNum = nHistoryNum;
}

void AircraftTrace::GetSSRCode( int &iSSR ) const
{
	std::string numberics("0123456789");
	std::string::size_type pos = m_strSSR.find_first_of(numberics);
	if (pos != std::string::npos)
	{
		iSSR = atoi(m_strSSR.substr(pos).c_str());
	}
	else
	{
		iSSR = -2;
	}
}