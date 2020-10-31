#pragma once

namespace xray {

class Light_R2;

class Light_Package_R2
{
public:
    xr_vector<Light_R2*> v_point;
    xr_vector<Light_R2*> v_spot;
    xr_vector<Light_R2*> v_shadowed;

    void clear();
    void sort();
};

}

