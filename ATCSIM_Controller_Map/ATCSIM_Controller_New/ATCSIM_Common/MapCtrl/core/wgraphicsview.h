/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wgraphicsview.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/29
  【描  述】:  此文件主要实现了WGraphicsView类
  【其  它】:   
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
 \brief                 这是一个抽象类，它定义了场景中视图的标准接口
\details   
 \author    陈龙
\date      2013/05/29
*/
class MAPAPI WGraphicsView //用于显示场景
{
public:
	explicit WGraphicsView(WGraphicsScene* scene);
	virtual ~WGraphicsView();

	//场景操作
	WGraphicsScene* scene() const;
	void setScene(WGraphicsScene* scene);

	//渲染操作
	void render(WPainter* painter, const WWorldRectF& rect);

	virtual void updateScene(const WWorldRectF& rect = WWorldRectF()) = 0;

	//光标操作
	virtual WCursor cursor() const = 0;
	virtual void setCursor(const WCursor& cursor) = 0;

	virtual WWorldSizeF size() const = 0;

	//右键菜单操作
	virtual void requestContextMenu(Ws::ContextMenuFlags flags);
	void onContextMenu(Ws::ContextMenuFlag flag);

	//场景变换矩阵，用于平移，放缩，旋转
	WMatrix worldTransform() const;

	/**
	\brief      setWorldTransform
	\Access    public 
	\param  const WMatrix & matrix
	\param  bool combine
	\retval     void
	\remark     设置视图的矩阵变换
					 如果第二参数combine为false则直接用第一参数matrix替换原来的矩阵
					 反之则将原来的矩阵右乘matrix，并用此结果替换原来的矩阵
	*/
	void setWorldTransform(const WMatrix& matrix, bool combine = false);

	/**
	\brief      reset
	\Access    public 
	\param  double factor
	\retval     void
	\remark     重置视图的矩阵变换
	*/
	void reset(double factor = 1.0);

	//平移场景中的若干单位
	void translate(double dx, double dy);
	void translate(const WWorldPointF& p);
	//平移视窗中的若干单位
	void translateView(double dx, double dy);
	void translateView(const WWorldPointF& p);
	//视图绕某个点旋转，默认为场景原点
	void rotate(double angle, const WWorldPointF& p); // 待测
	void rotate(double angle);
	//视图绕视图中心点旋转
	void rotateView(double angle);

	//设置场景原点在视窗中的位置
	void setCenter(const WWorldPointF& c);
	WWorldPointF center() const;

	//能否编辑图元
	bool editable() const;
	void setEditable(bool enabled);

	//获取图元代理
	WGraphicsItemProxyManager& itemProxyManager();
	const WGraphicsItemProxyManager& itemProxyManager() const;

	//获取图层代理
	WGraphicsLayerProxyManager& layerProxyManager();
	const WGraphicsLayerProxyManager& layerProxyManager() const;

	/**
	\brief      mapToScene
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     将视图上的点映射到场景中
	*/
	WWorldPointF mapToScene(const WWorldPointF& p);

	/**
	\brief      mapToView
	\Access    public 
	\param  const WWorldPointF & p
	\retval     WWorldPointF
	\remark     将场景中的点映射到视图中
	*/
	WWorldPointF mapToView(const WWorldPointF& p);

private:
	WMatrix _matrix; //场景到视图映射的矩阵，其逆矩阵即是视图到场景的映射的矩阵

private:
	WGraphicsScene* _scene; //视图所在的场景
	WWorldPointF _center; //视图的中心点
	bool _editable; //视图是否可以编辑
	WGraphicsItemProxyManager _item_proxy_manager; //图元代理
	WGraphicsLayerProxyManager _layer_proxy_manager; //图层代理
};

#endif