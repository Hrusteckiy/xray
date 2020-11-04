#include "stdafx.h"

#include "DetailManager_R1.hpp"

void CDetailManager_R1::buildColorDecompress(SlotItem& Item, DetailSlot& DS)
{
    Item.c_rgb.x = DS.r_qclr(DS.c_r, 15);
    Item.c_rgb.y = DS.r_qclr(DS.c_g, 15);
    Item.c_rgb.z = DS.r_qclr(DS.c_b, 15);
}

void CDetailManager_R1::buildColorHwRender(Fvector4* c_storage, const u32 base, SlotItem& Instance, const Fvector& c_ambient, const Fvector& c_hemi, const Fvector& c_sun)
{
    Fvector C;
    C.set(c_ambient);
    //C.mad(c_lmap,Instance.c_rgb);
    C.mad(c_hemi, Instance.c_hemi);
    C.mad(c_sun, Instance.c_sun);
    c_storage[base + 3].set(C.x, C.y, C.z, 1.f);
}