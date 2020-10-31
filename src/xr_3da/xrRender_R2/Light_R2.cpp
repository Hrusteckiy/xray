#include "stdafx.h"
#include "Light_R2.hpp"

namespace xray {

Light_R2::Light_R2(void)
    : Light()
{
    ZeroMemory(omnipart, sizeof(omnipart));
    s_spot = NULL;
    s_point = NULL;
    vis.frame2test = 0;	// xffffffff;
    vis.query_id = 0;
    vis.query_order = 0;
    vis.visible = true;
    vis.pending = false;
}

Light_R2::~Light_R2()
{
    for (int f = 0; f<6; f++)
        xr_delete(omnipart[f]);
    set_active(false);

    // remove from Lights_LastFrame
    for (u32 it = 0; it<RImplementation.Lights_LastFrame.size(); it++)
        if (this == RImplementation.Lights_LastFrame[it])
            RImplementation.Lights_LastFrame[it] = 0;
}

void Light_R2::set_texture(LPCSTR name)
{
    if ((0 == name) || (0 == name[0]))
    {
        // default shaders
        s_spot.destroy();
        s_point.destroy();
        return;
    }

#pragma todo				("Only shadowed spot implements projective texture")
    string256				temp;
    s_spot.create(RImplementation.Target->b_accum_spot, strconcat(sizeof(temp), temp, "r2\\accum_spot_", name), name);
    s_spot.create(RImplementation.Target->b_accum_spot, strconcat(sizeof(temp), temp, "r2\\accum_spot_", name), name);
}

void Light_R2::spatial_move()
{
    Light::spatial_move();

    if (flags.bActive) gi_generate();
    svis.invalidate();
}

// Xforms
void Light_R2::xform_calc()
{
    if (Device.dwFrame == m_xform_frame)	return;
    m_xform_frame = Device.dwFrame;

    // build final rotation / translation
    Fvector					L_dir, L_up, L_right;

    // dir
    L_dir.set(direction);
    float l_dir_m = L_dir.magnitude();
    if (_valid(l_dir_m) && l_dir_m>EPS_S)	L_dir.div(l_dir_m);
    else									L_dir.set(0, 0, 1);

    // R&N
    if (right.square_magnitude()>EPS)				{
        // use specified 'up' and 'right', just enshure ortho-normalization
        L_right.set(right);				L_right.normalize();
        L_up.crossproduct(L_dir, L_right);		L_up.normalize();
        L_right.crossproduct(L_up, L_dir);			L_right.normalize();
    }
    else {
        // auto find 'up' and 'right' vectors
        L_up.set(0, 1, 0);				if (_abs(L_up.dotproduct(L_dir))>.99f)	L_up.set(0, 0, 1);
        L_right.crossproduct(L_up, L_dir);			L_right.normalize();
        L_up.crossproduct(L_dir, L_right);		L_up.normalize();
    }

    // matrix
    Fmatrix					mR;
    mR.i = L_right;	mR._14 = 0;
    mR.j = L_up;		mR._24 = 0;
    mR.k = L_dir;	mR._34 = 0;
    mR.c = position;	mR._44 = 1;

    // switch
    switch (flags.type)	{
    case IRender_Light::REFLECTED:
    case IRender_Light::POINT:
    {
        // scale of identity sphere
        float		L_R = range;
        Fmatrix		mScale;		mScale.scale(L_R, L_R, L_R);
        m_xform.mul_43(mR, mScale);
    }
    break;
    case IRender_Light::SPOT:
    {
        // scale to account range and angle
        float		s = 2.f*range*tanf(cone / 2.f);
        Fmatrix		mScale;		mScale.scale(s, s, range);	// make range and radius
        m_xform.mul_43(mR, mScale);
    }
    break;
    case IRender_Light::OMNIPART:
    {
        float		L_R = 2 * range;		// volume is half-radius
        Fmatrix		mScale;		mScale.scale(L_R, L_R, L_R);
        m_xform.mul_43(mR, mScale);
    }
    break;
    default:
        m_xform.identity();
        break;
    }
}

//								+X,				-X,				+Y,				-Y,			+Z,				-Z
static	Fvector cmNorm[6] = { { 0.f, 1.f, 0.f }, { 0.f, 1.f, 0.f }, { 0.f, 0.f, -1.f }, { 0.f, 0.f, 1.f }, { 0.f, 1.f, 0.f }, { 0.f, 1.f, 0.f } };
static	Fvector cmDir[6] = { { 1.f, 0.f, 0.f }, { -1.f, 0.f, 0.f }, { 0.f, 1.f, 0.f }, { 0.f, -1.f, 0.f }, { 0.f, 0.f, 1.f }, { 0.f, 0.f, -1.f } };

void Light_R2::export(xray::Light_Package_R2& package)
{
    if (flags.bShadow)			{
        switch (flags.type)	{
        case IRender_Light::POINT:
        {
            // tough: create/update 6 shadowed lights
            if (0 == omnipart[0])	for (int f = 0; f<6; f++)
                omnipart[f] = xr_new<xray::Light_R2>();
            for (int f = 0; f<6; f++)	{
                xray::Light_R2* L = omnipart[f];
                Fvector				R;
                R.crossproduct(cmNorm[f], cmDir[f]);
                L->set_type(IRender_Light::OMNIPART);
                L->set_shadow(true);
                L->set_position(position);
                L->set_rotation(cmDir[f], R);
                L->set_cone(PI_DIV_2);
                L->set_range(range);
                L->set_color(color);
                L->spatial.sector = spatial.sector;	//. dangerous?
                L->s_spot = s_spot;
                L->s_point = s_point;
                package.v_shadowed.push_back(L);
            }
        }
        break;
        case IRender_Light::SPOT:
            package.v_shadowed.push_back(this);
            break;
        }
    }
    else	{
        switch (flags.type)	{
        case IRender_Light::POINT:		package.v_point.push_back(this);	break;
        case IRender_Light::SPOT:		package.v_spot.push_back(this);	break;
        }
    }
}

}
