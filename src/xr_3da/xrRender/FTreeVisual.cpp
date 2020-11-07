#include "stdafx.h"
#pragma hdrstop

#include "..\igame_persistent.h"
#include "..\igame_level.h"
#include "..\environment.h"
#include "..\fmesh.h"

#include "ftreevisual.h"

FTreeVisual::FTreeVisual	(void)
{
}

FTreeVisual::~FTreeVisual	(void)
{
}

void FTreeVisual::Release	()
{
	IRender_Visual::Release	();
}

void FTreeVisual::Load		(const char* N, IReader *data, u32 dwFlags)
{
	IRender_Visual::Load		(N,data,dwFlags);

	D3DVERTEXELEMENT9*	vFormat	= NULL;

	// read vertices
	R_ASSERT			(data->find_chunk(OGF_GCONTAINER));
	{
		// verts
		u32 ID				= data->r_u32				();
		vBase				= data->r_u32				();
		vCount				= data->r_u32				();
        vFormat = xray::renderBase.getVertexBufferFormat(ID);
		
		VERIFY				(NULL==p_rm_Vertices);

        p_rm_Vertices = xray::renderBase.getVertexBuffer(ID);
		p_rm_Vertices->AddRef();

		// indices
		dwPrimitives		= 0;
		ID					= data->r_u32				();
		iBase				= data->r_u32				();
		iCount				= data->r_u32				();
		dwPrimitives		= iCount/3;
		
		VERIFY				(NULL==p_rm_Indices);
        p_rm_Indices = xray::renderBase.getIndexBuffer(ID);
		p_rm_Indices->AddRef	();
	}

	// load tree-def
	R_ASSERT			(data->find_chunk(OGF_TREEDEF2));
	{
		data->r			(&xform,	sizeof(xform));
		data->r			(&c_scale,	sizeof(c_scale));	c_scale.rgb.mul	(.5f);	c_scale.hemi*=.5f;	c_scale.sun	*=.5f;
		data->r			(&c_bias,	sizeof(c_bias));	c_bias.rgb.mul	(.5f);	c_bias.hemi	*=.5f;	c_bias.sun	*=.5f;
		//Msg				("hemi[%f / %f], sun[%f / %f]",c_scale.hemi,c_bias.hemi,c_scale.sun,c_bias.sun);
	}

	// Geom
	rm_geom.create			(vFormat,p_rm_Vertices,p_rm_Indices);

	// Get constants
	m_xform				= "m_xform";
	m_xform_v			= "m_xform_v";
	c_consts			= "consts";
	c_wave				= "wave";
	c_wind				= "wind";
	c_c_bias			= "c_bias";
	c_c_scale			= "c_scale";
	c_c_sun				= "c_sun";
}

#define PCOPY(a)	a = pFrom->a
void	FTreeVisual::Copy	(IRender_Visual *pSrc)
{
	IRender_Visual::Copy	(pSrc);

	FTreeVisual	*pFrom		= dynamic_cast<FTreeVisual*> (pSrc);

	PCOPY(rm_geom);

	PCOPY(p_rm_Vertices);	if (p_rm_Vertices) p_rm_Vertices->AddRef();

	PCOPY(vBase);
	PCOPY(vCount);

	PCOPY(p_rm_Indices);	if (p_rm_Indices) p_rm_Indices->AddRef();

	PCOPY(iBase);
	PCOPY(iCount);
	PCOPY(dwPrimitives);

	PCOPY(xform);
	PCOPY(c_scale);
	PCOPY(c_bias);
}

void FTreeVisual_setup::calculate()
{
    dwFrame = Device.dwFrame;

    // Calc wind-vector3, scale
    float tm_rot = PI_MUL_2*Device.fTimeGlobal / ps_r__Tree_w_rot;
    wind.set(_sin(tm_rot), 0, _cos(tm_rot), 0);	wind.normalize();
    wind.mul(ps_r__Tree_w_amp); // dir1*amplitude
    scale = 1.f / float(FTreeVisual_quant);

    // setup constants
    wave.set(ps_r__Tree_Wave.x, ps_r__Tree_Wave.y, ps_r__Tree_Wave.z, Device.fTimeGlobal*ps_r__Tree_w_speed); // wave
    wave.div(PI_MUL_2);
}
