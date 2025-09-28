//utils.cpp
#include "utils.h"

void clear()
{
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

std::string files_iterator(const std::string &path, const std::string &right_str, FILES_TYPE type, ITERATOR_MODS mod, int *count)
{
  for(auto &obj : std::filesystem::directory_iterator(path))
  {
    std::string left_str = NULL_STR_KEY;
    switch(type)
    {
      case REGULAR_FILENAME:
      left_str = obj.path().filename().string();
      break;

      case REGULAR_STEM:
      left_str = obj.path().stem().string();
      break;

      case EXTENSION:
      left_str = obj.path().extension().string();
      break;
    }

    if(obj.is_regular_file() && left_str == right_str)
    {
      if(count)
        (*count)++;
      switch(mod)
      {
        case PRINT:
        std::cout << "|-" << obj.path().stem().string() << "\n";
        break;

        case FIND_AND_RETURN:
        return obj.path().string();
        break;

        case FIND_AND_PRINT:
        std::cout << "file exists!\n";
        return obj.path().string();
        break;
      }
    }
  }
  return NULL_STR_KEY;
}

int print_config_files(const std::string &path)
{
  int count = 0;
  files_iterator(path, CONFIG_EXTENSION, EXTENSION, PRINT, &count);
  if(count == 0)
    std::cout << "files no exists\n";
  return count;
}

void replace_all(std::string &str, const std::string &from, const std::string &to)
{
  if (from.empty()) return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos)
  {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

bool check_input_fail(int num_action, int min, int max)
{
  if(std::cin.fail() || num_action < min || num_action > max)
  {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "invalid input, try again\n";
    return true;
  }
  else return false;
}

name_path get_current_path(const std::string &dir_path)
{
  name_path np;
  while(np.path == NULL_STR_KEY)
  {
    std::cout << "filename (without full path end extension: "; std::cin >> np.filename;
    if(check_input_fail()) continue;
    if(np.filename == EXIT_TAG)
    {
      np.filename = NULL_STR_KEY;
      return np;
    }
    np.path = files_iterator(config_path, np.filename + CONFIG_EXTENSION, REGULAR_FILENAME, FIND_AND_RETURN);
    if(np.path == NULL_STR_KEY) std::cout << "file not found! try again\n";
  }
  return np;
}