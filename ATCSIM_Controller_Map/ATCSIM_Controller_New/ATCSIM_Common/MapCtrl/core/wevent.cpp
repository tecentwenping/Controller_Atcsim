#include "../wdllexport.h"
#include "wevent.h"

WEvent::WEvent(Type t) : _type(static_cast<unsigned short>(t))
{
}

WEvent::Type WEvent::type() const
{
	return static_cast<WEvent::Type>(_type);
}

void WEvent::setType(Type t)
{
	_type = static_cast<unsigned short>(t);
}

WInputEvent::WInputEvent(Type t, Ws::KeyboardModifiers modifiers) : WGraphicsSceneEvent(t), _modifiers(modifiers)
{
}

Ws::KeyboardModifiers WInputEvent::modifiers() const 
{ 
	return _modifiers; 
}

void WInputEvent::setModifiers(Ws::KeyboardModifiers amodifiers) 
{
	_modifiers = amodifiers; 
}

WGraphicsSceneEvent::WGraphicsSceneEvent(Type t) : WEvent(t), _w(0)
{
}

WGraphicsView* WGraphicsSceneEvent::widget() const
{
	return _w;
}

void WGraphicsSceneEvent::setWidget(WGraphicsView* w)
{
	_w = w;
}

WGraphicsSceneMouseEvent::WGraphicsSceneMouseEvent(Type t) : WGraphicsSceneEvent(t), 
						_button(Ws::NoButton), _buttons(Ws::NoButton), _modifiers(Ws::NoModifier)
{
}

WGraphicsSceneMouseEvent::~WGraphicsSceneMouseEvent()
{
}

WWorldPointF WGraphicsSceneMouseEvent::pos() const
{
	return _pos;
}

void WGraphicsSceneMouseEvent::setPos(const WWorldPointF &pos)
{
	_pos = pos;
}

WWorldPointF WGraphicsSceneMouseEvent::scenePos() const
{
	return _scenePos;
}

void WGraphicsSceneMouseEvent::setScenePos(const WWorldPointF &pos)
{
	_scenePos = pos;
}

WWorldPoint WGraphicsSceneMouseEvent::screenPos() const
{
	return _screenPos;
}

void WGraphicsSceneMouseEvent::setScreenPos(const WWorldPoint &pos)
{
	_screenPos = pos;
}

WWorldPointF WGraphicsSceneMouseEvent::buttonDownPos(Ws::MouseButton button) const
{
	std::map<Ws::MouseButton, WWorldPointF>::const_iterator ci = _buttonDownPos.find(button);
	return ci != _buttonDownPos.end() ? ci->second : WWorldPointF();
}

void WGraphicsSceneMouseEvent::setButtonDownPos(Ws::MouseButton button, const WWorldPointF &pos)
{
	_buttonDownPos.insert(std::make_pair(button, pos));
}

WWorldPointF WGraphicsSceneMouseEvent::buttonDownScenePos(Ws::MouseButton button) const
{
	std::map<Ws::MouseButton, WWorldPointF>::const_iterator ci = _buttonDownScenePos.find(button);
	return ci != _buttonDownScenePos.end() ? ci->second : WWorldPointF();
}

void WGraphicsSceneMouseEvent::setButtonDownScenePos(Ws::MouseButton button, const WWorldPointF &pos)
{
	_buttonDownScenePos.insert(std::make_pair(button, pos));
}

WWorldPoint WGraphicsSceneMouseEvent::buttonDownScreenPos(Ws::MouseButton button) const
{
	std::map<Ws::MouseButton, WWorldPoint>::const_iterator ci = _buttonDownScreenPos.find(button);
	return ci != _buttonDownScreenPos.end() ? ci->second : WWorldPoint();
}

void WGraphicsSceneMouseEvent::setButtonDownScreenPos(Ws::MouseButton button, const WWorldPoint &pos)
{
	_buttonDownScreenPos.insert(std::make_pair(button, pos));
}

WWorldPointF WGraphicsSceneMouseEvent::lastPos() const
{
	return _lastPos;
}

void WGraphicsSceneMouseEvent::setLastPos(const WWorldPointF &pos)
{
	_lastPos = pos;
}

WWorldPointF WGraphicsSceneMouseEvent::lastScenePos() const
{
	return _lastScenePos;
}

void WGraphicsSceneMouseEvent::setLastScenePos(const WWorldPointF &pos)
{
	_lastScenePos = pos;
}

WWorldPoint WGraphicsSceneMouseEvent::lastScreenPos() const
{
	return _lastScreenPos;
}

void WGraphicsSceneMouseEvent::setLastScreenPos(const WWorldPoint &pos)
{
	_lastScreenPos = pos;
}

Ws::MouseButtons WGraphicsSceneMouseEvent::buttons() const
{
	return _buttons;
}

void WGraphicsSceneMouseEvent::setButtons(Ws::MouseButtons buttons)
{
	_buttons = buttons;
}

Ws::MouseButton WGraphicsSceneMouseEvent::button() const
{
	return _button;
}

void WGraphicsSceneMouseEvent::setButton(Ws::MouseButton button)
{
	_button = button;
}

Ws::KeyboardModifiers WGraphicsSceneMouseEvent::modifiers() const
{
	
	return _modifiers;
}

void WGraphicsSceneMouseEvent::setModifiers(Ws::KeyboardModifiers modifiers)
{
	_modifiers = modifiers;
}

WKeyEvent::WKeyEvent(Type t, int key, Ws::KeyboardModifiers modifiers, const std::string& text,
					 bool autorep, unsigned short count)
					 : WInputEvent(t, modifiers), _txt(text), _k(key), _c(count), _autor(autorep)
{
}

int WKeyEvent::key() const 
{ 
	return _k; 
}

std::string WKeyEvent::text() const 
{
	return _txt; 
}

bool WKeyEvent::isAutoRepeat() const 
{ 
	return _autor; 
}

int WKeyEvent::count() const 
{
	return int(_c); 
}

WFocusEvent::WFocusEvent(Type t) : WGraphicsSceneEvent(t)
{
}

bool WFocusEvent::getFocus() const
{
	return type() == FocusIn;
}

bool WFocusEvent::lostFocus() const
{
	return type() == FocusOut;
}