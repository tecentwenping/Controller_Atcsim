/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wscenebinarywriter.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/31
  ����  ����:  ���ļ���Ҫ������WSceneBinaryWriter��
  ����  ����:   
******************************************************************************/
#ifndef _WBINARY_WRITER_H_
#define _WBINARY_WRITER_H_

#include <string>
#include <fstream>
#include "../wdllimport.h"
#include "wabstractscenewriter.h"

/** 
 \brief                 ����ʵ����WAbstractSceneWriter�ӿ�
\details   �������Զ�������ʽд�뵽�ļ���
 \author    ����
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

	/**
	\brief      close
	\Access    public 
	\retval     void
	\remark     �ر��ļ�
	*/
	void close();
	
protected:
	virtual void writeImpl(const WGraphicsItem* item);

private:
	static const int BUF_SIZE = 65536; //��������С

	std::ofstream _ofs; //���泡�����ļ�
	char _buf[BUF_SIZE]; //������
};

#endif