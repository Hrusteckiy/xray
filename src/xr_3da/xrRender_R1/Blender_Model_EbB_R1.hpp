#pragma once

#include "../xrRender/Blender_Model_EbB.h"

class CBlender_Model_EbB_R1 : public CBlender_Model_EbB
{
public:
    void Compile(CBlender_Compile& C) override;
};