#include "stdafx.h"
#pragma hdrstop

#include "ModelPool_R1.hpp"

#include "../SkeletonAnimated.h"
#include "../xrRender/FLOD.h"
#include "FProgressive_R1.hpp"
#include "FSkinned_R1.hpp"
#include "FTreeVisual_R1.hpp"
#include "FVisual_R1.hpp"

IRender_Visual*	CModelPool_R1::Instance_Create(u32 type)
{
    IRender_Visual *V = NULL;

    // Check types
    switch (type) {
    case MT_NORMAL:				// our base visual
        V = xr_new<Fvisual_R1>();
        break;
    case MT_HIERRARHY:
        V = xr_new<FHierrarhyVisual>();
        break;
    case MT_PROGRESSIVE:		// dynamic-resolution visual
        V = xr_new<FProgressive_R1>();
        break;
    case MT_SKELETON_ANIM:
        V = xr_new<CKinematicsAnimated>();
        break;
    case MT_SKELETON_RIGID:
        V = xr_new<CKinematics>();
        break;
    case MT_SKELETON_GEOMDEF_PM:
        V = xr_new<CSkeletonX_PM>();
        break;
    case MT_SKELETON_GEOMDEF_ST:
        V = xr_new<CSkeletonX_ST>();
        break;
    case MT_PARTICLE_EFFECT:
        V = xr_new<PS::CParticleEffect>();
        break;
    case MT_PARTICLE_GROUP:
        V = xr_new<PS::CParticleGroup>();
        break;
#ifndef _EDITOR
    case MT_LOD:
        V = xr_new<FLOD>();
        break;
    case MT_TREE_ST:
        V = xr_new<FTreeVisual_ST>();
        break;
    case MT_TREE_PM:
        V = xr_new<FTreeVisual_PM>();
        break;
#endif
    default:
        FATAL("Unknown visual type");
        break;
    }
    R_ASSERT(V);
    V->Type = type;
    return		V;
}