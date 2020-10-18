#include "stdafx.h"

#include "xrRender_console_cmd.hpp"

void CCC_tf_Aniso::apply()
{
    if (0 == HW.pDevice)	return;
    int	val = *value;	clamp(val, 1, 16);
    for (u32 i = 0; i<HW.Caps.raster.dwStages; i++)
        CHK_DX(HW.pDevice->SetSamplerState(i, D3DSAMP_MAXANISOTROPY, val));
}

CCC_tf_Aniso::CCC_tf_Aniso(LPCSTR N, int*	v)
    : CCC_Integer(N, v, 1, 16)
{ };
void CCC_tf_Aniso::Execute(LPCSTR args)
{
    CCC_Integer::Execute(args);
    apply();
}
void CCC_tf_Aniso::Status(TStatus& S)
{
    CCC_Integer::Status(S);
    apply();
}

void CCC_tf_MipBias::apply()
{
    if (0 == HW.pDevice)	return;
    for (u32 i = 0; i<HW.Caps.raster.dwStages; i++)
        CHK_DX(HW.pDevice->SetSamplerState(i, D3DSAMP_MIPMAPLODBIAS, *((LPDWORD)value)));
}

CCC_tf_MipBias::CCC_tf_MipBias(LPCSTR N, float*	v)
    : CCC_Float(N, v, -0.5f, +0.5f)
{ };

void CCC_tf_MipBias::Execute(LPCSTR args)
{
    CCC_Float::Execute(args);
    apply();
}

void CCC_tf_MipBias::Status(TStatus& S)
{
    CCC_Float::Status(S);
    apply();
}

CCC_Screenshot::CCC_Screenshot(LPCSTR N)
    : IConsole_Command(N) 
{ };

void CCC_Screenshot::Execute(LPCSTR args)
{
    string_path	name;	name[0] = 0;
    sscanf(args, "%s", name);
    LPCSTR		image = xr_strlen(name) ? name : 0;
    ::Render->Screenshot(IRender_interface::SM_NORMAL, image);
}

CCC_Preset::CCC_Preset(LPCSTR N, u32* V, xr_token* T)
    : CCC_Token(N, V, T)
{};

void CCC_Preset::Execute(LPCSTR args)
{
    CCC_Token::Execute(args);
    string_path		_cfg;
    string_path		cmd;

    switch (*value)	{
    case 0:		strcpy(_cfg, "rspec_minimum.ltx");	break;
    case 1:		strcpy(_cfg, "rspec_low.ltx");		break;
    case 2:		strcpy(_cfg, "rspec_default.ltx");	break;
    case 3:		strcpy(_cfg, "rspec_high.ltx");		break;
    case 4:		strcpy(_cfg, "rspec_extreme.ltx");	break;
    }
    FS.update_path(_cfg, "$game_config$", _cfg);
    strconcat(sizeof(cmd), cmd, "cfg_load", " ", _cfg);
    Console->Execute(cmd);
}