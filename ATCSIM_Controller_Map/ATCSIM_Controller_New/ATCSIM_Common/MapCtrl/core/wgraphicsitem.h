/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsitem.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫ����WGraphicsItem��WItemData��
  ����  ����:   
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
 \brief                 ������һЩ���õ�ͼԪ����
\details   
 \author    ����
\date      2013/05/23
*/
#define TYPE_ITEM 0 //ͼԪ����
#define TYPE_SHAPE_ITEM 1 //����״��ͼԪ����
#define TYPE_LINE_ITEM 2 //ֱ��ͼԪ
#define TYPE_RECT_ITEM 3 //����ͼԪ
#define TYPE_POLYGON_ITEM 4 //�����ͼԪ
#define TYPE_ARC_ITEM 5 //����ͼԪ
#define TYPE_ELLIPSE_ITEM 6 //��ԲͼԪ
#define TYPE_POLYLINE_ITEM 7 //����ͼԪ
#define TYPE_TEXT_ITEM 8 //��ͨ�ı�ͼԪ
#define TYPE_RICH_TEXT_ITEM 9 //���ı�ͼԪ
#define TYPE_POINT_ITEM 10 //��ͼԪ

/** 
 \brief                 �˺���Ҫ���ڻ�ȡͼԪ�����Ӧ������ָ�룬
						�ڻ�ȡ֮ǰ�뱣֤data_type���ͱ����ʵĶ�����
\details   
 \author    ����
\date      2013/05/23
*/
#define W_D() (dynamic_cast<data_type*>(baseData()))

/** 
 \brief                 ͬ�ϣ���֮ͬ���ǻ�ȡ���ǳ�������
\details   
 \author    ����
\date      2013/05/23
*/
#define W_CD() (dynamic_cast<const data_type*>(baseData()))

/** 
 \brief                 ͬW_D�꣬��֮ͬ�����ڶ�����һ������d���ڱ����ȡ��ָ��
\details   
 \author    ����
\date      2013/05/23
*/
#define W_DATA() (data_type* d = W_D())

/** 
 \brief                 ͬ�ϣ���֮ͬ�����ڱ�����ǳ���ָ��
\details   
 \author    ����
\date      2013/05/23
*/
#define W_CDATA() (data_type* d = W_CD())

/** 
 \brief         WItemData��WGraphicsItem��Ӧ�������࣬���涨ÿ��ͼԪ�����Ӧһ��������
\details  ���涨���е�ͼԪ��Ҫ��ֱ��or��ӣ���WGraphicsItem�̳�
			 ���涨���е�ͼԪ��Ҫ�����Ӧ��������
			 ���涨���е�ͼԪ��Ӧ��������Ҫô���丸���������̳У�Ҫô���丸�����������ͬһ����
 \author    ����
\date      2013/05/23
*/
class MAPAPI WItemData //ͼԪ���ݻ���
{
public:
	explicit WItemData(int typ = 0) : type(typ) {}
	
	void destroy() { delete this; }
	virtual WItemData* copy() const { return new WItemData(*this); }

	/**
	\brief      serialize
	\Access    virtual public 
	\param  char * buf ���������ָ��
	\retval     char*  = buf + �˶������л���С
	\remark    ͼԪ�����л�����
					�����������л���ʱ���벻Ҫ�����˻�������л�
	*/
	virtual char* serialize(char* buf) const;

	/**
	\brief      unserialize
	\Access    virtual public 
	\param  const char * buf
	\retval     const char*
	\remark    ͼԪ�����л����� 
	*/
	virtual const char* unserialize(const char* buf);

	/**
	\brief      serialize_size
	\Access    virtual public 
	\retval     size_t
	\remark    �˶������л���С���ֽ��� 
	*/
	virtual size_t serialize_size() const;

protected:
	virtual ~WItemData() {}

public:
	int type; //ͼԪ�������ͣ������ͼԪʶ����õ���
				//���в�ͬ���͵�ͼԪ�����浽ͬһ������ʧȥ��������Ϣ��
				//�ô��ֶο����ж�������Ϣ
	int layer; //ͼԪ���е�ͼ��
};

class MAPAPI WGraphicsItem : public WUncopable //ͼԪ����
{
	//֧�ֶ�̬������������
	RTTI_DECL(WGraphicsItem)

public:
	//����ÿһ��ͼԪ��Ҫ����һ���Լ���Ӧ��������Ϊdata_type��
	//�����W_D��ϵ�к��л��õ�������������ȡ�������ʵ����
	//���һ��ͼԪ�ͻ��������������һ�µģ�����Ҫ�������壬����WGraphicsEllipseItem
	typedef WItemData data_type;

public:
	friend class WGraphicsLayer;

    /**
	\brief      WGraphicsArcItem
	\Access    public 
	\param  data_type * d
				d����Ϊ0����ʱ���ڲ��ᶯ̬����һ������
				���d��Ϊ0�����������ⲿ�����ģ��뱣֤��������new�����ģ��벻Ҫ��ջ�ϴ��������ݴ���������
				��d������������ͼԪ�����ˣ�����������ͼԪ����ͼԪ�����ʵ���ʱ��ɾ����
				���벻Ҫ���ⲿ��dɾ����
	\retval     
	\remark    �Ժ������ݽ��й��� 
	*/
	explicit WGraphicsItem(data_type* d = 0);

	void destroy();

	WGraphicsScene* scene() const; //ͼԪ���ڳ���

	WGraphicsLayer* layer() const; //ͼԪ����ͼ��

	/**
	\brief      paint
	\Access    virtual public 
	\param  WPainter * painter
	\retval     void
	\remark    ����ʵ��ͼԪ�Ļ��� 
	*/
	virtual void paint(WPainter* painter) = 0;

	virtual bool contains(const WWorldPointF& point) const; //ͼԪ�Ƿ����ָ����
	virtual WWorldRectF boundingRect() const = 0; //ͼԪ�ı߽�����

	// �ֲ�����ϵ
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

	//������Щ����Ŀǰ��û���õ�	
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
	\remark    ��Ӧ���̵İ����¼� 
	*/
	virtual void keyPressEvent(WKeyEvent* event);

	/**
	\brief      keyReleaseEvent
	\Access    virtual public 
	\param  WKeyEvent * event
	\retval     void
	\remark    ��Ӧ���̵İ������ͷ��¼� 
	*/
	virtual void keyReleaseEvent(WKeyEvent* event);

	/**
	\brief      mouseMoveEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    ��Ӧ�����ƶ��¼� 
	*/
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mousePressEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    ��Ӧ���İ����¼� 
	*/
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mouseReleaseEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    ��Ӧ�����ͷ��¼� 
	*/
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      mouseDoubleClickEvent
	\Access    virtual public 
	\param  WGraphicsSceneMouseEvent * event
	\retval     void
	\remark    ��Ӧ����˫���¼� 
	*/
	virtual void mouseDoubleClickEvent(WGraphicsSceneMouseEvent* event);

	/**
	\brief      wheelEvent
	\Access    virtual public 
	\param  WGraphicsSceneWheelEvent * event
	\retval     void
	\remark     ��Ӧ���Ĺ����¼�
	*/
	virtual void wheelEvent(WGraphicsSceneWheelEvent* event);

	/**
	\brief      attachPoint
	\Access    virtual public 
	\param  const WWorldPointF & pos
	\param  WWorldPointF * attachedPos
	\retval     bool
	\remark     ��ͼԪ�ĵ���������
	*/
	virtual bool attachPoint(const WWorldPointF& pos, WWorldPointF* attachedPos) const; //����������

	enum { Type = TYPE_ITEM };
	/**
	\brief      type
	\Access    virtual public 
	\retval     int
	\remark     ͼԪ�����ͣ����������ͼԪ�Ķ�̬ʶ��ʱ�õ�
					 ǿ�Ҳ����鶯̬�޸��������ֵ�������ض����ͣ���Ӧ�����Ƿ���һ���������ֵ
	*/
	virtual int type() const; //ͼԪ������

	/**
	\brief      isEnabled
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ���Ч�����ֶ�Ŀǰû�����ã�
	*/
	bool isEnabled() const;

	/**
	\brief      isVisible
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ���ӣ������ӵ�ͼԪ����������ͼ����ʾ
	*/
	bool isVisible() const;

	/**
	\brief      isSelectable
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ�֧��ѡ�в�������֧��ѡ�в�����ͼԪ�������յ������е��κ���Ϣ
	*/
	bool isSelectable() const;

	/**
	\brief      isSelected
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ��Ѿ�ѡ��
	*/
	bool isSelected() const;

	/**
	\brief      isMovable
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ�֧���ƶ����������ֶ�Ŀǰû��ʹ�ã�
	*/
	bool isMovable() const;

	/**
	\brief      isTransformable
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ�֧�־���任�����ֶ�Ŀǰû��ʹ�ã�
	*/
	bool isTransformable() const;

	/**
	\brief      isScalable
	\Access    public 
	\retval     bool
	\remark     ͼԪ�Ƿ�֧�ַ�����Ĭ����֧�ֵģ���֧�ַ�����ͼԪ������ͼ��ηŴ���С�����Ĵ�С����仯
					 �����ֶ�Ŀǰֻ����WGraphicsTextItem���õ���
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
	\remark     ����ͼԪ���Ҽ��˵�
	*/
	void requestContextMenu(Ws::ContextMenuFlags flags);

	/**
	\brief      onContextMenu
	\Access    virtual public 
	\param  Ws::ContextMenuFlag flag
	\retval     void
	\remark     ��ӦͼԪ���Ҽ��˵�����
	*/
	virtual void onContextMenu(Ws::ContextMenuFlag flag);
	
	/**
	\brief      data
	\Access    public 
	\retval     data_type*
	\remark     ͼԪ��Ӧ�ĺ������ݣ��������ÿһ�������ͼԪ�ж�ʵ�ִ˺���
	*/
	data_type* data(); //ͼԪ��������

	/**
	\brief      data
	\Access    public 
	\retval     const data_type*
	\remark     ���������ĳ����汾
	*/
	const data_type* data() const;

	/**
	\brief      copy
	\Access    virtual public 
	\retval     WGraphicsItem*
	\remark     ����ͼԪ��һ����������������ڴ˺����ڲ��������ɴ˺����ĵ����߸���ɾ���˶���
	*/
	virtual WGraphicsItem* copy() const; //��¡һ������

	/**
	\brief      translate
	\Access    virtual public 
	\param  const WWorldPointF & offset
	\retval     void
	\remark     ��ͼԪƫ�����ɵ�λ������һ���麯���������ฺ��ʵ��
	*/
	virtual void translate(const WWorldPointF& offset); //ƽ��ͼԪ

	/**
	\brief      translate
	\Access    virtual public 
	\param  const WWorldPointF & offset
	\param  bool updating ָ���Ƿ����������ػ�
	\retval     void
	\remark    ��ͼԪƫ�����ɵ�λ 
	*/
	void translate(const WWorldPointF& offset, bool updating);

	/**
	\brief      expand
	\Access    public static 
	\param  WWorldRectF & r
	\retval     WWorldRectF&
	\remark     �˺������Ƽ�ʹ��
	*/
	static WWorldRectF& expand(WWorldRectF& r);

	/**
	\brief      expanded
	\Access    public static 
	\param  const WWorldRectF & r
	\retval     WWorldRectF
	\remark     �˺������Ƽ�ʹ��
	*/
	static WWorldRectF expanded(const WWorldRectF& r);

protected:
	virtual ~WGraphicsItem();

	/**
	\brief      baseData
	\Access    protected 
	\retval     WItemData*
	\remark     ���ػ���������
	*/
	WItemData* baseData();

	/**
	\brief      baseData
	\Access    protected 
	\retval     const WItemData*
	\remark     ���������ĳ����汾
	*/
	const WItemData* baseData() const;

private:
	/**
	\brief      setLayer
	\Access    private 
	\param  WGraphicsLayer * layer
	\retval     void
	\remark     ����ͼԪ��ͼ��
	*/
	void setLayer(WGraphicsLayer* layer);

protected:
	//CP -> control point
	static const double CP_ROTATE_HEADER; //��ת���Ƶ㵽���ο�ľ���
	static const double CP_RADIUS; //���Ƶ���ʾ�İ뾶��С
	static const WPen CP_PEN; //���ƿ��Ƶ�Ļ���
	static const WPen CP_SEL_PEN; //���Ʊ�ѡ�еĿ��Ƶ�Ļ���
	static const WPen DRAG_PEN; //ͼԪ���϶�ʱ���ƻ���
	static const WBrush CP_BRUSH; //���Ƶ�Ļ�ˢ
	static const WPen HOVER_PEN; //���������ͼԪ�ϵĻ���
	static const WBrush ROTATE_BRUSH; //��ת���Ƶ�Ļ�ˢ
	static const double ATTACH_DISTANCE; //ʵ����������ʱ����������
	static const double ATTACH_DISTANCE_SQUARE; //���������ƽ��

private:
	bool _enabled; //ͼԪ�Ƿ����
	bool _visible; //ͼԪ�Ƿ����
	bool _selectable; //ͼԪ�Ƿ���Ա�ѡ��
	bool _selected; //ͼԪ�Ƿ�ѡ����
	bool _movable; //ͼԪ�Ƿ�����ƶ�
	bool _transformable; //ͼԪ�Ƿ�֧�־���任
	bool _scalable; //ͼԪ�Ƿ�֧�����Ų���

	WGraphicsLayer* _layer; //ͼԪ����ͼ��
	WItemData* _data; //ͼԪ�ĺ�������
};

#endif