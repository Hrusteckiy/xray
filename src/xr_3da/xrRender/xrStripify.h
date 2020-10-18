#pragma once

void XRRENDER_API xrStripify (xr_vector<u16> &indices, xr_vector<u16> &perturb, int iCacheSize, int iMinStripLength);
int XRRENDER_API xrSimulate(xr_vector<u16> &indices, int iCacheSize);
