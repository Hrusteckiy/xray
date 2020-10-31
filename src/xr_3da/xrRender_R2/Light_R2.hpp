#pragma once

#include "../xrRender/light.h"
#include "Light_Package_R2.hpp"
#include "light_smapvis.h"
#include "light_GI.h"

namespace xray {

class Light_R2 : public Light
{
public:
    Light_R2* omnipart[6];
    xr_vector<light_indirect>	indirect;
    u32							indirect_photons;

    smapvis			svis;		// used for 6-cubemap faces

    ref_shader		s_spot;
    ref_shader		s_point;

    u32				m_xform_frame;
    Fmatrix			m_xform;

    struct _vis		{
        u32			frame2test;		// frame the test is sheduled to
        u32			query_id;		// ID of occlusion query
        u32			query_order;	// order of occlusion query
        bool		visible;		// visible/invisible
        bool		pending;		// test is still pending
        u16			smap_ID;
    }				vis;

    union			_xform	{
        struct		_D		{
            Fmatrix						combine;
            s32							minX, maxX;
            s32							minY, maxY;
            BOOL						transluent;
        }	D;
        struct		_P		{
            Fmatrix						world;
            Fmatrix						view;
            Fmatrix						project;
            Fmatrix						combine;
        }	P;
        struct		_S		{
            Fmatrix						view;
            Fmatrix						project;
            Fmatrix						combine;
            u32							size;
            u32							posX;
            u32							posY;
            BOOL						transluent;
        }	S;
    }	X;

    virtual void	set_texture(LPCSTR name);

    virtual	void	spatial_move();

    void			gi_generate();
    void			xform_calc();
    void			vis_prepare();
    void			vis_update();
    void			export(xray::Light_Package_R2& dest);

    Light_R2();
    virtual ~Light_R2();
};

}
