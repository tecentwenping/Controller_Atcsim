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
	static const size_t N = 24; //将一周分成N个方向，在没有找到空白区域后每次递增此方向
	static const double dθ = 2 * M_PI / N; //每次递增的角度
	static const double dr = 100.0; //在没有找到空白区域后，每次递增的搜索半径

	const rect* r = NormalizedRect(x1, y1, x2, y2); //将新标牌区域标准化

	BOOST_AUTO(i, m_valid_labels.find(id));
	bool exist = (i != m_valid_labels.end()); //标牌是否占用旧区域
	if (!r) //传递进来的标牌新区域不合法
	{
		if (exist) //如果标牌占用旧区域，就释放
		{
			UnfillBlocks(i->second);
			m_valid_labels.erase(i);
		}
		//如果标牌没有占用任何区域，就忽略
		return ;
	}

	//以下是标牌新区域合法的情形
	if (exist) //如果标牌占用旧区域
	{
		if (*r == i->second) //如果标牌占用区域没有改变，即新区域==旧区域，就忽略
		{
			return ;
		}

		//以下是标牌占用区域发生改变的情形
		UnfillBlocks(i->second); //先释放所占用旧区域
		i->second = *r;
	}
	else //如果标牌之前没有占用任何区域
	{
		m_valid_labels.insert(std::make_pair(id, *r));
	}
	
	data_type overlapped_id = FirstNonEmptyBlock(*r); //标牌占用的新区域在之前是被哪个标牌占用了（一部分），
																//也就是说标牌新区域是和原来的哪个标牌的区域是重叠的
	if (!overlapped_id) //没有标牌占用新区域
	{
		FillBlocks(*r, id); //填充标牌占用新区域
		return ;
	}

	//以下是有一个id为overlapped_id的标牌（记为B）和现有标牌（记为A）占用新区域有重叠的情形
	rect& overlapped_rect = m_valid_labels[overlapped_id]; //标牌B原来占用区域
	UnfillBlocks(overlapped_rect); //释放标牌B原来占用区域
	FillBlocks(*r, id); //填充标牌A占用新区域

	//以下是为标牌B找到一个空闲区域（新区域）的情形
	WAircraftGlyph* aircraft = reinterpret_cast<WAircraftGlyph*>(overlapped_id);
	WPointF c = aircraft->m_cd.aircraftMatrix.map(aircraft->data()->m_pos);
	WRectF& br = aircraft->data()->m_boundingRect;
	WRectF& sr = aircraft->data()->m_showRect;
	WPointF offPos = sr.bottomLeft() - br.bottomLeft();
	double w = br.width();
	double h = br.height();
	double x = br.x();
	double y = br.y();
	double θ = atan2(y, x); //搜索初始角度
	double radius = sqrt(x * x + y * y); //搜索初始半径

	bool found = false;
	while (!found) //直到找到为止，此为递增搜索半径的循环
	{
		for (size_t i = 0; i < N; ++i) //此为递增搜索角度的循环
		{
			θ += dθ * i; //递增搜索角度
			double rx = c.x() + radius * cos(θ);
			double ry = c.y() + radius * sin(θ);
			const rect* rc = NormalizedRect(rx, ry, rx + w, ry + h); //搜索的区域

			if (!rc) //搜索到的区域不合法，一般是由于搜索到屏幕外所致
					 //所以要及时终止循环，因为再继续搜索也不会有任何结果，此时搜索失败，这是最坏的结果
			{
				found = true;
				FillBlocks(overlapped_rect, overlapped_id);
				break;
			}
			
			if (IsEmpty(*rc)) //搜索到一个空白的区域，搜索成功，终止循环
									//重新设置被重叠的标牌的区域，并在界面更新
			{
				found = true;
				overlapped_rect = *rc;
				FillBlocks(overlapped_rect, overlapped_id);
				WRectF br_org = aircraft->boundingRect();
				br.setRect(rx - c.x(), ry - c.y(), w, h);
				//避让后计算标牌显示大小
				sr.setRect(br.bottomLeft().rx() + offPos.rx(),br.bottomLeft().ry() + offPos.ry(),sr.width(),sr.height());
				aircraft->scene()->update(br_org | aircraft->boundingRect());
				break;
			}
		}
		radius += dr; //递增搜索半径
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

