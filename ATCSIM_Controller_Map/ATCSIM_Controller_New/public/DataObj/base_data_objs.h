//!���ļ��ж������������صĶ����࣬�������¶���
//!����         AircraftData
//!����         Vehicle


#ifndef _H_BASE_DATA_OBJS_H
#define _H_BASE_DATA_OBJS_H
#include "DataObj.h"

class AltSimulate;
class SpdSimulate;
class FlyEnvelope;
class LandPhase;
class PhaseOnRunway ;


class AircraftPerformance : public DataObj
{
public:
	AircraftPerformance();
	~AircraftPerformance();
	virtual int GetId();
	virtual string GetDisplayLabel();

	int m_iAircraftPerformaceID;
	//!<-��������
	std::string m_strName;
	std::string m_strNameICAO;			//!<ICAO����
	bool m_bIsAirscrew;						//!<�Ƿ���������
	bool m_bIsHelicopter;					//!<�Ƿ���ֱ����
	int m_iWheelType;							//!<�ɻ���������ʽ0��ʾ����ʽ,1��ʾѩ��ʽ,2(ˮ�Ϸɻ�)
	int m_iEngineCount;					//!<��������
	std::string m_strWakeType;			//!<β������	H M L
	std::string m_strTypeBySpeed;			//!<�ɻ����ͣ��������ܵ�����ٶȻ���(A/B/C{C1,C2,C3,C4}/D)

	std::string  m_dWeight ;						//!�ɻ�Ȩ������ H M L
	double	 m_dSizeWidth;							 //!<���
	double	 m_dSizeLength;						 //!<����
	double   m_dSizeHeight;						 //!<�߶�
	double	 m_dDisFrontRearWheel;			 //!<ǰ���־�
	double	 m_dDisBetweenRearWheel;       //!<�����־�
	double	 m_dGearHeight;						 //!<����ܸ߶�
	double	 m_dDisFrontWheel2Nose;			 //!<ǰ�ֵ���ͷ����
	double   m_dDisRearWheel2Tail;			//!<������ܵ�β������

	//!<-���в���
	double m_dMaxTaxBrakeDis;					//!<���ɲ������
	double m_dMaxTaxAcc;							//!<���������ٶ�
	double m_dMaxTaxDec;							//!<���������ٶ�
	double m_dMaxFrontGearTurnAngle;		//!<���ǰ��ƫת�Ƕ�
	double m_dMaxTaxSpd;							//!<������ٶ�
	double m_dNormalTaxSpd;						//!<���������ٶ�
	double m_dTaxTurnSpd;							//!<��ֹת���ٶ�
	double m_dDisFollowMe;							//!<�����û��ͺ���ķɻ�Ҫ���ֵļ��

	double m_dPushbackSpd;							//!<���Ƴ����ߵ��ٶ�
	double m_dAttachDis;								//!<�Ƴ���ǰ�ֵľ���

	
	int		 m_iEngineStartDelayMin;		//!<����ʱ��
	int		 m_iEngineStartDelayMax;		//!<����ʱ��
	int		 m_iEngineShutDelayMin;		//!<�س�ʱ��
	int		 m_iEngineShutDelayMax;		//!<�س�ʱ��

	//!<-��ɽ׶�
	double m_dLaunchFromParkMin;		//!<�Ӿ�ֹ����ʼ���������ʱ��
	double m_dLaunchFromParkMax;		//!<�Ӿ�ֹ����ʼ�������ʱ��
	double m_dLaunchLiftFrontGearSpd;	//!<��ǰ��ʱ���ٶ�
	double m_dLaunchLiftSpd;				//!<����ٶ�
	double m_dLaunchDecisionSpd;		//!<��ɾ����ٶ�
	double m_dLaunchEndIasMin;			//!<��ɽ���ʱ����С�ٶ�
	double m_dLaunchEndIasMax;			//!<��ɽ���ʱ������ٶ�	
	double m_dLaunchEndAltMin;			//!<��ɽ���ʱ����С�߶�
	double m_dLaunchEndAltMax;			//!<��ɽ���ʱ�����߶�
	double m_dLaunchElvAngle;				//!<�������
	double m_dLaunchPitchRate;			//!<���������
	double m_dLaunchBreakDec;			//!<�ж���ɺ���ٶ�

	double m_dLaunchLiftFrontGearAccLightMin;		//!<������ʱ����̧ǰ�ֵļ��ٶȣ���Сֵ
	double m_dLaunchLiftFrontGearAccLightMax;		//!<������ʱ����̧ǰ�ֵļ��ٶȣ����ֵ
	double m_dLaunchLiftFrontGearAccMidMin;			//!<������ʱ����̧ǰ�ֵļ��ٶȣ���Сֵ
	double m_dLaunchLiftFrontGearAccMidMax;		//!<������ʱ����̧ǰ�ֵļ��ٶȣ����ֵ
	double m_dLaunchLiftFrontGearAccHeavyMin;		//!<������ʱ����̧ǰ�ֵļ��ٶȣ���Сֵ
	double m_dLaunchLiftFrontGearAccHeavyMax;		//!<������ʱ����̧ǰ�ֵļ��ٶȣ����ֵ
	double m_dLaunchLiftAccLightMin;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ���Сֵ
	double m_dLaunchLiftAccLightMax;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ����ֵ
	double m_dLaunchLiftAccMidMin;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ���Сֵ
	double m_dLaunchLiftAccMidMax;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ����ֵ
	double m_dLaunchLiftAccHeavyMin;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ���Сֵ
	double m_dLaunchLiftAccHeavyMax;						//!<������ʱ����̧ǰ�ֵ���صļ��ٶȣ����ֵ

	double m_dLaunchEndClimbRate;							//!<���������
	double m_dLaunchEndAcc;									//!<����ٶ�ʱ���ٶ�

	//!<-�������
	double m_dApproachIasMin;									//!<�����ٶȣ���С
	double m_dApproachIasMax;								//!<�����ٶȣ����
	double m_dNormalLandSpdMin;							//!<������½�ٶȣ���С
	double m_dNormalLandSpdMax;							//!<������½�ٶȣ����
	double m_dLandTouchDistanceMin;						//!<�ӵؾ��룬��С
	double m_dLandTouchDistanceMax;						//!<�ӵؾ��룬���
	double m_dLandReflyHeightMin;							//!<���ɸ߶ȣ���С
	double m_dLandReflyHeightMax;							//!<���ɸ߶ȣ����
	double	m_dTaxMinAcc ;										//!���滬����С���ٶ�
	double	m_dTaxMinDec ;										//!���滬����С���ٶ�


	double m_dLandVref;											//!<��ƽʱ���ٶ�
	double m_dLandRefHeight;									//!<��ƽʱ�߶�
	double m_dLandElvAngle;										//!<��ƽʱ�Ƕ�
	double m_dLandElvAngleRate;								//!<��ƽʱ�Ƕ���

	double m_dVacateSpd;											//!<�����ٶ�

	//!<-���в���
	double m_dNormalTurnBank;								//!<ת���¶ȣ���������λ����
	double m_dMaxTurnBank;									//!<ת���¶ȣ���󣬵�λ����
	double m_dNormalRollRate;									//!<���ú���ʣ���λ����/��
	double m_dNormalPitch;										//!<�������ǣ���λ����
	double m_dNormalPitchRate;								//!<���������ʣ���λ����/��

	double m_dAltitudeUplimit;									//!<����
	double m_dMinCruisingAltitude;							//!<Ѳ���߶ȣ���С
	double m_dNormalCruisingAltitude;						//!<Ѳ���߶ȣ�����
	double m_dMaxCruisingAltitude;							//!<Ѳ���߶ȣ����

	double m_dMinCruisingMach;						//!<Ѳ����գ����
	double m_dNormalCruisingMach;					//!<Ѳ����գ�����
	double m_dMaxCruisingMach;						//!<Ѳ����գ����

	double m_dMiddleLevel;							//!<�߶Ȳ�

	vector<boost::shared_ptr<AltSimulate> > m_vAltSimulate;    //!�߶�ģ��
	vector<boost::shared_ptr<SpdSimulate> > m_vSpdSimulate; //!�ٶ�ģ��
	vector<boost::shared_ptr<FlyEnvelope> > m_vFlyEnvelope;   //!���а���
	vector<boost::shared_ptr<PhaseOnRunway> > m_vPhase;      //!�½��׶�
	std::vector<int> m_vCompanys; //!�û��͵ĺ��չ�˾ID


	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{

		return ar & m_iAircraftPerformaceID & m_strName & m_strNameICAO			
			& m_bIsAirscrew & m_bIsHelicopter & m_iWheelType & m_iEngineCount
			& m_strWakeType & m_strTypeBySpeed  & m_dWeight & m_dSizeWidth & m_dSizeLength & m_dSizeHeight & m_dDisFrontRearWheel
			& m_dDisBetweenRearWheel & m_dGearHeight & m_dDisFrontWheel2Nose & m_dDisRearWheel2Tail & m_dMaxTaxBrakeDis & m_dMaxTaxAcc
			& m_dMaxTaxDec & m_dMaxFrontGearTurnAngle & m_dMaxTaxSpd
			& m_dNormalTaxSpd & m_dTaxTurnSpd & m_dDisFollowMe & m_dPushbackSpd
			& m_dAttachDis & m_iEngineStartDelayMin & m_iEngineStartDelayMax
			& m_iEngineShutDelayMin & m_iEngineShutDelayMax & m_dLaunchFromParkMin
			& m_dLaunchFromParkMax & m_dLaunchLiftFrontGearSpd & m_dLaunchLiftSpd
			& m_dLaunchDecisionSpd & m_dLaunchEndIasMin & m_dLaunchEndIasMax
			& m_dLaunchEndAltMin & m_dLaunchEndAltMax & m_dLaunchElvAngle
			& m_dLaunchPitchRate & m_dLaunchBreakDec & m_dLaunchLiftFrontGearAccLightMin
			& m_dLaunchLiftFrontGearAccLightMax & m_dLaunchLiftFrontGearAccMidMin
			& m_dLaunchLiftFrontGearAccMidMax & m_dLaunchLiftFrontGearAccHeavyMin & m_dLaunchLiftFrontGearAccHeavyMax
			& m_dLaunchLiftAccLightMin & m_dLaunchLiftAccLightMax & m_dLaunchLiftAccMidMin & m_dLaunchLiftAccMidMax
			& m_dLaunchLiftAccHeavyMin & m_dLaunchLiftAccHeavyMax & m_dLaunchEndClimbRate & m_dLaunchEndAcc
			& m_dApproachIasMin & m_dApproachIasMax & m_dNormalLandSpdMin & m_dNormalLandSpdMax & m_dLandTouchDistanceMin
			& m_dLandTouchDistanceMax & m_dLandReflyHeightMin & m_dLandReflyHeightMax & m_dTaxMinAcc & m_dTaxMinDec 
			& m_dLandVref & m_dLandRefHeight
			& m_dLandElvAngle & m_dLandElvAngleRate & m_dVacateSpd & m_dNormalTurnBank & m_dMaxTurnBank & m_dNormalRollRate
			& m_dNormalPitch & m_dNormalPitchRate & m_dAltitudeUplimit & m_dMinCruisingAltitude & m_dNormalCruisingAltitude
			& m_dMaxCruisingAltitude & m_dMinCruisingMach & m_dNormalCruisingMach & m_dMaxCruisingMach & m_dMiddleLevel 
			& m_vAltSimulate & m_vSpdSimulate & m_vFlyEnvelope & m_vPhase & m_vCompanys;
	}

};



class	AltSimulate : public DataObj
{
	public:
	AltSimulate();
	~AltSimulate();
	virtual int GetId();
		virtual int GetOwnerId();
	int		m_iAltsimulateId ;						//!�߶�ģ��ID
	int		m_iAircraftPerformanceId ;		//!����ID
	std::string  m_strCtype ;							//!d�½� c����
	double  m_dTopAltitude ;						//!�߶Ȳ������ 
	double  m_dBottomAltitude ;				//!�߶Ȳ������
	double  m_dMinCdRate ;						//!��С�����ʻ���С�½���
	double  m_dMaxCdRate ;					    //!��������ʻ�����½���
	double  m_dSlowCdRate ;						//!�������ʻ����½���
	double  m_dNormalCdRate ;				    //!���������ʻ������½���
	double  m_dExpediteCdRate ;			    //!�������ʻ���½���
	double  m_dNormalCdRateMin ;		    //!���������ʣ����½��ʣ���Χ����Сֵ
	double  m_dNormalCdRateMax ;		    //!���������ʣ����½��ʣ���Χ�����ֵ
	double	m_dLimitIas				;				//!�߶�ģ����ȱ�����Ʊ���
	std::string m_strWeightType;						//!��������	H M L

	template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar &  m_iAltsimulateId & m_iAircraftPerformanceId & m_strCtype
				& m_dTopAltitude & m_dBottomAltitude & m_dMinCdRate & m_dMaxCdRate
				& m_dSlowCdRate & m_dNormalCdRate & m_dExpediteCdRate & 
				m_dNormalCdRateMin & m_dNormalCdRateMax & m_dLimitIas & m_strWeightType;
		}

};



class		SpdSimulate : public DataObj
{
	public:
	SpdSimulate();
		~SpdSimulate();
		virtual int GetId();
		virtual int GetOwnerId();
	int			m_iSpdSimulateId ;				//!�ٶȷ���ID
	int			m_iAircraftPerformanceId ;	//!����ID
	std::string m_strSimulateType ;				//!0���� 1����
	int		m_dAboveOrBelow ;					//!����Ǽ��٣����Ϊ�߶Ȳ����Ϻ����� 0���ϣ�1����
	double		m_dSpd ;								//!�ٶ�
	double     m_dAccelaration ;					//!���ٶ�
	double m_dTopAltitude;						//!�߶Ȳ������ 
	double m_dBottomAltitude;					//!�߶Ȳ������ 
	
	template<typename Archive>
		Archive& serialize(Archive& ar,const unsigned int version)
		{
			return ar &  m_iSpdSimulateId & m_iAircraftPerformanceId & m_strSimulateType
				& m_dAboveOrBelow & m_dSpd & m_dAccelaration & m_dTopAltitude & m_dBottomAltitude;
		}

};


class FlyEnvelope : public DataObj
{
	public:
		FlyEnvelope();
		~FlyEnvelope();
		virtual int GetId();
		virtual int GetOwnerId();
	int m_iFlyEnvelopeId ;					//!���а���ID
	int m_iAircraftPerformanceId ;		//!����ID
	double m_dTas ;							//!���٣���λ������/Сʱ��
	double m_dAltitude ;						//!�߶ȣ���λ���ף�

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlyEnvelopeId & m_iAircraftPerformanceId & m_dTas & m_dAltitude;
	}
};

class	PhaseOnRunway	: public DataObj
{
public:
	PhaseOnRunway();
	~PhaseOnRunway();
	virtual int GetId();
	virtual int GetOwnerId();
	int m_dPhaseOnRunwayId ;				//!��ɽ���ʱID
	int m_dAircraftPerformanceId;			//!����ID
	std::string m_dLandOrLaunch	;		//!����'L'���䣬'S'���
	std::string m_dLandDecType	;			//! 0������1�޷��磬2�޼��ٰ壬3���޷���Ҳ�޼��ٰ壬4����ܵ����ٶ�
	std::string		m_dWeight	;				//!��L,��M,�� H.
	int		m_dPhaseNo	;				//!�׶κ�,��0��ʼ���,��0��4.�������׶�.
	double		m_dSpeedMin	;				//!��С�ٶ�
	double		m_dSpeedMax	;				//!����ٶ�
	double		m_dAccMin	;					//!��С���ٶ�
	double		m_dAccMax	;					//!�����ٶ�

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_dPhaseOnRunwayId & m_dAircraftPerformanceId & m_dLandOrLaunch
			& m_dLandDecType & m_dWeight & m_dPhaseNo & m_dSpeedMin & m_dSpeedMax
			& m_dAccMin & m_dAccMax ;
	}

};

//!�½����н׶�
class LandPhase : public DataObj
{
public:
	LandPhase();
	~LandPhase();
	virtual int GetId();
	virtual int GetOwnerId();
	int m_iLandPhaseID;    
	int	m_iAircraftPerformanceID;		//!����ID
	int m_iland_dec_type; //! 0������1�޷��磬2�޼��ٰ壬3���޷���Ҳ�޼��ٰ壬4����ܵ����ٶ�
	int m_iWeight;		//!��0,��1,��2.
	int m_iPhaseNo;		//!�׶κ�,��0��ʼ���,��0��4.�������׶�.
	double	m_dSpeedMin;	//!��С�ٶ�
	double	m_dSpeedMax;	//!����ٶ�
	double	m_dAccMin;	//!��С���ٶ�
	double	m_dAccMax;	//!�����ٶ�
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLandPhaseID & m_iAircraftPerformanceID & m_iland_dec_type & m_iWeight 
			& m_iPhaseNo & m_dSpeedMin & m_dSpeedMax & m_dAccMin & m_dAccMax;
	}

};



//!
//!����ģ��
class AircraftModel : public DataObj
{ 
public:
	AircraftModel();
	~AircraftModel();
	virtual int GetId();
	virtual int GetOwnerId();
	int m_iAircraftModelID;      /*�ɻ�ģ��ID*/
	int m_iAircraftPerformanceID; /*������ID*/
	std::string m_strmodel_file;	/*�ɻ���ģ���ļ�  */
	std::string m_strstart_engine_sound_file;	/*�������������ļ�*/
	std::string m_strshut_engine_sound_file;	/*�����������ļ� */
	std::string m_strlaunch_sound_file;		/*��������ļ�*/
	std::string m_strland_sound_file;			/*���������ļ�*/
	std::string m_strtax_sound_file;			/*���������ļ�  */
	std::string m_strfly_sound_file;			/* ���������ļ� */
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAircraftModelID & m_iAircraftPerformanceID & m_strmodel_file 
			& m_strstart_engine_sound_file & m_strshut_engine_sound_file & m_strlaunch_sound_file
			& m_strland_sound_file & m_strtax_sound_file & m_strfly_sound_file;
	}

};

/*-----------------����--------------*/
class AircraftData : public DataObj
{
public:
	int m_iAircraftID;
	std::string m_szAircraftName;
	double m_dIAS;
	double m_dAcceleration;
	double m_dDeceleration;

	AircraftData();
	~AircraftData();
	AircraftData(const AircraftData &aircraftData);
	AircraftData& operator=(const AircraftData& aircraft_data);

	int GetId();
	std::string GetDisplayLabel();

	bool IsEqual(DataObj *dataobj);
	void Copy(DataObj *dataobj);

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();


//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAircraftID & m_szAircraftName & m_dIAS & m_dAcceleration & m_dDeceleration;
	}

};


/*-----------------����--------------*/
class Vehicle : public DataObj
{
public:
	Vehicle(void);
	~Vehicle(void);
	int GetId();
	std::string GetDisplayLabel();
	//!void Copy(boost::shared_ptr<Vehicle> spVehicle);

	void SetVehicleID(int iVehicleID);		
	void SetVehicleName(string strVehicleName);  
	void SetType(int iType);			 
	void SetLength(double dLength);	      
	void SetHeight(double dHeight);	     
	void SetWidth(double dWidth);		  
	void SetNormalTaxSpeed(double dNormalTaxSpeed);   
	void SetMinTaxSpeed(double dMinTaxSpeed);	  
	void SetMaxTaxSpeed(double dMaxTaxSpeed);	  
	void SetReverseSpeed(double dReverseSpeed);
	void SetTurnSpeed(double dTurnSpeed);		  
	void SetNormalAccSpeed(double dNormalAccSpeed);   
	void SetMinAccSpeed(double dMinAccSpeed);	  
	void SetMaxAccSpeed(double dMaxAccSpeed);	  
	void SetNormalDecSpeed(double dNormalDecSpeed);   
	void SetMinDecSpeed(double dMinDecSpeed);	  
	void SetMaxDecSpeed(double dMaxDecSpeed);	  
	void SetMaxTaxBackSpd(double dMaxTaxBackSpd);	  
	void SetMaxFrontGearTurnHdg(double dMaxFrontGearTurnHdg);     
	void SetSizeTreadLen(double dSizeTreadLen);   		 
	void SetSizeTreadWidth(double dSizeTreadWidth);     	
	void SetMinBrakeDis(double dMinBrakeDis);		
	void SetAttachHeading(double dAttachHeading);		
	void SetModelFile(string strModelFile);
	void SetTaxingSoundFile(string  strTaxingSoundFile);
	void SetStartEngineSoundFile(string strStartEngineSoundFile);
	void SetShutdownEngineSoundFile(string strShutdownEngineSoundFile);
	void SetWarmwaitingSoundFile(string strWarmwaitingSoundFile);

	int GetVehicleID();		
	std::string GetVehicleName();  
	int GetType();			 
	double GetLength();	      
	double GetHeight();	     
	double GetWidth();		  
	double GetNormalTaxSpeed();   
	double GetMinTaxSpeed();	  
	double GetMaxTaxSpeed();	 
	double GetReserveSpeed();
	double GetTurnSpeed();		  
	double GetNormalAccSpeed();   
	double GetMinAccSpeed();	  
	double GetMaxAccSpeed();	  
	double GetNormalDecSpeed();   
	double GetMinDecSpeed();	  
	double GetMaxDecSpeed();	  
	double GetMaxTaxBackSpd();	  
	double GetMaxFrontGearTurnHdg();     
	double GetSizeTreadLen();   		 
	double GetSizeTreadWidth();     	
	double GetMinBrakeDis();		
	double GetAttachHeading();		
	std::string GetModelFile();
	std::string GetTaxingSoundFile();
	std::string GetStartEngineSoundFile();
	std::string GetShutdownEngineSoundFile();
	std::string GetWarmwaitingSoundFile();

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();

	//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iVehicleID & m_strVehicleName & m_iType 
			& m_dLength & m_dHeight & m_dWidth & m_dNormalTaxSpeed 
			& m_dMinTaxSpeed & m_dMaxTaxSpeed & m_dTurnSpeed 
			& m_dNormalAccSpeed & m_dReverseSpeed & m_dMinAccSpeed 
			& m_dMaxAccSpeed & m_dNormalDecSpeed & m_dMinDecSpeed 
			& m_dMaxDecSpeed & m_dMaxTaxBackSpd & m_dMaxFrontGearTurnHdg 
			& m_dSizeTreadLen & m_dSizeTreadWidth & m_dMinBrakeDis 
			& m_dAttachHeading & m_strModelFile & m_strTaxingSoundFile 
			& m_strStartEngineSoundFile & m_strShutdownEngineSoundFile 
			& m_strWarmwaitingSoundFile;
	}

public:
	int m_iVehicleID;						 /*���� ������ */
	std::string	m_strVehicleName;    /*��������*/
	int m_iType;								 /*��������*/
	double m_dLength;					 /*��������*/
	double m_dHeight;					 /*�����߶�*/
	double m_dWidth;					 /*�������*/
	double m_dNormalTaxSpeed;    /*�������������ٶ�*/
	double m_dMinTaxSpeed;			 /*������С�����ٶ�*/
	double m_dMaxTaxSpeed;		 /*����������ٶ�*/
	double m_dTurnSpeed;				 /*����ת���ٶ�*/
	double m_dNormalAccSpeed;    /*�����������ٶ�*/
	double m_dReverseSpeed;			 /*���������ٶ�*/
	double m_dMinAccSpeed;			 /*������С���ٶ�*/
	double m_dMaxAccSpeed;		 /*���������ٶ�*/
	double m_dNormalDecSpeed;    /*�����������ٶ�*/
	double m_dMinDecSpeed;	     /*������С���ٶ�*/
	double m_dMaxDecSpeed;	     /*���������ٶ�*/
	double m_dMaxTaxBackSpd;	     /*������󵹳��ٶ�*/
	double m_dMaxFrontGearTurnHdg;     /*�������ת��Ƕ�*/
	double m_dSizeTreadLen;   		 /*ǰ���־�*/
	double m_dSizeTreadWidth;     	 /*�����־�*/
	double m_dMinBrakeDis;		    /*���ɲ������*/
	double m_dAttachHeading;		/*������ɻ�����ʱ, ��Ҫ��ת�ķ���, ��Ҫ�����Ƴ�*/
	std::string  m_strModelFile;
	std::string  m_strTaxingSoundFile;
	std::string  m_strStartEngineSoundFile;
	std::string  m_strShutdownEngineSoundFile;
	std::string  m_strWarmwaitingSoundFile;
};

/*-----------------���չ�˾--------------*/
class Company : public DataObj
{
public:
	Company();
	~Company();
	Company(const Company &company);
	Company& operator=(const Company& company_data);

	int GetId();
	std::string GetDisplayLabel();

	void SetCompanyID(int iCompanyID);
	void SetCompanyName(string szCompanyName);
	void SetCode(string szCode);
	void SetIconID(int iIconID);
	void SetAircrafts(std::vector<int>& vAircraftData);

	int GetCompanyID();
	std::string GetCompanyName();
	std::string GetCode();
	int GetIconID();
	std::vector<int>& GetAircrafts();
	//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCompanyID & m_iIconID & m_szCode & m_szCompanyName &m_vAircrafts;	
	}
private:
	int m_iCompanyID;					/* ��˾��ID,������*/
	std::string m_szCompanyName; 	/* ���չ�˾���� varchar(50) not null unique	*/
	std::string m_szCode;
	int m_iIconID;	
	std::vector<int> m_vAircrafts; //!�ù�˾������ID

};

/*-----------------����--------------*/
class Flight : public DataObj
{
public:
	Flight();
	Flight(const Flight &filght);
	Flight& operator=(const Flight& flight);

	std::string GetDisplayLabel();
	void Copy(boost::shared_ptr<Flight> spFlight);
	int GetAlternateAirportId();
	int GetArrivalAirportId();
	int GetDepartureAirportId();
	int GetCompanyId();
	int GetFlightId();
	int GetDefaultAircraft();
	int GetDepartureTime();
	int GetArrivalTime();
	int GetPeriod();

	std::string GetCallsignNum();

	void SetFlightId(int iFlightID);
	void SetCallSignNum(std::string strCallsignNum);
	void SetCompanyId(int iCompanyID);
	void SetDefaultAircraft(int iDefaultAircraft);
	void SetDepartureAirportId(int iDepartureAirportID);
	void SetArrivalAirportId(int iArrivalAirportID);
	void SetAlternateAirportId(int iAlternateAirportID);
	void SetArrivalTime(int iArrivalTime);
	void SetDepartureTime(int iDepartureTime);
	void SetPeriod(int iPeriod);

	void ReadFromBuffer(const char* pBuffer, int &iOffSize);
	void WriteToBuffer(char* pBuffer, int &iOffSize);
	int GetBufferSize();
	//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlightID & m_iCompanyID & m_strCallsignNum & m_iDefaultAircraft &m_iDepartureAirportID
			&m_iArrivalAirportID &m_iAlternateAirportID &m_iDepartureTime &m_iArrivalTime &m_iPeriod;	
	}
public:
	int m_iFlightID;				/* ���������� */
	int m_iCompanyID;				/* ���չ�˾ID */
	std::string m_strCallsignNum;	/* ���ű��� */
	int m_iDefaultAircraft;		/* Ĭ�ϻ��� */
	int m_iDepartureAirportID;	/* ��������ID */
	int m_iArrivalAirportID;		/* �������ID */
	int m_iAlternateAirportID;	/* ��������ID */
	int m_iDepartureTime;			/* Ԥ�����ʱ�� ��0�㿪ʼ������� */
	int m_iArrivalTime;			/* Ԥ�Ƶ���ʱ�� ��0�㿪ʼ������� */
	int m_iPeriod;				/* ִ������ ÿbitλ�ӵ͵��߱�ʾ������ */
};

/*! 
\brief     ���͵Ļ������ݣ�Ϊ�Ӿ�ʹ�ã�
\details   ��Ϊ�Ӿ���Ҫ��Ŀ��ƻ������ݲ��࣬Ϊ�˼���������Ĵ�С����д���ࡣ
\author    JZH
\date      2013-06-04
*/
class AircraftForVis: public DataObj
{
public:
	AircraftForVis();
	~AircraftForVis();

	//
	int GetId();
	int GetOwnerId();
	string GetDisplayLabel();

	//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAircraftID & m_strModelFile & m_dSizeWidth & m_dSizeLength & m_dSizeHeight
			& m_dDisFrontRearWheel & m_dDisBetweenRearWheel & m_dGearHeight & m_dDisFrontWheel2Nose & m_dDisRearWheel2Tail
			& m_strStartEngineSoundFile & m_strShutEngineSoundFile & m_strLaunchSoundFile & m_strLandSoundFile & m_strTaxSoundFile
			& m_strFlySoundFile & m_dAirframeLength & m_dAirframeWidth & m_dAirframeHeight & m_bIsPlane & m_bIsHelicopter & m_bIsAirForce;	
	}
public:
	int m_iAircraftID;
	std::string m_strModelFile;		//!<�ɻ���ģ���ļ�����
	double m_dSizeWidth;			//!<���
	double m_dSizeLength;			//!<����
	double m_dSizeHeight;			//!<�߶�
	double m_dDisFrontRearWheel;	//!<ǰ���־�
	double m_dDisBetweenRearWheel;	//!<�����־�
	double m_dGearHeight;			//!<����ܸ߶�
	double m_dDisFrontWheel2Nose;	//!<ǰ�ֵ���ͷ����
	double m_dDisRearWheel2Tail;	//!<������ܵ�β������

	std::string m_strStartEngineSoundFile;	//!<�������������ļ�
	std::string m_strShutEngineSoundFile;	//!<�����������ļ�
	std::string m_strLaunchSoundFile;		//!<��������ļ�
	std::string m_strLandSoundFile;			//!<���������ļ�
	std::string m_strTaxSoundFile;			//!<���������ļ�
	std::string m_strFlySoundFile;			//!<���������ļ�

	double m_dAirframeLength;	//!<Length of plane (from origin to door)
	double m_dAirframeWidth;	//!<Width of Plane(Excluding swing)
	double m_dAirframeHeight;	//!<the height of plane's door to earth
	
	bool m_bIsPlane;		//!<�Ƿ��Ƿɻ�
	bool m_bIsHelicopter;	//!<�Ƿ���ֱ����
	bool m_bIsAirForce;		//!<�Ƿ�Ϊ����
};


/*! 
\brief     �����Ļ������ݣ�Ϊ�Ӿ�ʹ�ã�
\details   
\author    DXQ
\date      2013-06-019
*/
class VehicleForVis: public DataObj
{
public:
	VehicleForVis();
	~VehicleForVis();

//!boost���л�
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iVehicleID & m_strModelFile & m_dSizeWidth & m_dSizeLength & m_dSizeHeight & m_strStartEngineSoundFile 
			& m_strShutEngineSoundFile  & m_strTaxSoundFile;	
	}
public:
	int m_iVehicleID;
	std::string m_strModelFile;		//!<������ģ���ļ�����
	double m_dSizeWidth;			//!<���
	double m_dSizeLength;			//!<����
	double m_dSizeHeight;			//!<�߶�

	std::string m_strStartEngineSoundFile;	//!<�������������ļ�
	std::string m_strShutEngineSoundFile;	//!<�����������ļ�
	std::string m_strTaxSoundFile;			//!<���������ļ�
};

#endif