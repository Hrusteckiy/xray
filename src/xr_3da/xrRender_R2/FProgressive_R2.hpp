// FProgressive.h: interface for the FProgressive class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "FVisual_R2.hpp"

struct	FSlideWindowItem;

class FProgressive_R2 : public Fvisual_R2
{
protected:
    FSlideWindowItem	nSWI;
    FSlideWindowItem*	xSWI;
    u32					last_lod;
public:
    FProgressive_R2();
    virtual 			~FProgressive_R2();
    virtual void 		Render(float LOD);		// LOD - Level Of Detail  [0.0f - min, 1.0f - max], -1 = Ignored
    virtual void 		Load(const char* N, IReader *data, u32 dwFlags);
    virtual void 		Copy(IRender_Visual *pFrom);
    virtual void 		Release();
private:
    FProgressive_R2(const FProgressive_R2& other);
    void operator=(const FProgressive_R2& other);
};
