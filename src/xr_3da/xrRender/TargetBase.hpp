#pragma once

namespace xray {
namespace render {
class XRRENDER_API CTargetBase
{
public:
    void set_width(u32 w);
    void set_height(u32 h);

    u32 get_width();
    u32 get_height();

private:
    u32 width;
    u32 height;
};

extern XRRENDER_API CTargetBase targetBase;

}}