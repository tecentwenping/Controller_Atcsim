#ifndef _WAIRCRAFT_GLYPH_H_
#define _WAIRCRAFT_GLYPH_H_

#include <list>
#include "wpen.h"
#include "wfont.h"
#include "wbrush.h"
#include "wgraphicsitem.h"
#include "wfunctormanager_1.h"
#include "wmatrix.h"
#include "core/wpen.h"
#include "core/wgraphicsitem.h"
#include <boost/shared_ptr.hpp>
#include "EnumVarible.h"
#include "wgraphicslineitem.h"
#include "boost/thread/shared_mutex.hpp"

using namespace boost;

static const int AIRCRAFT_NOR = 0;

class Mosaic;
class WEvent;
class WBlockData;
class WAircraftGlyph;
class WAircraftItemData;
class WGraphicsView;


class WLabelEventFeedback
{
public:
	enum event_type
	{
		none = 0,
		mouse_move = 1,
		mouse_press = 2,
		mouse_release = 3,
		mouse_double_click = 4,
		label_selected = 5,
		label_deselected = 6,
	};

	enum event_area_type
	{
		gly_none = 0,
		gly_aircraft,	// 点击航迹符合
		gly_label,			// 点击标牌
	};

	WLabelEventFeedback() : m_item(0), m_itemData(0), m_blockData(0), m_eType(none), m_event(0)
	{
	}

	WAircraftGlyph* m_item;
	WAircraftItemData* m_itemData;
	WBlockData* m_blockData;
	event_type m_eType;
	event_area_type m_eAreaType;
	Ws::MouseButtons m_buttons;
	Ws::KeyboardModifiers m_modifiers;
	WEvent* m_event;
	WPointF m_pos; // screen pos
	WRectF m_rect; // screen rect
};

class WBlockData
{
public:
	int m_iId; //block identifier, may be used in event callback(s)
	WRectF m_boundingRect; //block's bounding rect
	bool m_bShowBounding; //whether to draw bounding rect
	std::wstring m_text; //block text
	WFont m_font; //font to draw text
	WPen m_penText; //pen to draw text
	WPen m_penBounding; //pen to draw bounding rect
	WBrush m_brush; //brush to draw bounding rect
};

class WAircraftItemData : public WItemData
{
	typedef boost::shared_ptr<WPointF> PointPtr;
public:
	WAircraftItemData();
public:
	int m_iId; //aircraft identifier
	int m_AircraftType;  //not USE
	AIRCRAFT_SYMBOL_TYPE m_eSymbolType;
	int m_nHeading;
	WPen m_pen; //pen to draw aircraft // not USE
	WColor m_SymbolColor; //aircraft's symbol color
	WPointF m_pos; //aircraft position
	WPointF m_PRLPos;
	std::vector<PointPtr> *m_vHistory;
	bool m_bShowAcft;
	bool m_bShowLabel;

	WRectF m_boundingRect; //label's bounding rect, warning: bounding rect's left bottom point is just offset value.
	WRectF m_showRect; // label's show rect
	bool m_bShowBounding; //whether to draw bounding rect
	WPen m_penBounding; //pen to draw bounding rect
	WBrush m_brush; //brush to draw bounding rect
	WPen m_penBoundingSel; //pen to draw bounding rect when label is selected
	WBrush m_brushSel; //pen to draw bounding rect when label is selected
	WPen m_penLine; //pen to draw the line between label and aircraft
	std::list<WBlockData> m_blocks; //blocks
};

//typedef WGraphicsLineItem WAircraftPreLineGlpyh;
//class WAircraftTailLineGlyph;

class WAircraftGlyph : public WGraphicsItem
{
	friend Mosaic;

public:
	typedef WAircraftItemData data_type;
	typedef WFunctorManager_1<const WLabelEventFeedback&, WAircraftGlyph*> WLabelCallbackManager;

public:
	explicit WAircraftGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);

	virtual bool contains(const WWorldPointF& point) const; //图元是否包含指定点
	virtual WWorldRectF boundingRect() const; //图元的边界区域

	data_type* data(); //图元核心数据
	const data_type* data() const;

	static WLabelCallbackManager& getCallbackManager();

	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);

	void setLabelLine(double length, double direction); //标牌线的矢量长度

	static void setLabelFont(const WFont& font); //标牌字体
	static WFont getLabelFont();
	static void setLineMaxLength(double length); //标牌线的最大长度
	static double getLineMaxLength();
	static void setLabelAvoidanceEnabled(bool enable); //标牌是否支持避让
	static bool getLabelAvoidanceEnabled();

	//whether show history point
	static void setLabelShowHistoryEnabled(bool enable);
	static bool getLabelShowHistoryEnabled();
	static void SetHistoryNum(const int iNum);

	//whether show preline
	static void setLableShowPreLineEnabled(bool enable);
	static bool getLabelShowPreLineEnabled();

	WBlockData* getBlockById(const int id);
	const WRectF& getBoundRectView() const {return m_cd.boundingRect;}

	//! cache的使用最好是所有都计算完成后才使用
	// cache的目的，为了保证绘制的时候与外部数据变更的控制，达到数据同步都在
	// updateCache的内部进行处理
	void updateCache(); // 更新本地缓存

private:
	WBlockData* getActivatedBlock(const WPointF& pos);
	void DrawLabelLine(WPainter* painter, const WPointF& p, const WRectF& r);

	void DrawAircraft(WPainter* painter, const WPointF& acftPos);
private:
	static WFont m_sLabelFont;
	static double m_sLineMaxLength;
	static bool m_sLabelAvoidance;
	static bool m_sShowHistoryPoint;
	static bool m_sShowPreLine;
	static int  m_sHstNum;

	struct cached_data
	{
		WMatrix labelMatrix_1; //label's inverted matrix in order to get event callbacks // for current view
		WRectF boundingRect; //bounding rect of label, view matrix   // for current view
		WMatrix aircraftMatrix; //aircraft's mapping matrix          // for current view
	};
	cached_data m_cd;// current view's cached_data

	std::list<WBlockData> m_blocks; //label content cache data

	boost::shared_mutex m_cache_locker; // cache data locker
	std::map<WGraphicsView*, cached_data> m_vcd;
};


//以下代码先保留，主要为后面可能进行拆分WAircraftGlyph用
//现在存在原因是：拆分的子类加入WGraphicsLayer问题，在WAircraftGlyph中是不好控制加入的
//暴露在外部类来控制，会带来管理的复杂
//class WAircraftTailLineGlyph : public WGraphicsItem
//{
//public:
//	typedef WAircraftItemData data_type;
//
//public:
//	explicit WAircraftTailLineGlyph(data_type* d) : WGraphicsItem(d) {}
//	
//	void paint(WPainter* painter)
//	{
//		data_type& d = *data();
//
//		painter->setPen(WPen(Ws::SolidLine, WColor(d.m_SymbolColor), 0));
//		//show history
//		for (size_t i = 0; i < d.m_vHistory->size(); ++i)
//		{
//			static const double R = 0.8;
//			WPointF p(d.m_vHistory->at(i)->x(), d.m_vHistory->at(i)->y());
//			painter->drawEllipse(WRectF(p.x() - R, p.y() - R, R * 2, R * 2)); //尾迹点
//		}
//	}
//
//	WWorldRectF boundingRect() const
//	{
//		//GlobleConfig::MaxHistoryPt;
//
//		const data_type& d = *data();
//		std::vector<WPointF> vHistory;
//		vHistory.reserve(5000);
//		size_t size = d.m_vHistory->size();
//		for (size_t i = 0; i < size; ++i)
//		{
//			vHistory.push_back(WPointF(d.m_vHistory->at(i)->x(), d.m_vHistory->at(i)->y()));
//		}
//		WWorldRectF rect_history = WPolylineF(vHistory).boundingRect();
//
//		return rect_history;
//	}
//
//	data_type* data()
//	{
//		return W_D(); 
//	}
//
//	const data_type* data() const
//	{
//		return W_CD();
//	}
//
//};



#endif