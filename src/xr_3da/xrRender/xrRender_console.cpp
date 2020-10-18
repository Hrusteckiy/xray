#include	"stdafx.h"
#pragma		hdrstop

#include	"xrRender_console.h"
#include	"xrRender_console_cmd.hpp"

u32			ps_Preset				=	2	;
xr_token							qpreset_token							[ ]={
	{ "Minimum",					0											},
	{ "Low",						1											},
	{ "Default",					2											},
	{ "High",						3											},
	{ "Extreme",					4											},
	{ 0,							0											}
};

// Common
//int		ps_r__Supersample			= 1		;
int			ps_r__LightSleepFrames		= 10	;

float		ps_r__Detail_l_ambient		= 0.9f	;
float		ps_r__Detail_l_aniso		= 0.25f	;
float		ps_r__Detail_density		= 0.3f	;
float		ps_r__Detail_rainbow_hemi	= 0.75f	;

float		ps_r__Tree_w_rot			= 10.0f	;
float		ps_r__Tree_w_speed			= 1.00f	;
float		ps_r__Tree_w_amp			= 0.005f;
Fvector		ps_r__Tree_Wave				= {.1f, .01f, .11f};
float		ps_r__Tree_SBC				= 1.5f	;	// scale bias correct

float		ps_r__WallmarkTTL			= 300.f	;
float		ps_r__WallmarkSHIFT			= 0.0001f;
float		ps_r__WallmarkSHIFT_V		= 0.0001f;

float		ps_r__GLOD_ssa_start		= 256.f	;
float		ps_r__GLOD_ssa_end			=  64.f	;
float		ps_r__LOD					=  1.f	;
//. float		ps_r__LOD_Power				=  1.5f	;
float		ps_r__ssaDISCARD			=  3.5f	;					//RO
float		ps_r__ssaDONTSORT			=  32.f	;					//RO
float		ps_r__ssaHZBvsTEX			=  96.f	;					//RO

int			ps_r__tf_Anisotropic		= 4		;

// to remove later
float		ps_r1_pps_u = 0.f;
float		ps_r1_pps_v = 0.f;

float		ps_r2_sun_lumscale			= 1.0f;				// 1.0f
float		ps_r2_dhemi_scale			= 1.f;				// 1.5f
int			ps_r2_dhemi_count			= 5;				// 5
float		ps_r2_lt_smooth				= 1.f;				// 1.f
float		ps_r2_slight_fade			= 1.f;				// 1.f

#ifndef _EDITOR

//-----------------------------------------------------------------------
void		xrRender_initconsole	()
{
	CMD3(CCC_Preset,	"_preset",				&ps_Preset,	qpreset_token	);

// Common
	CMD1(CCC_Screenshot,"screenshot"			);

//	CMD4(CCC_Integer,	"r__supersample",		&ps_r__Supersample,			1,		4		);
	
	CMD4(CCC_Float,		"r__geometry_lod",		&ps_r__LOD,					0.1f,	1.2f		);
//.	CMD4(CCC_Float,		"r__geometry_lod_pow",	&ps_r__LOD_Power,			0,		2		);

//.	CMD4(CCC_Float,		"r__detail_density",	&ps_r__Detail_density,		.05f,	0.99f	);
	CMD4(CCC_Float,		"r__detail_density",	&ps_r__Detail_density,		.2f,	0.6f	);

#ifdef DEBUG
	CMD4(CCC_Float,		"r__detail_l_ambient",	&ps_r__Detail_l_ambient,	.5f,	.95f	);
	CMD4(CCC_Float,		"r__detail_l_aniso",	&ps_r__Detail_l_aniso,		.1f,	.5f		);

	CMD4(CCC_Float,		"r__d_tree_w_amp",		&ps_r__Tree_w_amp,			.001f,	1.f		);
	CMD4(CCC_Float,		"r__d_tree_w_rot",		&ps_r__Tree_w_rot,			.01f,	100.f	);
    CMD4(CCC_Float,		"r__d_tree_w_speed",	&ps_r__Tree_w_speed,		1.0f,	10.f	);

    Fvector	tw_min,tw_max;

	tw_min.set			(EPS,EPS,EPS);
	tw_max.set			(2,2,2);
	CMD4(CCC_Vector3,	"r__d_tree_wave",		&ps_r__Tree_Wave,			tw_min, tw_max	);
#endif // DEBUG

	CMD2(CCC_tf_Aniso,	"r__tf_aniso",			&ps_r__tf_Anisotropic		); //	{1..16}
}

#endif
