#pragma once

#include "../xrRender/xrRender_console.h"

// R2
extern ECORE_API	float		ps_r2_ssaLOD_A;
extern ECORE_API	float		ps_r2_ssaLOD_B;
extern ECORE_API	float		ps_r2_tf_Mipbias;

// R2-specific
extern ECORE_API Flags32		ps_r2_ls_flags;				// r2-only
extern ECORE_API float			ps_r2_df_parallax_h;		// r2-only
extern ECORE_API float			ps_r2_df_parallax_range;	// r2-only
extern ECORE_API float			ps_r2_gmaterial;			// r2-only
extern ECORE_API float			ps_r2_tonemap_middlegray;	// r2-only
extern ECORE_API float			ps_r2_tonemap_adaptation;	// r2-only
extern ECORE_API float			ps_r2_tonemap_low_lum;		// r2-only
extern ECORE_API float			ps_r2_tonemap_amount;		// r2-only
extern ECORE_API float			ps_r2_ls_bloom_kernel_scale;// r2-only	// gauss
extern ECORE_API float			ps_r2_ls_bloom_kernel_g;	// r2-only	// gauss
extern ECORE_API float			ps_r2_ls_bloom_kernel_b;	// r2-only	// bilinear
extern ECORE_API float			ps_r2_ls_bloom_threshold;	// r2-only
extern ECORE_API float			ps_r2_ls_bloom_speed;		// r2-only
extern ECORE_API float			ps_r2_ls_dsm_kernel;		// r2-only
extern ECORE_API float			ps_r2_ls_psm_kernel;		// r2-only
extern ECORE_API float			ps_r2_ls_ssm_kernel;		// r2-only
extern ECORE_API Fvector		ps_r2_aa_barier;			// r2-only
extern ECORE_API Fvector		ps_r2_aa_weight;			// r2-only
extern ECORE_API float			ps_r2_aa_kernel;			// r2-only
extern ECORE_API float			ps_r2_mblur;				// .5f
extern ECORE_API int			ps_r2_GI_depth;				// 1..5
extern ECORE_API int			ps_r2_GI_photons;			// 8..256
extern ECORE_API float			ps_r2_GI_clip;				// EPS
extern ECORE_API float			ps_r2_GI_refl;				// .9f
extern ECORE_API float			ps_r2_ls_depth_scale;		// 1.0f
extern ECORE_API float			ps_r2_ls_depth_bias;		// -0.0001f
extern ECORE_API float			ps_r2_ls_squality;			// 1.0f
extern ECORE_API float			ps_r2_sun_near;				// 10.0f
extern ECORE_API float			ps_r2_sun_near_border;		// 1.0f
extern ECORE_API float			ps_r2_sun_tsm_projection;	// 0.2f
extern ECORE_API float			ps_r2_sun_tsm_bias;			// 0.0001f
extern ECORE_API float			ps_r2_sun_depth_far_scale;	// 1.00001f
extern ECORE_API float			ps_r2_sun_depth_far_bias;	// -0.0001f
extern ECORE_API float			ps_r2_sun_depth_near_scale;	// 1.00001f
extern ECORE_API float			ps_r2_sun_depth_near_bias;	// -0.0001f
//extern ECORE_API float			ps_r2_sun_lumscale;			// 0.5f
extern ECORE_API float			ps_r2_sun_lumscale_hemi;	// 1.0f
extern ECORE_API float			ps_r2_sun_lumscale_amb;		// 1.0f
extern ECORE_API float			ps_r2_zfill;				// .1f

//extern ECORE_API float			ps_r2_dhemi_scale;			// 1.5f
//extern ECORE_API int			ps_r2_dhemi_count;			// 5
//extern ECORE_API int			ps_r2_wait_sleep;
//extern ECORE_API float			ps_r2_slight_fade;			// 1.f
extern ECORE_API int			ps_r2_wait_sleep;

// ^^^ uncomment later

enum
{
    R2FLAG_SUN = (1 << 0),
    R2FLAG_SUN_FOCUS = (1 << 1),
    R2FLAG_SUN_TSM = (1 << 2),
    R2FLAG_SUN_DETAILS = (1 << 3),
    R2FLAG_TONEMAP = (1 << 4),
    R2FLAG_AA = (1 << 5),
    R2FLAG_GI = (1 << 6),
    R2FLAG_FASTBLOOM = (1 << 7),
    R2FLAG_GLOBALMATERIAL = (1 << 8),
    R2FLAG_ZFILL = (1 << 9),
    R2FLAG_R1LIGHTS = (1 << 10),
    R2FLAG_SUN_IGNORE_PORTALS = (1 << 11),

    //	R2FLAG_SUN_STATIC			= (1<<12),

    R2FLAG_EXP_SPLIT_SCENE = (1 << 13),
    R2FLAG_EXP_DONT_TEST_UNSHADOWED = (1 << 14),

    R2FLAG_USE_NVDBT = (1 << 15),
    R2FLAG_USE_NVSTENCIL = (1 << 16),

    R2FLAG_EXP_MT_CALC = (1 << 17),
};

extern void xrRender_R2_initconsole();
extern BOOL xrRender_test_hw();
extern void xrRender_apply_tf();