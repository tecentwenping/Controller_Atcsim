/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wscenebinaryreader.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/31
  【描  述】:  此文件主要包含WSceneBinaryReader类
  【其  它】:   
******************************************************************************/
#ifndef _WBINARY_READER_H_
#define _WBINARY_READER_H_

#include <string>
#include <fstream>
#include "../wdllimport.h"
#include "wabstractscenereader.h"

/** 
 \brief                 此类实现了WAbstractSceneReader类
\details   将场景以二进制形式从文件中读取出来
 \author    陈龙
\date      2013/05/31
*/
class MAPAPI WSceneBinaryReader : public WAbstractSceneReader
{
public:
	explicit WSceneBinaryReader(const std::string& fileName = std::string());

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

protected:
	virtual void readImpl();

private:
	/**
	\brief      fileSize
	\Access    private 
	\retval     int
	\remark     文件大小
	*/
	int fileSize();

private:
	std::ifstream _ifs; //读取场景的二进制文件
};

#endif