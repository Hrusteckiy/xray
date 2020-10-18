#include "stdafx.h"
#pragma hdrstop

#include "Blender_detail_still_R2.hpp"
#include "uber_deffer.h"

void CBlender_Detail_Still_R2::Compile(CBlender_Compile& C)
{
    IBlender::Compile(C);

    switch (C.iElement)
    {
    case SE_R2_NORMAL_HQ: 		// deffer wave
        uber_deffer(C, false, "detail_w", "base", true);
        break;
    case SE_R2_NORMAL_LQ: 		// deffer still
        uber_deffer(C, false, "detail_s", "base", true);
        break;
    }
}