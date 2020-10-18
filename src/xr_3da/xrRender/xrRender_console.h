#ifndef xrRender_consoleH
#define xrRender_consoleH
#pragma once

// Common
extern XRRENDER_API	int			ps_r__Supersample;
extern XRRENDER_API	int			ps_r__LightSleepFrames;

extern XRRENDER_API	float		ps_r__Detail_l_ambient;
extern XRRENDER_API	float		ps_r__Detail_l_aniso;
extern XRRENDER_API	float		ps_r__Detail_density;

extern XRRENDER_API	float		ps_r__Tree_w_rot;
extern XRRENDER_API	float		ps_r__Tree_w_speed;
extern XRRENDER_API	float		ps_r__Tree_w_amp;
extern XRRENDER_API	float		ps_r__Tree_SBC;		// scale bias correct
extern XRRENDER_API	Fvector		ps_r__Tree_Wave;

extern XRRENDER_API	float		ps_r__WallmarkTTL;
extern XRRENDER_API	float		ps_r__WallmarkSHIFT;
extern XRRENDER_API	float		ps_r__WallmarkSHIFT_V;

extern XRRENDER_API	float		ps_r__GLOD_ssa_start;
extern XRRENDER_API	float		ps_r__GLOD_ssa_end;
extern XRRENDER_API	float		ps_r__LOD;
//.extern XRRENDER_API	float		ps_r__LOD_Power		;
extern XRRENDER_API	float		ps_r__ssaDISCARD;
extern XRRENDER_API	float		ps_r__ssaDONTSORT;
extern XRRENDER_API	float		ps_r__ssaHZBvsTEX;
extern XRRENDER_API	int			ps_r__tf_Anisotropic;

// to remove later
extern XRRENDER_API	float		ps_r1_pps_u;
extern XRRENDER_API	float		ps_r1_pps_v;

extern XRRENDER_API float			ps_r2_sun_lumscale;			// 0.5f
extern XRRENDER_API float			ps_r2_dhemi_scale;			// 1.5f
extern XRRENDER_API int			ps_r2_dhemi_count;			// 5
extern XRRENDER_API float			ps_r2_lt_smooth;
extern XRRENDER_API float			ps_r2_slight_fade;			// 1.f
// to remove later

extern XRRENDER_API void xrRender_initconsole();

#endif // xrRender_consoleH
