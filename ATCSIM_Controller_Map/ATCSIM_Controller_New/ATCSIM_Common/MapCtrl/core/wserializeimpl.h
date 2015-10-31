#ifndef _WSERIALIZE_IMPL_H_
#define _WSERIALIZE_IMPL_H_

#include "../wdllimport.h"
#include "wpen.h"
#include "wfont.h"
#include "wcolor.h"
#include "wbrush.h"
#include "wworldline.h"
#include "wworldsize.h"
#include "wworldrect.h"
#include "wworldpoint.h"

MAPAPI char* serialize_impl(char* buf, const WWorldPointF& point);
MAPAPI char* serialize_impl(char* buf, const WWorldSizeF& size);
MAPAPI char* serialize_impl(char* buf, const WWorldRectF& rect);
MAPAPI char* serialize_impl(char* buf, const WWorldLineF& line);
MAPAPI char* serialize_impl(char* buf, const WColor& color);
MAPAPI char* serialize_impl(char* buf, const WBrush& brush);
MAPAPI char* serialize_impl(char* buf, const WPen& pen);
MAPAPI char* serialize_impl(char* buf, const WFont& font);

MAPAPI const char* unserialize_impl(const char* buf, WWorldPointF& point);
MAPAPI const char* unserialize_impl(const char* buf, WWorldSizeF& size);
MAPAPI const char* unserialize_impl(const char* buf, WWorldRectF& rect);
MAPAPI const char* unserialize_impl(const char* buf, WWorldLineF& line);
MAPAPI const char* unserialize_impl(const char* buf, WColor& color);
MAPAPI const char* unserialize_impl(const char* buf, WBrush& brush);
MAPAPI const char* unserialize_impl(const char* buf, WPen& pen);
MAPAPI const char* unserialize_impl(const char* buf, WFont& font);

MAPAPI size_t serialize_size_impl(const WWorldPointF& point);
MAPAPI size_t serialize_size_impl(const WWorldSizeF& size);
MAPAPI size_t serialize_size_impl(const WWorldRectF& rect);
MAPAPI size_t serialize_size_impl(const WWorldLineF& line);
MAPAPI size_t serialize_size_impl(const WColor& color);
MAPAPI size_t serialize_size_impl(const WBrush& brush);
MAPAPI size_t serialize_size_impl(const WPen& pen);
MAPAPI size_t serialize_size_impl(const WFont& font);

#endif