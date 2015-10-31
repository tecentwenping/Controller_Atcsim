#include <QString>
#include "cellformat.h"
#include "../core/wgraphicsitem.h"
#include "../core/wgraphicsarcitem.h"
#include "../core/wgraphicsrectitem.h"
#include "../core/wgraphicslineitem.h"
#include "../core/wgraphicstextitem.h"
#include "../core/wgraphicspointitem.h"
#include "../core/wgraphicsellipseitem.h"
#include "../core/wgraphicsrichtextitem.h"
#include "../core/wgraphicspolylineitem.h"
#include "../core/wgraphicspolygonitem.h"

QString cell_format(const WGraphicsItem& item)
{
	switch(item.type())
	{
	case TYPE_LINE_ITEM : return cell_format(dynamic_cast<const WGraphicsLineItem&>(item));
	case TYPE_RECT_ITEM : return cell_format(dynamic_cast<const WGraphicsRectItem&>(item));
	case TYPE_ELLIPSE_ITEM : return cell_format(dynamic_cast<const WGraphicsEllipseItem&>(item));
	case TYPE_ARC_ITEM : return cell_format(dynamic_cast<const WGraphicsArcItem&>(item));
	case TYPE_POLYGON_ITEM : return cell_format(dynamic_cast<const WGraphicsPolygonItem&>(item));
	case TYPE_POLYLINE_ITEM : return cell_format(dynamic_cast<const WGraphicsPolylineItem&>(item));
	case TYPE_TEXT_ITEM : return cell_format(dynamic_cast<const WGraphicsTextItem&>(item));
	case TYPE_RICH_TEXT_ITEM : return cell_format(dynamic_cast<const WGraphicsRichTextItem&>(item));
	case TYPE_POINT_ITEM : return cell_format(dynamic_cast<const WGraphicsPointItem&>(item));
	default : return QString();
	}
}

QString cell_format(const WGraphicsLineItem& item)
{
	WWorldLineF line = item.line();
	return QString().sprintf("LINE(%.0f, %.0f, %.0f, %.0f) D%.0f\272 H%.0f V%.0f L%.0f", line.x1(), line.y1(), line.x2(), line.y2(), line.angle(), line.dx(), line.dy(), line.length());
}

QString cell_format(const WGraphicsRectItem& item)
{
	WWorldRectF rect = item.rect();
	return QString().sprintf("RECT(%.0f, %.0f, %.0f, %.0f) W%.0f H%.0f", rect.left(), rect.top(), rect.right(), rect.bottom(), rect.width(), rect.height());
}

QString cell_format(const WGraphicsEllipseItem& item)
{
	WWorldRectF rect = item.rect();
	return QString().sprintf("RECT(%.0f, %.0f, %.0f, %.0f) W%.0f H%.0f", rect.left(), rect.top(), rect.right(), rect.bottom(), rect.width(), rect.height());
}

QString cell_format(const WGraphicsArcItem& item)
{
	WWorldRectF rect =item.rect();
	return QString().sprintf("RECT(%.0f, %.0f, %.0f, %.0f) C(%.0f, %.0f) D(%.0f\272, %.0f\272) R(%.0f, %.0f)", 
		rect.left(), rect.top(), rect.right(), rect.bottom(), rect.center().x(), rect.center().y(), 
		item.startAngle(), item.endAngle(), rect.width()/2, rect.height()/2);
}

QString cell_format(const WGraphicsPolygonItem& item)
{
	QString str;
	WWorldPolygonF p = item.polygon();
	
	unsigned size = p.size();
	if (size > 3)
	{
		for (unsigned i=0; i<size-1; ++i)
		{
			str += QString().sprintf("P%d(%.0f, %.0f) ", i+1, p[i].x(), p[i].y());
		}
	}

	return str;
}

QString cell_format(const WGraphicsPolylineItem& item)
{
	QString str;
	WWorldPolylineF p = item.polyline();

	unsigned size = p.size();
	for (unsigned i=0; i<size; ++i)
	{
		str += QString().sprintf("P%d(%.0f, %.0f) ", i+1, p[i].x(), p[i].y());
	}

	return str;
}

QString cell_format(const WGraphicsTextItem& item)
{
	return cell_format(item.pos()) + " " + QString::fromStdString(item.text());
}

QString cell_format(const WGraphicsRichTextItem& item)
{
	return cell_format(item.pos()) + " " + QString::fromStdString(item.text());
}

QString cell_format(const WGraphicsPointItem& item)
{
	return cell_format(item.pos());
}

QString cell_format(const WWorldPointF& point)
{
	return QString().sprintf("P(%.0f, %.0f)", point.x(), point.y());
}