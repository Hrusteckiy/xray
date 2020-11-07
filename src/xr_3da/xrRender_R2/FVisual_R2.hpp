#pragma once

#include "../xrRender/FVisual.h"

class Fvisual_R2 : public Fvisual
{
public:
    virtual void Render(float LOD) override;		// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored ?
    virtual void Load(LPCSTR N, IReader *data, u32 dwFlags) override;
};