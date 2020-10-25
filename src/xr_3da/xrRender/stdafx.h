// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#pragma warning(disable:4995)
#include "../stdafx.h"
#pragma warning(disable:4995)
#include <d3dx9.h>
#pragma warning(default:4995)
#pragma warning(disable:4714)
#pragma warning( 4 : 4018 )
#pragma warning( 4 : 4244 )

#ifdef XRRENDER_EXPORTS
#define XRRENDER_API __declspec(dllexport)
#else
#define XRRENDER_API __declspec(dllimport)
#endif

#include "../ResourceManager.h"
#include "../vis_common.h"
#include "../Render.h"
#include "../IGame_Level.h"
#include "../blenders/Blender.h"
#include "../blenders/Blender_CLSID.h"
#include "../psystem.h"
#include "xrRender_console.h"
#include "RenderBase.hpp"