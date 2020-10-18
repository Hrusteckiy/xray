#include "stdafx.h"
#pragma hdrstop

#include "Blender_Particle_R2.hpp"

void CBlender_Particle_R2::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    switch (C.iElement)
    {
    case SE_R2_NORMAL_HQ: 	// deffer
    case SE_R2_NORMAL_LQ: 	// deffer
        switch (oBlend.IDselected)
        {
        case 0:	C.r_Pass("deffer_particle", "deffer_particle", FALSE, TRUE, TRUE, FALSE, D3DBLEND_ONE, D3DBLEND_ZERO, FALSE, 200);	break;	// SET
        case 1: C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, TRUE, 0);	break;	// BLEND
        case 2:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE, 0);	break;	// ADD
        case 3:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// MUL
        case 4:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_SRCCOLOR, TRUE, 0);	break;	// MUL_2X
        case 5:	C.r_Pass("particle", "particle", FALSE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_ONE, TRUE, 0);	break;	// ALPHA-ADD
        };
        C.r_Sampler("s_base", C.L_textures[0], false, oClamp.value ? D3DTADDRESS_CLAMP : D3DTADDRESS_WRAP);
        C.r_End();
        break;
    case SE_R2_SHADOW:		// smap
        // HARD or SOFT: shadow-map
        switch (oBlend.IDselected)
        {
        case 0:	C.r_Pass("particle", "particle", FALSE, TRUE, TRUE, FALSE, D3DBLEND_ONE, D3DBLEND_ZERO, TRUE, 200);	break;	// SET
        case 1: C.r_Pass("particle-clip", "particle_s-blend", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// BLEND
        case 2:	C.r_Pass("particle-clip", "particle_s-add", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// ADD
        case 3:	C.r_Pass("particle-clip", "particle_s-mul", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// MUL
        case 4:	C.r_Pass("particle-clip", "particle_s-mul", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// MUL_2X
        case 5:	C.r_Pass("particle-clip", "particle_s-aadd", FALSE, TRUE, FALSE, TRUE, D3DBLEND_DESTCOLOR, D3DBLEND_ZERO, TRUE, 0);	break;	// ALPHA-ADD
        };
        C.r_Sampler("s_base", C.L_textures[0], false, oClamp.value ? D3DTADDRESS_CLAMP : D3DTADDRESS_WRAP);
        C.r_End();
        break;
    case 4: 	// deffer-EMAP
        break;
    };
}