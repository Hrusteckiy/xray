#include "stdafx.h"
#pragma hdrstop

#include "FTreeVisual_R1.hpp"

void FTreeVisual_R1::Render(float LOD)
{
    static FTreeVisual_setup	tvs;
    if (tvs.dwFrame != Device.dwFrame)	tvs.calculate();
    // setup constants
    float	s = ps_r__Tree_SBC;
    RCache.set_c(m_xform, xform);														// matrix
    RCache.set_c(c_consts, tvs.scale, tvs.scale, 0, 0);									// consts/scale
    RCache.set_c(c_wave, tvs.wave);													// wave
    RCache.set_c(c_wind, tvs.wind);													// wind
    CEnvDescriptor&	desc = g_pGamePersistent->Environment().CurrentEnv;
    RCache.set_c(c_c_scale, s*c_scale.rgb.x, s*c_scale.rgb.y, s*c_scale.rgb.z, s*c_scale.hemi);	// scale
    RCache.set_c(c_c_bias, s*c_bias.rgb.x + desc.ambient.x, s*c_bias.rgb.y + desc.ambient.y, s*c_bias.rgb.z + desc.ambient.z, s*c_bias.hemi);		// bias
    RCache.set_c(c_c_sun, s*c_scale.sun, s*c_bias.sun, 0, 0);							// sun
}


//-----------------------------------------------------------------------------------
// Stripified Tree
//-----------------------------------------------------------------------------------
FTreeVisual_ST::FTreeVisual_ST(void)
{
}
FTreeVisual_ST::~FTreeVisual_ST(void)
{
}
void FTreeVisual_ST::Release()
{
    inherited::Release();
}
void FTreeVisual_ST::Load(const char* N, IReader *data, u32 dwFlags)
{
    inherited::Load(N, data, dwFlags);
}
void FTreeVisual_ST::Render(float LOD)
{
    inherited::Render(LOD);
    RCache.set_Geometry(rm_geom);
    RCache.Render(D3DPT_TRIANGLELIST, vBase, 0, vCount, iBase, dwPrimitives);
    RCache.stat.r.s_flora.add(vCount);
}
void FTreeVisual_ST::Copy(IRender_Visual *pSrc)
{
    inherited::Copy(pSrc);
}

//-----------------------------------------------------------------------------------
// Progressive Tree
//-----------------------------------------------------------------------------------
FTreeVisual_PM::FTreeVisual_PM(void)
{
    pSWI = 0;
    last_lod = 0;
}
FTreeVisual_PM::~FTreeVisual_PM(void)
{
}
void FTreeVisual_PM::Release()
{
    inherited::Release();
}
void FTreeVisual_PM::Load(const char* N, IReader *data, u32 dwFlags)
{
    inherited::Load(N, data, dwFlags);
    R_ASSERT(data->find_chunk(OGF_SWICONTAINER));
    {
        u32 ID = data->r_u32();
        pSWI = xray::renderBase.getSlideWindowItem(ID);
    }
}
void FTreeVisual_PM::Render(float LOD)
{
    inherited::Render(LOD);
    int lod_id = last_lod;
    if (LOD >= 0.f) {
        lod_id = iFloor((1.f - LOD)*float(pSWI->count - 1) + 0.5f);
        last_lod = lod_id;
    }
    VERIFY(lod_id >= 0 && lod_id<int(pSWI->count));
    FSlideWindow& SW = pSWI->sw[lod_id];
    RCache.set_Geometry(rm_geom);
    RCache.Render(D3DPT_TRIANGLELIST, vBase, 0, SW.num_verts, iBase + SW.offset, SW.num_tris);
    RCache.stat.r.s_flora.add(SW.num_verts);
}

#define PCOPY(a)	a = pFrom->a
void FTreeVisual_PM::Copy(IRender_Visual *pSrc)
{
    inherited::Copy(pSrc);
    FTreeVisual_PM	*pFrom = dynamic_cast<FTreeVisual_PM*> (pSrc);
    PCOPY(pSWI);
}