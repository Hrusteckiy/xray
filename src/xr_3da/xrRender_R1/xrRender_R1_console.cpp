#include "stdafx.h"
#include "xrRender_R1_console.hpp"
#include "../xrRender/xrRender_console_cmd.hpp"

// R1
float		ps_r1_ssaLOD_A = 64.f;
float		ps_r1_ssaLOD_B = 48.f;
float		ps_r1_tf_Mipbias = 0.0f;
Flags32		ps_r1_flags = { R1FLAG_DLIGHTS };		// r1-only
float		ps_r1_lmodel_lerp = 0.1f;
float		ps_r1_dlights_clip = 30.f;
//float		ps_r1_pps_u = 0.f;
//float		ps_r1_pps_v = 0.f;

// R1-specific
int			ps_r1_GlowsPerFrame = 16;				// r1-only

class CCC_ModelPoolStat : public IConsole_Command
{
public:
    CCC_ModelPoolStat(LPCSTR N) : IConsole_Command(N)  { bEmptyArgsHandled = TRUE; };
    virtual void Execute(LPCSTR args) {
        xray::renderBase.Models->dump();
    }
};

void xrRender_R1_initconsole()
{
#ifdef DEBUG
    CMD4(CCC_Integer, "r__lsleep_frames", &ps_r__LightSleepFrames, 4, 30);
    CMD4(CCC_Float, "r__ssa_glod_start", &ps_r__GLOD_ssa_start, 128, 512);
    CMD4(CCC_Float, "r__ssa_glod_end", &ps_r__GLOD_ssa_end, 16, 96);
    CMD4(CCC_Float, "r__wallmark_shift_pp", &ps_r__WallmarkSHIFT, 0.0f, 1.f);
    CMD4(CCC_Float, "r__wallmark_shift_v", &ps_r__WallmarkSHIFT_V, 0.0f, 1.f);
    CMD4(CCC_Float, "r__wallmark_ttl", &ps_r__WallmarkTTL, 1.0f, 5.f*60.f);
    CMD1(CCC_ModelPoolStat, "stat_models");
#endif // DEBUG

    xrRender_initconsole();

    // R1
    CMD4(CCC_Float, "r1_ssa_lod_a", &ps_r1_ssaLOD_A, 16, 96);
    CMD4(CCC_Float, "r1_ssa_lod_b", &ps_r1_ssaLOD_B, 16, 64);
    CMD4(CCC_Float, "r1_lmodel_lerp", &ps_r1_lmodel_lerp, 0, 0.333f);
    CMD2(CCC_tf_MipBias, "r1_tf_mipbias", &ps_r1_tf_Mipbias);//	{-3 +3}
    CMD3(CCC_Mask, "r1_dlights", &ps_r1_flags, R1FLAG_DLIGHTS);
    CMD4(CCC_Float, "r1_dlights_clip", &ps_r1_dlights_clip, 10.f, 150.f);
    CMD4(CCC_Float, "r1_pps_u", &ps_r1_pps_u, -1.f, +1.f);
    CMD4(CCC_Float, "r1_pps_v", &ps_r1_pps_v, -1.f, +1.f);
    CMD4(CCC_Float, "r1_dlights_clip", &ps_r1_dlights_clip, 10.f, 150.f);

    // R1-specific
    CMD4(CCC_Integer, "r1_glows_per_frame", &ps_r1_GlowsPerFrame, 2, 32);
}

void xrRender_apply_tf()
{
    Console->Execute("r__tf_aniso");
    Console->Execute("r1_tf_mipbias");
}