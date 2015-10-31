#include <xutility>
#include "../wdllexport.h"
#include "wglobal.h"
#include "witemshareprivate.h"

//bool attachLine(const WWorldLineF& line, double attachDistance, const WWorldPointF& pos, WWorldPointF* attachedPos)
//{
//	WWorldPointF p[2] = {line.p1(), line.p2()};
//	for (unsigned i=0; i<array_size(p); ++i)
//	{
//		if (pos != p[i] && distance(pos, p[i]) < attachDistance)
//		{
//			if (attachedPos)
//			{
//				*attachedPos = p[i];
//			}
//			return true;
//		}
//	}
//
//	double x = pos.x();
//	double y = pos.y();
//	double x1 = p[0].x();
//	double y1 = p[0].y();
//	double x2 = p[1].x();
//	double y2 = p[1].y();
//
//	//Ax + By + C = 0
//	double A = y1 - y2;
//	double B = x2 - x1;
//	double C = y2 * x1 - y1 * x2;
//	double D = A * x + B * y + C;
//
//	if (!wFuzzyCompare(D, 0.0) && (in_range(x1, x2, x) || wFuzzyCompare(B, 0.0)) 
//		&& (in_range(y1, y2, y) || wFuzzyCompare(A, 0.0)))
//	{
//		//d = |Ax + By + C| / sqrt(A*A + B*B);
//		D *= D;
//		double D0 = A * A + B * B;
//		if (D < D0 * attachDistance * attachDistance)
//		{
//			if (attachedPos)
//			{
//				//A * x0 + B * y0 + C = 0
//				//x0 = -(B * y0 + C) / A
//				//y0 = -(A * x0 + C) / B
//				if (wFuzzyCompare(A, 0.0))
//				{
//					attachedPos->setXY(x, -C / B);
//				}
//				else if (wFuzzyCompare(B, 0.0))
//				{
//					attachedPos->setXY(-C / A, y);
//				}
//				else
//				{
//					double mx = -(B * y + C) / A;
//					double my = -(A * x + C) / B;
//					attachedPos->setXY((x + mx) / 2, (y + my) / 2);
//				}
//			}
//			return true;
//		}
//	}
//
//	return false;
//}

//�жϵ�P(x0, y0)�Ƿ����߶�L:P1(x1,y1)->P2(x2,y2)����(��������d),���������������߶��ϵ�������Q����
//�㷨���£�
//1. �ж�P�Ƿ���P1/P2����(distance(P, P1) < d),�����,Q�����꼴��P1/P2,�㷨����,����ת��2
//2. ����P��L�ľ���d0,���d0>d,����ʧ��,�㷨����,����ת��3
//3. ����P��L�ϵ�ͶӰ(����)R(x3, y3),���x3��x1,x2֮��,����y3��y1,y2֮��,Q����R,�����ɹ�,��������ʧ��,�㷨����

bool attachLine(const WWorldLineF& line, double attachDistance, const WWorldPointF& pos, WWorldPointF* attachedPos)
{
	WWorldPointF p[2] = {line.p1(), line.p2()};
	for (unsigned i=0; i<array_size(p); ++i)
	{
		if (pos != p[i] && distance(pos, p[i]) < attachDistance)
		{
			if (attachedPos)
			{
				*attachedPos = p[i];
			}
			return true;
		}
	}

	double x0 = pos.x();
	double y0 = pos.y();
	double x1 = p[0].x();
	double y1 = p[0].y();
	double x2 = p[1].x();
	double y2 = p[1].y();

	//ֱ��L����:Ax + By + C = 0
	double A = y1 - y2;
	double B = x2 - x1;
	double C = y2 * x1 - y1 * x2;
	double D = A * A + B * B;
	double delta = A * x0 + B * y0 + C;

	//����㵽ֱ�ߵľ���d = |A* x0 + B * y0 + C| / sqrt(A * A+B * B)
	if (!wFuzzyCompare(delta, 0.0) && fabs(delta) / sqrt(D) < attachDistance)
	{
		//�������ֱ���ϵ�ͶӰR
		//���߷���Bx - Ay + C0 = 0, ����C0 = A * y0 - B * x0
		//���ߺ�ֱ�ߵĽ��㼴��ͶӰR((-A*C-B*C0)/D, (A*C0-B*C)/D)
		double C0 = A * y0 - B * x0;
		double x3 = (-A * C - B * C0) / D;
		double y3 = (A * C0 - B * C) / D;

		if (in_range(x1, x2, x3) && in_range(y1, y2, y3))
		{
			if (attachedPos)
			{
				attachedPos->setXY(x3, y3);
			}
			return true;
		}
	}
	return false;
}

WWorldRectF boundingRect(WPF p1, WPF p2)
{
	double xmin = wMin(p1.x(), p2.x());
	double ymin = wMin(p1.y(), p2.y());
	double xmax = wMax(p1.x(), p2.x());
	double ymax = wMax(p1.y(), p2.y());

	return WWorldRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}

WWorldRectF boundingRect(WPF p1, WPF p2, WPF p3)
{
	double xmin = wMin(p1.x(), p2.x(), p3.x());
	double ymin = wMin(p1.y(), p2.y(), p3.y());
	double xmax = wMax(p1.x(), p2.x(), p3.x());
	double ymax = wMax(p1.y(), p2.y(), p3.y());

	return WWorldRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}

WWorldRectF boundingRect(WPF p1, WPF p2, WPF p3, WPF p4)
{
	double xmin = wMin(p1.x(), p2.x(), p3.x(), p4.x());
	double ymin = wMin(p1.y(), p2.y(), p3.y(), p4.y());
	double xmax = wMax(p1.x(), p2.x(), p3.x(), p4.x());
	double ymax = wMax(p1.y(), p2.y(), p3.y(), p4.y());

	return WWorldRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}

WWorldRectF boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5)
{
	double xmin = wMin(p1.x(), p2.x(), p3.x(), p4.x(), p5.x());
	double ymin = wMin(p1.y(), p2.y(), p3.y(), p4.y(), p5.y());
	double xmax = wMax(p1.x(), p2.x(), p3.x(), p4.x(), p5.x());
	double ymax = wMax(p1.y(), p2.y(), p3.y(), p4.y(), p5.y());

	return WWorldRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}

WWorldRectF boundingRect(WPF p1, WPF p2, WPF p3, WPF p4, WPF p5, WPF p6)
{
	double xmin = wMin(p1.x(), p2.x(), p3.x(), p4.x(), p5.x(), p6.x());
	double ymin = wMin(p1.y(), p2.y(), p3.y(), p4.y(), p5.y(), p6.y());
	double xmax = wMax(p1.x(), p2.x(), p3.x(), p4.x(), p5.x(), p6.x());
	double ymax = wMax(p1.y(), p2.y(), p3.y(), p4.y(), p5.y(), p6.y());

	return WWorldRectF(xmin, ymin, xmax-xmin, ymax-ymin);
}