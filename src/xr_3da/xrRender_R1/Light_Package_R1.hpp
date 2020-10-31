#pragma once

#include "../xrRender/light.h"

namespace xray {

class Light_Package_R1
{
public:
    xr_vector<Light*> v_point;
    xr_vector<Light*> v_spot;
    xr_vector<Light*> v_shadowed;

    void clear();
};

}
