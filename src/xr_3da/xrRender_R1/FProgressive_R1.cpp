// FProgressive.cpp: implementation of the FProgressive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma hdrstop

#include "../fmesh.h"
#include "FProgressive_R1.hpp"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FProgressive_R1::FProgressive_R1() : Fvisual_R1()
{
    xSWI = 0;
    last_lod = 0;
}

FProgressive_R1::~FProgressive_R1()
{

}

void FProgressive_R1::Release()
{
    Fvisual_R1::Release();
    xr_free(nSWI.sw);
    if (xSWI)		{
        xr_free(xSWI->sw);
        xr_delete(xSWI);
    }
}

void FProgressive_R1::Load(const char* N, IReader *data, u32 dwFlags)
{
    Fvisual_R1::Load(N, data, dwFlags);

    // normal SWI
    destructor<IReader> lods(data->open_chunk(OGF_SWIDATA));
    nSWI.reserved[0] = lods().r_u32();	// reserved 16 bytes
    nSWI.reserved[1] = lods().r_u32();
    nSWI.reserved[2] = lods().r_u32();
    nSWI.reserved[3] = lods().r_u32();
    nSWI.count = lods().r_u32();
    VERIFY(NULL == nSWI.sw);
    nSWI.sw = xr_alloc<FSlideWindow>(nSWI.count);
    lods().r(nSWI.sw, nSWI.count*sizeof(FSlideWindow));
}

void FProgressive_R1::Render(float LOD)
{
    int lod_id = last_lod;
    if (LOD >= 0.f){
        clamp(LOD, 0.f, 1.f);
        lod_id = iFloor((1.f - LOD)*float(nSWI.count - 1) + 0.5f);
        last_lod = lod_id;
    }
    VERIFY(lod_id >= 0 && lod_id<int(nSWI.count));
    FSlideWindow& SW = nSWI.sw[lod_id];
    RCache.set_Geometry(rm_geom);
    RCache.Render(D3DPT_TRIANGLELIST, vBase, 0, SW.num_verts, iBase + SW.offset, SW.num_tris);
    RCache.stat.r.s_static.add(SW.num_verts);
}

#define PCOPY(a)	a = pFrom->a
void FProgressive_R1::Copy(IRender_Visual *pSrc)
{
    Fvisual_R1::Copy(pSrc);
    FProgressive_R1 *pFrom = (FProgressive_R1*)pSrc;
    PCOPY(nSWI);
    PCOPY(xSWI);
}
