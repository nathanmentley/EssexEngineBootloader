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

void registerDynamicDaemon(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
void registerDynamicDriver(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
void registerDynamicApp(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name);
void enterKernel(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name, std::string dataFile);
