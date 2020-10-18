#include "stdafx.h"
#pragma hdrstop

#include "Blender_Particle_R1.hpp"

void CBlender_Particle_R1::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    switch (oBlend.IDselected)
    {
    case 0:	C.r_Pass("particle", "particle", TRUE, TRUE, TRUE, FALSE, D3DBLEND_ONE, D3DBLEND_ZERO, TRUE, 200);	break;	// SET
    case 1: C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, TRUE, 0);	break;	// BLEND
    case 2:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE, 0);	break;	// ADD
    case 3:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// MUL
    case 4:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_SRCCOLOR, TRUE, 0);	break;	// MUL_2X
    case 5:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_ONE, TRUE, 0);	break;	// ALPHA-ADD
    }
    C.r_Sampler("s_base", C.L_textures[0], false, oClamp.value ? D3DTADDRESS_CLAMP : D3DTADDRESS_WRAP);
    C.r_End();
}