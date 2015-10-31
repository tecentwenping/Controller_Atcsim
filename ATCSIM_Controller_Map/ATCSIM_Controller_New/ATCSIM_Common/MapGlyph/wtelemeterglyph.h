#ifndef _WTELEMETER_GLYPH_H_
#define _WTELEMETER_GLYPH_H_

#include "wpen.h"
#include "wfont.h"
#include "wworldline.h"
#include "wmatrix.h"
#include "wgraphicsitem.h"

//��λ��ʽ
enum TELE_UNIT
{
	TELE_METRIC = 0,
	TELE_IMPERIAL,
};

class WTelemeterItemData : public WItemData
{
public:
	WTelemeterItemData()
	{
		m_fontText = WFont("GulimChe", 14, 75);
		m_startTraceId = -1;
		m_endTraceId = -1;
		m_strTime.clear();
	}

	static void SetUnitType(const int iType);

	WLineF m_line;
	std::string m_strTime;	//��̬ʱ��
	int m_startTraceId; // ����Ƿ�����˶�Ŀ��
	int m_endTraceId;   // �յ��Ƿ�����˶�Ŀ��
	WPen m_penLine;
	WPen m_penText;
	WFont m_fontText;
	static TELE_UNIT m_sUnitType;
};

/*�����*/
class WTelemeterGlyph : public WGraphicsItem
{
	RTTI_DECL(WTelemeterGlyph)
public:
	typedef WTelemeterItemData data_type;

public:
	explicit WTelemeterGlyph(data_type* d = 0);


	virtual void paint(WPainter* painter);
	virtual WWorldRectF boundingRect() const;
	virtual void mousePressEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseMoveEvent(WGraphicsSceneMouseEvent* event);
	virtual void mouseReleaseEvent(WGraphicsSceneMouseEvent* event);

	data_type* data();
	const data_type* data() const;

	int GetTranslateAngle();


private:
	bool m_bToDel;
	WRectF m_label_bounding_rect;// ��������
	WMatrix m_matrixOrg; // ��������ϵ

	static const int MAX_CHARS = 10;
	static const int LABEL_BLOCK_COUNT = 3;
	/*\brief		label block data include rect and text
	\details   
	\author    
	\date      2013/05/22
	*/
	struct label_block 
	{
		WRectF block_rect;
		std::string block_text;
	};

	label_block m_labelBlockData[LABEL_BLOCK_COUNT];
};


#endif