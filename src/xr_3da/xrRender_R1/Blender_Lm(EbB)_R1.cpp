#include "stdafx.h"
#pragma hdrstop

#include "Blender_Lm(EbB)_R1.hpp"

void CBlender_LmEbB_R1::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);
    if (C.bEditor)	{
        C.PassBegin();
        {
            C.PassSET_ZB(TRUE, TRUE);
            C.PassSET_Blend_SET();
            C.PassSET_LightFog(TRUE, TRUE);

            // Stage1 - Env texture
            C.StageBegin();
            C.StageSET_Address(D3DTADDRESS_CLAMP);
            C.StageSET_Color(D3DTA_TEXTURE, D3DTOP_SELECTARG1, D3DTA_DIFFUSE);
            C.StageSET_Alpha(D3DTA_TEXTURE, D3DTOP_SELECTARG1, D3DTA_DIFFUSE);
            C.StageSET_TMC(oT2_Name, oT2_xform, "$null", 0);
            C.StageEnd();

            // Stage2 - Base texture
            C.StageBegin();
            C.StageSET_Color(D3DTA_TEXTURE, D3DTOP_BLENDTEXTUREALPHA, D3DTA_CURRENT);
            C.StageSET_Alpha(D3DTA_TEXTURE, D3DTOP_SELECTARG1, D3DTA_CURRENT);
            C.StageSET_TMC(oT_Name, oT_xform, "$null", 0);
            C.StageEnd();

            // Stage3 - Lighting - should work on all 2tex hardware
            C.StageBegin();
            C.StageSET_Color(D3DTA_DIFFUSE, D3DTOP_MODULATE, D3DTA_CURRENT);
            C.StageSET_Alpha(D3DTA_DIFFUSE, D3DTOP_SELECTARG2, D3DTA_CURRENT);
            C.Stage_Texture("$null");
            C.Stage_Matrix("$null", 0);
            C.Stage_Constant("$null");
            C.StageEnd();
        }
        C.PassEnd();
    }
    else {
        if (C.L_textures.size()<2)	Debug.fatal(DEBUG_INFO, "Not enought textures for shader, base tex: %s", *C.L_textures[0]);
        switch (C.iElement)
        {
        case SE_R1_NORMAL_HQ:
        case SE_R1_NORMAL_LQ:
            // Level view
            /*
            if (C.bDetail_Diffuse)
            {
            if (oBlend.value)	C.r_Pass	("lmapE_dt","lmapE_dt",TRUE,TRUE,FALSE,TRUE,D3DBLEND_SRCALPHA,D3DBLEND_INVSRCALPHA,TRUE,0);
            else				C.r_Pass	("lmapE_dt","lmapE_dt",TRUE);
            C.r_Sampler	("s_base",	C.L_textures[0]);
            C.r_Sampler	("s_lmap",	C.L_textures[1]);
            C.r_Sampler	("s_env",	oT2_Name,false,D3DTADDRESS_CLAMP);
            C.r_Sampler	("s_detail",C.detail_texture);
            C.r_End		();
            } else
            {
            */
            if (oBlend.value)	C.r_Pass("lmapE", "lmapE", TRUE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, TRUE, 0);
            else				C.r_Pass("lmapE", "lmapE", TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_lmap", C.L_textures[1]);
            C.r_Sampler_clf("s_hemi", *C.L_textures[2]);
            C.r_Sampler("s_env", oT2_Name, false, D3DTADDRESS_CLAMP);
            C.r_End();
            // }
            break;
        case SE_R1_LPOINT:
            C.r_Pass("lmap_point", "add_point", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler_clf("s_lmap", TEX_POINT_ATT);
            C.r_Sampler_clf("s_att", TEX_POINT_ATT);
            C.r_End();
            break;
        case SE_R1_LSPOT:
            C.r_Pass("lmap_spot", "add_spot", FALSE, TRUE, FALSE, TRUE, D3DBLEND_ONE, D3DBLEND_ONE, TRUE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler_clf("s_lmap", "internal\\internal_light_att", true);
            C.r_Sampler_clf("s_att", TEX_SPOT_ATT);
            C.r_End();
            break;
        case SE_R1_LMODELS:
            // Lighting only, not use alpha-channel
            C.r_Pass("lmap_l", "lmap_l", FALSE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_lmap", C.L_textures[1]);
            C.r_Sampler_clf("s_hemi", *C.L_textures[2]);
            C.r_End();
            break;
        }
    }
}