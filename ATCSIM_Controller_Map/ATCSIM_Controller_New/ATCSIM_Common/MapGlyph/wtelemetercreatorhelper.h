#ifndef _WTelemeterCreatorHelper_H_ 
#define _WTelemeterCreatorHelper_H_
/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: TelemeterPresenter.h
  ����  �ߡ�: @zcw
  ����  ����:1.0
  ��������ڡ�:2013/05/30
  ����  ����:  
    

  ����  ����:   
******************************************************************************/
#include <QObject>
#include <map>
#include <wworldpoint.h>
class WTelemeterGlyph;
class WTelemeterCreator;
class WGraphicsScene;



/** 
 \brief		Ϊ�˲���WTelemeterCreator����̫�࣬д�İ����࣬����������WTelemeterGlyph��������յ��TraceId
		���û���ҵ�����Ϊ-1
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