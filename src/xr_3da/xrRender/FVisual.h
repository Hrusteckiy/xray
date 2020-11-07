// FVisual.h: interface for the FVisual class.
//
//////////////////////////////////////////////////////////////////////
#ifndef FVisualH
#define FVisualH
#pragma once

#ifdef _EDITOR
#	include "fbasicvisual.h"
#else
#	include "../fbasicvisual.h"
#endif

class XRRENDER_API Fvisual : public IRender_Visual, public IRender_Mesh
{
public:
	IRender_Mesh*				m_fast			;	
public:
	virtual void				Render			(float LOD) = 0;		// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored ?
	virtual void				Load			(LPCSTR N, IReader *data, u32 dwFlags) = 0;
	virtual void				Copy			(IRender_Visual *pFrom	);
	virtual void				Release			();

	Fvisual();
	virtual ~Fvisual();
};

#endif 
