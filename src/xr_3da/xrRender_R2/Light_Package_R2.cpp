#include "stdafx.h"
#include "Light_Package_R2.hpp"
#include "Light_R2.hpp"

namespace xray {

void Light_Package_R2::clear()
{
	v_point.clear		();
	v_spot.clear		();
	v_shadowed.clear	();
}

IC bool pred_light_cmp(Light_R2* _1, Light_R2* _2)
{
    if (_1->vis.pending)
    {
        if (_2->vis.pending)	return	_1->vis.query_order > _2->vis.query_order;	// q-order
        else					return	false;										// _2 should be first
    }
    else {
        if (_2->vis.pending)	return	true;										// _1 should be first 
        else					return	_1->range > _2->range;						// sort by range
    }
}

void Light_Package_R2::sort()
{
    // resort lights (pending -> at the end), maintain stable order
    std::stable_sort(v_point.begin(), v_point.end(), pred_light_cmp);
    std::stable_sort(v_spot.begin(), v_spot.end(), pred_light_cmp);
    std::stable_sort(v_shadowed.begin(), v_shadowed.end(), pred_light_cmp);
}

}