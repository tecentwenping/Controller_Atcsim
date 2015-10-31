#include <exception>
#include "../wdllexport.h"
#include "witemfactory.h"
#include "../core/wserialize.h"
#include "wscenebinaryreader.h"

WSceneBinaryReader::WSceneBinaryReader(const std::string& fileName)
: _ifs(fileName.c_str(), std::ios_base::in | std::ios_base::binary) 
{
}

void WSceneBinaryReader::setFileName(const std::string& fileName)
{
	if (_ifs.is_open())
	{
		_ifs.close();
	}
	_ifs.open(fileName.c_str(), std::ios_base::in | std::ios_base::binary);
}

bool WSceneBinaryReader::isOpen() const
{
	return _ifs.is_open();
}

//void WSceneBinaryReader::readImpl()
//{
//	int totalSize = fileSize();
//	if (totalSize <= 0)
//	{
//		return ;
//	}
//
//	char* buf = new char[totalSize];
//	memset(buf, 0, totalSize);
//	char* const END = buf + totalSize;
//	_ifs.read(buf, totalSize);
//
//	bool error = false;
//	const char* curr = buf;
//	readBegin();
//	while (!error && curr < END)
//	{
//		int typ = -1;
//		unserialize(curr, typ);
//		WItemData* d = WItemFactory::createItemData(typ);
//		if (d)
//		{
//			curr = d->unserialize(curr);
//			itemAvailable(WItemFactory::createItem(d));
//		}
//		else
//		{
//			error = true;
//		}
//	}
//
//	_ifs.close();
//
//	delete[] buf;
//
//	if (error)
//	{
//		throw std::exception("file is corrupted");
//	}
//
//	readEnd();
//}

void WSceneBinaryReader::readImpl()
{
	int totalSize = fileSize();
	if (totalSize <= 0)
	{
		return ;
	}

	char* buf = new char[totalSize];
	memset(buf, 0, totalSize);
	char* const END = buf + totalSize;
	_ifs.read(buf, totalSize);

	bool error = false;
	const char* curr = buf;
	readBegin();
	while (!error && curr < END)
	{
		WGraphicsItem* item = 0;
		curr = WItemFactory::create(curr, &item);
		if (item)
		{
			itemAvailable(item);
		}
		else
		{
			error = true;
		}
	}

	_ifs.close();

	delete[] buf;

	if (error)
	{
		throw std::exception("file is corrupted");
	}

	readEnd();
}

int WSceneBinaryReader::fileSize()
{
	int totalSize = -1;
	if (isOpen())
	{
		totalSize = 0;
		char buf[65536];
		
		while (_ifs)
		{
			_ifs.read(buf, array_size(buf));
			totalSize += _ifs.gcount();
		}
		_ifs.clear();
		_ifs.seekg(0, std::ios_base::beg);
	}
	return totalSize;
}