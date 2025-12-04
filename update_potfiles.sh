#!/bin/sh

# SDR++ Core
xgettext -k_ -o core/locale/sdrpp_core.pot --from-code=UTF-8 -f core/POTFILES

# Decoder: Radio
xgettext -k_ -o decoder_modules/radio/locale/radio.pot --from-code=UTF-8 -f decoder_modules/radio/POTFILES

# Misc: Frequency Manager
xgettext -k_ -o misc_modules/frequency_manager/locale/frequency_manager.pot misc_modules/frequency_manager/src/main.cpp
