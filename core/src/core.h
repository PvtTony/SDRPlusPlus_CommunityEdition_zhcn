#pragma once
#include <config.h>
#include <module.h>
#include <module_com.h>
#include "command_args.h"
#include "i18n.h"
#include <locale.h>

namespace core {
    SDRPP_EXPORT ConfigManager configManager;
    SDRPP_EXPORT ModuleManager moduleManager;
    SDRPP_EXPORT ModuleComManager modComManager;
    SDRPP_EXPORT CommandArgsParser args;

    void setInputSampleRate(double samplerate);
};

int sdrpp_main(int argc, char* argv[]);