/* 
 * Essex Engine
 * 
 * Copyright (C) 2018 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */
#pragma once

#include <dlfcn.h>
#include <string>

#include <EssexEngineCore/WeakPointer.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/IApp.h>
#include <EssexEngineCore/IKernel.h>

void registerDynamicDaemon(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
void registerDynamicDriver(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
EssexEngine::WeakPointer<EssexEngine::Core::IApp> loadDynamicApp(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
EssexEngine::WeakPointer<EssexEngine::Core::IKernel> loadKernel(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name, std::string dataFile);
