//#ifndef _WLABEL_GLYPH_H_
//#define _WLABEL_GLYPH_H_
//
//#include <list>
//#include "wpen.h"
//#include "wfont.h"
//#include "wbrush.h"
//#include "wgraphicsitem.h"
//#include ".\ATCSIM_Client\src\tool\callback\wfunctormanager_1.h"
//#include "wmatrix.h"
//
//class WEvent;
//class WBlockData;
//class WLabelGlyph;
//class WLabelItemData;
//
//class WLabelEventFeedback
//{
//public:
//	enum event_type
//	{
//		none = 0,
//		mouse_move = 1,
//		mouse_press = 2,
//		mouse_release = 3,
//		mouse_double_click = 4,
//	};
//
//	WLabelEventFeedback() : m_item(0), m_itemData(0), m_blockData(0), m_eType(none), m_event(0)
//	{
//	}
//
//	WLabelGlyph* m_item;
//	WLabelItemData* m_itemData;
//	WBlockData* m_blockData;
//	event_type m_eType;
//	Ws::MouseButtons m_buttons;
//	Ws::KeyboardModifiers m_modifiers;
//	WEvent* m_event;
//};
//
//class WBlockData
//{
//public:
//	int m_iId; //block identifier, may be used in event callback(s)
//	WRectF m_boundingRect; //block's bounding rect
//	bool m_bShowBounding; //whether to draw bounding rect
//	std::wstring m_text; //block text
//	WFont m_font; //font to draw text
//	WPen m_penText; //pen to draw text
//	WPen m_penBounding; //pen to draw bounding rect
//	WBrush m_brush; //brush to draw bounding rect
//};
//
//class WLabelItemData : public WItemData
//{
//public:
//	int m_iId; //label identifier
//	WRectF m_boundingRect; //label's bounding rect
//	WPointF m_posTarget; //aircraft position
//	bool m_bShowBounding; //whether to draw bounding rect
//	WPen m_penBounding; //pen to draw bounding rect
//	WBrush m_brush; //brush to draw bounding rect
//	WPen m_penBoundingSel; //pen to draw bounding rect when label is selected
//	WBrush m_brushSel; //pen to draw bounding rect when label is selected
//	WPen m_penLine; //pen to draw the line between label and aircraft
//	std::list<WBlockData> m_blocks; //blocks
//};
//
//class WLabelGlyph : public WGraphicsItem
//{
//public:
//	typedef WLabelItemData data_type;
//	typedef WFunctorManager_1<const WLabelEventFeedback&, WLabelGlyph*> WLabelCallbackManager;
//
//public:
//	explicit WLabelGlyph(data_type* d = 0);
//
//	static WLabelCallbackManager& getCallbackManager();
//
//	virtual void paint(WPainter* painter);
//	virtual bool contains(const WWorldPointF& point) const; //图元是否包含指定点
//	virtual WWorldRectF boundingRect() const; //图元的边界区域
//
//	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
//	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
//	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);
//	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);
//
//	data_type* data();
//	const data_type* data() const;
//
//	void updateCache();
//
//private:
//	WMatrix getMatrix() const;
//	WMatrix getMatrix_1() const;
//	WBlockData* getActivatedBlock(const WPointF& pos);
//
//private:
//	struct cached_data
//	{
//		cached_data() : fx(1.0), fy(1.0) {}
//
//		double fx;
//		double fy;
//		WPointF labelBottomLeft;
//		WMatrix labelMatrix;
//		WMatrix labelMatrix_1;
//		WPointF labelCenter;
//		std::vector<WRectF> blockRects;
//		std::vector<WRectF> blockMappedRects;
//		std::vector<WMatrix> blockMatries;
//		WRectF boundingRect;
//	};
//	cached_data m_cd;
//};
//
//#endif