// BlenderDefault.cpp: implementation of the CBlender_BmmD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#pragma hdrstop

#include "blender_BmmD.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlender_BmmD::CBlender_BmmD	()
{
	description.CLS		= B_BmmD;
	strcpy				(oT2_Name,	"$null");
	strcpy				(oT2_xform,	"$null");
	description.version	= 3;
	strcpy				(oR_Name,	"detail\\detail_grnd_grass");	//"$null");
	strcpy				(oG_Name,	"detail\\detail_grnd_asphalt");	//"$null");
	strcpy				(oB_Name,	"detail\\detail_grnd_earth");	//"$null");
	strcpy				(oA_Name,	"detail\\detail_grnd_yantar");	//"$null");
}

CBlender_BmmD::~CBlender_BmmD	()
{
}

void	CBlender_BmmD::Save		(IWriter& fs )
{
	IBlender::Save	(fs);
	xrPWRITE_MARKER	(fs,"Detail map");
	xrPWRITE_PROP	(fs,"Name",				xrPID_TEXTURE,	oT2_Name);
	xrPWRITE_PROP	(fs,"Transform",		xrPID_MATRIX,	oT2_xform);
	xrPWRITE_PROP	(fs,"R2-R",				xrPID_TEXTURE,	oR_Name);
	xrPWRITE_PROP	(fs,"R2-G",				xrPID_TEXTURE,	oG_Name);
	xrPWRITE_PROP	(fs,"R2-B",				xrPID_TEXTURE,	oB_Name);
	xrPWRITE_PROP	(fs,"R2-A",				xrPID_TEXTURE,	oA_Name);
}

void	CBlender_BmmD::Load		(IReader& fs, u16 version )
{
	IBlender::Load	(fs,version);
	if (version<3)	{
		xrPREAD_MARKER	(fs);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oT2_Name);
		xrPREAD_PROP	(fs,xrPID_MATRIX,	oT2_xform);
	} else {
		xrPREAD_MARKER	(fs);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oT2_Name);
		xrPREAD_PROP	(fs,xrPID_MATRIX,	oT2_xform);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oR_Name);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oG_Name);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oB_Name);
		xrPREAD_PROP	(fs,xrPID_TEXTURE,	oA_Name);
	}
}
