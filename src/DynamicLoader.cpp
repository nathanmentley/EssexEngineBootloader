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

#include <EssexEngineBootloader/DynamicLoader.h>

typedef void (*simple_demo_function)(EssexEngine::WeakPointer<EssexEngine::Context>);
void registerDynamicDriver(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name) {
    simple_demo_function demo_function;
    void* library = dlopen(name.c_str(), RTLD_GLOBAL | RTLD_NOW);

    if (!library) {
        fprintf(stderr, "Couldn't open %s: %s\n", name.c_str(), dlerror());
    }

    dlerror();
    demo_function = (simple_demo_function)dlsym(library, "driver_init");
    char* error;
    if ((error = dlerror())) {
        fprintf(stderr, "Couldn't find driver entry: %s\n", error);
    }

    (*demo_function)(context);
}

typedef EssexEngine::Core::IDaemon* (*loadDynamicDaemonFunction)(EssexEngine::WeakPointer<EssexEngine::Context>);
EssexEngine::WeakPointer<EssexEngine::Core::IDaemon> loadDynamicDaemon(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name) {
    loadDynamicDaemonFunction daemonLoadLogic;
    void* library = dlopen(name.c_str(), RTLD_GLOBAL | RTLD_NOW);

    if (!library) {
        fprintf(stderr, "Couldn't open %s: %s\n", name.c_str(), dlerror());
    }

    dlerror();
    daemonLoadLogic = (loadDynamicDaemonFunction)dlsym(library, "daemon_init");
    char* error;
    if ((error = dlerror())) {
        fprintf(stderr, "Couldn't find daemon entry for %s: %s\n", name.c_str(), error);
    }

    EssexEngine::Core::IDaemon* daemon = (*daemonLoadLogic)(context);
    
    return EssexEngine::WeakPointer<EssexEngine::Core::IDaemon>(daemon);
}

typedef EssexEngine::Core::IApp* (*loadDynamicAppFunction)(EssexEngine::WeakPointer<EssexEngine::Context>);
EssexEngine::WeakPointer<EssexEngine::Core::IApp> loadDynamicApp(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name) {
    loadDynamicAppFunction appLoadLogic;
    void* library = dlopen(name.c_str(), RTLD_GLOBAL | RTLD_NOW);

    if (!library) {
        fprintf(stderr, "Couldn't open %s: %s\n", name.c_str(), dlerror());
    }

    dlerror();
    appLoadLogic = (loadDynamicAppFunction)dlsym(library, "app_init");
    char* error;
    if ((error = dlerror())) {
        fprintf(stderr, "Couldn't find app entry: %s\n", error);
    }

    EssexEngine::Core::IApp* app = (*appLoadLogic)(context);

    return EssexEngine::WeakPointer<EssexEngine::Core::IApp>(app);
}

typedef EssexEngine::Core::IKernel* (*kernel_entry_function)(EssexEngine::WeakPointer<EssexEngine::Context>, std::string dataFile);
EssexEngine::WeakPointer<EssexEngine::Core::IKernel> loadKernel(EssexEngine::WeakPointer<EssexEngine::Context> context, std::string name, std::string dataFile) {
    kernel_entry_function kernel_function;
    void* library = dlopen(name.c_str(), RTLD_GLOBAL | RTLD_NOW);

    if (!library) {
        fprintf(stderr, "Couldn't open %s: %s\n", name.c_str(), dlerror());
    }

    dlerror();
    kernel_function = (kernel_entry_function)dlsym(library, "kernel_init");
    char* error;
    if ((error = dlerror())) {
        fprintf(stderr, "Couldn't find kernel entry: %s\n", error);
    }

    EssexEngine::Core::IKernel* kernel = (*kernel_function)(context, dataFile);

    return EssexEngine::WeakPointer<EssexEngine::Core::IKernel>(kernel);
}
