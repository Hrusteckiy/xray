#pragma once

#include "../xrRender/Blender_tree.h"

class CBlender_Tree_R1 : public CBlender_Tree
{
public:
    void Compile(CBlender_Compile& C) override;
};