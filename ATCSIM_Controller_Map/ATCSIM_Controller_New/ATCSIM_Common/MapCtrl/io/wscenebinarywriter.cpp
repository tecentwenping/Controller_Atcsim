#include "../wdllexport.h"
#include "witemfactory.h"
#include "wscenebinarywriter.h"
#include "../core/wserialize.h"
#include "../core/wgraphicsitem.h"

WSceneBinaryWriter::WSceneBinaryWriter(const std::string& fileName) : _ofs(fileName.c_str(), std::ios_base::out | std::ios_base::binary)
{
}

void WSceneBinaryWriter::setFileName(const std::string& fileName)
{
	if (_ofs.is_open())
	{
		_ofs.close();
	}

	_ofs.open(fileName.c_str(), std::ios_base::out | std::ios_base::binary);
}

bool WSceneBinaryWriter::isOpen() const
{
	return _ofs.is_open();
}

void WSceneBinaryWriter::close()
{
	_ofs.close();
}

//void WSceneBinaryWriter::writeImpl(const WGraphicsItem* item)
//{
//	char* curr = item->data()->serialize(_buf);
//	int size = curr - _buf;
//
//	if (size > BUF_SIZE) //overflow
//	{
//		throw std::exception("graphics item too large");
//	}
//	else //write to file
//	{
//		_ofs.write(_buf, size);
//	}
//}
void WSceneBinaryWriter::writeImpl(const WGraphicsItem* item)
{
	int size = WItemFactory::serialize(_buf, *item) - _buf;
	if (size > BUF_SIZE) //overflow
	{
		throw std::exception("graphics item too large");
	}
	else //write to file
	{
		_ofs.write(_buf, size);
	}
}