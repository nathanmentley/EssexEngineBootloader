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

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <algorithm>
#include <unistd.h>

#include <string>

#include <EssexEngineCore/EssexEnvironment.h>
#include <EssexEngineCore/Context.h>
#include <EssexEngineCore/WeakPointer.h>
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
    char* answer = getcwd(buffer, sizeof(buffer));
    std::string cwd;
    if (answer)
    {
        cwd = answer;
    }
    
    std::string dataFilename = cwd + "/data.zip";
    
    EssexEngine::WeakPointer<EssexEngine::Context> context = EssexEngine::WeakPointer<EssexEngine::Context>(new EssexEngine::Context());
    context->RegisterDriver<EssexEngine::Core::Logging::ILogDriver>(new EssexEngine::Core::Logging::LogDriver(context));
    context->RegisterDaemon<EssexEngine::Core::Logging::LogDaemon>(new EssexEngine::Core::Logging::LogDaemon(context));

    loadDynamicDaemon(context, "libEssexEngineConfigDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineSystemDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineWindowDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineJsonDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineFileSystemDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineGfxDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineSfxDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineInputDaemon.dylib");
    loadDynamicDaemon(context, "libEssexEngineScriptDaemon.dylib");

    registerDynamicDriver(context, "libEssexEngineGTK3Driver.dylib");
    registerDynamicDriver(context, "libEssexEngineMacOSDriver.dylib");
    registerDynamicDriver(context, "libEssexEngineSDL2Driver.dylib");
    registerDynamicDriver(context, "libEssexEngineFileSystemDriver.dylib");
    registerDynamicDriver(context, "libEssexEnginePythonDriver.dylib");
    registerDynamicDriver(context, "libEssexEngineJsonCppDriver.dylib");

    EssexEngine::WeakPointer<EssexEngine::Core::IKernel> kernel = loadKernel(context, "libEssexEngineKernel.dylib", dataFilename);
    
    //registerDynamicApp(context, "libEssexEngineAppEditor.dylib");
    //registerDynamicApp(context, "libEssexEngineAppServer.dylib");
    //registerDynamicApp(context, "libEssexEngineAppShell.dylib");
    EssexEngine::WeakPointer<EssexEngine::Core::IApp> app = loadDynamicApp(context, "libEssexEngineAppGame.dylib");

    kernel->RunApp(app);

    kernel->Start();
    
    return 0;
}
