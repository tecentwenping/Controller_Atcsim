/******************************************************************************
   版权所有 (C), 2013 - 2014, 四川川大智胜软件股份有限公司
  【文件名】: wenums.h
  【作  者】: 陈龙
  【版  本】:1.0
  【完成日期】:2013/05/23
  【描  述】:  此文件定义了所有用到的枚举类型
  【其  它】:   
******************************************************************************/
#ifndef _WENUMS_H_
#define _WENUMS_H_

#include "wglobal.h"
#include "wflags.h"

NS_GLOBAL_BEGIN

/** 
 \brief                 笔的样式
\details   
 \author    陈龙
\date      2013/05/23
*/
enum PenStyle 
{
	NoPen,
	SolidLine,
	DashLine,
	DotLine,
	DashDotLine,
	DashDotDotLine,
	CustomDashLine
};

/** 
 \brief                 画刷的类型
\details   
 \author    陈龙
\date      2013/05/23
*/
enum BrushStyle 
{
	NoBrush,
	SolidPattern,
	Dense1Pattern,
	Dense2Pattern,
	Dense3Pattern,
	Dense4Pattern,
	Dense5Pattern,
	Dense6Pattern,
	Dense7Pattern,
	HorPattern,
	VerPattern,
	CrossPattern,
	BDiagPattern,
	FDiagPattern,
	DiagCrossPattern,
	LinearGradientPattern,
	RadialGradientPattern,
	ConicalGradientPattern,
	TexturePattern = 24
};

/** 
 \brief                 WPainter的背景模式
\details   
 \author    陈龙
\date      2013/05/23
*/
enum BGMode
{
	TransparentMode = 0,
	OpaqueMode = 1,
};

/** 
 \brief                 对齐方式
\details   
 \author    陈龙
\date      2013/05/23
*/
enum AlignmentFlag 
{
	AlignLeft = 0x0001,
	AlignLeading = AlignLeft,
	AlignRight = 0x0002,
	AlignTrailing = AlignRight,
	AlignHCenter = 0x0004,
	AlignJustify = 0x0008,
	AlignAbsolute = 0x0010,
	AlignHorizontal_Mask = AlignLeft | AlignRight | AlignHCenter | AlignJustify | AlignAbsolute,

	AlignTop = 0x0020,
	AlignBottom = 0x0040,
	AlignVCenter = 0x0080,
	AlignVertical_Mask = AlignTop | AlignBottom | AlignVCenter,

	AlignCenter = AlignVCenter | AlignHCenter
};

W_DECLARE_FLAGS(Alignment, AlignmentFlag)

/** 
 \brief                 定义了文本绘制细节
\details   
 \author    陈龙
\date      2013/05/23
*/
enum TextFlag
{
	TextSingleLine = 0x0100,
	TextDontClip = 0x0200,
	TextExpandTabs = 0x0400,
	TextShowMnemonic = 0x0800,
	TextWordWrap = 0x1000,
	TextWrapAnywhere = 0x2000,
	TextDontPrint = 0x4000,
	TextIncludeTrailingSpaces = 0x08000000,
	TextHideMnemonic = 0x8000,
	TextJustificationForced = 0x10000,
	TextForceLeftToRight = 0x20000,
	TextForceRightToLeft = 0x40000,
	TextLongestVariant = 0x80000,
	TextBypassShaping = 0x100000,
};

/** 
 \brief                 键盘上按键的修饰按键
\details   
 \author    陈龙
\date      2013/05/23
*/
enum KeyboardModifier
{
	NoModifier = 0x00000000	,//No modifier key is pressed.
	ShiftModifier = 0x02000000,	//A Shift key on the keyboard is pressed.
	ControlModifier = 0x04000000,	//A Ctrl key on the keyboard is pressed.
	AltModifier = 0x08000000,	//An Alt key on the keyboard is pressed.
	MetaModifier = 0x10000000,	//A Meta key on the keyboard is pressed.
	KeypadModifier = 0x20000000,	//A keypad button is pressed.
	GroupSwitchModifier = 0x40000000,	//X11 only. A Mode_switch key on the keyboard is pressed.
};
W_DECLARE_FLAGS(KeyboardModifiers, KeyboardModifier)

/** 
 \brief                 鼠标上的按键类型
\details   
 \author    陈龙
\date      2013/05/23
*/
enum MouseButton 
{
	NoButton         = 0x00000000,
	LeftButton       = 0x00000001,
	RightButton      = 0x00000002,
	MidButton        = 0x00000004,
	MiddleButton     = MidButton,
	XButton1         = 0x00000008,
	XButton2         = 0x00000010,
	MouseButtonMask  = 0x000000ff
};
W_DECLARE_FLAGS(MouseButtons, MouseButton)

/** 
 \brief                 键盘上的按键
\details   
 \author    陈龙
\date      2013/05/23
*/
enum Key 
{
	Key_Escape = 0x01000000,                // misc keys
	Key_Tab = 0x01000001,
	Key_Backtab = 0x01000002,
	Key_Backspace = 0x01000003,
	Key_Return = 0x01000004,
	Key_Enter = 0x01000005,
	Key_Insert = 0x01000006,
	Key_Delete = 0x01000007,
	Key_Pause = 0x01000008,
	Key_Print = 0x01000009,
	Key_SysReq = 0x0100000a,
	Key_Clear = 0x0100000b,
	Key_Home = 0x01000010,                // cursor movement
	Key_End = 0x01000011,
	Key_Left = 0x01000012,
	Key_Up = 0x01000013,
	Key_Right = 0x01000014,
	Key_Down = 0x01000015,
	Key_PageUp = 0x01000016,
	Key_PageDown = 0x01000017,
	Key_Shift = 0x01000020,                // modifiers
	Key_Control = 0x01000021,
	Key_Meta = 0x01000022,
	Key_Alt = 0x01000023,
	Key_CapsLock = 0x01000024,
	Key_NumLock = 0x01000025,
	Key_ScrollLock = 0x01000026,
	Key_F1 = 0x01000030,                // function keys
	Key_F2 = 0x01000031,
	Key_F3 = 0x01000032,
	Key_F4 = 0x01000033,
	Key_F5 = 0x01000034,
	Key_F6 = 0x01000035,
	Key_F7 = 0x01000036,
	Key_F8 = 0x01000037,
	Key_F9 = 0x01000038,
	Key_F10 = 0x01000039,
	Key_F11 = 0x0100003a,
	Key_F12 = 0x0100003b,
	Key_F13 = 0x0100003c,
	Key_F14 = 0x0100003d,
	Key_F15 = 0x0100003e,
	Key_F16 = 0x0100003f,
	Key_F17 = 0x01000040,
	Key_F18 = 0x01000041,
	Key_F19 = 0x01000042,
	Key_F20 = 0x01000043,
	Key_F21 = 0x01000044,
	Key_F22 = 0x01000045,
	Key_F23 = 0x01000046,
	Key_F24 = 0x01000047,
	Key_F25 = 0x01000048,                // F25 .. F35 only on X11
	Key_F26 = 0x01000049,
	Key_F27 = 0x0100004a,
	Key_F28 = 0x0100004b,
	Key_F29 = 0x0100004c,
	Key_F30 = 0x0100004d,
	Key_F31 = 0x0100004e,
	Key_F32 = 0x0100004f,
	Key_F33 = 0x01000050,
	Key_F34 = 0x01000051,
	Key_F35 = 0x01000052,
	Key_Super_L = 0x01000053,                 // extra keys
	Key_Super_R = 0x01000054,
	Key_Menu = 0x01000055,
	Key_Hyper_L = 0x01000056,
	Key_Hyper_R = 0x01000057,
	Key_Help = 0x01000058,
	Key_Direction_L = 0x01000059,
	Key_Direction_R = 0x01000060,
	Key_Space = 0x20,                // 7 bit printable ASCII
	Key_Any = Key_Space,
	Key_Exclam = 0x21,
	Key_QuoteDbl = 0x22,
	Key_NumberSign = 0x23,
	Key_Dollar = 0x24,
	Key_Percent = 0x25,
	Key_Ampersand = 0x26,
	Key_Apostrophe = 0x27,
	Key_ParenLeft = 0x28,
	Key_ParenRight = 0x29,
	Key_Asterisk = 0x2a,
	Key_Plus = 0x2b,
	Key_Comma = 0x2c,
	Key_Minus = 0x2d,
	Key_Period = 0x2e,
	Key_Slash = 0x2f,
	Key_0 = 0x30,
	Key_1 = 0x31,
	Key_2 = 0x32,
	Key_3 = 0x33,
	Key_4 = 0x34,
	Key_5 = 0x35,
	Key_6 = 0x36,
	Key_7 = 0x37,
	Key_8 = 0x38,
	Key_9 = 0x39,
	Key_Colon = 0x3a,
	Key_Semicolon = 0x3b,
	Key_Less = 0x3c,
	Key_Equal = 0x3d,
	Key_Greater = 0x3e,
	Key_Question = 0x3f,
	Key_At = 0x40,
	Key_A = 0x41,
	Key_B = 0x42,
	Key_C = 0x43,
	Key_D = 0x44,
	Key_E = 0x45,
	Key_F = 0x46,
	Key_G = 0x47,
	Key_H = 0x48,
	Key_I = 0x49,
	Key_J = 0x4a,
	Key_K = 0x4b,
	Key_L = 0x4c,
	Key_M = 0x4d,
	Key_N = 0x4e,
	Key_O = 0x4f,
	Key_P = 0x50,
	Key_Q = 0x51,
	Key_R = 0x52,
	Key_S = 0x53,
	Key_T = 0x54,
	Key_U = 0x55,
	Key_V = 0x56,
	Key_W = 0x57,
	Key_X = 0x58,
	Key_Y = 0x59,
	Key_Z = 0x5a,
	Key_BracketLeft = 0x5b,
	Key_Backslash = 0x5c,
	Key_BracketRight = 0x5d,
	Key_AsciiCircum = 0x5e,
	Key_Underscore = 0x5f,
	Key_QuoteLeft = 0x60,
	Key_BraceLeft = 0x7b,
	Key_Bar = 0x7c,
	Key_BraceRight = 0x7d,
	Key_AsciiTilde = 0x7e,

	Key_nobreakspace = 0x0a0,
	Key_exclamdown = 0x0a1,
	Key_cent = 0x0a2,
	Key_sterling = 0x0a3,
	Key_currency = 0x0a4,
	Key_yen = 0x0a5,
	Key_brokenbar = 0x0a6,
	Key_section = 0x0a7,
	Key_diaeresis = 0x0a8,
	Key_copyright = 0x0a9,
	Key_ordfeminine = 0x0aa,
	Key_guillemotleft = 0x0ab,        // left angle quotation mark
	Key_notsign = 0x0ac,
	Key_hyphen = 0x0ad,
	Key_registered = 0x0ae,
	Key_macron = 0x0af,
	Key_degree = 0x0b0,
	Key_plusminus = 0x0b1,
	Key_twosuperior = 0x0b2,
	Key_threesuperior = 0x0b3,
	Key_acute = 0x0b4,
	Key_mu = 0x0b5,
	Key_paragraph = 0x0b6,
	Key_periodcentered = 0x0b7,
	Key_cedilla = 0x0b8,
	Key_onesuperior = 0x0b9,
	Key_masculine = 0x0ba,
	Key_guillemotright = 0x0bb,        // right angle quotation mark
	Key_onequarter = 0x0bc,
	Key_onehalf = 0x0bd,
	Key_threequarters = 0x0be,
	Key_questiondown = 0x0bf,
	Key_Agrave = 0x0c0,
	Key_Aacute = 0x0c1,
	Key_Acircumflex = 0x0c2,
	Key_Atilde = 0x0c3,
	Key_Adiaeresis = 0x0c4,
	Key_Aring = 0x0c5,
	Key_AE = 0x0c6,
	Key_Ccedilla = 0x0c7,
	Key_Egrave = 0x0c8,
	Key_Eacute = 0x0c9,
	Key_Ecircumflex = 0x0ca,
	Key_Ediaeresis = 0x0cb,
	Key_Igrave = 0x0cc,
	Key_Iacute = 0x0cd,
	Key_Icircumflex = 0x0ce,
	Key_Idiaeresis = 0x0cf,
	Key_ETH = 0x0d0,
	Key_Ntilde = 0x0d1,
	Key_Ograve = 0x0d2,
	Key_Oacute = 0x0d3,
	Key_Ocircumflex = 0x0d4,
	Key_Otilde = 0x0d5,
	Key_Odiaeresis = 0x0d6,
	Key_multiply = 0x0d7,
	Key_Ooblique = 0x0d8,
	Key_Ugrave = 0x0d9,
	Key_Uacute = 0x0da,
	Key_Ucircumflex = 0x0db,
	Key_Udiaeresis = 0x0dc,
	Key_Yacute = 0x0dd,
	Key_THORN = 0x0de,
	Key_ssharp = 0x0df,
	Key_division = 0x0f7,
	Key_ydiaeresis = 0x0ff,
	Key_AltGr               = 0x01001103,
	Key_Multi_key           = 0x01001120,  // Multi-key character compose
	Key_Codeinput           = 0x01001137,
	Key_SingleCandidate     = 0x0100113c,
	Key_MultipleCandidate   = 0x0100113d,
	Key_PreviousCandidate   = 0x0100113e,

	Key_unknown = 0x01ffffff
};

enum CursorShape 
{
	ArrowCursor,
	UpArrowCursor,
	CrossCursor,
	WaitCursor,
	IBeamCursor,
	SizeVerCursor,
	SizeHorCursor,
	SizeBDiagCursor,
	SizeFDiagCursor,
	SizeAllCursor,
	BlankCursor,
	SplitVCursor,
	SplitHCursor,
	PointingHandCursor,
	ForbiddenCursor,
	WhatsThisCursor,
	BusyCursor,
	OpenHandCursor,
	ClosedHandCursor,
	DragCopyCursor,
	DragMoveCursor,
	DragLinkCursor,
	LastCursor = DragLinkCursor,
	BitmapCursor = 24,
	CustomCursor = 25
};

enum GraphicsItemChange
{
	ItemPositionChange,
	ItemMatrixChange,
	ItemVisibleChange,
	ItemEnabledChange,
	ItemSelectedChange,
	ItemParentChange,
	ItemChildAddedChange,
	ItemChildRemovedChange,
	ItemTransformChange,
	ItemPositionHasChanged,
	ItemTransformHasChanged,
	ItemSceneChange,
	ItemVisibleHasChanged,
	ItemEnabledHasChanged,
	ItemSelectedHasChanged,
	ItemParentHasChanged,
	ItemSceneHasChanged,
	ItemCursorChange,
	ItemCursorHasChanged,
	ItemToolTipChange,
	ItemToolTipHasChanged,
	ItemFlagsChange,
	ItemFlagsHaveChanged,
	ItemZValueChange,
	ItemZValueHasChanged,
	ItemOpacityChange,
	ItemOpacityHasChanged,
	ItemScenePositionHasChanged,
	ItemRotationChange,
	ItemRotationHasChanged,
	ItemScaleChange,
	ItemScaleHasChanged,
	ItemTransformOriginPointChange,
	ItemTransformOriginPointHasChanged
};

/** 
 \brief                 地图控件中的右键菜单
\details  !!!!!!! 已经不用了 
 \author    陈龙
\date      2013/05/23
*/
enum ContextMenuFlag
{
	NormalSize = 0x1,
	ZoomIn = 0x2,
	ZoomOut = 0x4,
	Copy = 0x8,
	Paste = 0x10,
	AddVertex = 0x20,
	DeleteVertex = 0x40,
};


W_DECLARE_FLAGS(ContextMenuFlags, ContextMenuFlag)


enum TransformationMode
{
	FastTransformation = 0,
	SmoothTransformation,
};

enum AspectRatioMode
{
	IgnoreAspectRatio = 0,
	KeepAspectRatio,
	KeepAspectRatioByExpanding,
};


enum RenderHint
{
	Antialiasing				 =	0x01,
	TextAntialiasing			 =  0x02,
	SmoothPixmapTransform		 =	0x04,
	HighQualityAntialiasing  	 =	0x08,
	NonCosmeticDefaultPen		 =	0x10,
};

NS_GLOBAL_END

#endif