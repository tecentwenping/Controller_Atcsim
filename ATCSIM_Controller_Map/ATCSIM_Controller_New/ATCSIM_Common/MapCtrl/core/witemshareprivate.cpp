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

//判断点P(x0, y0)是否在线段L:P1(x1,y1)->P2(x2,y2)附近(吸附距离d),如果是则给出其在线段上的吸附点Q坐标
//算法如下：
//1. 判断P是否在P1/P2附近(distance(P, P1) < d),如果是,Q点坐标即是P1/P2,算法结束,否则转到2
//2. 计算P到L的距离d0,如果d0>d,吸附失败,算法结束,否则转到3
//3. 计算P在L上的投影(垂足)R(x3, y3),如果x3在x1,x2之间,并且y3在y1,y2之间,Q即是R,吸附成功,否则吸附失败,算法结束

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

	//直线L方程:Ax + By + C = 0
	double A = y1 - y2;
	double B = x2 - x1;
	double C = y2 * x1 - y1 * x2;
	double D = A * A + B * B;
	double delta = A * x0 + B * y0 + C;

	//计算点到直线的距离d = |A* x0 + B * y0 + C| / sqrt(A * A+B * B)
	if (!wFuzzyCompare(delta, 0.0) && fabs(delta) / sqrt(D) < attachDistance)
	{
		//计算点在直线上的投影R
		//垂线方程Bx - Ay + C0 = 0, 其中C0 = A * y0 - B * x0
		//垂线和直线的交点即是投影R((-A*C-B*C0)/D, (A*C0-B*C)/D)
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