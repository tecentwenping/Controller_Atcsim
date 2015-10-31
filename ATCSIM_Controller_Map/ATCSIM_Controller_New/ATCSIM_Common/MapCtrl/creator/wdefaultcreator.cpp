#include "../wdllexport.h"
#include "wdefaultcreator.h"

WDefaultCreator::WDefaultCreator(WGraphicsScene* scene) : _scene(scene)
{
}

void WDefaultCreator::start()
{
}

void WDefaultCreator::mouseMoveEvent(WGraphicsSceneMouseEvent*)
{
}

void WDefaultCreator::mousePressEvent(WGraphicsSceneMouseEvent*)
{
}

void WDefaultCreator::mouseReleaseEvent(WGraphicsSceneMouseEvent*)
{
}

void WDefaultCreator::mouseDoubleClickEvent(WGraphicsSceneMouseEvent*)
{
}

void WDefaultCreator::keyPressEvent(WKeyEvent*)
{
}

void WDefaultCreator::keyReleaseEvent(WKeyEvent*)
{
}

WGraphicsScene* WDefaultCreator::scene() const
{
	return _scene;
}