#include "stdafx.h"
#pragma hdrstop

#include "Blender_Particle.h"

#define					oBlendCount	6

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBlender_Particle::CBlender_Particle()
{
	description.CLS		= B_PARTICLE;
	description.version	= 0;
	oBlend.Count		= oBlendCount;
	oBlend.IDselected	= 0;
	oAREF.value			= 32;
	oAREF.min			= 0;
	oAREF.max			= 255;
	oClamp.value		= TRUE;
}

CBlender_Particle::~CBlender_Particle()
{
	
}

void	CBlender_Particle::Save	( IWriter& fs	)
{
	IBlender::Save	(fs);

	// Blend mode
	xrP_TOKEN::Item	I;
	xrPWRITE_PROP	(fs,"Blending",	xrPID_TOKEN,     oBlend);
	I.ID = 0; strcpy(I.str,"SET");			fs.w		(&I,sizeof(I));
	I.ID = 1; strcpy(I.str,"BLEND");		fs.w		(&I,sizeof(I));
	I.ID = 2; strcpy(I.str,"ADD");			fs.w		(&I,sizeof(I));
	I.ID = 3; strcpy(I.str,"MUL");			fs.w		(&I,sizeof(I));
	I.ID = 4; strcpy(I.str,"MUL_2X");		fs.w		(&I,sizeof(I));
	I.ID = 5; strcpy(I.str,"ALPHA-ADD");	fs.w		(&I,sizeof(I));
	
	// Params
	xrPWRITE_PROP		(fs,"Texture clamp",xrPID_BOOL,		oClamp);
	xrPWRITE_PROP		(fs,"Alpha ref",	xrPID_INTEGER,	oAREF);
}

void	CBlender_Particle::Load	( IReader& fs, u16 version)
{
	IBlender::Load		(fs,version);

	xrPREAD_PROP		(fs,xrPID_TOKEN,		oBlend);	oBlend.Count =   oBlendCount;
	xrPREAD_PROP		(fs,xrPID_BOOL,			oClamp);
	xrPREAD_PROP		(fs,xrPID_INTEGER,		oAREF);
}
