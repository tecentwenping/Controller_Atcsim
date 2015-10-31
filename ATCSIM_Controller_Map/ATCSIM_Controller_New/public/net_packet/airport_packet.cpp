#include "airport_packet.h"

//����������Աϯλ��ʼ����
PKT_IMPLEMENT_DYNCREATE(InitializeClientPacket);

//�����������л���
PKT_IMPLEMENT_DYNCREATE(AirportDataPacket);

//�ظ����� �������ݰ�
PKT_IMPLEMENT_DYNCREATE(AckAirportDataPacket);

//�ظ������������ݰ�
PKT_IMPLEMENT_DYNCREATE(AckAirspaceDataPacket);

//�������ݰ�
PKT_IMPLEMENT_DYNCREATE(AckBaseDataPacket);

//ѵ���ƻ���
PKT_IMPLEMENT_DYNCREATE(AckExercisePacket);

//�ظ�������Աϯλѵ���ƻ�����ظ���
PKT_IMPLEMENT_DYNCREATE(AckAllTrainPlanNamePacket);

//�ظ����� ����ѵ���ƻ��Լ���ط��мƻ���������ظ���
PKT_IMPLEMENT_DYNCREATE(AckSingleTrainPlanPacket);

//�ظ����� ����ѵ���ƻ��Լ���ط��мƻ���������ظ����������ͻ��ˣ�
PKT_IMPLEMENT_DYNCREATE(AckSingleTrainPlanPacket_S);

//�ظ������Ӿ���ʼ����Ҫ�İ�
PKT_IMPLEMENT_DYNCREATE(VISInitPacket)


/*!
\brief:		���������л���ID��map�Եİ�
\details:	��Ҫ���ڽ�Աϯλϯλ��
			��Աϯλ���������͸ð��������л���ID�����֣��Թ�ѡ��ѵ���ƻ�ʹ�ã�
			DataServer�յ��ð���ظ�AckAirportPacket��
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AllAirportPacket)



/*!
\brief:		����ȫ������ID�����ֵ�map�԰�
\details:	��Ҫ���ڽ�Աϯλ
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AckAllAirportPacket)



/*!
\brief:		������ĳһ��������ѵ���ƻ�ID�����ֵ�map�԰�
\details:	��Ҫ���ڽ�Աϯλ��
			��Աϯλ���л�������ʱ���ͣ��Թ�ѡ��ѵ���ƻ�ʹ�ã�
			DataServer�յ��ð���ظ�AllExercisePacket����
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AllExercisePacket)


/*!
\brief:		����ĳһ������ȫ��ѵ���ƻ�ID�����ֵ�map�԰�
\details:	��Ҫ���ڽ�Աϯλ���Թ�ѡ��ѵ���ƻ�ʹ�á�
\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(AckAllExercisePacket)


/*!
\brief:		����ѵ���ƻ��Լ���ط��мƻ���������ظ���
\details:	��Ҫ���ں��ļ��㡣
\author DXQ
\date 2013/6/14
*/
PKT_IMPLEMENT_DYNCREATE(AckSingleExrecisePacket)



/*!
\brief:		����ѵ���ƻ��������͸��ͻ���
\details:	��Ҫ���ڿͻ��ˡ�
\author DXQ
\date 2013/6/18
*/
PKT_IMPLEMENT_DYNCREATE(AckSingleExrecisePacket_S)

/*!
\brief:		����ĳһ����ID��ѵ���ƻ�ID
\details:	��Ҫ���ڽ�Աϯλ��
			��Աϯλ��ѡ����ĳ�������е�ĳ��ѵ���ƻ��󣬵��׼��ʱ���͸ð���
			DataServer�յ��ð��󣬻ظ�һϵ�а���
			DataServer�ظ��İ����£�
								AckBaseDataPacket���������ݰ���
								AckAirportDataPacket���������ݰ���
								AckAirspaceDataPacket���������ݰ���
								AckExercisePacket��ѵ���ƻ�����
								AckSingleTrainPlanPacket_S���ͻ���ѵ���ƻ�����
								VISInitPacket���Ӿ���ʼ������

\author DXQ
\date 2013/6/13
*/
PKT_IMPLEMENT_DYNCREATE(InitExercisePacket)



/*!
\brief:		�л�������
\details:	��Ҫ����Designerϯλ����ʼ��ʱ�Լ��л�����ʱʹ�ã�
			Designer��ʼ��ʱ�����͸ð���
			Designer�л�����ʱ�����͸ð�
			DataServer�յ��ð��󣬻ظ�һϵ�а���
			DataServer�ظ��İ����£�
									AckBaseDataPacket���������ݰ���
									AckAirportDataPacket���������ݰ���
									AckAirspaceDataPacket���������ݰ���
									AckExercisePacket��ѵ���ƻ�����
\author DXQ
\date 2013/6/17
*/
PKT_IMPLEMENT_DYNCREATE(AirportChangePacket)

PKT_IMPLEMENT_DYNCREATE(ExerciseInfoPacket)