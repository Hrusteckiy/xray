#pragma once

#include "../xrRender/FTreeVisual.h"

class FTreeVisual_R1 : public FTreeVisual
{
public:
    virtual void Render(float LOD) override;							// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored
};

class FTreeVisual_ST : public FTreeVisual_R1
{
    typedef FTreeVisual_R1 inherited;
public:
    FTreeVisual_ST(void);
    virtual			~FTreeVisual_ST(void);

    virtual void	Render(float LOD);									// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored
    virtual void	Load(LPCSTR N, IReader *data, u32 dwFlags);
    virtual void	Copy(IRender_Visual *pFrom);
    virtual void	Release();
private:
    FTreeVisual_ST(const FTreeVisual_ST& other);
    void	operator=			(const FTreeVisual_ST& other);
};

class FTreeVisual_PM : public FTreeVisual_R1
{
    typedef FTreeVisual_R1 inherited;
private:
    FSlideWindowItem*	pSWI;
    u32					last_lod;
public:
    FTreeVisual_PM(void);
    virtual			~FTreeVisual_PM(void);

    virtual void	Render(float LOD);									// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored
    virtual void	Load(LPCSTR N, IReader *data, u32 dwFlags);
    virtual void	Copy(IRender_Visual *pFrom);
    virtual void	Release();
private:
    FTreeVisual_PM(const FTreeVisual_PM& other);
    void	operator=			(const FTreeVisual_PM& other);
};