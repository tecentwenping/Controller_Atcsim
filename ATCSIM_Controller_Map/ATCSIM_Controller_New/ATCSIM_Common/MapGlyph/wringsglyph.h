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

//���뻷
class WRingsItemData : public WItemData
{
public:
	virtual char* serialize(char* buf) const;
	virtual const char* unserialize(const char* buf);
	virtual size_t serialize_size() const;

	//���û�ȡ���뻷�����ĵ�
	const WPointF GetCenter() const;
	void SetCenter(const WPointF& c);
	
	bool AddRing(double radius); //����һ����
	//����count��������radiusBaseΪ�����뾶��ÿ�ε���step����λ
	void AddRings(double radiusBase, double step, size_t count); 
	bool RemoveRing(double radius); //ɾ��һ����
	void RemoveRings();
	const std::vector<double> GetRings() const;
	static void SetUnitType(const int type);

public:
	WPen m_pen;
	WPointF m_center; //���뻷���ĵ�
	std::set<double, WDoubleCompare> m_rings; //���İ뾶
	static RING_UNIT m_sUnitType;			//ϵͳ��ǰ�ĵ�λ��ʽ
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