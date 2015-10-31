#include "../wdllexport.h"
#include "wevent.h"
#include "weventlistener.h"

WEventOption& WEventListener::eventOption()
{
	return _eventOption;
}

const WEventOption& WEventListener::eventOption() const
{
	return _eventOption;
}

void WEventListener::setEventOption(const WEventOption& eventOption)
{
	_eventOption = eventOption;
}

void WEventListener::contextMenuEvent(WGraphicsItem*, WContextMenuEvent*)
{

}

void WEventListener::dragEnterEvent(WGraphicsItem*, WGraphicsSceneDragDropEvent*)
{

}

void WEventListener::dragLeaveEvent(WGraphicsItem*, WGraphicsSceneDragDropEvent*)
{

}

void WEventListener::dragMoveEvent(WGraphicsItem*, WGraphicsSceneDragDropEvent*)
{

}

void WEventListener::dropEvent(WGraphicsItem*, WGraphicsSceneDragDropEvent*)
{

}

void WEventListener::focusInEvent(WGraphicsItem*, WFocusEvent*)
{

}

void WEventListener::focusOutEvent(WGraphicsItem*, WFocusEvent*)
{

}

void WEventListener::hoverEnterEvent(WGraphicsItem*, WGraphicsSceneHoverEvent*)
{

}

void WEventListener::hoverLeaveEvent(WGraphicsItem*, WGraphicsSceneHoverEvent*)
{

}

void WEventListener::hoverMoveEvent(WGraphicsItem*, WGraphicsSceneHoverEvent*)
{

}

void WEventListener::inputMethodEvent(WGraphicsItem*, WInputMethodEvent*)
{

}

void WEventListener::keyPressEvent(WGraphicsItem*, WKeyEvent*)
{

}

void WEventListener::keyReleaseEvent(WGraphicsItem*, WKeyEvent*)
{

}

void WEventListener::mouseMoveEvent(WGraphicsItem*, WGraphicsSceneMouseEvent*)
{

}

void WEventListener::mousePressEvent(WGraphicsItem*, WGraphicsSceneMouseEvent*)
{

}

void WEventListener::mouseReleaseEvent(WGraphicsItem*, WGraphicsSceneMouseEvent*)
{

}

void WEventListener::mouseDoubleClickEvent(WGraphicsItem*, WGraphicsSceneMouseEvent*)
{

}

void WEventListener::wheelEvent(WGraphicsItem*, WGraphicsSceneWheelEvent*)
{

}

void WEventListener::itemChange(const WGraphicsChange&)
{

}