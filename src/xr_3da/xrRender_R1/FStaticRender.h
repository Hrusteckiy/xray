#pragma once

#include "../xrRender/r__dsgraph_structure.h"
#include "..\xrRender\hom.h"
#include "DetailManager_R1.hpp"
#include "glowmanager.h"
#include "fstaticrender_rendertarget.h"

#include "lightShadows.h"
#include "lightProjector.h"
#include "lightPPA.h"
#include "Light_DB_R1.hpp"

#include "../Fmesh.h"

// definition
class CRender : public R_dsgraph_structure
{
public:
	struct		_options	{
		u32		vis_intersect		: 1;	// config

		u32		distortion			: 1;	// run-time modified
		u32		disasm				: 1;	// config
		u32		forceskinw			: 1;	// config
	}			o;
	struct		_stats		{
		u32		o_queries,	o_culled;
	}			stats;
public:
	// Sector detection and visibility
	Fvector														vLastCameraPos;
	u32															uLastLTRACK;
	xrXRC														Sectors_xrc;
//.	R_occlusion													HWOCC;

    xray::CLight_DB_R1*											L_DB;
	CLightR_Manager*											L_Dynamic;
	CLightShadows*												L_Shadows;
	CLightProjector*											L_Projector;
	CGlowManager*												L_Glows;

    CRenderTarget*												Target;			// Render-target

	// R1-specific global constants
	Fmatrix														r1_dlight_tcgen			;
    xray::Light*												r1_dlight_light;
	float														r1_dlight_scale			;
	cl_light_PR													r1_dlight_binder_PR		;
	cl_light_C													r1_dlight_binder_color	;
	cl_light_XFORM												r1_dlight_binder_xform	;
	shared_str													c_ldynamic_props		;
private:
	// Loading / Unloading
	void								LoadBuffers				(CStreamReader	*fs);
	void								LoadVisuals				(IReader *fs);
	void								LoadLights				(IReader *fs);
	void								LoadSectors				(IReader *fs);

	BOOL								add_Dynamic				(IRender_Visual	*pVisual, u32 planes);		// normal processing
	void								add_Static				(IRender_Visual	*pVisual, u32 planes);
	void								add_leafs_Dynamic		(IRender_Visual	*pVisual);					// if detected node's full visibility
	void								add_leafs_Static		(IRender_Visual	*pVisual);					// if detected node's full visibility

public:
	ShaderElement*						rimp_select_sh_static	(IRender_Visual	*pVisual, float cdist_sq);
	ShaderElement*						rimp_select_sh_dynamic	(IRender_Visual	*pVisual, float cdist_sq);
	void								ApplyBlur4				(FVF::TL4uv*	dest, u32 w, u32 h, float k);
	void								apply_object			(IRenderable*	O);
	IC void								apply_lmaterial			()				{};
public:
	// feature level
	virtual	GenerationLevel			get_generation			()	{ return IRender_interface::GENERATION_R1; }

	// Loading / Unloading
	virtual	void					create					();
	virtual	void					destroy					();
	virtual	void					reset_begin				();
	virtual	void					reset_end				();

	virtual	void					level_Load				(IReader*);
	virtual void					level_Unload			();
	
	virtual IDirect3DBaseTexture9*	texture_load			(LPCSTR	fname, u32& msize);
	virtual HRESULT					shader_compile			(
		LPCSTR							name,
		LPCSTR                          pSrcData,
		UINT                            SrcDataLen,
		void*							pDefines,
		void*							pInclude,
		LPCSTR                          pFunctionName,
		LPCSTR                          pTarget,
		DWORD                           Flags,
		void*							ppShader,
		void*							ppErrorMsgs,
		void*							ppConstantTable);

	// Information
	virtual void					Statistics				(CGameFont* F);
	virtual LPCSTR					getShaderPath			()									{ return "r1\\";	}
	virtual IRender_Sector*			detectSector			(const Fvector& P);
    virtual IRender_Target*			getTarget					();
	
	// Main 
	virtual void					flush					();
	virtual void					set_Object				(IRenderable*		O	);
	virtual	void					add_Occluder			(Fbox2&	bb_screenspace	);			// mask screen region as oclluded
	virtual void					add_Visual				(IRender_Visual*	V	);			// add visual leaf (no culling performed at all)
	virtual void					add_Geometry			(IRender_Visual*	V	);			// add visual(s)	(all culling performed)
	
	//
	virtual IBlender*				blender_create			(CLASS_ID cls);
	virtual void					blender_destroy			(IBlender* &);

	//
	virtual IRender_ObjectSpecific*	ros_create				(IRenderable* parent);
	virtual void					ros_destroy				(IRender_ObjectSpecific* &);

	// Particle library
	virtual CPSLibrary*				ps_library				(){return &xray::renderBase.PSLibrary;}

	// Lighting
	virtual IRender_Light*			light_create			();
	virtual IRender_Glow*			glow_create				();
	
	// Models
	virtual IRender_Visual*			model_CreateParticles	(LPCSTR name);
	virtual IRender_DetailModel*	model_CreateDM			(IReader*F);
	virtual IRender_Visual*			model_Create			(LPCSTR name, IReader*data=0);
	virtual IRender_Visual*			model_CreateChild		(LPCSTR name, IReader*data);
	virtual IRender_Visual*			model_Duplicate			(IRender_Visual*	V);
	virtual void					model_Delete			(IRender_Visual* &	V, BOOL bDiscard);
	virtual void 					model_Delete			(IRender_DetailModel* & F);
	virtual void					model_Logging			(BOOL bEnable)				{ xray::renderBase.Models->Logging(bEnable); }
	virtual void					models_Prefetch			();
	virtual void					models_Clear			(BOOL b_complete);
	
	// Main
	virtual void					Calculate				();
	virtual void					Render					();
	virtual void					Screenshot				(ScreenshotMode mode=SM_NORMAL, LPCSTR name = 0);
	virtual void					OnFrame					();

	// Constructor/destructor/loader
	CRender							();
	virtual ~CRender				();
};

extern CRender						RImplementation;
