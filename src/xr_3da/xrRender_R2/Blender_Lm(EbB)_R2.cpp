#include "stdafx.h"
#pragma hdrstop

#include "Blender_Lm(EbB)_R2.hpp"

void CBlender_LmEbB_R2::Compile(CBlender_Compile& C)
{
    if (oBlend.value)	C.r_Pass("lmapE", "lmapE", TRUE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, TRUE, 0);
    else				C.r_Pass("lmapE", "lmapE", TRUE);
    C.r_Sampler("s_base", C.L_textures[0]);
    C.r_Sampler("s_lmap", C.L_textures[1]);
    C.r_Sampler_clf("s_hemi", *C.L_textures[2]);
    C.r_Sampler("s_env", oT2_Name, false, D3DTADDRESS_CLAMP);
    C.r_End();
}