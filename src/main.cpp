//main.cpp
#include "keys.h"
#include "actioner.h"
#include "utils.h"


int main(int argc, char* argv[])
{
  std::string config_filename = "";
  // create base files and dir
  ff::create_dir(config_path);
  // if only path arg
  if(argc == 1)
  {
    // always get any action
    std::cout << menu << "\n";
    int act = 0;
    bool run = true;
    while(true)
    {
      std::cout << "action: "; std::cin >> act;
      if(check_input_fail(act, 0, 8)) continue;
      if(act == 0)
        return 0;
      actioner(act);
    }
    return 0;
  }
  // any count > 1
  else
  {
    bool is_arg_filename = false;
    // specific index count
    int filename_arg_index = 0;
    // check help arg
    if(std::string(argv[1]) == "--help" or std::string(argv[1]) == "--h")
    {
      std::cout << guide << "\n";
      return 0;
    }
    // check target config file arg
    if(argv[1][0] == '=')
    {
      bool found_path = false;
      for(auto &obj : std::filesystem::directory_iterator(config_path))
      {
        if(obj.is_regular_file() && "=" + obj.path().filename().string() == std::string(argv[1]) + CONFIG_EXTENSION)
        {
          config_filename = obj.path().stem().string();
          is_arg_filename = true;
          // index + 1 if use target config filename
          filename_arg_index = 1;
          found_path = true;
          break;
        }
      }
      if(!found_path)
      {
        std::cout << "file not found!\n";
        return 1;
      }
    }
    // if target config file not set
    else
    {
      // if file exists get default config name from setting file
      if(ff::file_exists(config_path + SETTINGS_FILENAME + SETTINGS_EXTENSION))
      {
        config_filename = ff::read_value(config_path + SETTINGS_FILENAME + SETTINGS_EXTENSION, SETTINGS_KEY);
        bool found_name = false;
        for(auto &obj : std::filesystem::directory_iterator(config_path))
        {
          if(obj.is_regular_file() && obj.path().filename().string() == config_filename + CONFIG_EXTENSION)
          {
            found_name = true;
            break;
          }
        }
        // check exist name
        if(!found_name)
        {
          std::cout << "default config filename not exists!\n";
          return 1;
        }
      }
      // if file not exists
      else
      {
        std::cout << "pls set default config or set config name in arg\n";
        return 2;
      }
    }
    // open read stream
    ff::stream stream(config_path + config_filename + CONFIG_EXTENSION, READ);
    std::string key = NULL_STR_KEY;
    // $uo "short_cmd"
    // $uo =main #not valid form
    // check valid target filename form
    if(argc == 2 && is_arg_filename)
    {
      std::cout << "cmd not set!\n";
      stream.close();
      return 4;
    }
    // read target short cmd
    ff::block b = ff::find_block_stream(stream, argv[1 + filename_arg_index]);
    if(!b.found())
    {
      std::cout << "cmd not found!\n";
      stream.close();
      return 3;
    }
    // find current key
    std::string full_cmd = NULL_STR_KEY;
    if(argc == 2 || (argc == 3 && is_arg_filename))
    {
      key = DEFAULT_KEY;
      full_cmd = ff::read_value_stream(stream, key, true, b.start_line, b.end_line);
    }
    // any count > 2
    // find any args
    else
    {
      key = argv[2 + filename_arg_index];
      full_cmd = ff::read_value_stream(stream, key, true, b.start_line, b.end_line);
    }
    if(full_cmd == FF_NULL_STR)
    {
      // find args array if not found any args
      key = ARGS_KEY;
      stream.clear_stream();
      full_cmd = ff::read_value_stream(stream, key, true, b.start_line, b.end_line);
    }
    
    //not found any key
    if(full_cmd == FF_NULL_STR)
    {
      std::cout << "cmd not found!\n";
      stream.close();
      return 5;
    }
    // only if not found other args
    if(key == ARGS_KEY)
    {
      // change arg_x to real args
      for(int i = 2 + filename_arg_index; i < argc; i++)
      {
        std::string arg = "arg_" + std::to_string(i - (1 + filename_arg_index));
        replace_all(full_cmd, arg, argv[i]);
      }
    }
    // send full cmd
    system(full_cmd.c_str());
    // close read stream
    stream.close();
    return 0;
  }
}

// codes:
// 0 -> successfully exit
// 1 -> config name not valid
// 2 -> settings file not exists
// 3 -> short cmd in target file not found
// 4 -> cmd not set
// 5 -> cmd not found