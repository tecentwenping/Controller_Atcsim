/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wgraphicsview.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/29
  ����  ����:  ���ļ���Ҫʵ����WGraphicsView��
  ����  ����:   
******************************************************************************/
#ifndef _WGRAPHICS_VIEW_H_
#define _WGRAPHICS_VIEW_H_

#include "../wdllimport.h"
#include "wmatrix.h"
#include "wgraphicsitem.h"
#include "wgraphicsproxymanager.h"

class WCursor;
class WPainter;
class WGraphicsItem;
class WGraphicsScene;

//scene -----> view   _matrix
//view -----> scene _matrix.inverted

/** 
 \brief                 ����һ�������࣬�������˳�������ͼ�ı�׼�ӿ�
\details   
 \author    ����
\date      2013/05/29
*/
class MAPAPI WGraphicsView //������ʾ����
{
public:
	explicit WGraphicsView(WGraphicsScene* scene);
	virtual ~WGraphicsView();

	//��������
	WGraphicsScene* scene() const;
	void setScene(WGraphicsScene* scene);

	//��Ⱦ����
	void render(WPainter* painter, const WWorldRectF& rect);

	virtual void updateScene(const WWorldRectF& rect = WWorldRectF()) = 0;

	//������
	virtual WCursor cursor() const = 0;
	virtual void setCursor(const WCursor& cursor) = 0;

	virtual WWorldSizeF size() const = 0;

	//�Ҽ��˵�����
	virtual void requestContextMenu(Ws::ContextMenuFlags flags);
	void onContextMenu(Ws::ContextMenuFlag flag);

	//�����任��������ƽ�ƣ���������ת
	WMatrix worldTransform() const;

	/**
	\brief      setWorldTransform
	\Access    public 
	\param  const WMatrix & matrix
	\param  bool combine
	\retval     void
	\remark     ������ͼ�ľ���任
					 ����ڶ�����combineΪfalse��ֱ���õ�һ����matrix�滻ԭ���ľ���
					 ��֮��ԭ���ľ����ҳ�matrix�����ô˽���滻ԭ���ľ���
	*/
	void setWorldTransform(const WMatrix& matrix, bool combine = false);

	/**
	\brief      reset
	\Access    public 
	\param  double factor
	\retval     void
	\remark     ������ͼ�ľ���任
	*/
	void reset(double factor = 1.0);

	//ƽ�Ƴ����е����ɵ�λ
	void translate(double dx, double dy);
	void translate(const WWorldPointF& p);
	//ƽ���Ӵ��е����ɵ�λ
	void translateView(double dx, double dy);
	void translateView(const WWorldPointF& p);
	//��ͼ��ĳ������ת��Ĭ��Ϊ����ԭ��
	void rotate(double angle, const WWorldPointF& p); // ����
	void rotate(double angle);
	//��ͼ����ͼ���ĵ���ת
	void rotateView(double angle);

	//���ó���ԭ�����Ӵ��е�λ��
	void setCenter(const WWorldPointF& c);
	WWorldPointF center() const;

	//�ܷ�༭ͼԪ
	bool editable() const;
	void setEditable(bool enabled);

	//��ȡͼԪ����
	WGraphicsItemProxyManager& itemProxyManager();
	const WGraphicsItemProxyManager& itemProxyManager() const;

	//��ȡͼ�����
	WGraphicsLayerProxyManager& layerProxyManager();
	const WGraphicsLayerProxyManager& layerProxyManager() const;

	/**
	\brief      mapToScene
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     ����ͼ�ϵĵ�ӳ�䵽������
	*/
	WWorldPointF mapToScene(const WWorldPointF& p);

	/**
	\brief      mapToView
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     �������еĵ�ӳ�䵽��ͼ��
	*/
	WWorldPointF mapToView(const WWorldPointF& p);

private:
	WMatrix _matrix; //��������ͼӳ��ľ��������������ͼ��������ӳ��ľ���

private:
	WGraphicsScene* _scene; //��ͼ���ڵĳ���
	WWorldPointF _center; //��ͼ�����ĵ�
	bool _editable; //��ͼ�Ƿ���Ա༭
	WGraphicsItemProxyManager _item_proxy_manager; //ͼԪ����
	WGraphicsLayerProxyManager _layer_proxy_manager; //ͼ�����
};

#endif