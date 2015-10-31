#pragma once
#include "GlobalSpace.h"

struct ST_INTENSITY_POS
{
public:
	ST_INTENSITY_POS(){};
	~ST_INTENSITY_POS(){};

	int getIntensity() const { return iLevel; }
	double getPosX() const { return PosX; }
	double getPosY() const { return PosY; }
	double getPosZ() const { return PosZ; }
	void   setIntensity( int lev ){ iLevel=lev; }

	ST_INTENSITY_POS& ST_INTENSITY_POS::operator=( const ST_INTENSITY_POS& posInst )
	{
		if( this == &posInst )
			return *this;

		PosX = posInst.getPosX();
		PosY = posInst.getPosY();
		PosZ = posInst.getPosZ();
		iLevel = posInst.getIntensity();
		return *this;
	}
    
	/*char* readFromBuffer(char* vBuffer)
	{
		char *pTemp = vBuffer;

		memcpy(&iLevel, pTemp, sizeof(iLevel));
		pTemp += sizeof(iLevel);	
		memcpy(&PosX, pTemp, sizeof(PosX));
		pTemp += sizeof(PosX);	
		memcpy(&PosY, pTemp, sizeof(PosY));
		pTemp += sizeof(PosY);		
		memcpy(&PosZ, pTemp, sizeof(PosZ));
		pTemp += sizeof(PosZ);	

		return pTemp;
	}

	char* dumpToBuffer(char* voBuffer)
	{
		char *pTemp = voBuffer;

		memcpy(pTemp, &iLevel, sizeof(iLevel));
		pTemp += sizeof(iLevel);	
		memcpy(pTemp, &PosX, sizeof(PosX));
		pTemp += sizeof(PosX);	
		memcpy(pTemp, &PosY, sizeof(PosY));
		pTemp += sizeof(PosY);		
		memcpy(pTemp, &PosZ, sizeof(PosZ));
		pTemp += sizeof(PosZ);	

		return pTemp;		
	}*/

	int  length()  {return sizeof(int) + sizeof(double)*3; }
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & iLevel & PosX & PosY & PosZ ;
	}

private:
	int		iLevel;			//ǿ�ȵȼ�
	double	PosX;           //x, y,	zλ����Ϣ	�ڻ�����/�ĵ������е�λ��
	double	PosY;
	double	PosZ;

	friend 	bool  operator==( const ST_INTENSITY_POS& left, const ST_INTENSITY_POS& right )
	{
		return ( (left.getPosX()-right.getPosX())<1e-3 && (left.getPosY()-right.getPosY())<1e-3 && (left.getPosZ()-right.getPosZ())<1e-3 );
	}
};

class ST_EnvDataForVisGen // �Ӿ�λ��Ҫ�Ļ�����Ϣ
{
public:
	ST_EnvDataForVisGen() {clearEnvInfo();};
	~ST_EnvDataForVisGen(){};

	void clearEnvInfo()
	{
		m_iRainLevel = 0;
		m_iSnowLevel = 0;
		m_iDustLevel = 0;
		m_bLightningOn = false;
		m_bRisenDustOn = false;
		m_bLightningOn = false;
		m_bHazeOn      = false;
		m_bFogOn       = false;
		m_vSmoke.clear();
		m_vRadiantFog.clear();
		m_bTriggerOneLightning = false;
		m_vectEnvTime.clear();
		m_vectEnvTime.push_back(0);
		m_vectEnvTime.push_back(0);
		m_vectEnvTime.push_back(0);
		m_vectEnvTime.push_back(0);
		m_vectEnvTime.push_back(0);
		m_vectEnvTime.push_back(0);
	}

	int getTsAirportID()	 { return m_iAirportID; }
	int getRainLevel()		 { return m_iRainLevel; }
	int getSnowLevel()		 { return m_iSnowLevel; }
	int getDustLevel()	     { return m_iDustLevel; }
	int getLightningLevel()  {return m_LightningInf.getIntensity();}

	bool isLightningOn()		  { return m_bLightningOn; }
	bool isFogOn()				  { return m_bFogOn; }
	bool isHazeOn()               {return m_bHazeOn;}
	bool isRisenDustOn()		  { return m_bRisenDustOn; }
	bool isTriggerOneLightning()  { return m_bTriggerOneLightning; }

	double getWindSpeed()		{ return m_dWindSpd; }
	double getWindDir()			{ return m_dWindDir; }
	double getVisibility()		{ return m_dVisibility; }
	double getTemperature()		{ return m_dTemperature; }

	const std::string&		 getAirportModelName()		{ return m_strModelName; }
	const ST_INTENSITY_POS&  getTriggerLightningInfo()  { return m_LightningInf; }

	const std::vector<ST_INTENSITY_POS>&  getSmoke()	   { return m_vSmoke; }
	const std::vector<ST_INTENSITY_POS>&  getRadiantFog()  { return m_vRadiantFog; }
	bool   getTrainTime( int *time, int len )  
	{
		if ( len < 6 )
		{
			CGlobalSpace::ExceptionHandler.displayWarning(__EXCEPTION_SITE__,"Not enough space for training time storage!");
			return false;
		}
		memset( time, 0, 6 );
		if ( m_vectEnvTime.size()>=6 )	
		{
			for ( int i=0; i<6; ++i )
			{
				time[i] = m_vectEnvTime[i]; 
			}
			return true;
		}
		else
		{
			CGlobalSpace::ExceptionHandler.displayWarning(__EXCEPTION_SITE__,"The training time info in environment is not complete!");
			return false;
		}
	}
	void setAirportModelName( const std::string modelName ) { m_strModelName=modelName; }
	void setVisibility( double vVisibility )				{ m_dVisibility = vVisibility; }
	void setRisenDust(bool bOn)								{ m_bRisenDustOn=bOn; }
	void setDustLevel(int  iLevel)                          { m_iDustLevel=iLevel; }
	void setWindSpeed(double windSpd)						{ m_dWindSpd=windSpd; }
	void setWindDir(double windDir)			                { m_dWindDir=windDir; }
	void setRainLevel(int rainLevel)			            { m_iRainLevel=rainLevel; }
	void setSnowLevel(int snowLevel)			            { m_iSnowLevel=snowLevel; }
	void setFogOn(bool bOn)									{ m_bFogOn=bOn; }
	void setHazeStatus(bool vStatus)                        {m_bHazeOn = vStatus;}           
	void setLightningOn(bool bOn)			                { m_bLightningOn=bOn; }
	void setTsAirportID( int id )                           { m_iAirportID=id;}
	void addSmoke( const ST_INTENSITY_POS& smoke )
	{
		m_vSmoke.push_back( smoke );
	}
	void addRadiantFog( const ST_INTENSITY_POS& fog )
	{
		m_vRadiantFog.push_back( fog );
	}
	void setTrainingTime( int *time, int len )
	{ 
		if ( len < 6 )
		{
			CGlobalSpace::ExceptionHandler.displayWarning( __EXCEPTION_SITE__, "The training time is not complete!" );
			return;
		}
		m_vectEnvTime.clear();
		for ( int i=0; i<len; ++i )
		{
			m_vectEnvTime.push_back( time[i] );
		}
	}

	//int length() 
	//{
	//	int iSize=0;

	//	iSize += sizeof(int)*4 + sizeof(double)*4 + sizeof(bool)*5 + m_strModelName.length() + 1 + sizeof(double)*m_vectEnvTime.size() + sizeof(m_vectEnvTime.size());
	//	
	//	if ( !m_vSmoke.empty()  )
	//	{
	//		iSize += sizeof(m_vSmoke.size());
	//		iSize += m_vSmoke.size() * m_vSmoke[0].length();
	//	}
	//	if ( !m_vRadiantFog.empty()  )
	//	{
	//		iSize += sizeof(m_vRadiantFog.size());
	//		iSize += m_vRadiantFog.size() * m_vRadiantFog[0].length();
	//	}

	//	iSize += m_LightningInf.length();

	//	return iSize;
	//}

	//char* dumpToBuffer(char *voBuffer)
	//{
	//	char* pTemp = voBuffer;

	//	memcpy(pTemp, &m_dTemperature, sizeof(m_dTemperature));
	//	pTemp += sizeof(m_dTemperature);
	//	memcpy(pTemp, &m_dVisibility, sizeof(m_dVisibility));
	//	pTemp += sizeof(m_dVisibility);
	//	memcpy(pTemp, & m_dWindDir, sizeof( m_dWindDir));
	//	pTemp += sizeof( m_dWindDir);
	//	memcpy(pTemp, & m_dWindSpd, sizeof( m_dWindSpd));
	//	pTemp += sizeof( m_dWindSpd);
	//	memcpy(pTemp, m_strModelName.c_str(), m_strModelName.length()+1);
	//	pTemp += m_strModelName.length()+1;

	//	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	//	pTemp += sizeof(m_iAirportID);

	//	memcpy(pTemp, &m_iDustLevel, sizeof(m_iDustLevel));
	//	pTemp += sizeof(m_iDustLevel);
	//	memcpy(pTemp, &m_iRainLevel, sizeof(m_iRainLevel));
	//	pTemp += sizeof(m_iRainLevel);
	//	memcpy(pTemp, &m_iSnowLevel, sizeof(m_iSnowLevel));
	//	pTemp += sizeof(m_iSnowLevel);

	//	int num = m_vectEnvTime.size();
	//	memcpy(pTemp, &num, sizeof(int));
	//	pTemp += sizeof(int);

	//	for (int i=0; i<num; i++)
	//	{
	//		int dTimeElement;
	//		memcpy(pTemp, &dTimeElement, sizeof(dTimeElement));
	//		pTemp += sizeof(dTimeElement);
	//	}


	//	ST_INTENSITY_POS stiNtenStruct1;
	//	int number = m_vRadiantFog.size();
	//	memcpy(pTemp, &number, sizeof(number));
	//	pTemp += sizeof(number);

	//	ST_INTENSITY_POS stiNtenStruct2;
	//	for (int i = 0 ; i< number ; i++)
	//	{
	//		stiNtenStruct2 = m_vRadiantFog.at(i);
	//		pTemp = stiNtenStruct2.dumpToBuffer(pTemp);
	//	} 
	//	number = m_vSmoke.size();
	//	memcpy(pTemp, &number, sizeof(number));
	//	pTemp += sizeof(number);

	//	ST_INTENSITY_POS stiNtenStruct3;
	//	for (int i = 0 ; i< number ; i++)
	//	{
	//		stiNtenStruct3 = m_vSmoke.at(i);
	//		pTemp = stiNtenStruct3.dumpToBuffer(pTemp);
	//	} 
	//	memcpy(pTemp, &m_bFogOn, sizeof(m_bFogOn));
	//	pTemp += sizeof(m_bFogOn);
	//	memcpy(pTemp, &m_bHazeOn, sizeof(m_bHazeOn));
	//	pTemp += sizeof(m_bHazeOn);
	//	memcpy(pTemp, &m_bLightningOn, sizeof(m_bLightningOn));
	//	pTemp += sizeof(m_bLightningOn);
	//	memcpy(pTemp, &m_bRisenDustOn, sizeof(m_bRisenDustOn));
	//	pTemp += sizeof(m_bRisenDustOn);

	//	memcpy(pTemp, &m_bTriggerOneLightning, sizeof(m_bTriggerOneLightning));
	//	pTemp += sizeof(m_bTriggerOneLightning);

	//	pTemp = m_LightningInf.dumpToBuffer(pTemp);

	//	return pTemp;
	//}

	/*char* readFromBuffer(char *vBuffer)
	{
		char *pTemp = vBuffer;

		memcpy(&m_dTemperature, pTemp, sizeof(m_dTemperature));
		pTemp += sizeof(m_dTemperature);
		memcpy(&m_dVisibility, pTemp, sizeof(m_dVisibility));
		pTemp += sizeof(m_dVisibility);
		memcpy(&m_dWindDir, pTemp, sizeof(m_dWindDir));
		pTemp += sizeof(m_dWindDir);
		memcpy(&m_dWindSpd, pTemp, sizeof(m_dWindSpd));
		pTemp += sizeof(m_dWindSpd);
		m_strModelName.assign(pTemp);
		pTemp += m_strModelName.length() + 1;
		memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
		pTemp+=sizeof(m_iAirportID);

		memcpy(&m_iDustLevel, pTemp, sizeof(m_iDustLevel));
		pTemp+=sizeof(m_iDustLevel);
		memcpy(&m_iRainLevel, pTemp, sizeof(m_iRainLevel));
		pTemp+=sizeof(m_iRainLevel);
		memcpy(&m_iSnowLevel, pTemp, sizeof(m_iSnowLevel));
		pTemp+=sizeof(m_iSnowLevel);

		int num;
		memcpy(&num, pTemp, sizeof(int));
		pTemp += sizeof(int);
		int iTimeElement;
		m_vectEnvTime.clear();
		for (int i=0; i<num; ++i )
		{
			memcpy(&iTimeElement, pTemp, sizeof(iTimeElement));
			pTemp += sizeof(iTimeElement);
			m_vectEnvTime.push_back(iTimeElement);
		}

		memcpy(&num, pTemp, sizeof(num));
		pTemp += sizeof(num);

		ST_INTENSITY_POS stIntenSityStruct;	
		for (int i=0; i<num; i++)
		{
			pTemp = stIntenSityStruct.readFromBuffer(pTemp);
			m_vRadiantFog.push_back(stIntenSityStruct);
		}

		memcpy(&num, pTemp, sizeof(num));
		pTemp += sizeof(num);

		for (int i=0; i<num; i++)
		{
			pTemp = stIntenSityStruct.readFromBuffer(pTemp);
			m_vSmoke.push_back(stIntenSityStruct);
		}

		memcpy(&m_bFogOn, pTemp, sizeof(m_bFogOn));
		pTemp += sizeof(m_bFogOn);
		memcpy(&m_bHazeOn, pTemp, sizeof(m_bHazeOn));
		pTemp += sizeof(m_bHazeOn);
		memcpy(&m_bLightningOn, pTemp, sizeof(m_bLightningOn));
		pTemp += sizeof(m_bLightningOn);
		memcpy(&m_bRisenDustOn, pTemp, sizeof(m_bRisenDustOn));
		pTemp += sizeof(m_bRisenDustOn);

		memcpy(&m_bTriggerOneLightning, pTemp, sizeof(m_bTriggerOneLightning));
		pTemp += sizeof(m_bTriggerOneLightning);

		pTemp = m_LightningInf.readFromBuffer(pTemp);

		return pTemp;
	}*/
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAirportID & m_iRainLevel & m_iSnowLevel & m_bLightningOn 
			& m_bFogOn & m_bHazeOn & m_bRisenDustOn & m_iDustLevel & m_dWindSpd & m_dWindDir
			& m_dVisibility & m_dTemperature & m_vectEnvTime &m_strModelName &m_vSmoke 
			& m_vRadiantFog & m_bTriggerOneLightning & m_LightningInf;
	}
private:
	// ���������Ļ���
	int m_iAirportID;
	int m_iRainLevel;			/* ��������1~3����0�������� */
	int m_iSnowLevel;			/* ѩ������1~3����0������ѩ */

	//��ɳ�������ǿ��ͨ�������ܼ���������.
	bool		m_bLightningOn;		//�Ƿ�������,������,���Ӿ������.
	bool		m_bFogOn;				//�Ƿ���ȫ����. ǿ�ȵȼ�ͨ���ܼ���������
	bool        m_bHazeOn;
	bool		m_bRisenDustOn;		//�Ƿ�����ɳ, �������ٶ����ƶ���������ٷ������. ������ɳ��ͬʱ��������.

	////����������һ��������ɳ��ʱ����ϯλ�˺��Ӿ��������˵Ĵ���.��������һ�����ݲ��з��ͳ�ȥ.
	int		m_iDustLevel;			//����Ũ�ȵȼ�, 0����ʾû�и���.
	double  m_dWindSpd;		/* ���� Ĭ��0 */
	double  m_dWindDir;		/* ���� Ĭ��0 */

	double m_dVisibility; // �ܼ���
	double m_dTemperature; // �¶�
	std::vector<int> m_vectEnvTime;	//ѵ���ƻ���ǰʱ��:X��X��X��XʱX��X��

	std::string  m_strModelName;// the index of used airport model file name
	std::vector<ST_INTENSITY_POS> m_vSmoke;		//��---ǿ�Ⱥ�λ����Ϣ
	std::vector<ST_INTENSITY_POS> m_vRadiantFog; //������---ǿ�Ⱥ�λ����Ϣ
	bool				m_bTriggerOneLightning; //�Ƿ񴥷�һ������
	ST_INTENSITY_POS	m_LightningInf;	//��Ϊ�������������Ϣ

};