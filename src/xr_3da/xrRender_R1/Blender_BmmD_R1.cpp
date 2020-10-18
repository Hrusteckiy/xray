#include "stdafx.h"
#pragma hdrstop

#include "Blender_BmmD_R1.hpp"

void CBlender_BmmD_R1::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    if (C.bEditor)	{
        C.PassBegin();
        {
            C.PassSET_ZB(TRUE, TRUE);
            C.PassSET_Blend_SET();
            C.PassSET_LightFog(TRUE, TRUE);

            // Stage1 - Base texture
            C.StageBegin();
            C.StageSET_Color(D3DTA_TEXTURE, D3DTOP_MODULATE, D3DTA_DIFFUSE);
            C.StageSET_Alpha(D3DTA_TEXTURE, D3DTOP_MODULATE, D3DTA_DIFFUSE);
            C.StageSET_TMC(oT_Name, oT_xform, "$null", 0);
            C.StageEnd();

            // Stage2 - Second texture
            C.StageBegin();
            C.StageSET_Color(D3DTA_TEXTURE, D3DTOP_MODULATE2X, D3DTA_CURRENT);
            C.StageSET_Alpha(D3DTA_TEXTURE, D3DTOP_SELECTARG2, D3DTA_CURRENT);
            C.StageSET_TMC(oT2_Name, oT2_xform, "$null", 0);
            C.StageEnd();
        }
        C.PassEnd();
    }
    else {
        if (C.L_textures.size()<2)	Debug.fatal(DEBUG_INFO, "Not enought textures for shader, base tex: %s", *C.L_textures[0]);
        switch (C.iElement)
        {
        case SE_R1_NORMAL_HQ:
            C.r_Pass("impl_dt", "impl_dt", TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_lmap", C.L_textures[1]);
            C.r_Sampler("s_detail", oT2_Name);
            C.r_End();
            break;
        case SE_R1_NORMAL_LQ:
            C.r_Pass("impl_dt", "impl_dt", TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_lmap", C.L_textures[1]);
            C.r_Sampler("s_detail", oT2_Name);
            C.r_End();
            break;
        case SE_R1_LPOINT:
            C.r_Pass("impl_point", "add_point", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler_clf("s_lmap", TEX_POINT_ATT);
            C.r_Sampler_clf("s_att", TEX_POINT_ATT);
            C.r_End();
            break;
        case SE_R1_LSPOT:
            C.r_Pass("impl_spot", "add_spot", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler_clf("s_lmap", "internal\\internal_light_att", true);
            C.r_Sampler_clf("s_att", TEX_SPOT_ATT);
            C.r_End();
            break;
        case SE_R1_LMODELS:
            C.r_Pass("impl_l", "impl_l", FALSE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_lmap", C.L_textures[1]);
            C.r_End();
            break;
        }
    }
}