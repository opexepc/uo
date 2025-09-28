//utils.h
#pragma once
#include "keys.h"

enum FILES_TYPE
{
  REGULAR_FILENAME,
  REGULAR_STEM,
  EXTENSION
};

enum ITERATOR_MODS
{
  PRINT,
  FIND_AND_PRINT,
  FIND_AND_RETURN
};

struct name_path
{
  std::string filename = NULL_STR_KEY;
  std::string path = NULL_STR_KEY;
  bool empty()
  {
    return true ? (filename == NULL_STR_KEY && path == NULL_STR_KEY) : false;
  }
};

void clear();
// this function return filename or name without extension or only extension (check FILES_TYPE)
std::string files_iterator
 (const std::string &path, const std::string &right_str,
  FILES_TYPE type, ITERATOR_MODS mod, int *count = nullptr);
// print all files with config extension
int print_config_files(const std::string &path);
// replace blocks in string
void replace_all(std::string &str, const std::string &from, const std::string &to);
// simple function for check input std::cin fails
bool check_input_fail(int num_action = 0, int min = INT32_MIN, int max = INT32_MAX);

// return filename and full path
name_path get_current_path(const std::string &dir_path);