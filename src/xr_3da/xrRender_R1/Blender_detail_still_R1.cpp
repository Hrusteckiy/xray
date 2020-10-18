#include "stdafx.h"
#pragma hdrstop

#include "Blender_detail_still_R1.hpp"

void CBlender_Detail_Still_R1::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    if (C.bEditor)
    {
        C.PassBegin();
        {
            C.PassSET_ZB(TRUE, TRUE);
            if (oBlend.value)	C.PassSET_Blend_BLEND(TRUE, 200);
            else				C.PassSET_Blend_SET(TRUE, 200);
            C.PassSET_LightFog(TRUE, TRUE);

            // Stage1 - Base texture
            C.StageBegin();
            C.StageSET_Color(D3DTA_TEXTURE, D3DTOP_MODULATE, D3DTA_DIFFUSE);
            C.StageSET_Alpha(D3DTA_TEXTURE, D3DTOP_MODULATE, D3DTA_DIFFUSE);
            C.StageSET_TMC(oT_Name, "$null", "$null", 0);
            C.StageEnd();
        }
        C.PassEnd();
    }
    else {
        switch (C.iElement)
        {
        case SE_R1_NORMAL_HQ:
            C.r_Pass("detail_wave", "detail", FALSE, TRUE, TRUE, FALSE, D3DBLEND_ONE, D3DBLEND_ZERO, oBlend.value ? TRUE : FALSE, oBlend.value ? 200 : 0);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_End();
            break;
        case SE_R1_NORMAL_LQ:
            C.r_Pass("detail_still", "detail", FALSE, TRUE, TRUE, FALSE, D3DBLEND_ONE, D3DBLEND_ZERO, oBlend.value ? TRUE : FALSE, oBlend.value ? 200 : 0);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_End();
            break;
        case SE_R1_LPOINT:
            break;
        case SE_R1_LSPOT:
            break;
        case SE_R1_LMODELS:
            break;
        }
    }
}