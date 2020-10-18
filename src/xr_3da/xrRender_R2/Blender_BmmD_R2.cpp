#include "stdafx.h"
#pragma hdrstop

#include "Blender_BmmD_R2.hpp"
#include "uber_deffer.h"

void CBlender_BmmD_R2::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    // codepath is the same, only the shaders differ
    // ***only pixel shaders differ***
    string256				mask;
    strconcat(sizeof(mask), mask, C.L_textures[0].c_str(), "_mask");
    switch (C.iElement)
    {
    case SE_R2_NORMAL_HQ: 		// deffer
        uber_deffer(C, true, "impl", "impl", false, oT2_Name[0] ? oT2_Name : 0, true);
        C.r_Sampler("s_mask", mask);
        C.r_Sampler("s_lmap", C.L_textures[1]);

        C.r_Sampler("s_dt_r", oR_Name, false, D3DTADDRESS_WRAP, D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR, D3DTEXF_ANISOTROPIC);
        C.r_Sampler("s_dt_g", oG_Name, false, D3DTADDRESS_WRAP, D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR, D3DTEXF_ANISOTROPIC);
        C.r_Sampler("s_dt_b", oB_Name, false, D3DTADDRESS_WRAP, D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR, D3DTEXF_ANISOTROPIC);
        C.r_Sampler("s_dt_a", oA_Name, false, D3DTADDRESS_WRAP, D3DTEXF_ANISOTROPIC, D3DTEXF_LINEAR, D3DTEXF_ANISOTROPIC);

        C.r_Sampler("s_dn_r", strconcat(sizeof(mask), mask, oR_Name, "_bump"));
        C.r_Sampler("s_dn_g", strconcat(sizeof(mask), mask, oG_Name, "_bump"));
        C.r_Sampler("s_dn_b", strconcat(sizeof(mask), mask, oB_Name, "_bump"));
        C.r_Sampler("s_dn_a", strconcat(sizeof(mask), mask, oA_Name, "_bump"));

        C.r_End();
        break;
    case SE_R2_NORMAL_LQ: 		// deffer
        uber_deffer(C, false, "base", "impl", false, oT2_Name[0] ? oT2_Name : 0, true);
        C.r_Sampler("s_lmap", C.L_textures[1]);
        C.r_End();
        break;
    case SE_R2_SHADOW:			// smap
        if (RImplementation.o.HW_smap)	C.r_Pass("shadow_direct_base", "dumb", FALSE, TRUE, TRUE, FALSE);
        else							C.r_Pass("shadow_direct_base", "shadow_direct_base", FALSE);
        C.r_Sampler("s_base", C.L_textures[0]);
        C.r_End();
        break;
    }
}