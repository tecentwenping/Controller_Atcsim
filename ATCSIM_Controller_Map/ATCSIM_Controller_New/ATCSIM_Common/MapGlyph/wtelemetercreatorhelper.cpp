#include "wtelemetercreatorhelper.h"

#include <boost/typeof/typeof.hpp>
#include "wtelemetercreator.h"
#include "wglyphidentity.h"
#include "waircraftglyph.h"
#include "wtelemeterglyph.h"
#include "wgraphicsscene.h"


/**
\brief      TelemeterHelper
\Access    public 
\param  WGraphicsScene * s
\retval     
\remark     
*/
TelemeterHelper::TelemeterHelper( WGraphicsScene* s, WTelemeterCreator* creator ) :s(s)
{
	connect(creator, SIGNAL(stepOver(WTelemeterGlyph*, int, const WPointF&)), this, SLOT(match_trace_id(WTelemeterGlyph*, int, const WPointF&)));
}

/**
\brief      match_trace_id
\Access    public 
\param  WTelemeterGlyph * item
\param  int step
\param  const WPointF & p
\retval     void
\remark     
*/
void TelemeterHelper::match_trace_id( WTelemeterGlyph* item, int step, const WPointF& p )
{
	WTelemeterGlyph::data_type& d = *(item->data());
	
	WPointF pOut;
	if (step == 0)
	{
		d.m_startTraceId = search_for_id(p, pOut);
		if (d.m_startTraceId != -1)
		{
			d.m_line.setP1(pOut);
		}
	}
	else
	{
		d.m_endTraceId = search_for_id(p, pOut);
		if (d.m_startTraceId == d.m_endTraceId) // 保证不能同一个目标进行相连，同一目标相连，无意义 
		{
			d.m_endTraceId = -1;
		}
	
		if (d.m_endTraceId != -1)
		{
			d.m_line.setP2(pOut);
		}
	}
}


/**
\brief      search_for_id
\Access    protected 
\param  const WPointF & p
\param[out] pOut 如何存在点，则返回该点
\retval    int 
\remark     
*/
int TelemeterHelper::search_for_id( const WPointF& p, WPointF& pOut )
{
	WGraphicsLayer* l = s->layer(GLYPH_AIRCRAFT);
	if (l)
	{
		std::vector<WGraphicsItem*>& v = l->items();
		BOOST_FOREACH(WGraphicsItem* item, v)
		{
			if (item->contains(p))
			{
				// search item in scene
				WAircraftGlyph* gly = dynamic_cast<WAircraftGlyph*>(item);
				pOut = gly->data()->m_pos;
				return gly->data()->m_iId;
			}
		}
	}

	return -1;
}



