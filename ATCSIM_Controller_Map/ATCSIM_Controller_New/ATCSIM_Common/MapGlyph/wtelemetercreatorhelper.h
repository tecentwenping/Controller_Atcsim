#ifndef _WTelemeterCreatorHelper_H_ 
#define _WTelemeterCreatorHelper_H_
/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: TelemeterPresenter.h
  【作  者】: @zcw
  【版  本】:1.0
  【完成日期】:2013/05/30
  【描  述】:  
    

  【其  它】:   
******************************************************************************/
#include <QObject>
#include <map>
#include <wworldpoint.h>
class WTelemeterGlyph;
class WTelemeterCreator;
class WGraphicsScene;



/** 
 \brief		为了不让WTelemeterCreator关联太多，写的帮助类，该类来设置WTelemeterGlyph中起点与终点的TraceId
		如果没有找到，则为-1
 \details   
 \author    @zcw
 \date      2013/05/31
*/
class TelemeterHelper : QObject
{
	Q_OBJECT
public:
	explicit TelemeterHelper(WGraphicsScene* s, WTelemeterCreator* creator);

public slots:
	void match_trace_id(WTelemeterGlyph* item, int step, const WPointF& p);
protected:
	int search_for_id(const WPointF& p, WPointF& pOut = WPointF());
private:
	WGraphicsScene* s;
};
#endif