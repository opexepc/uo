//texts.h
#pragma once
#include <string>
#include "keys.h"

const std::string menu = R"(
  set action:

  0 - exit
  1 - new config
  2 - list configs
  3 - view config
  4 - delete config
  5 - cmd master
  6 - set default config
  7 - help
  8 - view this menu
  )";

const std::string guide = R"(
  guide:
  
==========================================================================================================

  $uo                                 -> control panel

  $uo --help                          -> this guide

  $uo "short cmd"                     -> send full equal DEFAULT cmd
                                         if default config name is valid

  $uo ="config filename" "short cmd"  -> send full equal DEFAULT cmd
                                         if default config name not set or you want use target config name

  $uo "short cmd" "arg"               -> send full equal cmd WITH ARG
                                         if default config name is valid

==========================================================================================================

  "arg" may be solo custom or array args: arg_1 arg_2 arg_3 ...
  example:
    in file:
      *1* [a] = echo a
      *2* [b] = echo b
      *3* [c] = echo c
      *4* [)" ARGS_KEY R"(] = echo custom: arg_1, arg_2
      *5* [)" DEFAULT_KEY R"(] = echo def
    in console:
      $uo a -> a
      $uo b -> b
      $uo c -> c
      $uo a b c -> a b
      $uo -> def

  [a] = echo a
   ^    ^
   |    |
  arg   full cmd

==========================================================================================================

  if you want exit from filename input write )" EXIT_TAG R"(

==========================================================================================================
  )";

const std::string cmd_menu = R"(
  set action:

  0 - exit
  1 - add new short cmd
  2 - add new full cmd
  3 - remove short cmd
  4 - remove full cmd
  5 - view this menu
  )";

const std::string arg_menu = R"(
  set action:
  
  1 - add custom arg
  2 - add default arg
  3 - add array arg
  )";