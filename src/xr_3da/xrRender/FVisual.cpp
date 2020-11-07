// FVisual.cpp: implementation of the FVisual class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma hdrstop

#pragma warning(disable:4995)
#include <d3dx9.h>
#pragma warning(default:4995)

#include "../fmesh.h"
#include "fvisual.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Fvisual::Fvisual()  : IRender_Visual()
{
	m_fast	=	0;
}

Fvisual::~Fvisual()
{
	xr_delete	(m_fast);
}

void Fvisual::Release	()
{
	IRender_Visual::Release	();
}

#define PCOPY(a)	a = pFrom->a
void	Fvisual::Copy			(IRender_Visual *pSrc)
{
	IRender_Visual::Copy		(pSrc);

	Fvisual	*pFrom				= dynamic_cast<Fvisual*> (pSrc);

	PCOPY	(rm_geom);

	PCOPY	(p_rm_Vertices); if (p_rm_Vertices) p_rm_Vertices->AddRef();
	PCOPY	(vBase);
	PCOPY	(vCount);

	PCOPY	(p_rm_Indices); if (p_rm_Indices) p_rm_Indices->AddRef();
	PCOPY	(iBase);
	PCOPY	(iCount);
	PCOPY	(dwPrimitives);

	PCOPY	(m_fast);
}
