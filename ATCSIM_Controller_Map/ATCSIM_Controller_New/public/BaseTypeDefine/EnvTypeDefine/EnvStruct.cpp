#include "EnvStruct.h"
 //////////////////////////////////////////////////////////////////////////

ST_RUNWAY_ENV::ST_RUNWAY_ENV()
{
	dDewpoint = 0;
	dEndCBase = 0;
	dEndRVR = 0;
	dMidRVR = 0;
	dStartCBase = 0;
	dStartRVR = 0;
	dTemperature = 0;
	dWindDir = 0;
	dWindSpd = 0;
	iLight = 0;
	dQFE = 0;
	dQNH = 0;
	iRunwayID = 0;


	//lichun 2011.03.30
	dRandomWindSpd = 0;
	dRandomWindDir = 0;

	m_iIsGuestingWindSpd = 0;
	dWindMaxSpd = 0;
	dWindMinSpd = 0;
	dRandomWindMaxSpd = 0;
	dRandomWindMinSpd = 0;

	m_iIsGuestingWindDir = 0;
	m_iWindDirection = 0;
	m_dGuestingWindDir = 0;
	m_dGuestingRandomWindDir = 0;
	m_dFrictionNum=0;
}

ST_RUNWAY_ENV::ST_RUNWAY_ENV( ST_RUNWAY_ENV const& runwayEnv )
{
	dDewpoint = runwayEnv.dDewpoint;
	dEndCBase = runwayEnv.dEndCBase;
	dEndRVR = runwayEnv.dEndRVR;
	dMidRVR = runwayEnv.dMidRVR;
	dStartCBase = runwayEnv.dStartCBase;
	dStartRVR = runwayEnv.dStartRVR;
	dTemperature = runwayEnv.dTemperature;
	dWindDir = runwayEnv.dWindDir;
	dWindSpd = runwayEnv.dWindSpd;
	iLight = runwayEnv.iLight;
	dQFE = runwayEnv.dQFE;
	dQNH = runwayEnv.dQNH;
	iRunwayID = runwayEnv.iRunwayID;
	//lichun 2011.03.30
	dRandomWindSpd = runwayEnv.dRandomWindSpd;
	dRandomWindDir = runwayEnv.dRandomWindDir;

	m_iIsGuestingWindSpd = runwayEnv.m_iIsGuestingWindSpd;
	dWindMaxSpd = runwayEnv.dWindMaxSpd;
	dWindMinSpd = runwayEnv.dWindMinSpd;
	dRandomWindMaxSpd = runwayEnv.dRandomWindMaxSpd;
	dRandomWindMinSpd = runwayEnv.dRandomWindMinSpd;

	m_iIsGuestingWindDir  = runwayEnv.m_iIsGuestingWindDir;
	m_iWindDirection = runwayEnv.m_iWindDirection;
	m_dGuestingWindDir = runwayEnv.m_dGuestingWindDir;
	m_dGuestingRandomWindDir = runwayEnv.m_dGuestingRandomWindDir;
	m_dFrictionNum=runwayEnv.m_dFrictionNum;
}

ST_RUNWAY_ENV::~ST_RUNWAY_ENV()
{

}

ST_RUNWAY_ENV& ST_RUNWAY_ENV::operator=( ST_RUNWAY_ENV const& runwayEnv )
{
	dDewpoint = runwayEnv.dDewpoint;
	dEndCBase = runwayEnv.dEndCBase;
	dEndRVR = runwayEnv.dEndRVR;
	dMidRVR = runwayEnv.dMidRVR;
	dStartCBase = runwayEnv.dStartCBase;
	dStartRVR = runwayEnv.dStartRVR;
	dTemperature = runwayEnv.dTemperature;
	dWindDir = runwayEnv.dWindDir;
	dWindSpd = runwayEnv.dWindSpd;
	iLight = runwayEnv.iLight;
	dQFE = runwayEnv.dQFE;
	dQNH = runwayEnv.dQNH;
	iRunwayID = runwayEnv.iRunwayID;

	//lichun 2011.03.30
	dRandomWindSpd = runwayEnv.dRandomWindSpd;
	dRandomWindDir = runwayEnv.dRandomWindDir;

	m_iIsGuestingWindSpd = runwayEnv.m_iIsGuestingWindSpd;
	dWindMaxSpd = runwayEnv.dWindMaxSpd;
	dWindMinSpd = runwayEnv.dWindMinSpd;
	dRandomWindMaxSpd = runwayEnv.dRandomWindMaxSpd;
	dRandomWindMinSpd = runwayEnv.dRandomWindMinSpd;

	m_iIsGuestingWindDir = runwayEnv.m_iIsGuestingWindDir;
	m_iWindDirection = runwayEnv.m_iWindDirection;
	m_dGuestingWindDir = runwayEnv.m_dGuestingWindDir;
	m_dGuestingRandomWindDir = runwayEnv.m_dGuestingRandomWindDir;
     m_dFrictionNum=runwayEnv.m_dFrictionNum;
	return *this;
}
/*
void ST_RUNWAY_ENV::ReadFromBuffer( const char* pBuffer )
{
	const char *pTemp = pBuffer;

	memcpy(&dDewpoint, pTemp, sizeof(dDewpoint));
	pTemp += sizeof(dDewpoint);

	memcpy(&dEndCBase, pTemp, sizeof(dEndCBase));
	pTemp += sizeof(dEndCBase);

	memcpy(&dEndRVR, pTemp, sizeof(dEndRVR));
	pTemp += sizeof(dEndRVR);

	memcpy(&dMidRVR, pTemp, sizeof(dMidRVR));
	pTemp += sizeof(dMidRVR);

	memcpy(&dStartCBase, pTemp, sizeof(dStartCBase));
	pTemp += sizeof(dStartCBase);

	memcpy(&dStartRVR, pTemp, sizeof(dStartRVR));
	pTemp += sizeof(dStartRVR);

	memcpy(&dTemperature, pTemp, sizeof(dTemperature));
	pTemp += sizeof(dTemperature);

	memcpy(&dWindDir, pTemp, sizeof(dWindDir));
	pTemp += sizeof(dWindDir);

	memcpy(&dWindSpd, pTemp, sizeof(dWindSpd));
	pTemp += sizeof(dWindSpd);

	memcpy(&iLight, pTemp, sizeof(iLight));
	pTemp += sizeof(iLight);

	memcpy(&dQFE, pTemp, sizeof(dQFE));
	pTemp += sizeof(dQFE);

	memcpy(&dQNH, pTemp, sizeof(dQNH));
	pTemp += sizeof(dQNH);

	memcpy(&iRunwayID, pTemp, sizeof(iRunwayID));
	pTemp += sizeof(iRunwayID);
	//lichun 2011.03.30
	memcpy(&dRandomWindSpd, pTemp, sizeof(dRandomWindSpd));
	pTemp += sizeof(dRandomWindSpd);

	memcpy(&dRandomWindDir, pTemp, sizeof(dRandomWindDir));
	pTemp += sizeof(dRandomWindDir);

	memcpy(&m_iIsGuestingWindSpd, pTemp, sizeof(m_iIsGuestingWindSpd));
	pTemp += sizeof(m_iIsGuestingWindSpd);

	memcpy(&dWindMaxSpd, pTemp, sizeof(dWindMaxSpd));
	pTemp += sizeof(dWindMaxSpd);

	memcpy(&dWindMinSpd, pTemp, sizeof(dWindMinSpd));
	pTemp += sizeof(dWindMinSpd);

	memcpy(&dRandomWindMaxSpd, pTemp, sizeof(dRandomWindMaxSpd));
	pTemp += sizeof(dRandomWindMaxSpd);

	memcpy(&dRandomWindMinSpd, pTemp, sizeof(dRandomWindMinSpd));
	pTemp += sizeof(dRandomWindMinSpd);

	memcpy(&m_iIsGuestingWindDir, pTemp, sizeof(m_iIsGuestingWindDir));
	pTemp += sizeof(m_iIsGuestingWindDir);

	memcpy(&m_iWindDirection, pTemp, sizeof(m_iWindDirection));
	pTemp += sizeof(m_iWindDirection);

	memcpy(&m_dGuestingWindDir, pTemp, sizeof(m_dGuestingWindDir));
	pTemp += sizeof(m_dGuestingWindDir);

	memcpy(&m_dGuestingRandomWindDir, pTemp, sizeof(m_dGuestingRandomWindDir));
	pTemp += sizeof(m_dGuestingRandomWindDir);

	memcpy(&m_dFrictionNum,pTemp,sizeof(double));
	pTemp+=sizeof(double);
}

void ST_RUNWAY_ENV::WriteToBuffer( char* pBuffer )
{
	char *pTemp = pBuffer;

	memcpy(pTemp, &dDewpoint, sizeof(dDewpoint));
	pTemp += sizeof(dDewpoint);

	memcpy(pTemp, &dEndCBase, sizeof(dEndCBase));
	pTemp += sizeof(dEndCBase);

	memcpy(pTemp, &dEndRVR, sizeof(dEndRVR));
	pTemp += sizeof(dEndRVR);

	memcpy(pTemp, &dMidRVR, sizeof(dMidRVR));
	pTemp += sizeof(dMidRVR);

	memcpy(pTemp, &dStartCBase, sizeof(dStartCBase));
	pTemp += sizeof(dStartCBase);

	memcpy(pTemp, &dStartRVR, sizeof(dStartRVR));
	pTemp += sizeof(dStartRVR);

	memcpy(pTemp, &dTemperature, sizeof(dTemperature));
	pTemp += sizeof(dTemperature);

	memcpy(pTemp, &dWindDir, sizeof(dWindDir));
	pTemp += sizeof(dWindDir);

	memcpy(pTemp, &dWindSpd, sizeof(dWindSpd));
	pTemp += sizeof(dWindSpd);

	memcpy(pTemp, &iLight, sizeof(iLight));
	pTemp += sizeof(iLight);

	memcpy(pTemp, &dQFE, sizeof(dQFE));
	pTemp += sizeof(dQFE);

	memcpy(pTemp, &dQNH, sizeof(dQNH));
	pTemp += sizeof(dQNH);

	memcpy(pTemp, &iRunwayID, sizeof(iRunwayID));
	pTemp += sizeof(iRunwayID);


	//lichun 2011.03.30
	memcpy(pTemp, &dRandomWindSpd, sizeof(dRandomWindSpd));
	pTemp += sizeof(dRandomWindSpd);

	memcpy(pTemp, &dRandomWindDir, sizeof(dRandomWindDir));
	pTemp += sizeof(dRandomWindDir);

	memcpy(pTemp, &m_iIsGuestingWindSpd, sizeof(m_iIsGuestingWindSpd));
	pTemp += sizeof(m_iIsGuestingWindSpd);

	memcpy(pTemp, &dWindMaxSpd, sizeof(dWindMaxSpd));
	pTemp += sizeof(dWindMaxSpd);

	memcpy(pTemp, &dWindMinSpd, sizeof(dWindMinSpd));
	pTemp += sizeof(dWindMinSpd);

	memcpy(pTemp, &dRandomWindMaxSpd, sizeof(dRandomWindMaxSpd));
	pTemp += sizeof(dRandomWindMaxSpd);

	memcpy(pTemp, &dRandomWindMinSpd, sizeof(dRandomWindMinSpd));
	pTemp += sizeof(dRandomWindMinSpd);

	memcpy(pTemp, &m_iIsGuestingWindDir, sizeof(m_iIsGuestingWindDir));
	pTemp += sizeof(m_iIsGuestingWindDir);

	memcpy(pTemp, &m_iWindDirection, sizeof(m_iWindDirection));
	pTemp += sizeof(m_iWindDirection);

	memcpy(pTemp, &m_dGuestingWindDir, sizeof(m_dGuestingWindDir));
	pTemp += sizeof(m_dGuestingWindDir);

	memcpy(pTemp, &m_dGuestingRandomWindDir, sizeof(m_dGuestingRandomWindDir));
	pTemp += sizeof(m_dGuestingRandomWindDir);

	memcpy(pTemp,&m_dFrictionNum,sizeof(double));
	pTemp+=sizeof(double);
}

int ST_RUNWAY_ENV::GetBufferSize()
{
	int size = 0;

	size += sizeof(dDewpoint);
	size += sizeof(dEndCBase);
	size += sizeof(dEndRVR);
	size += sizeof(dMidRVR);
	size += sizeof(dStartCBase);
	size += sizeof(dStartRVR);
	size += sizeof(dTemperature);
	size += sizeof(dWindDir);
	size += sizeof(dWindSpd);
	size += sizeof(iLight);
	size += sizeof(dQFE);
	size += sizeof(dQNH);
	size += sizeof(iRunwayID);

	//lichun 2011.03.30
	size += sizeof(dRandomWindSpd);
	size += sizeof(dRandomWindDir);

	size += sizeof(m_iIsGuestingWindSpd);
	size += sizeof(dWindMaxSpd);
	size += sizeof(dWindMinSpd);
	size += sizeof(dRandomWindMaxSpd);
	size += sizeof(dRandomWindMinSpd);

	size += sizeof(m_iIsGuestingWindDir);
	size += sizeof(m_iWindDirection);
	size += sizeof(m_dGuestingWindDir);
	size += sizeof(m_dGuestingRandomWindDir);
	size+=sizeof(double);

	return size;
}
*/

ST_POS_INTENSITY::ST_POS_INTENSITY()
{
	iLevel = 0;	//默认没有强度,也就是没有这个特效
	dXPos = dYPos = dZPos = 0;
}

ST_POS_INTENSITY::ST_POS_INTENSITY( ST_POS_INTENSITY const& lightningInf )
{
	iLevel = lightningInf.iLevel;
	dXPos = lightningInf.dXPos;
	dYPos = lightningInf.dYPos;
	dZPos = lightningInf.dZPos;
}

ST_POS_INTENSITY& ST_POS_INTENSITY::operator=( ST_POS_INTENSITY const& lightningInf )
{
	iLevel = lightningInf.iLevel;
	dXPos = lightningInf.dXPos;
	dYPos = lightningInf.dYPos;
	dZPos = lightningInf.dZPos;
	return *this;
}

ST_POS_INTENSITY::~ST_POS_INTENSITY()
{

}

/*
//////////////////////////////////////////////////////////////////////////
ST_INTENSITY_POS::ST_INTENSITY_POS()
{
	iLevel = 0;	//默认没有强度,也就是没有这个特效
	dXPos = dYPos = dZPos = 0;
}

ST_INTENSITY_POS::ST_INTENSITY_POS( ST_INTENSITY_POS const& lightningInf )
{
	iLevel = lightningInf.iLevel;
	dXPos = lightningInf.dXPos;
	dYPos = lightningInf.dYPos;
	dZPos = lightningInf.dZPos;
}

ST_INTENSITY_POS& ST_INTENSITY_POS::operator=( ST_INTENSITY_POS const& lightningInf )
{
	iLevel = lightningInf.iLevel;
	dXPos = lightningInf.dXPos;
	dYPos = lightningInf.dYPos;
	dZPos = lightningInf.dZPos;
	return *this;
}

ST_INTENSITY_POS::~ST_INTENSITY_POS()
{

}

void ST_INTENSITY_POS::ReadFromBuffer( const char* pBuffer )
{
	const char* pTemp = pBuffer;

	memcpy(&iLevel, pTemp, sizeof(iLevel));
	pTemp += sizeof(iLevel);

	memcpy(&dXPos, pTemp, sizeof(dXPos));
	pTemp += sizeof(dXPos);

	memcpy(&dYPos, pTemp, sizeof(dYPos));
	pTemp += sizeof(dYPos);

	memcpy(&dZPos, pTemp, sizeof(dZPos));
	pTemp += sizeof(dZPos);
}

void ST_INTENSITY_POS::WriteToBuffer( char* pBuffer )
{
	char* pTemp = pBuffer;

	memcpy(pTemp, &iLevel, sizeof(iLevel));
	pTemp += sizeof(iLevel);

	memcpy(pTemp, &dXPos, sizeof(dXPos));
	pTemp += sizeof(dXPos);

	memcpy(pTemp, &dYPos, sizeof(dYPos));
	pTemp += sizeof(dYPos);

	memcpy(pTemp, &dZPos, sizeof(dZPos));
	pTemp += sizeof(dZPos);
}

int ST_INTENSITY_POS::GetBufferSize()
{
	int size = 0;

	size += sizeof(iLevel);
	size += sizeof(dXPos);
	size += sizeof(dYPos);
	size += sizeof(dZPos);

	return size;
}
*/
//////////////////////////////////////////////////////////////////////////

ST_AirportEnvBaseData::ST_AirportEnvBaseData()
{

}
ST_AirportEnvBaseData::~ST_AirportEnvBaseData()
{

}

ST_AirportEnvBaseData& ST_AirportEnvBaseData::operator=( ST_AirportEnvBaseData const& temp )
{
	this->m_envTime = temp.m_envTime;
	this->m_iAirportID = temp.m_iAirportID;
	this->m_iAirspaceID = temp.m_iAirspaceID;
	this->m_iDustLevel = temp.m_iDustLevel;

	this->m_iRainLevel = temp.m_iRainLevel;
	this->m_iSnowLevel = temp.m_iSnowLevel;

	this->m_strModelName = temp.m_strModelName;
	this->m_dDewpoint = temp.m_dDewpoint;
	this->m_dQFE = temp.m_dQFE;
	this->m_dQNH = temp.m_dQNH;
	this->m_dTemperature = temp.m_dTemperature;
	this->m_dVisibility = temp.m_dVisibility;
	this->m_dWindDir = temp.m_dWindDir;
	this->m_dWindSpd = temp.m_dWindSpd;

	m_bLightningOn = temp.m_bLightningOn;
	m_bFogOn = temp.m_bFogOn;
	m_bHazeOn = temp.m_bHazeOn;
	m_bRisenDustOn = temp.m_bRisenDustOn;

	m_vSmoke = temp.m_vSmoke;
	m_vRadiantFog = temp.m_vRadiantFog;

	return *this;
}

/*
void ST_AirportEnvBaseData::ReadFromBuffer( const char* pBuffer )
{
	const char* pTemp = pBuffer;

	memcpy(&m_dDewpoint, pTemp, sizeof(m_dDewpoint));
	pTemp += sizeof(m_dDewpoint);

	memcpy(&m_dQFE,pTemp,sizeof(m_dQFE));
	pTemp += sizeof(m_dQFE);
	memcpy(&m_dQNH,pTemp,sizeof(m_dQNH));
	pTemp += sizeof(m_dQNH);
	memcpy(&m_dTemperature,pTemp,sizeof(m_dTemperature));
	pTemp += sizeof(m_dTemperature);
	memcpy(&m_dVisibility,pTemp,sizeof(m_dVisibility));
	pTemp += sizeof(m_dVisibility);
	memcpy(&m_dWindDir,pTemp,sizeof(m_dWindDir));
	pTemp += sizeof(m_dWindDir);
	memcpy(&m_dWindSpd,pTemp,sizeof(m_dWindSpd));
	pTemp += sizeof(m_dWindSpd);
	m_strModelName.assign(pTemp);
	pTemp += m_strModelName.length() + 1;
	memcpy(&m_iAirportID, pTemp, sizeof(m_iAirportID));
	pTemp+=sizeof(m_iAirportID);
	memcpy(&m_iAirspaceID, pTemp, sizeof(m_iAirspaceID));
	pTemp+=sizeof(m_iAirspaceID);
	memcpy(&m_iDustLevel, pTemp, sizeof(m_iDustLevel));
	pTemp+=sizeof(m_iDustLevel);
	memcpy(&m_iRainLevel, pTemp, sizeof(m_iRainLevel));
	pTemp+=sizeof(m_iRainLevel);
	memcpy(&m_iSnowLevel, pTemp, sizeof(m_iSnowLevel));
	pTemp+=sizeof(m_iSnowLevel);

	int num;
	memcpy(&num, pTemp, sizeof(int));
	pTemp += sizeof(int);

	for (int i=0; i<num; i++)
	{
		int dTimeElement;
		memcpy(&dTimeElement, pTemp, sizeof(dTimeElement));
		pTemp += sizeof(dTimeElement);
		m_envTime.push_back(dTimeElement);
	}

	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	for (int i=0; i<num; i++)
	{
		ST_INTENSITY_POS stIntenSityStruct;	
		stIntenSityStruct.ReadFromBuffer(pTemp);
		pTemp += stIntenSityStruct.GetBufferSize();	
		m_vRadiantFog.push_back(stIntenSityStruct);
	}

	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	for (int i=0; i<num; i++)
	{
		ST_INTENSITY_POS stIntenSityStruct;	
		stIntenSityStruct.ReadFromBuffer(pTemp);
		pTemp += stIntenSityStruct.GetBufferSize();	
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
}

void ST_AirportEnvBaseData::WriteToBuffer( char* pBuffer )
{
	char* pTemp = pBuffer;

	memcpy(pTemp, &m_dDewpoint, sizeof(m_dDewpoint));
	pTemp += sizeof(m_dDewpoint);
	memcpy(pTemp, &m_dQFE, sizeof(m_dQFE));
	pTemp += sizeof(m_dQFE);
	memcpy(pTemp, &m_dQNH, sizeof(m_dQNH));
	pTemp += sizeof(m_dQNH);
	memcpy(pTemp, &m_dTemperature, sizeof(m_dTemperature));
	pTemp += sizeof(m_dTemperature);
	memcpy(pTemp, &m_dVisibility, sizeof(m_dVisibility));
	pTemp += sizeof(m_dVisibility);
	memcpy(pTemp, & m_dWindDir, sizeof( m_dWindDir));
	pTemp += sizeof( m_dWindDir);
	memcpy(pTemp, & m_dWindSpd, sizeof( m_dWindSpd));
	pTemp += sizeof( m_dWindSpd);
	memcpy(pTemp, m_strModelName.c_str(), m_strModelName.length()+1);
	pTemp += m_strModelName.length()+1;

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);
	memcpy(pTemp, &m_iAirspaceID, sizeof(m_iAirspaceID));
	pTemp += sizeof(m_iAirspaceID);
	memcpy(pTemp, &m_iDustLevel, sizeof(m_iDustLevel));
	pTemp += sizeof(m_iDustLevel);
	memcpy(pTemp, &m_iRainLevel, sizeof(m_iRainLevel));
	pTemp += sizeof(m_iRainLevel);
	memcpy(pTemp, &m_iSnowLevel, sizeof(m_iSnowLevel));
	pTemp += sizeof(m_iSnowLevel);

	int num = m_envTime.size();
	memcpy(pTemp, &num, sizeof(int));
	pTemp += sizeof(int);

	for (int i=0; i<num; i++)
	{
		memcpy(pTemp, &m_envTime.at(i), sizeof(int));
		pTemp += sizeof(int);
	}



	ST_INTENSITY_POS stiNtenStruct1;
	int number = m_vRadiantFog.size();
	memcpy(pTemp, &number, sizeof(number));
	pTemp += sizeof(number);

	ST_INTENSITY_POS stiNtenStruct2;
	for (int i = 0 ; i< number ; i++)
	{
		stiNtenStruct2 = m_vRadiantFog.at(i);
		stiNtenStruct2.WriteToBuffer(pTemp);
		pTemp += stiNtenStruct2.GetBufferSize();
	} 
	number = m_vSmoke.size();
	memcpy(pTemp, &number, sizeof(number));
	pTemp += sizeof(number);

	ST_INTENSITY_POS stiNtenStruct3;
	for (int i = 0 ; i< number ; i++)
	{
		stiNtenStruct3 = m_vSmoke.at(i);
		stiNtenStruct3.WriteToBuffer(pTemp);
		pTemp += stiNtenStruct3.GetBufferSize();
	} 
	memcpy(pTemp, &m_bFogOn, sizeof(m_bFogOn));
	pTemp += sizeof(m_bFogOn);
	memcpy(pTemp, &m_bHazeOn, sizeof(m_bHazeOn));
	pTemp += sizeof(m_bHazeOn);
	memcpy(pTemp, &m_bLightningOn, sizeof(m_bLightningOn));
	pTemp += sizeof(m_bLightningOn);
	memcpy(pTemp, &m_bRisenDustOn, sizeof(m_bRisenDustOn));
	pTemp += sizeof(m_bRisenDustOn);
}

int ST_AirportEnvBaseData::GetBufferSize()
{
	int size = 0;

	size += sizeof(m_dDewpoint);
	size += sizeof(m_dQFE);
	size += sizeof(m_dQNH);
	size += sizeof(m_dTemperature);
	size += sizeof(m_dVisibility);
	size += sizeof(m_dWindDir);
	size += sizeof(m_dWindSpd);
	size += m_strModelName.length()+1;
	size += sizeof(m_iAirportID);
	size += sizeof(m_iAirspaceID);
	size += sizeof(m_iDustLevel);
	size += sizeof(m_iRainLevel);
	size += sizeof(m_iSnowLevel);

	int num = m_envTime.size();
	size += sizeof(int);

	for (vector<int>::size_type i=0; i<m_envTime.size(); i++)
	{
		size += sizeof(int);
	}

	num = m_vRadiantFog.size();
	size += sizeof(num);	
	for (vector<ST_INTENSITY_POS>::size_type i=0; i<m_vRadiantFog.size(); i++)
	{
		size += (m_vRadiantFog.at(i).GetBufferSize());
	}

	num = m_vSmoke.size();
	size += sizeof(num);	
	for (vector<ST_INTENSITY_POS>::size_type i=0; i<m_vSmoke.size(); i++)
	{
		size += (m_vSmoke.at(i).GetBufferSize());
	}
	size += sizeof(m_bFogOn);
     size += sizeof(m_bHazeOn);
	size += sizeof(m_bLightningOn);
	size += sizeof(m_bRisenDustOn);
	return size;
}
*/

//////////////////////////////////////////////////////////////////////////

ST_AirportEnvForEnvPacket::ST_AirportEnvForEnvPacket()
{
	
}

ST_AirportEnvForEnvPacket::~ST_AirportEnvForEnvPacket()
{

}
ST_AirportEnvForEnvPacket & ST_AirportEnvForEnvPacket::operator=( ST_AirportEnvForEnvPacket const& temp )
{
	std::vector<ST_RUNWAY_ENV>::const_iterator iter = temp.m_vRunwayEnv.begin();
	//ST_RUNWAY_ENV tempEnv;
	this->m_vRunwayEnv.clear();
	for (;iter != temp.m_vRunwayEnv.end();iter++)
	{
		//tempEnv.dDewpoint = iter->dDewpoint;
		//tempEnv.dEndCBase = iter->dEndCBase;
		//tempEnv.dEndRVR = iter->dEndRVR;
		//tempEnv.dMidRVR = iter->dMidRVR;
		//tempEnv.dStartCBase = iter->dStartCBase;
		//tempEnv.dStartRVR = iter->dStartRVR;
		//tempEnv.dTemperature = iter->dTemperature;
		//tempEnv.dWindDir = iter->dWindDir;
		//tempEnv.dWindSpd = iter->dWindSpd;
		//tempEnv.iRunwayID = iter->iRunwayID;
		//tempEnv.iLight = iter->iLight;
		//tempEnv.dQFE = iter->dQFE;
 	//	tempEnv.dQNH = iter->dQNH;
		//tempEnv.dRandomWindSpd = iter->dRandomWindSpd;
		//tempEnv.dRandomWindDir = iter->dRandomWindDir;
		//tempEnv.m_iIsGuestingWindSpd = iter->m_iIsGuestingWindSpd;
		//tempEnv.dRandomWindMaxSpd = iter->dRandomWindMaxSpd;
		//tempEnv.dRandomWindMinSpd = iter->dRandomWindMinSpd;
	
		//tempEnv.m_iIsGuestingWindDir = iter->m_iIsGuestingWindDir;
		//tempEnv.m_iWindDirection = iter->m_iWindDirection;
		//tempEnv.m_dGuestingWindDir = iter->m_dGuestingWindDir;
		//tempEnv.m_dGuestingRandomWindDir = iter->m_dGuestingRandomWindDir;
		
		this->m_vRunwayEnv.push_back(*iter);
	}
	m_airportEnvBaseData = temp.m_airportEnvBaseData;
	return *this;
}

/*
void ST_AirportEnvForEnvPacket::ReadFromBuffer( const char* pBuffer )
{
	const char *pTemp =pBuffer;

	m_airportEnvBaseData.ReadFromBuffer(pTemp);
	pTemp += m_airportEnvBaseData.GetBufferSize();

	int num;
	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	for(int i=0; i<num; i++)
	{
		ST_RUNWAY_ENV runwayEnv;

		runwayEnv.ReadFromBuffer(pTemp);
		pTemp += runwayEnv.GetBufferSize();
		m_vRunwayEnv.push_back(runwayEnv);

	}
}

void ST_AirportEnvForEnvPacket::WriteToBuffer( char* pBuffer )
{
	char *pTemp =pBuffer;

	m_airportEnvBaseData.WriteToBuffer(pTemp);
	pTemp += m_airportEnvBaseData.GetBufferSize();

	int num = m_vRunwayEnv.size();
	memcpy(pTemp, &num, sizeof(num));
	pTemp += sizeof(num);

	for(int i=0; i<num; i++)
	{
		ST_RUNWAY_ENV runwayEnv = m_vRunwayEnv.at(i);

		runwayEnv.WriteToBuffer(pTemp);
		pTemp += runwayEnv.GetBufferSize();

	}
}

int ST_AirportEnvForEnvPacket::GetBufferSize()
{
	int size = 0;

	size += m_airportEnvBaseData.GetBufferSize();

	int num =m_vRunwayEnv.size();	
	size += sizeof(num);

	for (int i=0; i<num; i++)
	{
		size += (m_vRunwayEnv.at(i).GetBufferSize());
	}

	return size;
}
*/
/*
//////////////////////////////////////////////////////////////////////////
ST_AirportEnvForVisServer::ST_AirportEnvForVisServer()
{
	m_bTriggerOneLightning = false;
}

ST_AirportEnvForVisServer::~ST_AirportEnvForVisServer()
{

}

ST_AirportEnvForVisServer& ST_AirportEnvForVisServer::operator=( ST_AirportEnvForVisServer const& temp )
{
	m_bTriggerOneLightning = temp.m_bTriggerOneLightning;
	m_LightningInf = temp.m_LightningInf;
	m_airportEnvBaseData = temp.m_airportEnvBaseData;
	return *this;
}
*/
/*
void ST_AirportEnvForVisServer::ReadFromBuffer( const char* pBuffer )
{
	const char* pTemp = pBuffer;

	m_airportEnvBaseData.ReadFromBuffer(pTemp);
	pTemp += m_airportEnvBaseData.GetBufferSize();

	memcpy(&m_bTriggerOneLightning, pTemp, sizeof(m_bTriggerOneLightning));
	pTemp += sizeof(m_bTriggerOneLightning);

	m_LightningInf.ReadFromBuffer(pTemp);
	pTemp += m_LightningInf.GetBufferSize();
}

void ST_AirportEnvForVisServer::WriteToBuffer( char* pBuffer )
{
	char* pTemp = pBuffer;

	m_airportEnvBaseData.WriteToBuffer(pTemp);
	pTemp += m_airportEnvBaseData.GetBufferSize();

	memcpy(pTemp, &m_bTriggerOneLightning, sizeof(m_bTriggerOneLightning));
	pTemp += sizeof(m_bTriggerOneLightning);

	m_LightningInf.WriteToBuffer(pTemp);
	pTemp += m_LightningInf.GetBufferSize();
}

int ST_AirportEnvForVisServer::GetBufferSize()
{
	int size = 0;

	size += m_airportEnvBaseData.GetBufferSize();

	size += sizeof(m_bTriggerOneLightning);
	size += m_LightningInf.GetBufferSize();

	return size;
}
*/
//--------------------------------------视景专用的EnvBaseData------------------------------------
/*
ST_AirportEnvBaseData_VS::ST_AirportEnvBaseData_VS()
{

}
ST_AirportEnvBaseData_VS::~ST_AirportEnvBaseData_VS()
{

}

ST_AirportEnvBaseData_VS& ST_AirportEnvBaseData_VS::operator=( ST_AirportEnvBaseData_VS const& temp )
{
	this->m_envTime = temp.m_envTime;
	this->m_iAirportID = temp.m_iAirportID;
	this->m_iDustLevel = temp.m_iDustLevel;

	this->m_iRainLevel = temp.m_iRainLevel;
	this->m_iSnowLevel = temp.m_iSnowLevel;

	this->m_strModelName = temp.m_strModelName;
	this->m_dTemperature = temp.m_dTemperature;
	this->m_dVisibility = temp.m_dVisibility;
	this->m_dWindDir = temp.m_dWindDir;
	this->m_dWindSpd = temp.m_dWindSpd;

	m_bLightningOn = temp.m_bLightningOn;
	m_bFogOn = temp.m_bFogOn;
	m_bHazeOn = temp.m_bHazeOn;
	m_bRisenDustOn = temp.m_bRisenDustOn;

	m_vSmoke = temp.m_vSmoke;
	m_vRadiantFog = temp.m_vRadiantFog;

	return *this;
}
*/
/*
void ST_AirportEnvBaseData_VS::ReadFromBuffer( const char* pBuffer )
{
	const char* pTemp = pBuffer;

	memcpy(&m_dTemperature,pTemp,sizeof(m_dTemperature));
	pTemp += sizeof(m_dTemperature);
	memcpy(&m_dVisibility,pTemp,sizeof(m_dVisibility));
	pTemp += sizeof(m_dVisibility);
	memcpy(&m_dWindDir,pTemp,sizeof(m_dWindDir));
	pTemp += sizeof(m_dWindDir);
	memcpy(&m_dWindSpd,pTemp,sizeof(m_dWindSpd));
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

	for (int i=0; i<num; i++)
	{
		int dTimeElement;
		memcpy(&dTimeElement, pTemp, sizeof(dTimeElement));
		pTemp += sizeof(dTimeElement);
		m_envTime.push_back(dTimeElement);
	}


	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	for (int i=0; i<num; i++)
	{
		ST_INTENSITY_POS stIntenSityStruct;	
		stIntenSityStruct.ReadFromBuffer(pTemp);
		pTemp += stIntenSityStruct.GetBufferSize();	
		m_vRadiantFog.push_back(stIntenSityStruct);
	}

	memcpy(&num, pTemp, sizeof(num));
	pTemp += sizeof(num);

	for (int i=0; i<num; i++)
	{
		ST_INTENSITY_POS stIntenSityStruct;	
		stIntenSityStruct.ReadFromBuffer(pTemp);
		pTemp += stIntenSityStruct.GetBufferSize();	
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
}

void ST_AirportEnvBaseData_VS::WriteToBuffer( char* pBuffer )
{
	char* pTemp = pBuffer;

	memcpy(pTemp, &m_dTemperature, sizeof(m_dTemperature));
	pTemp += sizeof(m_dTemperature);
	memcpy(pTemp, &m_dVisibility, sizeof(m_dVisibility));
	pTemp += sizeof(m_dVisibility);
	memcpy(pTemp, & m_dWindDir, sizeof( m_dWindDir));
	pTemp += sizeof( m_dWindDir);
	memcpy(pTemp, & m_dWindSpd, sizeof( m_dWindSpd));
	pTemp += sizeof( m_dWindSpd);
	memcpy(pTemp, m_strModelName.c_str(), m_strModelName.length()+1);
	pTemp += m_strModelName.length()+1;

	memcpy(pTemp, &m_iAirportID, sizeof(m_iAirportID));
	pTemp += sizeof(m_iAirportID);

	memcpy(pTemp, &m_iDustLevel, sizeof(m_iDustLevel));
	pTemp += sizeof(m_iDustLevel);
	memcpy(pTemp, &m_iRainLevel, sizeof(m_iRainLevel));
	pTemp += sizeof(m_iRainLevel);
	memcpy(pTemp, &m_iSnowLevel, sizeof(m_iSnowLevel));
	pTemp += sizeof(m_iSnowLevel);



	int num = m_envTime.size();
	memcpy(pTemp, &num, sizeof(int));
	pTemp += sizeof(int);

	for (int i=0; i<num; i++)
	{
		memcpy(pTemp, &m_envTime.at(i), sizeof(int));
		pTemp += sizeof(int);
	}


	ST_INTENSITY_POS stiNtenStruct1;
	int number = m_vRadiantFog.size();
	memcpy(pTemp, &number, sizeof(number));
	pTemp += sizeof(number);

	ST_INTENSITY_POS stiNtenStruct2;
	for (int i = 0 ; i< number ; i++)
	{
		stiNtenStruct2 = m_vRadiantFog.at(i);
		stiNtenStruct2.WriteToBuffer(pTemp);
		pTemp += stiNtenStruct2.GetBufferSize();
	} 
	number = m_vSmoke.size();
	memcpy(pTemp, &number, sizeof(number));
	pTemp += sizeof(number);

	ST_INTENSITY_POS stiNtenStruct3;
	for (int i = 0 ; i< number ; i++)
	{
		stiNtenStruct3 = m_vSmoke.at(i);
		stiNtenStruct3.WriteToBuffer(pTemp);
		pTemp += stiNtenStruct3.GetBufferSize();
	} 
	memcpy(pTemp, &m_bFogOn, sizeof(m_bFogOn));
	pTemp += sizeof(m_bFogOn);
	memcpy(pTemp, &m_bHazeOn, sizeof(m_bHazeOn));
	pTemp += sizeof(m_bHazeOn);

	memcpy(pTemp, &m_bLightningOn, sizeof(m_bLightningOn));
	pTemp += sizeof(m_bLightningOn);
	memcpy(pTemp, &m_bRisenDustOn, sizeof(m_bRisenDustOn));
	pTemp += sizeof(m_bRisenDustOn);
}

int ST_AirportEnvBaseData_VS::GetBufferSize()
{
	int size = 0;

	size += sizeof(m_dTemperature);
	size += sizeof(m_dVisibility);
	size += sizeof(m_dWindDir);
	size += sizeof(m_dWindSpd);
	size += m_strModelName.length()+1;
	size += sizeof(m_iAirportID);
	size += sizeof(m_iDustLevel);
	size += sizeof(m_iRainLevel);
	size += sizeof(m_iSnowLevel);

	int num = m_envTime.size();
	size += sizeof(int);

	for (vector<int>::size_type i=0; i<m_envTime.size(); i++)
	{
		size += sizeof(int);
	}


	int num2 = m_vRadiantFog.size();
	size += sizeof(num2);	
	for (vector<ST_INTENSITY_POS>::size_type i=0; i<m_vRadiantFog.size(); i++)
	{
		size += (m_vRadiantFog.at(i).GetBufferSize());
	}

	int num3 = m_vSmoke.size();
	size += sizeof(num3);	
	for (vector<ST_INTENSITY_POS>::size_type i=0; i<m_vSmoke.size(); i++)
	{
		size += (m_vSmoke.at(i).GetBufferSize());
	}
	size += sizeof(m_bFogOn);
	size += sizeof(m_bHazeOn);
	size += sizeof(m_bLightningOn);
	return size;
}
*/
