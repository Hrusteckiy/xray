#pragma once

#include "../xrRender/light.h"
#include "Light_Package_R1.hpp"

namespace xray {

class CLight_DB_R1
{
private:
    xr_vector<ref_light> v_static;
public:
    ref_light sun_original;
    ref_light sun_adapted;
    Light_Package_R1 package;

    void add_light(Light* L);

    void Load(IReader* fs);
    void Unload();

    Light* Create();
    void Update();

    CLight_DB_R1();
    ~CLight_DB_R1();
};

}
