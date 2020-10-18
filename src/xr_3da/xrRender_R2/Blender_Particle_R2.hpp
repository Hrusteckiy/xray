#pragma once

#include "../xrRender/Blender_Particle.h"

class CBlender_Particle_R2 : public CBlender_Particle
{
public:
    void Compile(CBlender_Compile& C) override;
};