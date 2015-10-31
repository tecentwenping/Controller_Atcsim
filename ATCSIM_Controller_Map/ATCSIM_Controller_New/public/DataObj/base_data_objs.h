//!此文件中定义基础数据相关的对象类，包括以下对象：
//!机型         AircraftData
//!车辆         Vehicle


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
	//!<-基本参数
	std::string m_strName;
	std::string m_strNameICAO;			//!<ICAO名称
	bool m_bIsAirscrew;						//!<是否有螺旋桨
	bool m_bIsHelicopter;					//!<是否是直升机
	int m_iWheelType;							//!<飞机的轮子形式0表示滚轮式,1表示雪撬式,2(水上飞机)
	int m_iEngineCount;					//!<引擎数量
	std::string m_strWakeType;			//!<尾流类型	H M L
	std::string m_strTypeBySpeed;			//!<飞机类型，按进入跑道入口速度划分(A/B/C{C1,C2,C3,C4}/D)

	std::string  m_dWeight ;						//!飞机权重类型 H M L
	double	 m_dSizeWidth;							 //!<宽度
	double	 m_dSizeLength;						 //!<长度
	double   m_dSizeHeight;						 //!<高度
	double	 m_dDisFrontRearWheel;			 //!<前后轮距
	double	 m_dDisBetweenRearWheel;       //!<左右轮距
	double	 m_dGearHeight;						 //!<起落架高度
	double	 m_dDisFrontWheel2Nose;			 //!<前轮到机头距离
	double   m_dDisRearWheel2Tail;			//!<后起落架到尾部距离

	//!<-滑行参数
	double m_dMaxTaxBrakeDis;					//!<最大刹车距离
	double m_dMaxTaxAcc;							//!<滑行最大加速度
	double m_dMaxTaxDec;							//!<滑行最大减速度
	double m_dMaxFrontGearTurnAngle;		//!<最大前轮偏转角度
	double m_dMaxTaxSpd;							//!<最大滑行速度
	double m_dNormalTaxSpd;						//!<正常滑行速度
	double m_dTaxTurnSpd;							//!<静止转弯速度
	double m_dDisFollowMe;							//!<跟进该机型后面的飞机要保持的间距

	double m_dPushbackSpd;							//!<被推车推走的速度
	double m_dAttachDis;								//!<推车与前轮的距离

	
	int		 m_iEngineStartDelayMin;		//!<开车时间
	int		 m_iEngineStartDelayMax;		//!<开车时间
	int		 m_iEngineShutDelayMin;		//!<关车时间
	int		 m_iEngineShutDelayMax;		//!<关车时间

	//!<-起飞阶段
	double m_dLaunchFromParkMin;		//!<从静止到开始滑动的最短时间
	double m_dLaunchFromParkMax;		//!<从静止到开始滑动的最长时间
	double m_dLaunchLiftFrontGearSpd;	//!<提前轮时的速度
	double m_dLaunchLiftSpd;				//!<离地速度
	double m_dLaunchDecisionSpd;		//!<起飞决断速度
	double m_dLaunchEndIasMin;			//!<起飞结束时的最小速度
	double m_dLaunchEndIasMax;			//!<起飞结束时的最大速度	
	double m_dLaunchEndAltMin;			//!<起飞结束时的最小高度
	double m_dLaunchEndAltMax;			//!<起飞结束时的最大高度
	double m_dLaunchElvAngle;				//!<起飞仰角
	double m_dLaunchPitchRate;			//!<起飞仰角率
	double m_dLaunchBreakDec;			//!<中断起飞后减速度

	double m_dLaunchLiftFrontGearAccLightMin;		//!<轻载重时，到抬前轮的加速度，最小值
	double m_dLaunchLiftFrontGearAccLightMax;		//!<轻载重时，到抬前轮的加速度，最大值
	double m_dLaunchLiftFrontGearAccMidMin;			//!<中载重时，到抬前轮的加速度，最小值
	double m_dLaunchLiftFrontGearAccMidMax;		//!<中载重时，到抬前轮的加速度，最大值
	double m_dLaunchLiftFrontGearAccHeavyMin;		//!<重载重时，到抬前轮的加速度，最小值
	double m_dLaunchLiftFrontGearAccHeavyMax;		//!<重载重时，到抬前轮的加速度，最大值
	double m_dLaunchLiftAccLightMin;						//!<轻载重时，从抬前轮到离地的加速度，最小值
	double m_dLaunchLiftAccLightMax;						//!<轻载重时，从抬前轮到离地的加速度，最大值
	double m_dLaunchLiftAccMidMin;						//!<中载重时，从抬前轮到离地的加速度，最小值
	double m_dLaunchLiftAccMidMax;						//!<中载重时，从抬前轮到离地的加速度，最大值
	double m_dLaunchLiftAccHeavyMin;						//!<重载重时，从抬前轮到离地的加速度，最小值
	double m_dLaunchLiftAccHeavyMax;						//!<重载重时，从抬前轮到离地的加速度，最大值

	double m_dLaunchEndClimbRate;							//!<起飞爬升率
	double m_dLaunchEndAcc;									//!<起飞速度时加速度

	//!<-降落参数
	double m_dApproachIasMin;									//!<进近速度，最小
	double m_dApproachIasMax;								//!<进近速度，最大
	double m_dNormalLandSpdMin;							//!<正常着陆速度，最小
	double m_dNormalLandSpdMax;							//!<正常着陆速度，最大
	double m_dLandTouchDistanceMin;						//!<接地距离，最小
	double m_dLandTouchDistanceMax;						//!<接地距离，最大
	double m_dLandReflyHeightMin;							//!<复飞高度，最小
	double m_dLandReflyHeightMax;							//!<复飞高度，最大
	double	m_dTaxMinAcc ;										//!地面滑行最小加速度
	double	m_dTaxMinDec ;										//!地面滑行最小减速度


	double m_dLandVref;											//!<拉平时的速度
	double m_dLandRefHeight;									//!<拉平时高度
	double m_dLandElvAngle;										//!<拉平时角度
	double m_dLandElvAngleRate;								//!<拉平时角度率

	double m_dVacateSpd;											//!<脱离速度

	//!<-空中参数
	double m_dNormalTurnBank;								//!<转弯坡度，正常，单位：度
	double m_dMaxTurnBank;									//!<转弯坡度，最大，单位：度
	double m_dNormalRollRate;									//!<常用横滚率，单位：度/秒
	double m_dNormalPitch;										//!<常用仰角，单位：度
	double m_dNormalPitchRate;								//!<常用仰角率，单位：度/秒

	double m_dAltitudeUplimit;									//!<升限
	double m_dMinCruisingAltitude;							//!<巡航高度，最小
	double m_dNormalCruisingAltitude;						//!<巡航高度，正常
	double m_dMaxCruisingAltitude;							//!<巡航高度，最大

	double m_dMinCruisingMach;						//!<巡航马赫，最大
	double m_dNormalCruisingMach;					//!<巡航马赫，正常
	double m_dMaxCruisingMach;						//!<巡航马赫，最大

	double m_dMiddleLevel;							//!<高度层

	vector<boost::shared_ptr<AltSimulate> > m_vAltSimulate;    //!高度模拟
	vector<boost::shared_ptr<SpdSimulate> > m_vSpdSimulate; //!速度模拟
	vector<boost::shared_ptr<FlyEnvelope> > m_vFlyEnvelope;   //!飞行包线
	vector<boost::shared_ptr<PhaseOnRunway> > m_vPhase;      //!下降阶段
	std::vector<int> m_vCompanys; //!该机型的航空公司ID


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
	int		m_iAltsimulateId ;						//!高度模拟ID
	int		m_iAircraftPerformanceId ;		//!机型ID
	std::string  m_strCtype ;							//!d下降 c爬升
	double  m_dTopAltitude ;						//!高度层的上限 
	double  m_dBottomAltitude ;				//!高度层的下限
	double  m_dMinCdRate ;						//!最小爬升率或最小下降率
	double  m_dMaxCdRate ;					    //!最大爬升率或最大下降率
	double  m_dSlowCdRate ;						//!慢爬升率或慢下降率
	double  m_dNormalCdRate ;				    //!正常爬升率或正常下降率
	double  m_dExpediteCdRate ;			    //!快爬升率或快下降率
	double  m_dNormalCdRateMin ;		    //!正常爬升率（或下降率）范围的最小值
	double  m_dNormalCdRateMax ;		    //!正常爬升率（或下降率）范围的最大值
	double	m_dLimitIas				;				//!高度模拟中缺少限制表速
	std::string m_strWeightType;						//!载重类型	H M L

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
	int			m_iSpdSimulateId ;				//!速度仿真ID
	int			m_iAircraftPerformanceId ;	//!机型ID
	std::string m_strSimulateType ;				//!0加速 1减速
	int		m_dAboveOrBelow ;					//!如果是加速，则分为高度层以上和以下 0以上，1以下
	double		m_dSpd ;								//!速度
	double     m_dAccelaration ;					//!加速度
	double m_dTopAltitude;						//!高度层的上限 
	double m_dBottomAltitude;					//!高度层的下限 
	
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
	int m_iFlyEnvelopeId ;					//!飞行包线ID
	int m_iAircraftPerformanceId ;		//!机型ID
	double m_dTas ;							//!真速（单位：公里/小时）
	double m_dAltitude ;						//!高度（单位：米）

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
	int m_dPhaseOnRunwayId ;				//!起飞降落时ID
	int m_dAircraftPerformanceId;			//!机型ID
	std::string m_dLandOrLaunch	;		//!类型'L'降落，'S'起飞
	std::string m_dLandDecType	;			//! 0正常，1无反喷，2无减速板，3既无反喷也无减速板，4冲出跑道减速度
	std::string		m_dWeight	;				//!轻L,中M,重 H.
	int		m_dPhaseNo	;				//!阶段号,从0开始编号,从0到4.最多五个阶段.
	double		m_dSpeedMin	;				//!最小速度
	double		m_dSpeedMax	;				//!最大速度
	double		m_dAccMin	;					//!最小加速度
	double		m_dAccMax	;					//!最大加速度

	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_dPhaseOnRunwayId & m_dAircraftPerformanceId & m_dLandOrLaunch
			& m_dLandDecType & m_dWeight & m_dPhaseNo & m_dSpeedMin & m_dSpeedMax
			& m_dAccMin & m_dAccMax ;
	}

};

//!下降滑行阶段
class LandPhase : public DataObj
{
public:
	LandPhase();
	~LandPhase();
	virtual int GetId();
	virtual int GetOwnerId();
	int m_iLandPhaseID;    
	int	m_iAircraftPerformanceID;		//!机型ID
	int m_iland_dec_type; //! 0正常，1无反喷，2无减速板，3既无反喷也无减速板，4冲出跑道减速度
	int m_iWeight;		//!轻0,中1,重2.
	int m_iPhaseNo;		//!阶段号,从0开始编号,从0到4.最多五个阶段.
	double	m_dSpeedMin;	//!最小速度
	double	m_dSpeedMax;	//!最大速度
	double	m_dAccMin;	//!最小加速度
	double	m_dAccMax;	//!最大加速度
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iLandPhaseID & m_iAircraftPerformanceID & m_iland_dec_type & m_iWeight 
			& m_iPhaseNo & m_dSpeedMin & m_dSpeedMax & m_dAccMin & m_dAccMax;
	}

};



//!
//!机型模型
class AircraftModel : public DataObj
{ 
public:
	AircraftModel();
	~AircraftModel();
	virtual int GetId();
	virtual int GetOwnerId();
	int m_iAircraftModelID;      /*飞机模型ID*/
	int m_iAircraftPerformanceID; /*航空器ID*/
	std::string m_strmodel_file;	/*飞机的模型文件  */
	std::string m_strstart_engine_sound_file;	/*启动引擎声音文件*/
	std::string m_strshut_engine_sound_file;	/*关引擎声音文件 */
	std::string m_strlaunch_sound_file;		/*起飞声音文件*/
	std::string m_strland_sound_file;			/*降落声音文件*/
	std::string m_strtax_sound_file;			/*滑行声音文件  */
	std::string m_strfly_sound_file;			/* 飞行声音文件 */
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAircraftModelID & m_iAircraftPerformanceID & m_strmodel_file 
			& m_strstart_engine_sound_file & m_strshut_engine_sound_file & m_strlaunch_sound_file
			& m_strland_sound_file & m_strtax_sound_file & m_strfly_sound_file;
	}

};

/*-----------------机型--------------*/
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


//!boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iAircraftID & m_szAircraftName & m_dIAS & m_dAcceleration & m_dDeceleration;
	}

};


/*-----------------车辆--------------*/
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

	//!boost序列化
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
	int m_iVehicleID;						 /*车辆 主键码 */
	std::string	m_strVehicleName;    /*车辆名称*/
	int m_iType;								 /*车辆类型*/
	double m_dLength;					 /*车辆长度*/
	double m_dHeight;					 /*车辆高度*/
	double m_dWidth;					 /*车辆宽度*/
	double m_dNormalTaxSpeed;    /*车辆正常滑行速度*/
	double m_dMinTaxSpeed;			 /*车辆最小滑行速度*/
	double m_dMaxTaxSpeed;		 /*车辆最大滑行速度*/
	double m_dTurnSpeed;				 /*车辆转弯速度*/
	double m_dNormalAccSpeed;    /*车辆正常加速度*/
	double m_dReverseSpeed;			 /*车辆倒车速度*/
	double m_dMinAccSpeed;			 /*车辆最小加速度*/
	double m_dMaxAccSpeed;		 /*车辆最大加速度*/
	double m_dNormalDecSpeed;    /*车辆正常减速度*/
	double m_dMinDecSpeed;	     /*车辆最小减速度*/
	double m_dMaxDecSpeed;	     /*车辆最大减速度*/
	double m_dMaxTaxBackSpd;	     /*车辆最大倒车速度*/
	double m_dMaxFrontGearTurnHdg;     /*车辆最大转弯角度*/
	double m_dSizeTreadLen;   		 /*前后轮距*/
	double m_dSizeTreadWidth;     	 /*左右轮距*/
	double m_dMinBrakeDis;		    /*最短刹车距离*/
	double m_dAttachHeading;		/*车辆与飞机连接时, 需要旋转的方向, 主要用于推车*/
	std::string  m_strModelFile;
	std::string  m_strTaxingSoundFile;
	std::string  m_strStartEngineSoundFile;
	std::string  m_strShutdownEngineSoundFile;
	std::string  m_strWarmwaitingSoundFile;
};

/*-----------------航空公司--------------*/
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
	//!boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iCompanyID & m_iIconID & m_szCode & m_szCompanyName &m_vAircrafts;	
	}
private:
	int m_iCompanyID;					/* 公司的ID,主键码*/
	std::string m_szCompanyName; 	/* 航空公司名称 varchar(50) not null unique	*/
	std::string m_szCode;
	int m_iIconID;	
	std::vector<int> m_vAircrafts; //!该公司航空器ID

};

/*-----------------航班--------------*/
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
	//!boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iFlightID & m_iCompanyID & m_strCallsignNum & m_iDefaultAircraft &m_iDepartureAirportID
			&m_iArrivalAirportID &m_iAlternateAirportID &m_iDepartureTime &m_iArrivalTime &m_iPeriod;	
	}
public:
	int m_iFlightID;				/* 航班主键码 */
	int m_iCompanyID;				/* 航空公司ID */
	std::string m_strCallsignNum;	/* 呼号编码 */
	int m_iDefaultAircraft;		/* 默认机型 */
	int m_iDepartureAirportID;	/* 出发机场ID */
	int m_iArrivalAirportID;		/* 到达机场ID */
	int m_iAlternateAirportID;	/* 备降机场ID */
	int m_iDepartureTime;			/* 预计起飞时间 从0点开始起的秒数 */
	int m_iArrivalTime;			/* 预计到达时间 从0点开始起的秒数 */
	int m_iPeriod;				/* 执行周期 每bit位从低到高表示星期数 */
};

/*! 
\brief     机型的基础数据（为视景使用）
\details   因为视景需要的目标计划的内容不多，为了减少网络包的大小，特写此类。
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

	//!boost序列化
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
	std::string m_strModelFile;		//!<飞机的模型文件名称
	double m_dSizeWidth;			//!<宽度
	double m_dSizeLength;			//!<长度
	double m_dSizeHeight;			//!<高度
	double m_dDisFrontRearWheel;	//!<前后轮距
	double m_dDisBetweenRearWheel;	//!<左右轮距
	double m_dGearHeight;			//!<起落架高度
	double m_dDisFrontWheel2Nose;	//!<前轮到机头距离
	double m_dDisRearWheel2Tail;	//!<后起落架到尾部距离

	std::string m_strStartEngineSoundFile;	//!<启动引擎声音文件
	std::string m_strShutEngineSoundFile;	//!<关引擎声音文件
	std::string m_strLaunchSoundFile;		//!<起飞声音文件
	std::string m_strLandSoundFile;			//!<降落声音文件
	std::string m_strTaxSoundFile;			//!<滑行声音文件
	std::string m_strFlySoundFile;			//!<飞行声音文件

	double m_dAirframeLength;	//!<Length of plane (from origin to door)
	double m_dAirframeWidth;	//!<Width of Plane(Excluding swing)
	double m_dAirframeHeight;	//!<the height of plane's door to earth
	
	bool m_bIsPlane;		//!<是否是飞机
	bool m_bIsHelicopter;	//!<是否是直升机
	bool m_bIsAirForce;		//!<是否为军机
};


/*! 
\brief     车辆的基础数据（为视景使用）
\details   
\author    DXQ
\date      2013-06-019
*/
class VehicleForVis: public DataObj
{
public:
	VehicleForVis();
	~VehicleForVis();

//!boost序列化
public:
	template<typename Archive>
	Archive& serialize(Archive& ar,const unsigned int version)
	{
		return ar & m_iVehicleID & m_strModelFile & m_dSizeWidth & m_dSizeLength & m_dSizeHeight & m_strStartEngineSoundFile 
			& m_strShutEngineSoundFile  & m_strTaxSoundFile;	
	}
public:
	int m_iVehicleID;
	std::string m_strModelFile;		//!<车辆的模型文件名称
	double m_dSizeWidth;			//!<宽度
	double m_dSizeLength;			//!<长度
	double m_dSizeHeight;			//!<高度

	std::string m_strStartEngineSoundFile;	//!<启动引擎声音文件
	std::string m_strShutEngineSoundFile;	//!<关引擎声音文件
	std::string m_strTaxSoundFile;			//!<滑行声音文件
};

#endif