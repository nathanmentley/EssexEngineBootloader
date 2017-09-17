/* 
 * Essex Engine
 * 
 * Copyright (C) 2017 Nathan Mentley - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the BSD license.
 *
 * You should have received a copy of the BSD license with
 * this file. If not, please visit: https://github.com/nathanmentley/EssexEngine
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>

#include <string>

#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/UniquePointer.h>
#include <EssexEngineCore/WeakPointer.h>

#include <EssexEngineCore/LogDaemon.h>
#include <EssexEngineCore/LogDriver.h>

#include <EssexEngineBootloader/DynamicLoader.h>


#include <execinfo.h>


void handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int main(int argc, char **argv)
{
    signal(SIGSEGV, handler);   // install our handler

    char buffer[512];
    char *answer = getcwd(buffer, sizeof(buffer));
    std::string cwd;
    if (answer)
    {
        cwd = answer;
    }
    
    std::string dataFilename = cwd + "/data.zip";
    
    EssexEngine::UniquePointer<EssexEngine::Context> context = EssexEngine::UniquePointer<EssexEngine::Context>(new EssexEngine::Context());
    context->RegisterDriver<EssexEngine::Core::Logging::ILogDriver>(new EssexEngine::Core::Logging::LogDriver(context.GetWeakPointer()));
    context->RegisterDaemon<EssexEngine::Core::Logging::LogDaemon>(new EssexEngine::Core::Logging::LogDaemon(context.GetWeakPointer()));

    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineConfigDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineSystemDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineWindowDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineJsonDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineFileSystemDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineGfxDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineSfxDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineInputDaemon.dylib");
    registerDynamicDaemon(context.GetWeakPointer(), "libEssexEngineScriptDaemon.dylib");

    registerDynamicDriver(context.GetWeakPointer(), "libEssexEngineGTK3Driver.dylib");
    registerDynamicDriver(context.GetWeakPointer(), "libEssexEngineSDL2Driver.dylib");
    registerDynamicDriver(context.GetWeakPointer(), "libEssexEngineFileSystemDriver.dylib");
    registerDynamicDriver(context.GetWeakPointer(), "libEssexEnginePythonDriver.dylib");
    registerDynamicDriver(context.GetWeakPointer(), "libEssexEngineJsonCppDriver.dylib");

    registerDynamicApp(context.GetWeakPointer(), "libEssexEngineAppEditor.dylib");
    //registerDynamicApp(context.GetWeakPointer(), "libEssexEngineAppServer.dylib");
    //registerDynamicApp(context.GetWeakPointer(), "libEssexEngineAppGame.dylib");

    enterKernel(context.GetWeakPointer(), "libEssexEngineKernel.dylib", dataFilename);
    
	return 0;
}
