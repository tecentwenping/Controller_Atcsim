/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wscenebinarywriter.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要定义了WSceneBinaryWriter类
  【其  它】:   
******************************************************************************/
#ifndef _WBINARY_WRITER_H_
#define _WBINARY_WRITER_H_

#include <string>
#include <fstream>
#include "../wdllimport.h"
#include "wabstractscenewriter.h"

/** 
 \brief                 此类实现了WAbstractSceneWriter接口
\details   将场景以二进制形式写入到文件中
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WSceneBinaryWriter : public WAbstractSceneWriter
{
public:
	explicit WSceneBinaryWriter(const std::string& fileName = std::string());

	/**
	\brief      setFileName
	\Access    public 
	\param  const std::string & fileName
	\retval     void
	\remark     设置文件名
	*/
	void setFileName(const std::string& fileName);

	/**
	\brief      isOpen
	\Access    public 
	\retval     bool
	\remark     文件是否打开
	*/
	bool isOpen() const;

	/**
	\brief      close
	\Access    public 
	\retval     void
	\remark     关闭文件
	*/
	void close();
	
protected:
	virtual void writeImpl(const WGraphicsItem* item);

private:
	static const int BUF_SIZE = 65536; //缓冲区大小

	std::ofstream _ofs; //保存场景的文件
	char _buf[BUF_SIZE]; //缓冲区
};

#endif