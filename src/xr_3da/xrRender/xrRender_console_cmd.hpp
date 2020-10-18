#pragma once

#include "../XR_IOConsole.h"
#include "../xr_ioc_cmd.h"

class XRRENDER_API CCC_tf_Aniso : public CCC_Integer
{
public:
    void apply();
    CCC_tf_Aniso(LPCSTR N, int*	v);
    virtual void Execute(LPCSTR args);
    virtual void Status(TStatus& S);
};

class XRRENDER_API CCC_tf_MipBias : public CCC_Float
{
public:
    void apply();
    CCC_tf_MipBias(LPCSTR N, float*	v);
    virtual void Execute(LPCSTR args);
    virtual void Status(TStatus& S);
};

class XRRENDER_API CCC_Screenshot : public IConsole_Command
{
public:
    CCC_Screenshot(LPCSTR N);
    virtual void Execute(LPCSTR args);
};

class XRRENDER_API CCC_Preset : public CCC_Token
{
public:
    CCC_Preset(LPCSTR N, u32* V, xr_token* T);
    virtual void Execute(LPCSTR args);
};