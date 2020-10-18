#pragma once

#include "../xrRender/xrRender_console.h"

// R1
extern ECORE_API	float		ps_r1_ssaLOD_A;
extern ECORE_API	float		ps_r1_ssaLOD_B;
extern ECORE_API	float		ps_r1_tf_Mipbias;
extern ECORE_API	float		ps_r1_lmodel_lerp;
extern ECORE_API	float		ps_r1_dlights_clip;
//extern ECORE_API	float		ps_r1_pps_u;
//extern ECORE_API	float		ps_r1_pps_v;

// ^^^ uncomment later

// R1-specific
extern ECORE_API	int			ps_r1_GlowsPerFrame;	// r1-only
extern ECORE_API	Flags32		ps_r1_flags;			// r1-only
enum
{
    R1FLAG_DLIGHTS = (1 << 0),
};

extern void xrRender_R1_initconsole();
extern void xrRender_apply_tf();