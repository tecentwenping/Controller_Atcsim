#ifndef __TOWER_TIME_VER4_X_H__
#define __TOWER_TIME_VER4_X_H__
#include "Serial_Base.h"
#define POINT_PER_SECOND 1000

/*****************************************************
					NOTE !!! 
						by wangdanxia 2003-07-31
  TowerTime的串行化很特殊，是对一个私有成员的串行化，
  不能用CodeGen生成其串行化代码 
******************************************************/


class CTowerTime
{//用以记录相对时间，以ms为单位
	//PKT_DECLARE_DYNCREATE(CTowerTime);
public:
	CTowerTime(int points);
	CTowerTime();
	CTowerTime & operator =(const CTowerTime & v);
	//arithmatic operations
	CTowerTime operator + ( CTowerTime &v);
	CTowerTime operator - ( CTowerTime &v);
	CTowerTime operator + ( int v);
	CTowerTime operator - ( int v);
	//logic operations
	int operator == (const CTowerTime & v) const; 
	int operator != (const CTowerTime & v) const;
	int operator >= (const CTowerTime & v) const;
	int operator <= (const CTowerTime & v) const;
	int operator > (const CTowerTime & v) const;
	int operator < (const CTowerTime & v) const;
 	int operator == (const int v) const;
	int operator != (const int v) const;
	int operator >= (const int v) const;
	int operator <= (const int v) const;
	int operator > (const int v) const;
	int operator < (const int v) const;
	// type casting
	operator int();

// Set value
	void SetTime(int hour, int minute, int second)
	{ m_points = (hour *3600 + minute * 60 + second)*POINT_PER_SECOND;}
	void SetTime(int minute, int second)
	{ m_points = (minute * 60+second) * POINT_PER_SECOND;}
	void SetTime(int second)
	{ m_points = second * POINT_PER_SECOND;}
// Get Value
	void GetTime(int *hour, int *minute, int *second)
	{
		int sec=m_points/POINT_PER_SECOND;
		*hour=sec/3600;
		*minute=(sec - *hour*3600)/60;
		*second=sec - *hour*3600 - *minute *60;
	}	
	int GetPoints() { return m_points; };
	void SetPoints(int points) {m_points = points;};

	int DecPoints(int points) { return m_points -= points;};
	int DecPoints(double points)
	{
		m_millisecond  += points * 1000;
		m_points -= (int)m_millisecond;
		m_millisecond -= (int)(m_millisecond);
		return m_points;
	}

	int IncPoints(int points) { return m_points += points;};
	static int SecondToPoint(double second);//秒转换成毫秒
	static double PointToSecond(int point);//毫秒转换成秒

private:
	int m_points;

	double m_millisecond; // 用于记录累计误差
	//SERIALIZE_PACKET(m_points& m_millisecond);
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_points & m_millisecond;
	}
/*
	virtual void ReadFromBuffer(const char* pBuffer);
	virtual void WriteToBuffer(char* pBuffer);
	virtual int GetBufferSize();
	*/
};
#endif
