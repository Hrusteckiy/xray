#pragma once

// refs
struct	FSlideWindowItem;

class XRRENDER_API FTreeVisual : public IRender_Visual, public IRender_Mesh
{
protected:
	struct	_5color
	{
		Fvector					rgb;		// - all static lighting
		float					hemi;		// - hemisphere
		float					sun;		// - sun
	};
protected:
	_5color						c_scale;
	_5color						c_bias;
	Fmatrix						xform;

    shared_str m_xform;
    shared_str m_xform_v;
    shared_str c_consts;
    shared_str c_wave;
    shared_str c_wind;
    shared_str c_c_bias;
    shared_str c_c_scale;
    shared_str c_c_sun;

public:
	virtual void Render			(float LOD) = 0;									// LOD - Level Of Detail  [0.0f - min, 1.0f - max], Ignored
	virtual void Load			(LPCSTR N, IReader *data, u32 dwFlags);
	virtual void Copy			(IRender_Visual *pFrom	);
	virtual void Release		();

	FTreeVisual(void);
	virtual ~FTreeVisual(void);
};

struct XRRENDER_API FTreeVisual_setup
{
    u32			dwFrame;
    float		scale;
    Fvector4	wave;
    Fvector4	wind;

    FTreeVisual_setup() { dwFrame = 0; }

    void calculate();
};

const int		FTreeVisual_tile	= 16;
const int		FTreeVisual_quant	= 32768/FTreeVisual_tile;
