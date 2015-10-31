#ifndef _WRINGS_GLYPH_H_
#define _WRINGS_GLYPH_H_

#include <set>
#include <vector>
#include "wpen.h"
#include "wglobal.h"
#include "wgraphicsitem.h"

enum RING_UNIT
{
	RING_METRIC = 0,
	RING_IMPERIAL
};

struct WDoubleCompare
{
	bool operator()(double lhs, double rhs) const
	{
		return (lhs < rhs) && !numeric_equal(lhs, rhs);
	}
};

//距离环
class WRingsItemData : public WItemData
{
public:
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	//设置获取距离环的中心点
	const WPointF GetCenter() const;
	void SetCenter(const WPointF& c);
	
	bool AddRing(double radius); //增加一个环
	//增加count个环，以radiusBase为基础半径，每次递增step个单位
	void AddRings(double radiusBase, double step, size_t count); 
	bool RemoveRing(double radius); //删除一个环
	void RemoveRings();
	const std::vector<double> GetRings() const;
	static void SetUnitType(const int type);

public:
	WPen m_pen;
	WPointF m_center; //距离环中心点
	std::set<double, WDoubleCompare> m_rings; //环的半径
	static RING_UNIT m_sUnitType;			//系统当前的单位制式
};

class WRingsGlyph : public WGraphicsItem
{
	RTTI_DECL(WRingsGlyph)

public:
	typedef WRingsItemData data_type;

public:
	explicit WRingsGlyph(data_type* d = 0);

	virtual void paint(WPainter* painter);
	virtual WRectF boundingRect() const;

	data_type* data();
	const data_type* data() const;
};

#endif