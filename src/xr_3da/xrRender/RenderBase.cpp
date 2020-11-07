#include "stdafx.h"
#include "RenderBase.hpp"
#include "TargetBase.hpp"

#include <xrCore/stream_reader.h>
#include <xr_3da/xrLevel.h>

namespace xray {

XRRENDER_API float r_ssaDISCARD;
XRRENDER_API float r_ssaDONTSORT;
XRRENDER_API float r_ssaLOD_A, r_ssaLOD_B;
XRRENDER_API float r_ssaGLOD_start, r_ssaGLOD_end;
XRRENDER_API float r_ssaHZBvsTEX;

XRRENDER_API CRenderBase renderBase;

ref_shader CRenderBase::getShader(int id)
{
    VERIFY(id<int(renderBase.Shaders.size()));
    return renderBase.Shaders[id];
}

IRender_Sector* CRenderBase::getSector(int id)
{
    VERIFY(id<int(renderBase.Sectors.size()));
    return renderBase.Sectors[id];
}

IRender_Visual* CRenderBase::getVisual(int id)
{
    VERIFY(id<int(renderBase.Visuals.size()));
    return renderBase.Visuals[id];
}

void CRenderBase::add_StaticWallmark(ref_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* verts)
{
    if (T->suppress_wm)	return;
    VERIFY2(_valid(P) && _valid(s) && T && verts && (s>EPS_L), "Invalid static wallmark params");
    renderBase.Wallmarks->AddStaticWallmark(T, verts, P, &*S, s);
}

void CRenderBase::clear_static_wallmarks()
{
    renderBase.Wallmarks->clear();
}

void CRenderBase::add_SkeletonWallmark(intrusive_ptr<CSkeletonWallmark> wm)
{
    renderBase.Wallmarks->AddSkeletonWallmark(wm);
}

void CRenderBase::add_SkeletonWallmark(const Fmatrix* xf, CKinematics* obj, ref_shader& sh, const Fvector& start, const Fvector& dir, float size)
{
    renderBase.Wallmarks->AddSkeletonWallmark(xf, obj, sh, start, dir, size);
}

void CRenderBase::blender_destroy(IBlender* &B)
{
    xr_delete(B);
}

BOOL CRenderBase::occ_visible(vis_data& P)
{
    return renderBase.HOM.visible(P);
}

BOOL CRenderBase::occ_visible(sPoly& P)
{
    return renderBase.HOM.visible(P);
}

BOOL CRenderBase::occ_visible(Fbox& P)
{
    return renderBase.HOM.visible(P);
}

void CRenderBase::rmNear()
{
    D3DVIEWPORT9 VP = { 0, 0, render::targetBase.get_width(), render::targetBase.get_height(), 0, 0.02f };
    CHK_DX(HW.pDevice->SetViewport(&VP));
}
void CRenderBase::rmFar()
{
    D3DVIEWPORT9 VP = { 0, 0, render::targetBase.get_width(), render::targetBase.get_height(), 0.99999f, 1.f };
    CHK_DX(HW.pDevice->SetViewport(&VP));
}
void CRenderBase::rmNormal()
{
    D3DVIEWPORT9 VP = { 0, 0, render::targetBase.get_width(), render::targetBase.get_height(), 0, 1.f };
    CHK_DX(HW.pDevice->SetViewport(&VP));
}

IRender_Portal* CRenderBase::getPortal(int id)
{
    VERIFY(id<int(renderBase.Portals.size()));
    return renderBase.Portals[id];
}

IRender_Sector* CRenderBase::getSectorActive()
{
    return renderBase.pLastSector;
}

FSlideWindowItem* CRenderBase::getSlideWindowItem(int id)
{
    VERIFY(id<int(renderBase.slideWindowItems.size()));
    return &renderBase.slideWindowItems[id];
}

D3DVERTEXELEMENT9* CRenderBase::getVertexBufferFormat(int id)
{
    VERIFY(id<int(renderBase.DCL.size()));
    return renderBase.DCL[id].begin();
}

IDirect3DVertexBuffer9*	CRenderBase::getVertexBuffer(int id)
{
    VERIFY(id<int(renderBase.vertexBuffer.size()));
    return renderBase.vertexBuffer[id];
}

IDirect3DIndexBuffer9* CRenderBase::getIndexBuffer(int id)
{
    VERIFY(id<int(renderBase.indexBuffer.size()));
    return renderBase.indexBuffer[id];
}

void CRenderBase::loadSlideWindowItems(CStreamReader* base_fs)
{
    // allocate memory for portals
    if (base_fs->find_chunk(fsL_SWIS))
    {
        CStreamReader		*fs = base_fs->open_chunk(fsL_SWIS);
        u32 item_count = fs->r_u32();

        xr_vector<FSlideWindowItem>::iterator it = renderBase.slideWindowItems.begin();
        xr_vector<FSlideWindowItem>::iterator it_e = renderBase.slideWindowItems.end();

        for (; it != it_e; ++it)
            xr_free((*it).sw);

        renderBase.slideWindowItems.clear_not_free();

        renderBase.slideWindowItems.resize(item_count);
        for (u32 c = 0; c<item_count; c++){
            FSlideWindowItem& swi = renderBase.slideWindowItems[c];
            swi.reserved[0] = fs->r_u32();
            swi.reserved[1] = fs->r_u32();
            swi.reserved[2] = fs->r_u32();
            swi.reserved[3] = fs->r_u32();
            swi.count = fs->r_u32();
            VERIFY(NULL == swi.sw);
            swi.sw = xr_alloc<FSlideWindow>(swi.count);
            fs->r(swi.sw, sizeof(FSlideWindow)*swi.count);
        }

        fs->close();
    }
}

}