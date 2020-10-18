#pragma once

#include "../xrRender/Blender_tree.h"

class CBlender_Tree_R2 : public CBlender_Tree
{
public:
    void Compile(CBlender_Compile& C) override;
};