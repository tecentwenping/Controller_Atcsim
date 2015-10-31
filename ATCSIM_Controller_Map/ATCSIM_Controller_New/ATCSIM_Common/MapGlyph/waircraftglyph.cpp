#include <boost/foreach.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/thread/detail/singleton.hpp>
#include <boost/integer/static_min_max.hpp>
#include "wevent.h"
#include "wpainter.h"
#include "wpainterproxy.h"
#include "wgraphicsscene.h"
#include "wgraphicschange.h"
#include "waircraftglyph.h"
#include "guitransform.h"
#include "core/wpainter.h"
#include "core/wpainterproxy.h"
#include "Mosaic.h"
#include "witemshareprivate.h"
#include "wgraphicsview.h"


double WAircraftGlyph::m_sLineMaxLength = 500.0;
WFont WAircraftGlyph::m_sLabelFont("GulimChe", 14, 75);
bool WAircraftGlyph::m_sLabelAvoidance = false;
bool WAircraftGlyph::m_sShowHistoryPoint = false;
bool WAircraftGlyph::m_sShowPreLine = false;
int WAircraftGlyph::m_sHstNum = 10;

struct Point
{
	int x;
	int y;
};

//////////////////////////////////////////////////////////////////////////
// �ɻ����� �ṹ, ���ڷɻ����εĶ���λ�����
typedef struct __DetailedAircraft
{
	Point points[128];// �˵���Ϣ
	unsigned long point_num;// �˵���Ŀ
} DetailedAircraft;

// �ɻ���С��Ŀ.    20041201 ĿǰΪ A, B, C/D ����
static const int aircraft_size_num = 3;

//�ɻ�������Ϣ. �����ǵ����ɻ�, �����˫��
//����������wubo 2012-01-12
//����10x10������ϵ������������ĺ���
static const DetailedAircraft aircrafts[] = 
{
	{
		{
			{ 0, -5},// ͷ
			{-1, -4}, {-1, -2}, {-5, -2}, {-4, -1}, {-1, -1}, {-1,  3},
			{-3,  3}, 
			{ 0,  5},// β
			{ 3,  3}, { 1,  3}, { 1, -1}, { 4, -1}, { 5, -2},
			{ 1, -2}, { 1, -4}
		},
			16
	},// ����С�ɻ�

	{
		{
			{ 0, -6},// ͷ
			{-1, -5}, {-1, -2}, {-7, -2}, {-7, -1}, {-6,  0}, {-1,  0},
			{-1,  4}, {-3,  4}, {-3,  5}, {-1,  5}, 
			{ 0,  8},// β
			{ 1,  5}, { 3,  5}, { 3,  4}, { 1,  4}, { 1,  0},
			{ 6,  0}, { 7, -1}, { 7, -2}, { 1, -2}, { 1, -5}
		},
			22
		},// �����зɻ�

		{
			{
				{ 0, -9},// ͷ
				{-1, -8}, {-1, -3}, {-9, -3}, {-9, -2}, {-8, -1}, {-1, -1},
				{-1,  5}, {-4,  5}, {-4,  6}, {-1,  6}, 
				{ 0,  9},// β
				{ 1,  6}, { 4,  6}, { 4,  5}, { 1,  5}, { 1, -1},
				{ 8, -1}, { 9, -2}, { 9, -3}, { 1, -3}, { 1, -8}
			},
				22
		},// ������ɻ�

		{
			{
				{ 0, -5},// ͷ
				{-1, -4}, {-1, -2}, {-2, -2}, {-3, -3}, {-4, -2}, {-5, -2},
				{-3,  0}, {-2, -1}, {-1, -1}, {-1,  3}, {-3,  3}, 
				{ 0,  5},// β
				{ 3,  3}, { 1,  3}, { 1, -1}, { 2, -1}, { 3,  0},
				{ 5, -2}, { 4, -2}, { 3, -3}, { 2, -2}, { 1, -2}, { 1, -4}
			},
				24
			},// ˫��С�ɻ�

			{
				{
					{ 0, -6},// ͷ
					{-1, -5}, {-1, -2}, {-2, -2}, {-4, -4}, {-6, -2}, {-7, -2},
					{-7, -1}, {-6,  0}, {-5,  0}, {-4,  1}, {-3,  0}, {-1,  0},
					{-1,  4}, {-3,  4}, {-3,  5}, {-1,  5}, 
					{ 0,  8},// β
					{ 1,  5}, { 3,  5}, { 3,  4}, { 1,  4}, { 1,  0},
					{ 3,  0}, { 4,  1}, { 5,  0}, { 6,  0}, { 7, -1}, { 7, -2},
					{ 6, -2}, { 4,  -4}, { 2, -2}, { 1, -2}, { 1, -5}
				},
					34
			},// ˫���зɻ�

			{
				{
					{ 0, -12},// ͷ
					{-1, -11}, {-1, -3}, {-3, -3}, {-5, -5}, {-7, -3}, {-12, -3},
					{-12, -2}, {-8, -1}, {-6, -1}, {-5,  0}, {-4, -1}, {-2, -1},
					{-2,  5}, {-2,  5}, {-2,  6}, {-1,  9}, 
					{ 0,  10},// β
					{ 1,  9}, { 2,  6}, { 2,  5}, { 2,  5}, { 2, -1},
					{ 4, -1}, { 5,  0}, { 6, -1}, { 8, -1}, { 12, -2}, { 12, -3},
					{ 7, -3}, { 5, -5}, { 3, -3}, { 1, -3}, { 1, -11}
				},
					34
				},// ˫����ɻ�
};
//////////////////////////////////////////////////////////////////////////

WAircraftItemData::WAircraftItemData() :
				m_AircraftType(AIRCRAFT_NOR),
					m_bShowBounding(false),
					m_bShowAcft(true),
					m_vHistory(NULL),
					m_bShowLabel(true),
					m_eSymbolType(SYMBOL_COMBINED)
{
	m_SymbolColor.setRgb(137, 237, 153);
}

WAircraftGlyph::WAircraftGlyph(data_type* d) : WGraphicsItem(d ? d : new data_type)
{
}

void WAircraftGlyph::setLabelFont(const WFont& font)
{
	m_sLabelFont = font;
}

WFont WAircraftGlyph::getLabelFont()
{
	return m_sLabelFont;
}

void WAircraftGlyph::setLineMaxLength(double length)
{
	m_sLineMaxLength = length;
}

double WAircraftGlyph::getLineMaxLength()
{
	return m_sLineMaxLength;
}

void WAircraftGlyph::setLabelAvoidanceEnabled(bool enable)
{
	m_sLabelAvoidance = enable;
}

bool WAircraftGlyph::getLabelAvoidanceEnabled()
{
	return m_sLabelAvoidance;
}

void WAircraftGlyph::paint(WPainter* painter)
{
	data_type& d = *data();
	painter->setBrush(WBrush(Ws::NoBrush));
	m_cd.aircraftMatrix = painter->worldTransform();
	m_cd.labelMatrix_1 = m_cd.aircraftMatrix.inverted();
	const WMatrix& mapToView = m_cd.aircraftMatrix;
	painter->setWorldTransform(WMatrix());

	WColor symbolColor = d.m_SymbolColor;

	WPointF view_aircraft_pos_f = mapToView.map(d.m_pos);

	static const double R = 10.0;
	static const double RS = 15.0; //draw a bigger circle around, when aircraft is selected

	double x = view_aircraft_pos_f.x();
	double y = view_aircraft_pos_f.y();
	if (d.m_eSymbolType == SYMBOL_COMBINED/*AIRCRAFT_NOR*/)
	{
		
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}

		//tmp  
		painter->drawEllipse(WRectF(x - R, y - R, R * 2, R * 2));
		painter->drawLine(WLineF(x - R, y, x + R, y));
		painter->drawLine(WLineF(x, y - R, x, y + R));

		//DrawAircraft(painter, view_aircraft_pos);
	}
	else if (d.m_eSymbolType == SYMBOL_PRIMARY)//һ���״�
	{
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}
		painter->drawLine(WLineF(x - R, y, x + R, y));
		painter->drawLine(WLineF(x, y - R, x, y + R));
	}
	else if (d.m_eSymbolType == SYMBOL_SECONDARY)//�����״�
	{
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}
		painter->drawEllipse(WRectF(x - R, y - R, R * 2, R * 2));
	}
	else if (d.m_eSymbolType == SYMBOL_PLAN)//�ƻ�����
	{
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}
		painter->drawRect(WRectF(x - R, y - R, R * 2, R * 2));
	}
	else if (d.m_eSymbolType == SYMBOL_COAST)//����ä��
	{
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}
		WPen pen;
		pen.setWidth(4);
		pen.setColor(WColor(255, 255, 255));
		painter->setPen(pen);
		painter->drawLine(WWorldLineF(x - R, y, x - R / 2, y));
		painter->drawLine(WWorldLineF(x + R, y, x + R / 2, y));
		painter->drawLine(WWorldLineF(x, y - R, x, y - R / 2));
		painter->drawLine(WWorldLineF(x, y + R, x, y + R / 2));
		pen.setWidth(1);
		pen.setColor(symbolColor);
		painter->setPen(pen);
	}
	else if (d.m_eSymbolType == SYMBOL_SPI)//����SPI�澯״̬
	{
		painter->setPen(WPen(symbolColor));
		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - RS, y - RS, RS * 2, RS * 2));
		}
		painter->drawLine(WLineF(x - R, y, x + R, y));
		painter->drawLine(WLineF(x, y - R, x, y + R));
		WPen pen;
		pen.setStyle(Ws::DashLine);
		pen.setColor(WColor(255, 255, 255));
		painter->setPen(pen);
		painter->drawEllipse(WRectF(x - R, y - R, R * 2, R * 2));
		pen.setStyle(Ws::SolidLine);
		pen.setColor(symbolColor);
		painter->setPen(pen);
	}
	else if (d.m_eSymbolType == SYMBOL_VEHICLE)//��������(ʵ������)
	{
		painter->setPen(WPen(symbolColor));
		painter->setBrush(WBrush(symbolColor, Ws::SolidPattern));
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(x, y - 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(x - 5, y + 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(x + 5, y + 5);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
		painter->setBrush(WBrush(Ws::NoBrush));

		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - R, y - R, R * 2, R * 2));
		}

	}
	else if (d.m_eSymbolType == SYMBOL_ADSB) // ADSB�ݶ����ţ��ο�Indra�ֲᣩʵ������
	{
		painter->setPen(WPen(symbolColor));
		painter->setBrush(WBrush(symbolColor, Ws::SolidPattern));
		WPointF Tmppoint;
		std::vector<WPointF> vPoints;
		Tmppoint.setXY(x, y - 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(x - 5, y);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(x, y + 5);
		vPoints.push_back(Tmppoint);
		Tmppoint.setXY(x + 5, y);
		vPoints.push_back(Tmppoint);
		painter->drawPolygon(WWorldPolygonF(vPoints));
		painter->setBrush(WBrush(Ws::NoBrush));

		if (isSelected())
		{
			painter->drawEllipse(WRectF(x - R, y - R, R * 2, R * 2));
		}
	}
	else if (d.m_eSymbolType == SYMBOL_PIC_AIRCRAFT || d.m_eSymbolType == SYMBOL_PIC_HELICOPTER)
	{
		painter->setPen(WPen(symbolColor));
		painter->setBrush(WBrush(symbolColor, Ws::SolidPattern));
		painter->setBrush(WBrush(Ws::NoBrush));
		painter->setRenderHint(Ws::SmoothPixmapTransform);

		WPixmap pixmap(d.m_eSymbolType == SYMBOL_PIC_AIRCRAFT ? ":/plane.png" : ":/helicopter.png");
		WPixmap newPixmap = pixmap.xrotated(-90 + d.m_nHeading, Ws::SmoothTransformation);
		painter->drawPixmap(view_aircraft_pos_f-WPointF(newPixmap.width()/2, newPixmap.height()/2), newPixmap);
	}

	WLineF line(WPointF(), d.m_boundingRect.center());
	if (line.length() > m_sLineMaxLength)
	{
		line.setLength(m_sLineMaxLength);
		WPointF offPoint = line.p2() - d.m_boundingRect.center();
		d.m_boundingRect.translate(offPoint);
		d.m_showRect.translate(offPoint);
	}

	WPointF view_label_pos_f = d.m_boundingRect.bottomLeft() + view_aircraft_pos_f;// aircraft pos + label offset pos
	WPointF offset_f = d.m_showRect.bottomLeft() - d.m_boundingRect.bottomLeft();
	WRectF view_label_rect(WRectF(view_label_pos_f, WSizeF(d.m_boundingRect.width(), d.m_boundingRect.height())));
	//���Ʊ���
	if (m_sLabelAvoidance)
	{
		const WRectF& r = view_label_rect;
		Mosaic::Instance().Allocate(reinterpret_cast<int>(this), r.left(), r.bottom(), r.right(), r.top());
	}

	// label show rectָ���Ʊ߿���ʾ���򣬱�����ʱ����Ҫ��ʾ�߿򣬱߿�������������ܲ�һ�£���C��ʾ
	WRectF label_show_rect(WRectF(view_label_rect.bottomLeft(), WSizeF(d.m_showRect.width(), d.m_showRect.height())));
	label_show_rect.translate(offset_f);

	//show history
	// β��������ⲿ���ݣ���Ӧ�ü����������ⲿĬ�Ϸ����˺ܴ����ݴ��ڣ��ҵ�����һ�����ӵ�Ĭ�����ֵ
	// �ڲ�ͨ���±���ʲ���������
	// ���ⲿ����������С���ͱ���ü�������
	if (m_sShowHistoryPoint && d.m_vHistory != NULL 
		&& d.m_vHistory->size() > 1)
	{
		size_t n = d.m_vHistory->size() - 1;
		size_t count = (m_sHstNum < n) ? m_sHstNum : n;
		size_t pos = n - 1;
		for (size_t i = 0; i < count; ++i, --pos)
		{
			static const double R = 0.8;
			double dx = 0.00;
			double dy = 0.00;
			mapToView.map((*d.m_vHistory)[pos]->x(), (*d.m_vHistory)[pos]->y(), &dx, &dy);
			painter->drawEllipse(WRectF(dx - R, dy - R, R * 2, R * 2)); //β����
		}
	}

	//show preline
	if (m_sShowPreLine)
	{
		painter->drawLine(WLineF(view_aircraft_pos_f, mapToView.map(d.m_PRLPos))); //Ԥ����
	}

	
	if (d.m_bShowLabel)
	{
		//show linkline ���ڲ���������һ����һ�������ĵ�����ֻ������һ�㵽���α߿���㷨��
		DrawLabelLine(painter, view_aircraft_pos_f, label_show_rect);

		WPainterProxy proxy(painter);
		painter->setRenderHint(Ws::Antialiasing, false); // ���ƾ��ε�ʱ��ȥ������ݣ�Ч������
		painter->setRenderHint(Ws::TextAntialiasing, false);

		if (d.m_bShowBounding)
		{	
			painter->setPen(d.m_penBounding); // ���Ʊ߿���ɫ�뺽���������ı��Ƿֿ���
			painter->drawRect(label_show_rect);
		}

		//show label
		painter->setFont(m_sLabelFont);

		m_cache_locker.lock();   // �Է���d.m_blocks���м����������߳���FormatLable��ʱ���������֯m_blocks���ݣ�������Ҫͬ������
		BOOST_FOREACH(const WBlockData& block, m_blocks)
		{
			painter->setPen(block.m_penText);
			WRectF r = block.m_boundingRect.translated(view_label_pos_f);
			painter->drawText(r, Ws::AlignCenter, block.m_text);
		}
		m_cache_locker.unlock();
	}

	// for test bounding rect, don't delete, 
	/*{
		WPainterProxy proxy(painter);
		painter->setWorldTransform(m_cd.aircraftMatrix);
		painter->setPen(WPen(Ws::DashDotDotLine, WColor(255, 0, 0), 0));
		painter->drawRect(boundingRect());
	}*/

	m_cd.boundingRect = view_label_rect; // save
	WGraphicsView* m_curView = painter->device();
	m_vcd[m_curView] = m_cd; // save for current view
	painter->setWorldTransform(m_cd.aircraftMatrix);
}

void WAircraftGlyph::DrawAircraft(WPainter* painter, const WPointF& acftPos)
{
	DetailedAircraft acft = aircrafts[5];
	int radius;           // ����ɻ����ε㵽�ɻ������е�ľ���, ������ת
	double angle;         // ����ɻ����ε�����ڷɻ������е�ľ���, ������ת
	double temp_x, temp_y;// ���ε���ת���ֵ, ������ת

	data_type& d = *data();
	int theta = d.m_nHeading;
	angle = theta + 0.00;
	WPointF point;
	std::vector<WPointF> vPoint;
	for (int i = 0; i < (int)acft.point_num; ++i)
	{
		radius = (int)sqrt((double)(acft.points[i].x * acft.points[i].x + acft.points[i].y * acft.points[i].y));
		// 		//angle = aircraft_direction[acft_code];
		// 		// ����ʾ�Ƕȵ�����: �ɻ�����ģ�����Ի���ֱ��Y��, ��ͷָ��Y�Ḻ����(Windows ��������ϵ)ȡ�õ����ε�
		// 		// ���Ƕ�����������X������Ϊ����
		// 		// �������֮�������90��, ��Ҫ��������
		angle = atan2(acft.points[i].x + 0.0f, acft.points[i].y + 0.0f) + M_PI/2.0;
		//angle = atan2(acft.points[i].x + 0.0f, acft.points[i].y + 0.0f) + PI/2;
		angle +=  theta*M_PI/180;
		temp_x = radius * cos(angle);
		temp_y = radius * sin(angle);
		(temp_x >= 0.0) ? (temp_x += 0.5) : (temp_x -= 0.5);
		(temp_y >= 0.0) ? (temp_y += 0.5) : (temp_y -= 0.5);
		acft.points[i].x = (int)temp_x;
		acft.points[i].y = (int)temp_y;
		acft.points[i].x += acftPos.x();
		acft.points[i].y += acftPos.y();

		point.setXY(acft.points[i].x, acft.points[i].y);
		vPoint.push_back(point);
	}

	painter->drawPolygon(WWorldPolygonF(vPoint));

}

bool WAircraftGlyph::contains(const WWorldPointF& point) const
{
	static const double R = 10.0;

	const data_type& d = *data();
	bool contain = false;
	if (d.m_bShowLabel)
	{
		contain = d.m_boundingRect.translated(m_cd.aircraftMatrix.map(d.m_pos)).contains(m_cd.aircraftMatrix.map(point));
	}
	return contain | (::distance(point, d.m_pos) < R / m_cd.aircraftMatrix.m11());
}



WWorldRectF WAircraftGlyph::boundingRect() const
{
	static const double R = 15.0;
	static const double PEN_WIDTH = 2.0;
	

	const data_type& d = *data();

	const WPointF& p = d.m_pos;


	WRectF rect_history(d.m_pos.x(), d.m_pos.y(), 0, 0);

	if (m_sShowHistoryPoint && d.m_vHistory != NULL
		&& d.m_vHistory->size() > 1)
	{
		std::vector<WPointF> vHistory;
		vHistory.reserve(5000);
		size_t n = d.m_vHistory->size() - 1;
		size_t size = (m_sHstNum < n) ? m_sHstNum : n;
		size_t pos = n - 1;
		for (size_t i = 0; i < size; ++i, --pos)
		{
			vHistory.push_back(WPointF((*d.m_vHistory)[pos]->x(), (*d.m_vHistory)[pos]->y()));
		}
		rect_history = WPolylineF(vHistory).boundingRect();
	}

	
	WRectF rect_prl(d.m_pos.x(), d.m_pos.y(), 0, 0);
	if (m_sShowPreLine)
	{
		rect_prl = ::boundingRect(d.m_pos, d.m_PRLPos);
	}
	WRectF rect_aircraft = m_cd.labelMatrix_1.mapRect(WRectF(
		m_cd.aircraftMatrix.map(p).x() - R, m_cd.aircraftMatrix.map(p).y() - R, R * 2, R * 2));
	WRectF rect_label(d.m_pos.x(), d.m_pos.y(), 0, 0);
	if (d.m_bShowLabel)
	{
		rect_label = m_cd.labelMatrix_1.mapRect(
			d.m_boundingRect.translated(m_cd.aircraftMatrix.map(d.m_pos)).adjusted(-PEN_WIDTH, -PEN_WIDTH,
			PEN_WIDTH, PEN_WIDTH));
	}

	return rect_history | rect_prl | rect_aircraft | rect_label;  // scene rect
}

WAircraftGlyph::data_type* WAircraftGlyph::data()
{
	return W_D();
}

const WAircraftGlyph::data_type* WAircraftGlyph::data() const
{
	return W_CD();
}

WAircraftGlyph::WLabelCallbackManager& WAircraftGlyph::getCallbackManager()
{
	return boost::detail::thread::singleton<WLabelCallbackManager>::instance();
}

WBlockData* WAircraftGlyph::getActivatedBlock(const WPointF& pos)
{
	data_type& d = *data();
	WPointF p = m_cd.aircraftMatrix.map(pos) - m_cd.aircraftMatrix.map(d.m_pos);//
	p -= d.m_boundingRect.bottomLeft();
	
	//std::list<WBlockData>& blocks = data()->m_blocks;

	m_cache_locker.lock();
	BOOST_FOREACH(WBlockData& block, m_blocks) // block data���Ǿֲ�����
	{
		if (block.m_boundingRect.contains(p))
		{
			m_cache_locker.unlock();
			return &block;
		}
	}
	m_cache_locker.unlock();

	return 0;
}

WBlockData* WAircraftGlyph::getBlockById(const int id)
{
	m_cache_locker.lock();
	BOOST_FOREACH(WBlockData& block, m_blocks) // block data���Ǿֲ�����
	{
		if (block.m_iId == id)
		{
			m_cache_locker.unlock();
			return &block;
		}
	}

	m_cache_locker.unlock();
	return 0;
}

static void fill_label_event_feedback(WLabelEventFeedback& feedback, WAircraftGlyph* item, 
									  WGraphicsSceneMouseEvent* event)
{
	feedback.m_item = item;
	feedback.m_itemData = item->data();
	feedback.m_buttons = event->buttons();
	feedback.m_modifiers = event->modifiers();
	feedback.m_event = event;
}

void WAircraftGlyph::mouseMoveEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected())
	{
		if (event->buttons() & Ws::LeftButton) //drag move
		{
			WGraphicsView* m_curView = event->widget();
			m_cd = m_vcd[m_curView];
			WPointF p = m_cd.aircraftMatrix.map(event->scenePos()) - m_cd.aircraftMatrix.map(event->lastScenePos());
			data()->m_boundingRect.translate(p);
			data()->m_showRect.translate(p);
			scene()->update();
		}
	}
}

void WAircraftGlyph::mousePressEvent(WGraphicsSceneMouseEvent* event)
{
	WGraphicsView* m_curView = event->widget();
	m_cd = m_vcd[m_curView];

	static const double R = 10.0;

	const data_type& d = *data();
	bool contain = false;
	if (d.m_bShowLabel)
	{
		contain = d.m_boundingRect.translated(m_cd.aircraftMatrix.map(d.m_pos)).contains(m_cd.aircraftMatrix.map(event->scenePos()));
	}
	bool bContainAircraft = ::distance(event->scenePos(), d.m_pos) < R / m_cd.aircraftMatrix.m11();

	if (isSelected())
	{
		if (contain | bContainAircraft)
		{
			WLabelEventFeedback feedback;
			fill_label_event_feedback(feedback, this, event);
			feedback.m_eType = WLabelEventFeedback::mouse_press;
			feedback.m_eAreaType = contain ? WLabelEventFeedback::gly_label : WLabelEventFeedback::gly_aircraft;
			feedback.m_blockData = getActivatedBlock(event->scenePos());
			feedback.m_pos = m_cd.aircraftMatrix.map(event->scenePos());
			feedback.m_rect = m_cd.boundingRect;
			getCallbackManager().call(this, feedback);
		}
		else //status transfer, selected ---> not selected
		{
			setSelected(false);
			scene()->update(boundingRect());
			scene()->itemChange(WGraphicsChange(WGraphicsChange::Unselected, this));

			WLabelEventFeedback feedback;
			fill_label_event_feedback(feedback, this, event);
			feedback.m_eType = WLabelEventFeedback::label_deselected;
			feedback.m_pos = m_cd.aircraftMatrix.map(event->scenePos());
			feedback.m_rect = m_cd.boundingRect;
			getCallbackManager().call(this, feedback);
		}
	}
	else if (contain | bContainAircraft) //status transfer, not selected ---> selected
	{
		setSelected();
		scene()->update(boundingRect());
		scene()->itemChange(WGraphicsChange(WGraphicsChange::Selected, this));

		WLabelEventFeedback feedback;
		fill_label_event_feedback(feedback, this, event);
		feedback.m_eType = WLabelEventFeedback::label_selected;
		feedback.m_eAreaType = contain ? WLabelEventFeedback::gly_label : WLabelEventFeedback::gly_aircraft;
		feedback.m_blockData = getActivatedBlock(event->scenePos());
		feedback.m_pos = m_cd.aircraftMatrix.map(event->scenePos());
		feedback.m_rect = m_cd.boundingRect;
		getCallbackManager().call(this, feedback);
	}

}

void WAircraftGlyph::mouseReleaseEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected())
	{
		WLabelEventFeedback feedback;
		fill_label_event_feedback(feedback, this, event);
		feedback.m_eType = WLabelEventFeedback::mouse_release;
		feedback.m_blockData = getActivatedBlock(event->scenePos());
		feedback.m_pos = m_cd.aircraftMatrix.map(event->scenePos());
		feedback.m_rect = m_cd.boundingRect;
		getCallbackManager().call(this, feedback);
	}
}

void WAircraftGlyph::mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event)
{
	if (isSelected())
	{
		static const double R = 10.0;

		const data_type& d = *data();
		bool contain = d.m_boundingRect.translated(m_cd.aircraftMatrix.map(d.m_pos)).contains(m_cd.aircraftMatrix.map(event->scenePos()));
		bool bContainAircraft = ::distance(event->scenePos(), d.m_pos) < R / m_cd.aircraftMatrix.m11();

		WLabelEventFeedback feedback;
		fill_label_event_feedback(feedback, this, event);
		feedback.m_eType = WLabelEventFeedback::mouse_double_click;
		feedback.m_eAreaType = contain ? WLabelEventFeedback::gly_label : WLabelEventFeedback::gly_aircraft;
		feedback.m_blockData = getActivatedBlock(event->scenePos());
		feedback.m_pos = m_cd.aircraftMatrix.map(event->scenePos());
		feedback.m_rect = m_cd.boundingRect;
		getCallbackManager().call(this, feedback);
	}
}

void WAircraftGlyph::DrawLabelLine( WPainter* painter, const WPointF& p, const WRectF& r )
{
	// draw label line in screen 
	const WPointF& cp = r.center();
	//
	const WPointF& bl = r.bottomLeft();
	const WPointF& tl = r.topLeft();
	const WPointF& tr = r.topRight();

	double x1, y1, x2, y2;
	x1 = tl._x; // l
	x2 = tr._x; // r
	y1 = bl._y; // top
	y2 = tl._y; // bottom
	// y1 < y2

	double x_out;
	double rx_out = p.x();
	double y_out;
	double ry_out = p.y();
	// l & r 
	if (p._x < x1)
	{
		x_out = x1; // x1
		y_out = (cp._y - p._y)*(x_out - p._x)/(cp._x - p._x) + p._y;
		if (y_out >= y1 && y_out <= y2)
		{
			rx_out = x_out;
			ry_out = y_out;
		}
	} 
	else if(p._x > x2)
	{
		x_out = x2; // x2
		y_out = (cp._y - p._y)*(x_out - p._x)/(cp._x - p._x) + p._y;
		if (y_out >= y1 && y_out <= y2)
		{
			rx_out = x_out;
			ry_out = y_out;
		}
	}

	// top & bottom
	if (p._y < y1)
	{
		y_out = y1; // y1
		x_out = (cp._x - p._x)*(y_out - p._y)/(cp._y - p._y) + p._x;
		if (x_out >= x1 && x_out <= x2)
		{
			rx_out = x_out;
			ry_out = y_out;
		}
	}
	else if (p._y > y2)
	{
		y_out = y2; // y2
		x_out = (cp._x - p._x)*(y_out - p._y)/(cp._y - p._y) + p._x;
		if (x_out >= x1 && x_out <= x2)
		{
			rx_out = x_out;
			ry_out = y_out;
		}
	}

	painter->drawLine(WLineF(p._x, p._y, rx_out, ry_out));
}
/**
\brief     setLabelLine
\Access    public 
\param     double length
\param     double direction
\retval    void
\remark     
*/
void WAircraftGlyph::setLabelLine( double length, double direction )
{
	direction *= M_PI / 180;
	WRectF& r = data()->m_boundingRect;
	r.translate(WPointF(length * cos(direction), length * sin(direction)) - r.bottomLeft());
}


/**
\brief     setLabelShowHistoryEnabled
\Access    public static 
\param     bool enable
\retval    void
\remark     
*/
void WAircraftGlyph::setLabelShowHistoryEnabled( bool enable )
{
	m_sShowHistoryPoint = enable;
}

/**
\brief     getLabelShowHistoryEnabled
\Access    public static 
\retval    bool
\remark     
*/
bool WAircraftGlyph::getLabelShowHistoryEnabled()
{
	return m_sShowHistoryPoint;
}

/**
\brief     setLableShowPreLineEnabled
\Access    public static 
\param     bool enable
\retval    void
\remark     
*/
void WAircraftGlyph::setLableShowPreLineEnabled( bool enable )
{
	m_sShowPreLine = enable;
}

/**
\brief     getLabelShowPreLineEnabled
\Access    public static 
\retval    bool
\remark     
*/
bool WAircraftGlyph::getLabelShowPreLineEnabled()
{
	return m_sShowPreLine;
}

/**
\brief      SetHstNum
\Access    public static
\param  const int iNum
\retval     void
\remark     
*/
void WAircraftGlyph::SetHistoryNum( const int iNum )
{
	m_sHstNum = iNum;
}

/**
\brief      updateCache
\Access    public 
\retval     void
\remark     
*/
void WAircraftGlyph::updateCache()
{
	m_cache_locker.lock();
	data_type& d = *data();
	m_blocks.clear();
	m_blocks.resize(d.m_blocks.size());
	//copy data
	m_blocks.assign(d.m_blocks.begin(), d.m_blocks.end());
	m_cache_locker.unlock();
}




