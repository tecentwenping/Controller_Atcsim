/******************************************************************************
   ��Ȩ���� (C), 2013 - 2014, �Ĵ�������ʤ����ɷ����޹�˾
  ���ļ�����: wevent.h
  ����  �ߡ�: ����
  ����  ����:1.0
  ��������ڡ�:2013/05/23
  ����  ����:  ���ļ���Ҫ����˳��������õ��������¼���
  ����  ����:  ��һ�����¼���ʵ�������в�û���õ� 
******************************************************************************/
#ifndef _WEVENT_H_
#define _WEVENT_H_

#include <map>
#include <string>
#include "../wdllimport.h"
#include "wenums.h"
#include "wworldpoint.h"

class WGraphicsItem;
class WGraphicsView;

/** 
 \brief                 �����¼��Ļ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WEvent
{
public:
	//�¼�����ö��
	enum Type 
	{
		None = 0,                               // invalid event
		Timer = 1,                              // timer event
		MouseButtonPress = 2,                   // mouse button pressed
		MouseButtonRelease = 3,                 // mouse button released
		MouseButtonDblClick = 4,                // mouse button double click
		MouseMove = 5,                          // mouse move
		KeyPress = 6,                           // key pressed
		KeyRelease = 7,                         // key released
		FocusIn = 8,                            // keyboard focus received
		FocusOut = 9,                           // keyboard focus lost
		Enter = 10,                             // mouse enters widget
		Leave = 11,                             // mouse leaves widget
		Paint = 12,                             // paint widget
		Move = 13,                              // move widget
		Resize = 14,                            // resize widget
		Create = 15,                            // after widget creation
		Destroy = 16,                           // during widget destruction
		Show = 17,                              // widget is shown
		Hide = 18,                              // widget is hidden
		Close = 19,                             // request to close widget
		Quit = 20,                              // request to quit application
		ParentChange = 21,                      // widget has been reparented
		ParentAboutToChange = 131,              // sent just before the parent change is done
		ThreadChange = 22,                      // object has changed threads
		WindowActivate = 24,                    // window was activated
		WindowDeactivate = 25,                  // window was deactivated
		ShowToParent = 26,                      // widget is shown to parent
		HideToParent = 27,                      // widget is hidden to parent
		Wheel = 31,                             // wheel event
		WindowTitleChange = 33,                 // window title changed
		WindowIconChange = 34,                  // icon changed
		ApplicationWindowIconChange = 35,       // application icon changed
		ApplicationFontChange = 36,             // application font changed
		ApplicationLayoutDirectionChange = 37,  // application layout direction changed
		ApplicationPaletteChange = 38,          // application palette changed
		PaletteChange = 39,                     // widget palette changed
		Clipboard = 40,                         // internal clipboard event
		Speech = 42,                            // reserved for speech input
		MetaCall =  43,                         // meta call event
		SockAct = 50,                           // socket activation
		WinEventAct = 132,                      // win event activation
		DeferredDelete = 52,                    // deferred delete event
		DragEnter = 60,                         // drag moves into widget
		DragMove = 61,                          // drag moves in widget
		DragLeave = 62,                         // drag leaves or is cancelled
		Drop = 63,                              // actual drop
		DragResponse = 64,                      // drag accepted/rejected
		ChildAdded = 68,                        // new child widget
		ChildPolished = 69,                     // polished child widget
		ChildRemoved = 71,                      // deleted child widget
		ShowWindowRequest = 73,                 // widget's window should be mapped
		PolishRequest = 74,                     // widget should be polished
		Polish = 75,                            // widget is polished
		LayoutRequest = 76,                     // widget should be relayouted
		UpdateRequest = 77,                     // widget should be repainted
		UpdateLater = 78,                       // request update() later

		EmbeddingControl = 79,                  // ActiveX embedding
		ActivateControl = 80,                   // ActiveX activation
		DeactivateControl = 81,                 // ActiveX deactivation
		ContextMenu = 82,                       // context popup menu
		InputMethod = 83,                       // input method
		AccessibilityPrepare = 86,              // accessibility information is requested
		TabletMove = 87,                        // Wacom tablet event
		LocaleChange = 88,                      // the system locale changed
		LanguageChange = 89,                    // the application language changed
		LayoutDirectionChange = 90,             // the layout direction changed
		Style = 91,                             // internal style event
		TabletPress = 92,                       // tablet press
		TabletRelease = 93,                     // tablet release
		OkRequest = 94,                         // CE (Ok) button pressed
		HelpRequest = 95,                       // CE (?)  button pressed

		IconDrag = 96,                          // proxy icon dragged

		FontChange = 97,                        // font has changed
		EnabledChange = 98,                     // enabled state has changed
		ActivationChange = 99,                  // window activation has changed
		StyleChange = 100,                      // style has changed
		IconTextChange = 101,                   // icon text has changed
		ModifiedChange = 102,                   // modified state has changed
		MouseTrackingChange = 109,              // mouse tracking state has changed

		WindowBlocked = 103,                    // window is about to be blocked modally
		WindowUnblocked = 104,                  // windows modal blocking has ended
		WindowStateChange = 105,

		ToolTip = 110,
		WhatsThis = 111,
		StatusTip = 112,

		ActionChanged = 113,
		ActionAdded = 114,
		ActionRemoved = 115,

		FileOpen = 116,                         // file open request

		Shortcut = 117,                         // shortcut triggered
		ShortcutOverride = 51,                  // shortcut override request

		WhatsThisClicked = 118,

		ToolBarChange = 120,                    // toolbar visibility toggled

		ApplicationActivate = 121,              // application has been changed to active
		ApplicationActivated = ApplicationActivate, // deprecated
		ApplicationDeactivate = 122,            // application has been changed to inactive
		ApplicationDeactivated = ApplicationDeactivate, // deprecated

		QueryWhatsThis = 123,                   // query what's this widget help
		EnterWhatsThisMode = 124,
		LeaveWhatsThisMode = 125,

		ZOrderChange = 126,                     // child widget has had its z-order changed

		HoverEnter = 127,                       // mouse cursor enters a hover widget
		HoverLeave = 128,                       // mouse cursor leaves a hover widget
		HoverMove = 129,                        // mouse cursor move inside a hover widget

		AccessibilityHelp = 119,                // accessibility help text request
		AccessibilityDescription = 130,         // accessibility description text request

		// last event id used = 132
		AcceptDropsChange = 152,

		MenubarUpdated = 153,                    // Support event for Q3MainWindow, which needs to
		// knwow when QMenubar is updated.

		ZeroTimerEvent = 154,                   // Used for Windows Zero timer events

		GraphicsSceneMouseMove = 155,           // GraphicsView
		GraphicsSceneMousePress = 156,
		GraphicsSceneMouseRelease = 157,
		GraphicsSceneMouseDoubleClick = 158,
		GraphicsSceneContextMenu = 159,
		GraphicsSceneHoverEnter = 160,
		GraphicsSceneHoverMove = 161,
		GraphicsSceneHoverLeave = 162,
		GraphicsSceneHelp = 163,
		GraphicsSceneDragEnter = 164,
		GraphicsSceneDragMove = 165,
		GraphicsSceneDragLeave = 166,
		GraphicsSceneDrop = 167,
		GraphicsSceneWheel = 168,

		KeyboardLayoutChange = 169,             // keyboard layout changed

		DynamicPropertyChange = 170,            // A dynamic property was changed through setProperty/property

		TabletEnterProximity = 171,
		TabletLeaveProximity = 172,

		NonClientAreaMouseMove = 173,
		NonClientAreaMouseButtonPress = 174,
		NonClientAreaMouseButtonRelease = 175,
		NonClientAreaMouseButtonDblClick = 176,

		MacSizeChange = 177,                    // when the Qt::WA_Mac{Normal,Small,Mini}Size changes

		ContentsRectChange = 178,               // sent by QWidget::setContentsMargins (internal)

		MacGLWindowChange = 179,                // Internal! the window of the GLWidget has changed

		FutureCallOut = 180,

		GraphicsSceneResize  = 181,
		GraphicsSceneMove  = 182,

		CursorChange = 183,
		ToolTipChange = 184,

		NetworkReplyUpdated = 185,              // Internal for QNetworkReply

		GrabMouse = 186,
		UngrabMouse = 187,
		GrabKeyboard = 188,
		UngrabKeyboard = 189,
		MacGLClearDrawable = 191,               // Internal Cocoa, the window has changed, so we must clear

		StateMachineSignal = 192,
		StateMachineWrapped = 193,

		TouchBegin = 194,
		TouchUpdate = 195,
		TouchEnd = 196,

		RequestSoftwareInputPanel = 199,
		CloseSoftwareInputPanel = 200,

		UpdateSoftKeys = 201,                   // Internal for compressing soft key updates

		WinIdChange = 203,
		// 512 reserved for Qt Jambi's MetaCall event
		// 513 reserved for Qt Jambi's DeleteOnMainThread event

		User = 1000,                            // first user event id
		MaxUser = 65535                         // last user event id
	};

public :
	explicit WEvent(Type t = WEvent::None);
	virtual ~WEvent() {}

	/**
	\brief      type
	\Access    public 
	\retval     WEvent::Type
	\remark     ��ȡ�¼�����
	*/
	Type type() const;

	/**
	\brief      setType
	\Access    public 
	\param  Type t
	\retval     void
	\remark    �����¼����� 
	*/
	void setType(Type t);

private:
	unsigned short _type; //�¼�����
};

/** 
 \brief                 �����¼�����
\details   
 \author    ����
\date      2013/05/23
*/
class  MAPAPI WGraphicsSceneEvent : public WEvent
{
public:
	explicit WGraphicsSceneEvent(Type t = WEvent::None);

	/**
	\brief      widget
	\Access    public 
	\retval     WGraphicsView*
	\remark    ��ȡ�����¼����Ӵ� 
	*/
	WGraphicsView* widget() const;

	/**
	\brief      setWidget
	\Access    public 
	\param  WGraphicsView * w
	\retval     void
	\remark    ���ò����¼����Ӵ� 
	*/
	void setWidget(WGraphicsView* w);

private:
WGraphicsView* _w; //�����¼����Ӵ�
};

/** 
 \brief                 �����¼�����
\details  
 \author    ����
\date      2013/05/23
*/
class MAPAPI WInputEvent : public WGraphicsSceneEvent
{
public:
	WInputEvent(Type t = None, Ws::KeyboardModifiers modifiers = Ws::NoModifier);

	Ws::KeyboardModifiers modifiers() const;
	void setModifiers(Ws::KeyboardModifiers amodifiers);

protected:
	Ws::KeyboardModifiers _modifiers; //���̰����μ�
};

/** 
 \brief                 ���뷨�¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WInputMethodEvent : public WEvent
{

};

/** 
 \brief                 ����¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WMouseEvent : public WInputEvent
{

};

/** 
 \brief                 �����еļ��̰����¼�
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WKeyEvent : public WInputEvent
{
public:
	WKeyEvent(Type t, int key, Ws::KeyboardModifiers modifiers, const std::string& text = std::string(),
		bool autorep = false, unsigned short count = 1);

	int key() const;
	std::string text() const;
	bool isAutoRepeat() const;
	int count() const;

private:
	std::string _txt; //�������������
	int _k; //����ɨ����
	unsigned short _c; //�����ظ��Ĵ���
	unsigned int _autor:1; //�Ƿ����Զ��ظ�
};

/** 
 \brief                 ����ϵĹ����¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WWheelEvent : public WInputEvent
{
	
};

/** 
 \brief                 ����Ҽ��˵��¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WContextMenuEvent : public WInputEvent
{

};

/** 
 \brief                 �����е��Ϸ��¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsSceneDragDropEvent : public WGraphicsSceneEvent
{

};

/** 
 \brief                 ���������ͣ�������¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsSceneHoverEvent : public WGraphicsSceneEvent
{

};

/** 
 \brief                 �����е�����¼�
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsSceneMouseEvent : public WGraphicsSceneEvent
{
public:
	explicit WGraphicsSceneMouseEvent(Type t = None);
	~WGraphicsSceneMouseEvent();

	WWorldPointF pos() const;
	void setPos(const WWorldPointF &pos);

	WWorldPointF scenePos() const;
	void setScenePos(const WWorldPointF &pos);

	WWorldPoint screenPos() const;
	void setScreenPos(const WWorldPoint &pos);

	WWorldPointF buttonDownPos(Ws::MouseButton button) const;
	void setButtonDownPos(Ws::MouseButton button, const WWorldPointF &pos);

	WWorldPointF buttonDownScenePos(Ws::MouseButton button) const;
	void setButtonDownScenePos(Ws::MouseButton button, const WWorldPointF &pos);

	WWorldPoint buttonDownScreenPos(Ws::MouseButton button) const;
	void setButtonDownScreenPos(Ws::MouseButton button, const WWorldPoint &pos);

	WWorldPointF lastPos() const;
	void setLastPos(const WWorldPointF &pos);

	WWorldPointF lastScenePos() const;
	void setLastScenePos(const WWorldPointF &pos);

	WWorldPoint lastScreenPos() const;
	void setLastScreenPos(const WWorldPoint &pos);

	Ws::MouseButtons buttons() const;
	void setButtons(Ws::MouseButtons buttons);

	Ws::MouseButton button() const;
	void setButton(Ws::MouseButton button);

	Ws::KeyboardModifiers modifiers() const;
	void setModifiers(Ws::KeyboardModifiers modifiers);

private:
	WWorldPointF _pos; //�����item����ϵ�е����꣨û��ʵ�֣�����ʹ�ã�
	WWorldPointF _scenePos; //����ڳ�������ϵ�е�����
	WWorldPoint _screenPos; //��겻��Ļ�����е����꣨û��ʵ�֣�����ʹ�ã�
	WWorldPointF _lastPos;//�ϴ������item����ϵ�е����꣨û��ʵ�֣�����ʹ�ã�
	WWorldPointF _lastScenePos; //����ڳ�������ϵ�е�����
	WWorldPoint _lastScreenPos;//�ϴ���겻��Ļ�����е����꣨û��ʵ�֣�����ʹ�ã�
	std::map<Ws::MouseButton, WWorldPointF> _buttonDownPos; //��������
	std::map<Ws::MouseButton, WWorldPointF> _buttonDownScenePos; //��������
	std::map<Ws::MouseButton, WWorldPoint> _buttonDownScreenPos; //��������
	Ws::MouseButton _button; //��갴��
	Ws::MouseButtons _buttons; //��갴���ǣ������ж������ͬʱ������
	Ws::KeyboardModifiers _modifiers; //�������ΰ�����
};

/** 
 \brief                 �����е��������¼�
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WGraphicsSceneWheelEvent : public WGraphicsSceneEvent
{

};


/** 
 \brief                 ʧȥ/��ȡ������¼���ʵ��û���õ���
\details   
 \author    ����
\date      2013/05/23
*/
class MAPAPI WFocusEvent : public WGraphicsSceneEvent
{
public:
	explicit WFocusEvent(Type t = None);

	bool getFocus() const;
	bool lostFocus() const;
};

#endif