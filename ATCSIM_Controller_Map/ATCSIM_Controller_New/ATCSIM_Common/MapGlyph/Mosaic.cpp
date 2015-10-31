#include <cmath>
#include <memory>
#include <xutility>
#include <boost/typeof/typeof.hpp>
#include "Mosaic.h"
#include "waircraftglyph.h"
#include "wgraphicsscene.h"

Mosaic::Mosaic()
{
	SetMosaicScreen(1280, 1024);
}

/**
\brief      ~Mosaic
\Access    private 
\retval     
\remark     
*/
Mosaic::~Mosaic()
{
	Clear();
}


const Mosaic::rect* Mosaic::NormalizedRect(double x1, double y1, double x2, double y2)
{
	static rect r;

	if (x2 < x1)
	{
		std::swap(x1, x2);
	}

	if (y2 < y1)
	{
		std::swap(y1, y2);
	}

	if ((x1 > X) || (x2 < 0) || (y1 > Y) || (y2 < 0))
	{
		return 0;
	}

	if (x1 < 0)
	{
		x1 = 0;
	}
	else if (x2 > X)
	{
		x2 = X;
	}

	if (y1 < 0)
	{
		y1 = 0;
	}
	else if (y2 > Y)
	{
		y2 = Y;
	}

	x1 /= PIXELS_PER_BLOCK_X;
	y1 /= PIXELS_PER_BLOCK_Y;
	double w = (x2 - x1) / PIXELS_PER_BLOCK_X;
	double h = (y2 - y1) / PIXELS_PER_BLOCK_Y;

	r.setRect(static_cast<size_t>(x1), static_cast<size_t>(y1), static_cast<size_t>(w), static_cast<size_t>(h));

	return &r;
}

Mosaic::data_type Mosaic::FirstNonEmptyBlock(const rect& r) const
{
	size_t x1 = r.x();
	size_t y1 = r.y();
	size_t x2 = x1 + r.width();
	size_t y2 = y1 + r.height();

	for (size_t y = y1; y < y2; ++y) 
	{
		for (size_t x = x1; x < x2; ++x)
		{
			if (m_data[y][x])
			{
				return m_data[y][x];
			}
		}
	}

	return 0;
}

void Mosaic::FillBlocks(const rect& r, data_type val)
{
	size_t y1 = r.y();
	size_t y2 = y1 + r.height();
	size_t x1 = r.x();
	size_t x2 = x1 + r.width();

	for (size_t y = y1; y < y2; ++y)
	{
		for (size_t x = x1; x < x2; ++x)
		{
			m_data[y][x] = val;
		}
	}
}

void Mosaic::Allocate(int id, double x1, double y1, double x2, double y2)
{
	static const size_t N = 24; //��һ�ֳܷ�N��������û���ҵ��հ������ÿ�ε����˷���
	static const double d�� = 2 * M_PI / N; //ÿ�ε����ĽǶ�
	static const double dr = 100.0; //��û���ҵ��հ������ÿ�ε����������뾶

	const rect* r = NormalizedRect(x1, y1, x2, y2); //���±��������׼��

	BOOST_AUTO(i, m_valid_labels.find(id));
	bool exist = (i != m_valid_labels.end()); //�����Ƿ�ռ�þ�����
	if (!r) //���ݽ����ı��������򲻺Ϸ�
	{
		if (exist) //�������ռ�þ����򣬾��ͷ�
		{
			UnfillBlocks(i->second);
			m_valid_labels.erase(i);
		}
		//�������û��ռ���κ����򣬾ͺ���
		return ;
	}

	//�����Ǳ���������Ϸ�������
	if (exist) //�������ռ�þ�����
	{
		if (*r == i->second) //�������ռ������û�иı䣬��������==�����򣬾ͺ���
		{
			return ;
		}

		//�����Ǳ���ռ���������ı������
		UnfillBlocks(i->second); //���ͷ���ռ�þ�����
		i->second = *r;
	}
	else //�������֮ǰû��ռ���κ�����
	{
		m_valid_labels.insert(std::make_pair(id, *r));
	}
	
	data_type overlapped_id = FirstNonEmptyBlock(*r); //����ռ�õ���������֮ǰ�Ǳ��ĸ�����ռ���ˣ�һ���֣���
																//Ҳ����˵�����������Ǻ�ԭ�����ĸ����Ƶ��������ص���
	if (!overlapped_id) //û�б���ռ��������
	{
		FillBlocks(*r, id); //������ռ��������
		return ;
	}

	//��������һ��idΪoverlapped_id�ı��ƣ���ΪB�������б��ƣ���ΪA��ռ�����������ص�������
	rect& overlapped_rect = m_valid_labels[overlapped_id]; //����Bԭ��ռ������
	UnfillBlocks(overlapped_rect); //�ͷű���Bԭ��ռ������
	FillBlocks(*r, id); //������Aռ��������

	//������Ϊ����B�ҵ�һ���������������򣩵�����
	WAircraftGlyph* aircraft = reinterpret_cast<WAircraftGlyph*>(overlapped_id);
	WPointF c = aircraft->m_cd.aircraftMatrix.map(aircraft->data()->m_pos);
	WRectF& br = aircraft->data()->m_boundingRect;
	WRectF& sr = aircraft->data()->m_showRect;
	WPointF offPos = sr.bottomLeft() - br.bottomLeft();
	double w = br.width();
	double h = br.height();
	double x = br.x();
	double y = br.y();
	double �� = atan2(y, x); //������ʼ�Ƕ�
	double radius = sqrt(x * x + y * y); //������ʼ�뾶

	bool found = false;
	while (!found) //ֱ���ҵ�Ϊֹ����Ϊ���������뾶��ѭ��
	{
		for (size_t i = 0; i < N; ++i) //��Ϊ���������Ƕȵ�ѭ��
		{
			�� += d�� * i; //���������Ƕ�
			double rx = c.x() + radius * cos(��);
			double ry = c.y() + radius * sin(��);
			const rect* rc = NormalizedRect(rx, ry, rx + w, ry + h); //����������

			if (!rc) //�����������򲻺Ϸ���һ����������������Ļ������
					 //����Ҫ��ʱ��ֹѭ������Ϊ�ټ�������Ҳ�������κν������ʱ����ʧ�ܣ�������Ľ��
			{
				found = true;
				FillBlocks(overlapped_rect, overlapped_id);
				break;
			}
			
			if (IsEmpty(*rc)) //������һ���հ׵����������ɹ�����ֹѭ��
									//�������ñ��ص��ı��Ƶ����򣬲��ڽ������
			{
				found = true;
				overlapped_rect = *rc;
				FillBlocks(overlapped_rect, overlapped_id);
				WRectF br_org = aircraft->boundingRect();
				br.setRect(rx - c.x(), ry - c.y(), w, h);
				//���ú���������ʾ��С
				sr.setRect(br.bottomLeft().rx() + offPos.rx(),br.bottomLeft().ry() + offPos.ry(),sr.width(),sr.height());
				aircraft->scene()->update(br_org | aircraft->boundingRect());
				break;
			}
		}
		radius += dr; //���������뾶
	}
}

/**
\brief      SetMosaicScreen
\Access    public 
\param  size_t x
\param  size_t y
\retval     void
\remark     
*/
void Mosaic::SetMosaicScreen( size_t x, size_t y )
{
	Clear();
	X = x;
	Y = y;
	BLOCKS_IN_X = X / PIXELS_PER_BLOCK_X;
	BLOCKS_IN_Y = Y / PIXELS_PER_BLOCK_Y;

	m_data.resize(Y);
	BOOST_FOREACH(std::vector<data_type>& i, m_data)
	{
		i.resize(X, 0);
	}
}

