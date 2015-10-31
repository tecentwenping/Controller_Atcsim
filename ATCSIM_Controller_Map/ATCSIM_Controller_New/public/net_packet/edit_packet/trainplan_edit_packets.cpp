#include "trainplan_edit_packets.h"
#include <string>
//训练计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(TrainPlanEditPacket);
//飞机目标信息编辑包
PKT_IMPLEMENT_DYNCREATE(ObjPlanEditPacket);
//飞机计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(TPFlyPlanEditPacket);
//云计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(CloudPlanEditPacket);
//烟计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(SmokePlanEditPacket);

//车辆计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(VehiclePlanEditPacket);

//特效运动物体信息编辑包
PKT_IMPLEMENT_DYNCREATE(SpecialEffectObjPlanEditPacket);

//训练计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(TrainPlanDataEditPacket);


//飞机计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(FlyPlanDataEditPacket);

//环境参数计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(EnvPlanEditPacket);

//环境参数子对象计划信息编辑包
PKT_IMPLEMENT_DYNCREATE(EnvObjectPlanEditPacket);