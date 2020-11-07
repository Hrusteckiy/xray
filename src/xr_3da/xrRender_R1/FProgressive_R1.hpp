// FProgressive.h: interface for the FProgressive class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "FVisual_R1.hpp"

struct	FSlideWindowItem;

class FProgressive_R1 : public Fvisual_R1
{
protected:
    FSlideWindowItem	nSWI;
    FSlideWindowItem*	xSWI;
    u32					last_lod;
public:
    FProgressive_R1();
    virtual 			~FProgressive_R1();
    virtual void 		Render(float LOD);		// LOD - Level Of Detail  [0.0f - min, 1.0f - max], -1 = Ignored
    virtual void 		Load(const char* N, IReader *data, u32 dwFlags);
    virtual void 		Copy(IRender_Visual *pFrom);
    virtual void 		Release();
private:
    FProgressive_R1(const FProgressive_R1& other);
    void operator=(const FProgressive_R1& other);
};
