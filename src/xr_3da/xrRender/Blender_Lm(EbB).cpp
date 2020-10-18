// BlenderDefault.cpp: implementation of the CBlender_LmEbB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma hdrstop

#include "blender_Lm(EbB).h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlender_LmEbB::CBlender_LmEbB	()
{
	description.CLS		= B_LmEbB;
	description.version	= 0x1;
	strcpy				(oT2_Name,	"$null");
	strcpy				(oT2_xform,	"$null");
	oBlend.value		= FALSE;
}

CBlender_LmEbB::~CBlender_LmEbB	()
{
}

void	CBlender_LmEbB::Save(	IWriter& fs )
{
	description.version	= 0x1;
	IBlender::Save		(fs);
	xrPWRITE_MARKER		(fs,"Environment map");
	xrPWRITE_PROP		(fs,"Name",				xrPID_TEXTURE,	oT2_Name);
	xrPWRITE_PROP		(fs,"Transform",		xrPID_MATRIX,	oT2_xform);
	xrPWRITE_PROP		(fs,"Alpha-Blend",		xrPID_BOOL,		oBlend);
}

void	CBlender_LmEbB::Load(	IReader& fs, u16 version )
{
	IBlender::Load	(fs,version);
	xrPREAD_MARKER	(fs);
	xrPREAD_PROP	(fs,xrPID_TEXTURE,	oT2_Name);
	xrPREAD_PROP	(fs,xrPID_MATRIX,	oT2_xform);
	if (version>=0x1)	{
		xrPREAD_PROP	(fs,xrPID_BOOL,	oBlend);
	}
}
