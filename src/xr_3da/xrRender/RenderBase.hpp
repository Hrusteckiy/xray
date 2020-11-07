#pragma once

#include "r__dsgraph_structure.h"

#include <xr_3da/SkeletonCustom.h>
#include "WallmarksEngine.h"
#include "HOM.h"
#include "DetailManager.h"
#include "ModelPool.h"
#include <xr_3da/Fmesh.h>
#include "PSLibrary.h"

namespace xray {

extern XRRENDER_API float r_ssaDISCARD;
extern XRRENDER_API float r_ssaDONTSORT;
extern XRRENDER_API float r_ssaLOD_A, r_ssaLOD_B;
extern XRRENDER_API float r_ssaGLOD_start, r_ssaGLOD_end;
extern XRRENDER_API float r_ssaHZBvsTEX;

class XRRENDER_API CRenderBase : public R_dsgraph_structure
{
public:
    // overriding (mostly) as empty methods to be able to create instance of CRenderBase
    // these methods are not used in common render files so it shouldn't break anything
    // in the end specific R1 or R2 implemntation will be used unless they are the same
    virtual GenerationLevel get_generation() { return static_cast<IRender_interface::GenerationLevel>(-1); }
    virtual void create() {}
    virtual void destroy() {}
    virtual void reset_begin() {}
    virtual void reset_end() {}
    virtual void level_Load(IReader* fs) {}
    virtual void level_Unload() {}
    virtual IDirect3DBaseTexture9* texture_load(LPCSTR fname, u32& msize) { return nullptr; }
    virtual HRESULT shader_compile(LPCSTR name, LPCSTR pSrcData, UINT SrcDataLen,
        void* pDefines, void* pInclude, LPCSTR pFunctionName, LPCSTR pTarget,
        DWORD  Flags, void* ppShader, void* ppErrorMsgs, void* ppConstantTable) { return 0; }
    
    virtual LPCSTR getShaderPath() { return ""; }
    virtual ref_shader getShader(int id);
    virtual IRender_Sector* getSector(int id);
    virtual IRender_Visual* getVisual(int id);
    virtual IRender_Sector* detectSector(const Fvector& P) { return nullptr; }
    virtual IRender_Target* getTarget() { return nullptr; }

    // Main
    virtual void flush() {} // should be impemented here later { r_dsgraph_render_graph (0); }
    virtual void set_Object(IRenderable* O) {}
    virtual	void add_Occluder(Fbox2& bb_screenspace) {}
    virtual void add_Visual(IRender_Visual*	V) {}
    virtual void add_Geometry(IRender_Visual*	V) {} // should be impemented here later { add_Static(V,View->getMask()); }

    // wallmarks
    virtual void add_StaticWallmark(ref_shader& S, const Fvector& P, float s, CDB::TRI* T, Fvector* V);
    virtual void clear_static_wallmarks();
    virtual void add_SkeletonWallmark(intrusive_ptr<CSkeletonWallmark> wm);
    virtual void add_SkeletonWallmark(const Fmatrix* xf, CKinematics* obj, ref_shader& sh, const Fvector& start, const Fvector& dir, float size);

    //
    virtual IBlender* blender_create(CLASS_ID cls) { return nullptr; }
    virtual void blender_destroy(IBlender* &B);

    //
    virtual IRender_ObjectSpecific* ros_create(IRenderable* parent) { return nullptr; } // should be impemented here later { return xr_new<CROS_impl>(); }
    virtual void ros_destroy(IRender_ObjectSpecific* &) {} // should be impemented here later { xr_delete(p); }

    // Lighting
    virtual IRender_Light* light_create() { return nullptr; }
    virtual IRender_Glow* glow_create() { return nullptr; }

    // Models
    virtual IRender_Visual* model_CreateParticles(LPCSTR name) { return nullptr; } // add implementation (it's the same for R1 and R2) from here...
    virtual IRender_DetailModel* model_CreateDM(IReader* F) { return nullptr; }
    virtual IRender_Visual* model_Create(LPCSTR name, IReader* data = 0) { return nullptr; }
    virtual IRender_Visual* model_CreateChild(LPCSTR name, IReader*	data) { return nullptr; }
    virtual IRender_Visual* model_Duplicate(IRender_Visual*	V) { return nullptr; }
    virtual void model_Delete(IRender_Visual* &	V, BOOL bDiscard = FALSE) {}
    virtual void model_Delete(IRender_DetailModel* & F) {}
    virtual void model_Logging(BOOL bEnable) {}
    virtual void models_Prefetch() {}
    virtual void models_Clear(BOOL b_complete) {} // ...to here

    // Occlusion culling
    virtual BOOL occ_visible(vis_data& V);
    virtual BOOL occ_visible(Fbox& B);
    virtual BOOL occ_visible(sPoly& P);

    // Main
    virtual void Calculate() {}
    virtual void Render() {}
    virtual void Screenshot(ScreenshotMode mode = SM_NORMAL, LPCSTR name = 0) {} // implemented in r__screenshot.cpp, add this file to xrRnder later
    virtual void OnFrame() {}

    // Render Mode
    virtual void rmNear();
    virtual void rmFar();
    virtual void rmNormal();

    // fields and methods for renders only
    virtual IRender_Portal* getPortal(int id);
    virtual IRender_Sector* getSectorActive();

    FSlideWindowItem* getSlideWindowItem(int id);
    D3DVERTEXELEMENT9* getVertexBufferFormat(int id);
    IDirect3DVertexBuffer9*	getVertexBuffer(int id);
    IDirect3DIndexBuffer9* getIndexBuffer(int id);
    IRender_Visual* model_CreatePE(LPCSTR name);

    xr_vector<ref_shader> Shaders;
    xr_vector<IRender_Sector*> Sectors;
    xr_vector<IRender_Visual*> Visuals;
    xr_vector<IRender_Portal*> Portals;
    CSector* pLastSector;

    CWallmarksEngine* Wallmarks;
    CDB::MODEL* rmPortals;
    CHOM HOM;
    CDetailManager* Details;
    CModelPool* Models;

    // Global containers
    xr_vector<FSlideWindowItem> slideWindowItems;
    typedef svector<D3DVERTEXELEMENT9, MAXD3DDECLLENGTH + 1> VertexDeclarator;
    xr_vector<VertexDeclarator> DCL;
    xr_vector<IDirect3DVertexBuffer9*> vertexBuffer;
    xr_vector<IDirect3DIndexBuffer9*> indexBuffer;
    CPSLibrary PSLibrary;

protected:
    // Loading / Unloading
    //void LoadVisuals(IReader *fs);
    //void LoadSectors(IReader *fs);
    void loadSlideWindowItems(CStreamReader* base_fs);
};

extern XRRENDER_API CRenderBase renderBase;
}