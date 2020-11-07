#pragma once

#include "../xrRender/ModelPool.h"

class CModelPool_R1 : public CModelPool
{
public:
    virtual IRender_Visual*	Instance_Create(u32 Type) override;
};