/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wscenebinaryreader.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ����WSceneBinaryReader��
  ����  ����:   
******************************************************************************/
#ifndef _WBINARY_READER_H_
#define _WBINARY_READER_H_

#include <string>
#include <fstream>
#include "../wdllimport.h"
#include "wabstractscenereader.h"

/** 
 \brief                 ����ʵ����WAbstractSceneReader��
\details   �������Զ�������ʽ���ļ��ж�ȡ����
 \author    ����
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
	\remark     �����ļ���
	*/
	void setFileName(const std::string& fileName);

	/**
	\brief      isOpen
	\Access    public 
	\retval     bool
	\remark     �ļ��Ƿ��
	*/
	bool isOpen() const;

protected:
	virtual void readImpl();

private:
	/**
	\brief      fileSize
	\Access    private 
	\retval     int
	\remark     �ļ���С
	*/
	int fileSize();

private:
	std::ifstream _ifs; //��ȡ�����Ķ������ļ�
};

#endif