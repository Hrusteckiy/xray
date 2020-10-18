#include "stdafx.h"
#pragma hdrstop

#include "Blender_tree_R2.hpp"
#include "uber_deffer.h"

void CBlender_Tree_R2::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    //*************** codepath is the same, only shaders differ
    LPCSTR	tvs = "tree";
    LPCSTR	tvs_s = "shadow_direct_tree";
    if (oNotAnTree.value)	{ tvs = "tree_s"; tvs_s = "shadow_direct_tree_s"; }
    switch (C.iElement)
    {
    case SE_R2_NORMAL_HQ:	// deffer
        uber_deffer(C, true, tvs, "base", oBlend.value);
        break;
    case SE_R2_NORMAL_LQ:	// deffer
        uber_deffer(C, false, tvs, "base", oBlend.value);
        break;
    case SE_R2_SHADOW:		// smap-spot
        if (oBlend.value)	C.r_Pass(tvs_s, "shadow_direct_base_aref", FALSE, TRUE, TRUE, TRUE, D3DBLEND_ZERO, D3DBLEND_ONE, TRUE, 200);
        else				C.r_Pass(tvs_s, "shadow_direct_base", FALSE);
        C.r_Sampler("s_base", C.L_textures[0]);
        C.r_End();
        break;
    }
}