#pragma once

#include "../xrRender/DetailManager.h"

class CDetailManager_R1 : public CDetailManager
{
public:
    void buildColorDecompress(SlotItem& Item, DetailSlot& DS) override;
    void buildColorHwRender(Fvector4* c_storage, const u32 base, SlotItem& Instance, const Fvector& c_ambient, const Fvector& c_hemi, const Fvector& c_sun) override;
};