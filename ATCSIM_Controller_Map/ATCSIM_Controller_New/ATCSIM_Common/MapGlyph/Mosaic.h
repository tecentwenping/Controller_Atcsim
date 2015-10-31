#ifndef _MOSAIC_H_
#define _MOSAIC_H_

#include <hash_set>
#include <hash_map>
#include "wworldrect.h"

class Mosaic
{
public:
	typedef int block_data_type; //ÿһ�����汣�������
	typedef block_data_type data_type;
	typedef WWorldRectT<size_t> rect;
	
public:
	inline static Mosaic& Instance();

	inline void Clear(); //�����������
	//! ����Mosaic��Ļ��С
	void SetMosaicScreen(size_t x, size_t y);
	void Allocate(int id, double x1, double y1, double x2, double y2); //Ϊ���Ʒ���һ������ʵ�ֱ��Ʊ���

private:
	Mosaic();
	~Mosaic();
	//disable copy and assignment
	Mosaic(const Mosaic&);
	Mosaic& operator=(const Mosaic&);
	
	void FillBlocks(const rect& r, data_type val); //�������������
	inline void UnfillBlocks(const rect&r); //�ͷ�����

	data_type FirstNonEmptyBlock(const rect& r) const; //�ҵ������֣�ռ�ô�����ı���id
	inline bool IsEmpty(const rect& r) const; //�����Ƿ�Ϊ��

	const rect* NormalizedRect(double x1, double y1, double x2, double y2);

private:
	//static const size_t X = 1280; //screen pixel count in x coordinate
	//static const size_t Y = 1024; //screen pixel count in y coordinate
	
	static const size_t PIXELS_PER_BLOCK_X = 1; //block pixel count in x coordinate
	static const size_t PIXELS_PER_BLOCK_Y = 1; //block pixel count in y coordinate
	//static const size_t BLOCKS_IN_X = X / PIXELS_PER_BLOCK_X; //block count in x coordinate �п�
	//static const size_t BLOCKS_IN_Y = Y / PIXELS_PER_BLOCK_Y; //block count in y coordinate �п�
	size_t X;
	size_t Y;
	size_t BLOCKS_IN_X;
	size_t BLOCKS_IN_Y;
	//data_type* m_data;
	std::vector<std::vector<data_type> > m_data;
	//data_type m_data[BLOCKS_IN_Y][BLOCKS_IN_X]; //���еĿ����ݣ����ĳһ������Ϊ0���������һ��û�б��κ�
																			//����ռ�ã������Ϊ0�����������Ϊռ�ô˿�ı���id
	stdext::hash_map<data_type, rect> m_valid_labels; //<id, rect> ��¼���кϷ��ı��ƣ���������Ļ�ڣ���ռ
																				//�õĿ�����
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