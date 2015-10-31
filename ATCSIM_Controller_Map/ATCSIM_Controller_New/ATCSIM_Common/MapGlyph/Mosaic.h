#ifndef _MOSAIC_H_
#define _MOSAIC_H_

#include <hash_set>
#include <hash_map>
#include "wworldrect.h"

class Mosaic
{
public:
	typedef int block_data_type; //每一块里面保存的数据
	typedef block_data_type data_type;
	typedef WWorldRectT<size_t> rect;
	
public:
	inline static Mosaic& Instance();

	inline void Clear(); //清空所有数据
	//! 设置Mosaic屏幕大小
	void SetMosaicScreen(size_t x, size_t y);
	void Allocate(int id, double x1, double y1, double x2, double y2); //为标牌分配一块区域，实现标牌避让

private:
	Mosaic();
	~Mosaic();
	//disable copy and assignment
	Mosaic(const Mosaic&);
	Mosaic& operator=(const Mosaic&);
	
	void FillBlocks(const rect& r, data_type val); //用数据填充区域
	inline void UnfillBlocks(const rect&r); //释放区域

	data_type FirstNonEmptyBlock(const rect& r) const; //找到（部分）占用此区域的标牌id
	inline bool IsEmpty(const rect& r) const; //区域是否为空

	const rect* NormalizedRect(double x1, double y1, double x2, double y2);

private:
	//static const size_t X = 1280; //screen pixel count in x coordinate
	//static const size_t Y = 1024; //screen pixel count in y coordinate
	
	static const size_t PIXELS_PER_BLOCK_X = 1; //block pixel count in x coordinate
	static const size_t PIXELS_PER_BLOCK_Y = 1; //block pixel count in y coordinate
	//static const size_t BLOCKS_IN_X = X / PIXELS_PER_BLOCK_X; //block count in x coordinate 行块
	//static const size_t BLOCKS_IN_Y = Y / PIXELS_PER_BLOCK_Y; //block count in y coordinate 列块
	size_t X;
	size_t Y;
	size_t BLOCKS_IN_X;
	size_t BLOCKS_IN_Y;
	//data_type* m_data;
	std::vector<std::vector<data_type> > m_data;
	//data_type m_data[BLOCKS_IN_Y][BLOCKS_IN_X]; //所有的块数据，如果某一块数据为0，则表明这一块没有被任何
																			//标牌占用，如果不为0，则这个数字为占用此块的标牌id
	stdext::hash_map<data_type, rect> m_valid_labels; //<id, rect> 记录所有合法的标牌（标牌在屏幕内）所占
																				//用的块区域
};

inline void Mosaic::UnfillBlocks(const rect&r)
{
	FillBlocks(r, data_type());
}

inline Mosaic& Mosaic::Instance()
{
	static Mosaic mosaic;
	return mosaic;
}

inline void Mosaic::Clear()
{
	m_valid_labels.clear();
	m_data.clear();
}

bool Mosaic::IsEmpty(const rect& r) const
{
	return FirstNonEmptyBlock(r) == 0;
}

#endif