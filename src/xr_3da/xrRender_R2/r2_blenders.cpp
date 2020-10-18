#include "stdafx.h"

#include "uber_deffer.h"

#include "Blender_BmmD_R2.hpp"
#include "blender_deffer_flat.h"
#include "blender_deffer_model.h"
#include "blender_deffer_aref.h"
#include "..\xrRender\blender_screen_set.h"
#include "..\xrRender\blender_editor_wire.h"
#include "..\xrRender\blender_editor_selection.h"
#include "Blender_tree_R2.hpp"
#include "Blender_detail_still_R2.hpp"
#include "Blender_Particle_R2.hpp"
#include "Blender_Model_EbB_R2.hpp"
#include "Blender_Lm(EbB)_R2.hpp"

IBlender*	CRender::blender_create	(CLASS_ID cls)
{	
	switch (cls)
	{
	case B_DEFAULT:			return xr_new<CBlender_deffer_flat>		();		
	case B_DEFAULT_AREF:	return xr_new<CBlender_deffer_aref>		(true);
	case B_VERT:			return xr_new<CBlender_deffer_flat>		();
	case B_VERT_AREF:		return xr_new<CBlender_deffer_aref>		(false);
	case B_SCREEN_SET:		return xr_new<CBlender_Screen_SET>		();	
	case B_SCREEN_GRAY:		return 0;
	case B_EDITOR_WIRE:		return xr_new<CBlender_Editor_Wire>		();	
	case B_EDITOR_SEL:		return xr_new<CBlender_Editor_Selection>();
	case B_LIGHT:			return 0;
	case B_LmBmmD:			return xr_new<CBlender_BmmD_R2>			();	
	case B_LaEmB:			return 0;
	case B_LmEbB:			return xr_new<CBlender_LmEbB_R2>		();
	case B_B:				return 0;
	case B_BmmD:			return xr_new<CBlender_BmmD_R2>			();	
	case B_SHADOW_TEX:		return 0;
	case B_SHADOW_WORLD:	return 0;
	case B_BLUR:			return 0;
	case B_MODEL:			return xr_new<CBlender_deffer_model>	();		
	case B_MODEL_EbB:		return xr_new<CBlender_Model_EbB_R2>	();	
	case B_DETAIL:			return xr_new<CBlender_Detail_Still_R2>	();	
	case B_TREE:			return xr_new<CBlender_Tree_R2>			();	
	case B_PARTICLE:		return xr_new<CBlender_Particle_R2>		();
	}
	return 0;
}

void		CRender::blender_destroy(IBlender* &B)
{
	xr_delete(B);
}
