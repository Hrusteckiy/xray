#include "stdafx.h"

#include "DetailManager_R2.hpp"

void CDetailManager_R2::apply_lmaterial()
{
    RImplementation.apply_lmaterial();
}

void CDetailManager_R2::buildColorHwRender(Fvector4* c_storage, const u32 base, SlotItem& Instance, const Fvector& c_ambient, const Fvector& c_hemi, const Fvector& c_sun)
{
    // R2 only needs hemisphere
    float h = Instance.c_hemi;
    float s = Instance.c_sun;
    c_storage[base + 3].set(s, s, s, h);
}