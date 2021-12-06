
//----------------------------------------------------------------------------//
//																			  //
//					Rain Forest Game Engine                                   //
//                                                                            //
//----------------------------------------------------------------------------//
//                                                                            //
// File : RainForest.h                                                        //
//                                                                            //
// Desc : Common header that includes access to commonly needed components    //
//        of the core framework.                                              //
//                                                                            //
//----------------------------------------------------------------------------//
//                  Rodrigo dos Reis (reiso) 2021                             //
//                                                                            //
// 436f6e736167726520616f2053656e686f72207475646f206f2071756520766f6365206661 //
// 7a2c2065206f73207365757320706c616e6f7320736572616f2062656d2d73756365646964 //
// 6f732e0d0a4162656e636f612053656e686f722e20416d656d                         //
//----------------------------------------------------------------------------//

#pragma once
#ifndef _RAINFORESTENGINE_H_ 
#define _RAINFORESTENGINE_H_

// Core
#include <RFGEAPI.h>

// Renderer
#include "Renderer/rfRenderer.h"
#include "Renderer/rfRenderCommand.h"
#include "Renderer/Platform/Directx9Renderer.h"

// Application
#include "System/rfApplication.h"

// Engine Configuration
#include "System/rfConfig.h"

// Game Logic related classes
#include "Game/Elements/rfGame.h"

// World Game
#include "Game/rfGameWorld.h"

// Game Engine UI
#include "UI/imgui.h"
#include "UI/imgui_impl_dx9.h"
#include "UI/imgui_impl_win32.h"

#endif _RAINFORESTENGINE_H_