//actioner.cpp
#include "actioner.h"

void actioner(int act)
{
  switch(act)
  {
    case 1:
    {
      print_config_files(config_path);
      std::string filename = NULL_STR_KEY;
      while(filename == NULL_STR_KEY)
      {
        std::cout << "filename (without full path end extension: "; std::cin >> filename;
        if(check_input_fail()) continue;
        if(filename == EXIT_TAG)
          return;
      }
      std::string path = config_path + filename + CONFIG_EXTENSION;
      if(ff::file_exists(path))
        std::cout << "failed create file, file already exist!\n";
      else
      {
        if(ff::create_file(path))
          std::cout << "successfully create file!\n";
        else
          std::cout << "failed create file\n";
      };
    }
    break;

    case 2:
      print_config_files(config_path);
    break;

    case 3:
    {
      print_config_files(config_path);
      name_path np = get_current_path(config_path);
      if(np.empty())
        return;
      std::cout << np.filename << ":\n";
      ff::print_lines(np.path);
    }
    break;

    case 4:
    {
      print_config_files(config_path);
      name_path np = get_current_path(config_path);
      if(np.empty())
        return;
      ff::remove(np.path);
    }
    break;

    case 5:
      clear();
      cmd_loop();
      clear();
      std::cout << menu << "\n";
    break;

    case 6:
    {
      if(print_config_files(config_path) == 0)
        return;
      ff::create_file(config_path + SETTINGS_FILENAME + SETTINGS_EXTENSION);
      name_path np = get_current_path(config_path);
      if(np.empty())
        return;
      ff::write_value(config_path + SETTINGS_FILENAME + SETTINGS_EXTENSION, SETTINGS_KEY, np.filename);
    }
    break;

    case 7:
      std::cout << guide << "\n";
    break;

    case 8:
      clear();
      std::cout << menu << "\n";
    break;
  }
}