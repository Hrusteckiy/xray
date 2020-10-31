#include "stdafx.h"
#include "TargetBase.hpp"

namespace xray {
namespace render {

XRRENDER_API CTargetBase targetBase;

void CTargetBase::set_width(u32 w)
{
    width = w;
}

void CTargetBase::set_height(u32 h)
{
    height = h;
}

u32 CTargetBase::get_width()
{
    return width;
}

u32 CTargetBase::get_height()
{
    return height;
}

}}