#include "airport_packet.h"

//发包：管制员席位初始化包
PKT_IMPLEMENT_DYNCREATE(InitializeClientPacket);

//发包：机场切换包
PKT_IMPLEMENT_DYNCREATE(AirportDataPacket);

//回复包： 机场数据包
PKT_IMPLEMENT_DYNCREATE(AckAirportDataPacket);

//回复包：空域数据包
PKT_IMPLEMENT_DYNCREATE(AckAirspaceDataPacket);

//基础数据包
PKT_IMPLEMENT_DYNCREATE(AckBaseDataPacket);

//训练计划包
PKT_IMPLEMENT_DYNCREATE(AckExercisePacket);

//回复包：教员席位训练计划请求回复包
PKT_IMPLEMENT_DYNCREATE(AckAllTrainPlanNamePacket);

//回复包： 单条训练计划以及相关飞行计划数据请求回复包
PKT_IMPLEMENT_DYNCREATE(AckSingleTrainPlanPacket);

//回复包： 单条训练计划以及相关飞行计划数据请求回复包（发给客户端）
PKT_IMPLEMENT_DYNCREATE(AckSingleTrainPlanPacket_S);

//回复包：视景初始化需要的包
PKT_IMPLEMENT_DYNCREATE(VISInitPacket)


/*!
\brief:		请求获得所有机场ID与map对的包
\details:	主要用于教员席位席位；
			教员席位在启动后发送该包请求所有机场ID与名字，以供选择训练计划使用；
			DataServer收到该包后回复AckAirportPacket包
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AllAirportPacket)



/*!
\brief:		包含全部机场ID与名字的map对包
\details:	主要用于教员席位
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AckAllAirportPacket)



/*!
\brief:		请求获得某一机场所有训练计划ID与名字的map对包
\details:	主要用于教员席位；
			教员席位在切换机场的时候发送，以供选择训练计划使用；
			DataServer收到该包后回复AllExercisePacket包。
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AllExercisePacket)


/*!
\brief:		包含某一机场的全部训练计划ID与名字的map对包
\details:	主要用于教员席位，以供选择训练计划使用。
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AckAllExercisePacket)


/*!
\brief:		单条训练计划以及相关飞行计划数据请求回复包
\details:	主要用于核心计算。
\author DXQ
\date 2013/6/14
*/
PKT_IMPLEMENT_DYNCREATE(AckSingleExrecisePacket)



/*!
\brief:		单条训练计划包，发送给客户端
\details:	主要用于客户端。
\author DXQ
\date 2013/6/18
*/
PKT_IMPLEMENT_DYNCREATE(AckSingleExrecisePacket_S)

/*!
\brief:		包含某一机场ID与训练计划ID
\details:	主要用于教员席位；
			教员席位在选择了某个机场中的某个训练计划后，点击准备时发送该包；
			DataServer收到该包后，回复一系列包；
			DataServer回复的包如下：
								AckBaseDataPacket（基础数据包）
								AckAirportDataPacket（机场数据包）
								AckAirspaceDataPacket（空中数据包）
								AckExercisePacket（训练计划包）
								AckSingleTrainPlanPacket_S（客户端训练计划包）
								VISInitPacket（视景初始化包）

\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(InitExercisePacket)



/*!
\brief:		切换机场包
\details:	主要用于Designer席位，初始化时以及切换机场时使用；
			Designer初始化时，发送该包；
			Designer切换机场时，发送该包
			DataServer收到该包后，回复一系列包；
			DataServer回复的包如下：
									AckBaseDataPacket（基础数据包）
									AckAirportDataPacket（机场数据包）
									AckAirspaceDataPacket（空中数据包）
									AckExercisePacket（训练计划包）
\author DXQ
\date 2013/6/17
*/
PKT_IMPLEMENT_DYNCREATE(AirportChangePacket)

PKT_IMPLEMENT_DYNCREATE(ExerciseInfoPacket)