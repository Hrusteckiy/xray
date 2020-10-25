#include "stdafx.h"
#include "RenderBase.hpp"

namespace xray {

XRRENDER_API float r_ssaDISCARD;
XRRENDER_API float r_ssaDONTSORT;
XRRENDER_API float r_ssaLOD_A, r_ssaLOD_B;
XRRENDER_API float r_ssaGLOD_start, r_ssaGLOD_end;
XRRENDER_API float r_ssaHZBvsTEX;

XRRENDER_API CRenderBase renderBase;

ref_shader CRenderBase::getShader(int id)
{
    VERIFY(id<int(Shaders.size()));
    return Shaders[id];
}

IRender_Sector* CRenderBase::getSector(int id)
{
    VERIFY(id<int(Sectors.size()));
    return Sectors[id];
}

IRender_Visual* CRenderBase::getVisual(int id)
{
    VERIFY(id<int(Visuals.size()));
    return Visuals[id];
}

void CRenderBase::add_StaticWallmark(ref_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* verts)
{
    if (T->suppress_wm)	return;
    VERIFY2(_valid(P) && _valid(s) && T && verts && (s>EPS_L), "Invalid static wallmark params");
    xray::renderBase.Wallmarks->AddStaticWallmark(T, verts, P, &*S, s);
}

void CRenderBase::clear_static_wallmarks()
{
    xray::renderBase.Wallmarks->clear();
}

void CRenderBase::add_SkeletonWallmark(intrusive_ptr<CSkeletonWallmark> wm)
{
    xray::renderBase.Wallmarks->AddSkeletonWallmark(wm);
}

void CRenderBase::add_SkeletonWallmark(const Fmatrix* xf, CKinematics* obj, ref_shader& sh, const Fvector& start, const Fvector& dir, float size)
{
    xray::renderBase.Wallmarks->AddSkeletonWallmark(xf, obj, sh, start, dir, size);
}

void CRenderBase::blender_destroy(IBlender* &B)
{
    xr_delete(B);
}

IRender_Portal* CRenderBase::getPortal(int id)
{
    VERIFY(id<int(Portals.size()));
    return Portals[id];
}

IRender_Sector* CRenderBase::getSectorActive()
{
    return pLastSector;
}

}