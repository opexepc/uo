//keys.h
#pragma once

#include <iostream>
#include <string>
#include <ff.h>
#include <stdio.h>
#include "keys.h"

// settings keys
#define SETTINGS_FILENAME "settings"
#define SETTINGS_KEY ">default<"
// types keys
#define DEFAULT_KEY "<DEFAULT>"
#define ARGS_KEY "args"
// extensions
#define CONFIG_EXTENSION ".ccf"
#define SETTINGS_EXTENSION ".lf"
// any other keys
#define NULL_STR_KEY "<N>"
#define EXIT_TAG "#exit"

const std::string config_path = ff::get_config_path(".uo");