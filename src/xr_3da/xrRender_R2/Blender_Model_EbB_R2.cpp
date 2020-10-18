#include "stdafx.h"
#pragma hdrstop

#include "Blender_Model_EbB_R2.hpp"
#include "uber_deffer.h"

void CBlender_Model_EbB_R2::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    if (oBlend.value)	{
        // forward
        LPCSTR	vsname = 0;
        LPCSTR	psname = 0;
        switch (C.iElement)
        {
        case 0:
        case 1:
            vsname = psname = "model_env_lq";
            C.r_Pass(vsname, psname, TRUE, TRUE, FALSE, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA, TRUE, 0);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_Sampler("s_env", oT2_Name, false, D3DTADDRESS_CLAMP);
            C.r_End();
            break;
        }
    }
    else {
        // deferred
        switch (C.iElement)
        {
        case SE_R2_NORMAL_HQ: 	// deffer
            uber_deffer(C, true, "model", "base", false);
            break;
        case SE_R2_NORMAL_LQ: 	// deffer
            uber_deffer(C, false, "model", "base", false);
            break;
        case SE_R2_SHADOW:		// smap
            if (RImplementation.o.HW_smap)	C.r_Pass("shadow_direct_model", "dumb", FALSE, TRUE, TRUE, FALSE);
            else							C.r_Pass("shadow_direct_model", "shadow_direct_base", FALSE);
            C.r_Sampler("s_base", C.L_textures[0]);
            C.r_End();
            break;
        }
    }
}