#pragma once

#include "../ISpatial.h"

namespace xray {

class XRRENDER_API Light : public IRender_Light, public ISpatial
{
public:
	struct {
		u32			type	:	4;
		u32			bStatic	:	1;
		u32			bActive	:	1;
		u32			bShadow	:	1;
	}				flags;
	Fvector			position	;
	Fvector			direction	;
	Fvector			right		;
	float			range		;
	float			cone		;
	Fcolor			color		;

	vis_data		hom			;
	u32				frame_render;

	virtual void	set_type				(LT type)						{ flags.type = type;		}
	virtual void	set_active				(bool b);
	virtual bool	get_active				()								{ return flags.bActive;		}
	virtual void	set_shadow				(bool b)						
	{ 
		flags.bShadow=b;			
	}
	virtual void	set_position			(const Fvector& P);
	virtual void	set_rotation			(const Fvector& D, const Fvector& R);
	virtual void	set_cone				(float angle);
	virtual void	set_range				(float R);
	virtual void	set_virtual_size		(float R)						{};
	virtual void	set_color				(const Fcolor& C)				{ color.set(C);				}
	virtual void	set_color				(float r, float g, float b)		{ color.set(r,g,b,1);		}
	virtual void	set_texture				(LPCSTR name);

	virtual	void	spatial_move			();
	virtual	Fvector	spatial_sector_point	();

	virtual IRender_Light*	dcast_Light		()	{ return this; }

	vis_data&		get_homdata				();

	float			get_LOD					();

    Light();
    virtual ~Light();
};

}
