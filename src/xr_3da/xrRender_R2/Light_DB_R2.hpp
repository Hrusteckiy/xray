#pragma once

#include "Light_R2.hpp"
#include "Light_Package_R2.hpp"

namespace xray {

class CLight_DB_R2
{
private:
    xr_vector<ref_light> v_static;
public:
    ref_light sun_original;
    ref_light sun_adapted;
    Light_Package_R2 package;

    void add_light(Light_R2* L);

    void Load(IReader* fs);
    void Unload();

    Light_R2* Create();
    void Update();

    CLight_DB_R2();
    ~CLight_DB_R2();
};

}
