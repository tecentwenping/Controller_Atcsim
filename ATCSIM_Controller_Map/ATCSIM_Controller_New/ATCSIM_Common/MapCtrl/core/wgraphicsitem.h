/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsitem.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件主要有类WGraphicsItem和WItemData类
  【其  它】:   
******************************************************************************/
#ifndef _WGRAPHICS_ITEM_H_
#define _WGRAPHICS_ITEM_H_

#include "../wdllimport.h"
#include "wenums.h"
#include "wrttimacro.h"
#include "wworldrect.h"
#include "wuncopyable.h"

class WPen;
class WBrush;
class WPainter;
class WKeyEvent;
class WFocusEvent;
class WGraphicsLayer;
class WGraphicsScene;
class WItemChangeEvent;
class WInputMethodEvent;
class WContextMenuEvent;
class WGraphicsSceneHoverEvent;
class WGraphicsSceneWheelEvent;
class WGraphicsSceneMouseEvent;
class WGraphicsSceneDragDropEvent;

/** 
 \brief                 定义了一些常用的图元类型
\details   
 \author    陈龙
\date      2013/05/23
*/
#define TYPE_ITEM 0 //图元基类
#define TYPE_SHAPE_ITEM 1 //有形状的图元基类
#define TYPE_LINE_ITEM 2 //直线图元
#define TYPE_RECT_ITEM 3 //矩形图元
#define TYPE_POLYGON_ITEM 4 //多边形图元
#define TYPE_ARC_ITEM 5 //弧线图元
#define TYPE_ELLIPSE_ITEM 6 //椭圆图元
#define TYPE_POLYLINE_ITEM 7 //折线图元
#define TYPE_TEXT_ITEM 8 //普通文本图元
#define TYPE_RICH_TEXT_ITEM 9 //富文本图元
#define TYPE_POINT_ITEM 10 //点图元

/** 
 \brief                 此宏主要用于获取图元自身对应的数据指针，
						在获取之前请保证data_type类型被合适的定义了
\details   
 \author    陈龙
\date      2013/05/23
*/
#define W_D() (dynamic_cast<data_type*>(baseData()))

/** 
 \brief                 同上，不同之处是获取的是常量数据
\details   
 \author    陈龙
\date      2013/05/23
*/
#define W_CD() (dynamic_cast<const data_type*>(baseData()))

/** 
 \brief                 同W_D宏，不同之处在于定义了一个变量d用于保存获取的指针
\details   
 \author    陈龙
\date      2013/05/23
*/
#define W_DATA() (data_type* d = W_D())

/** 
 \brief                 同上，不同之处在于保存的是常量指针
\details   
 \author    陈龙
\date      2013/05/23
*/
#define W_CDATA() (data_type* d = W_CD())

/** 
 \brief         WItemData是WGraphicsItem对应的数据类，按规定每种图元都会对应一个数据类
\details  按规定所有的图元都要（直接or间接）从WGraphicsItem继承
			 按规定所有的图元都要有其对应的数据类
			 按规定所有的图元对应的数据类要么从其父类的数据类继承，要么和其父类的数据类是同一类型
 \author    陈龙
\date      2013/05/23
*/
class MAPAPI WItemData //图元数据基类
{
public:
	explicit WItemData(int typ = 0) : type(typ) {}
	
	void destroy() { delete this; }
	virtual WItemData* copy() const { return new WItemData(*this); }

	/**
	\brief      serialize
	\Access    virtual public 
	\param  char * buf 输出缓冲区指针
	\retval     char*  = buf + 此对象序列化大小
	\remark    图元的序列化操作
					在子类中序列化的时候请不要忘记了基类的序列化
	*/
	virtual char* serialize(char* buf) const;

	/**
	\brief      unserialize
	\Access    virtual public 
	\param  const char * buf
	\retval     const char*
	\remark    图元反序列化操作 
	*/
	virtual const char* unserialize(const char* buf);

	/**
	\brief      serialize_size
	\Access    virtual public 
	\retval     size_t
	\remark    此对象序列化大小的字节数 
	*/
	virtual size_t serialize_size() const;

protected:
	virtual ~WItemData() {}

public:
	int type; //图元具体类型，这个在图元识别会用到，
				//所有不同类型的图元被保存到同一容器后，失去了类型信息，
				//用此字段可以判断类型信息
	int layer; //图元所有的图层
};

class MAPAPI WGraphicsItem : public WUncopable //图元基类
{
	//支持动态创建的声明宏
	RTTI_DECL(WGraphicsItem)

public:
	//几乎每一个图元都要定义一个自己相应的数据类为data_type，
	//这个在W_D等系列宏中会用到，可以用来获取自身的真实数据
	//如果一个图元和基类的数据类型是一致的，则不需要这样定义，比如WGraphicsEllipseItem
	typedef WItemData data_type;

public:
	friend class WGraphicsLayer;

    /**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  data_type * d
				d可以为0，此时类内部会动态创建一份数据
				如果d不为0，则数据是外部创建的（请保证数据是用new创建的，请不要将栈上创建的数据传进来），
				则d对象现在属于图元管理了，生命周期由图元负责，图元会在适当的时候删除，
				（请不要在外部将d删除）
	\retval     
	\remark    以核心数据进行构造 
	*/
	explicit WGraphicsItem(data_type* d = 0);

	void destroy();

	WGraphicsScene* scene() const; //图元所在场景

	WGraphicsLayer* layer() const; //图元所在图层

	/**
	\brief      paint
	\Access    virtual public 
	\param  WPainter * painter
	\retval     void
	\remark    这里实现图元的绘制 
	*/
	virtual void paint(WPainter* painter) = 0;

	virtual bool contains(const WWorldPointF& point) const; //图元是否包含指定点
	virtual WWorldRectF boundingRect() const = 0; //图元的边界区域

	// 局部坐标系
	//inline WWorldPointF pos() const;
	//inline void setPos(const WWorldPointF& pos);
	//inline void setPos(double x, double y);
	//inline void setX(double x);
	//inline void setY(double y);
	//inline double x() const;
	//inline double y() const;
	//inline const WMatrix& mapFromScene() const; //scene->item
	//inline const WMatrix& mapToScene() const;
	//inline void moveBy(const WWorldPointF& p);
	//inline void moveBy(double dx, double dy);

	//inline void resetTransform();
	//inline double rotation() const;
	//inline double setRotation(double angle);
	//inline double scale() const;
	//inline double setScale(double factor);
	//inline WWorldRectF sceneBoundingRect() const {}
	//inline WWorldPointF scenePos() const;
	//inline WMatrix sceneTransform() const;

	//void setTransform(const WMatrix& matrix, bool combine = false);
	//const WMatrix& transform() const;

	//以下这些函数目前还没有用到	
	virtual void contextMenuEvent(WContextMenuEvent* event);
	virtual void dragEnterEvent(WGraphicsSceneDragDropEvent* event);
	virtual void dragLeaveEvent(WGraphicsSceneDragDropEvent* event);
	virtual void dragMoveEvent(WGraphicsSceneDragDropEvent* event);
	virtual void dropEvent(WGraphicsSceneDragDropEvent* event);

	virtual void focusInEvent(WFocusEvent* event);
	virtual void focusOutEvent(WFocusEvent* event);

	virtual void hoverEnterEvent(WGraphicsSceneHoverEvent* event);
	virtual void hoverLeaveEvent(WGraphicsSceneHoverEvent* event);
	virtual void hoverMoveEvent(WGraphicsSceneHoverEvent* event);

	virtual void inputMethodEvent(WInputMethodEvent* event);

	/**
	\brief      keyPressEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark    响应键盘的按下事件 
	*/
	virtual void keyPressEvent(WKeyEvent* event);

	/**
	\brief      keyReleaseEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark    响应键盘的按键的释放事件 
	*/
	virtual void keyReleaseEvent(WKeyEvent* event);

	/**
	\brief      mouseMoveEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    响应鼠标的移动事件 
	*/
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mousePressEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    响应鼠标的按下事件 
	*/
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mouseReleaseEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    响应鼠标的释放事件 
	*/
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mouseDoubleClickEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    响应鼠标的双击事件 
	*/
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      wheelEvent
	\Access    virtual public 
	\param  WGraphicsSceneWheelEvent * event
	\retval     void
	\remark     响应鼠标的滚轮事件
	*/
	virtual void wheelEvent(WGraphicsSceneWheelEvent* event);

	/**
	\brief      attachPoint
	\Access    virtual public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\retval     bool
	\remark     此图元的点吸附功能
	*/
	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const; //点吸附功能

	enum { Type = TYPE_ITEM };
	/**
	\brief      type
	\Access    virtual public 
	\retval     int
	\remark     图元的类型，这个可能在图元的动态识别时用到
					 强烈不建议动态修改这个返回值，对于特定类型，它应该总是返回一个不变的数值
	*/
	virtual int type() const; //图元的类型

	/**
	\brief      isEnabled
	\Access    public 
	\retval     bool
	\remark     图元是否有效（此字段目前没有作用）
	*/
	bool isEnabled() const;

	/**
	\brief      isVisible
	\Access    public 
	\retval     bool
	\remark     图元是否可视，不可视的图元将不会在视图上显示
	*/
	bool isVisible() const;

	/**
	\brief      isSelectable
	\Access    public 
	\retval     bool
	\remark     图元是否支持选中操作，不支持选中操作的图元将不会收到场景中的任何消息
	*/
	bool isSelectable() const;

	/**
	\brief      isSelected
	\Access    public 
	\retval     bool
	\remark     图元是否已经选中
	*/
	bool isSelected() const;

	/**
	\brief      isMovable
	\Access    public 
	\retval     bool
	\remark     图元是否支持移动操作（此字段目前没有使用）
	*/
	bool isMovable() const;

	/**
	\brief      isTransformable
	\Access    public 
	\retval     bool
	\remark     图元是否支持矩阵变换（此字段目前没有使用）
	*/
	bool isTransformable() const;

	/**
	\brief      isScalable
	\Access    public 
	\retval     bool
	\remark     图元是否支持放缩，默认是支持的，不支持放缩的图元无论视图如何放大缩小，它的大小不会变化
					 （此字段目前只有在WGraphicsTextItem中用到）
	*/
	bool isScalable() const;

	void setEnabled(bool enabled = true);
	void setVisible(bool visible = true, bool updating = false);
	void setSelectable(bool selectable = true);
	void setSelected(bool selected = true);
	void setMovable(bool movable = true);
	void setTransformable(bool transformable = true);
	void setScalable(bool scalable = true);

	/**
	\brief      requestContextMenu
	\Access    public 
	\param  Ws::ContextMenuFlags flags
	\retval     void
	\remark     请求图元的右键菜单
	*/
	void requestContextMenu(Ws::ContextMenuFlags flags);

	/**
	\brief      onContextMenu
	\Access    virtual public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     响应图元的右键菜单操作
	*/
	virtual void onContextMenu(Ws::ContextMenuFlag flag);
	
	/**
	\brief      data
	\Access    public 
	\retval     data_type*
	\remark     图元对应的核心数据，请最好在每一个具体的图元中都实现此函数
	*/
	data_type* data(); //图元核心数据

	/**
	\brief      data
	\Access    public 
	\retval     const data_type*
	\remark     上述函数的常量版本
	*/
	const data_type* data() const;

	/**
	\brief      copy
	\Access    virtual public 
	\retval     WGraphicsItem*
	\remark     返回图元的一个拷贝，这个对象在此函数内部创建，由此函数的调用者负责删除此对象
	*/
	virtual WGraphicsItem* copy() const; //克隆一个副本

	/**
	\brief      translate
	\Access    virtual public 
	\param  const WWorldPointF & offset
	\retval     void
	\remark     将图元偏移若干单位，这是一个虚函数，由子类负责实现
	*/
	virtual void translate(const WWorldPointF& offset); //平移图元

	/**
	\brief      translate
	\Access    virtual public 
	\param  const WWorldPointF & offset
	\param  bool updating 指定是否立即进行重绘
	\retval     void
	\remark    将图元偏移若干单位 
	*/
	void translate(const WWorldPointF& offset, bool updating);

	/**
	\brief      expand
	\Access    public static 
	\param  WWorldRectF & r
	\retval     WWorldRectF&
	\remark     此函数不推荐使用
	*/
	static WWorldRectF& expand(WWorldRectF& r);

	/**
	\brief      expanded
	\Access    public static 
	\param  const WWorldRectF & r
	\retval     WWorldRectF
	\remark     此函数不推荐使用
	*/
	static WWorldRectF expanded(const WWorldRectF& r);

protected:
	virtual ~WGraphicsItem();

	/**
	\brief      baseData
	\Access    protected 
	\retval     WItemData*
	\remark     返回基类型数据
	*/
	WItemData* baseData();

	/**
	\brief      baseData
	\Access    protected 
	\retval     const WItemData*
	\remark     上述函数的常量版本
	*/
	const WItemData* baseData() const;

private:
	/**
	\brief      setLayer
	\Access    private 
	\param  WGraphicsLayer * layer
	\retval     void
	\remark     设置图元的图层
	*/
	void setLayer(WGraphicsLayer* layer);

protected:
	//CP -> control point
	static const double CP_ROTATE_HEADER; //旋转控制点到矩形框的距离
	static const double CP_RADIUS; //控制点显示的半径大小
	static const WPen CP_PEN; //绘制控制点的画笔
	static const WPen CP_SEL_PEN; //绘制被选中的控制点的画笔
	static const WPen DRAG_PEN; //图元被拖动时绘制画笔
	static const WBrush CP_BRUSH; //控制点的画刷
	static const WPen HOVER_PEN; //鼠标悬浮在图元上的画笔
	static const WBrush ROTATE_BRUSH; //旋转控制点的画刷
	static const double ATTACH_DISTANCE; //实现吸附功能时的吸附距离
	static const double ATTACH_DISTANCE_SQUARE; //上述距离的平方

private:
	bool _enabled; //图元是否可用
	bool _visible; //图元是否可视
	bool _selectable; //图元是否可以被选择
	bool _selected; //图元是否被选择了
	bool _movable; //图元是否可以移动
	bool _transformable; //图元是否支持矩阵变换
	bool _scalable; //图元是否支持缩放操作

	WGraphicsLayer* _layer; //图元所在图层
	WItemData* _data; //图元的核心数据
};

#endif