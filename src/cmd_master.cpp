//cmd_master.cpp
#include "cmd_master.h"

void cmd_loop()
{
  print_config_files(config_path);
  name_path np = get_current_path(config_path);
  if(np.empty())
    return;
  int act = -1;

  std::cout << np.filename << ":\n";
  ff::print_lines(np.path);
  std::cout << cmd_menu << "\n";
  while(true)
  {
    std::cout << "[cmd master] action: "; std::cin >> act;
    if(check_input_fail(act, 0, 5)) continue;
    switch(act)
    {
      case 0:
        return;
      break;

      case 1:
      {
        std::string block_name = NULL_STR_KEY;
        while(block_name == NULL_STR_KEY)
        {
          std::cout << "block name: "; std::cin >> block_name;
          if(check_input_fail()) continue;
        }
        ff::block b = ff::find_block(np.path, block_name);
        if(!b.found())
        {
          ff::stream stream(np.path, WRITE);
          ff::write_block_tag_stream(stream, block_name, OPEN, 0, stream.str_count() + 2);
          ff::write_block_tag_stream(stream, block_name, CLOSE, 0);
          stream.close();
        }
        else
        {
          std::cout << "this short cmd already exist\n";
          continue;
        }
      }
      break;

      case 2:
      {
        std::string block_name = NULL_STR_KEY;
        std::string full_cmd = NULL_STR_KEY;
        std::string arg = NULL_STR_KEY;
        while(block_name == NULL_STR_KEY)
        {
          std::cout << "block name: "; std::cin >> block_name;
          if(check_input_fail()) continue;
        }
        ff::block b = ff::find_block(np.path, block_name);
        if(!b.found())
        {
          std::cout << "block not found\n";
          continue;
        }
        else
        {
          int act = -1;
          std::cout << arg_menu << "\n";
          while(act == -1)
          {
            std::cout << "action: "; std::cin >> act;
            if(check_input_fail(act, 1, 3))
            {
              act = -1;
              continue;
            }
          }
          std::cin.ignore(100000, '\n');
          switch(act)
          {
            case 1:
              while(arg == NULL_STR_KEY)
              {
                std::cout << "arg: "; std::cin >> arg;
                if(check_input_fail()) continue;
              }
            break;

            case 2:
              arg = DEFAULT_KEY;
            break;

            case 3:
             arg = ARGS_KEY;
            break;
          }
          if(ff::find_line_for_key(np.path, arg, b.start_line, b.end_line) != FF_LINE_NPOS)
          {
            std::cout << "full cmd with this arg already exist\n";
            char choise = 0;
            std::cout << "change cmd? [Y/n]: "; std::cin >> choise;
            if(!(choise == 'Y' || choise == 'y'))
              continue;
          }
          while(full_cmd == NULL_STR_KEY)
          {
            std::cout << "full cmd: ";
            std::cin.ignore(100000, '\n');
            std::getline(std::cin, full_cmd);
            if(check_input_fail()) continue;
          }
          ff::write_value(np.path, arg, full_cmd, 0, b.start_line, b.end_line);
        }
      }      
      break;

      case 3:
      {
        std::string block_name = NULL_STR_KEY;
        while(block_name == NULL_STR_KEY)
        {
          std::cout << "block name: "; std::cin >> block_name;
          if(check_input_fail()) continue;
        }
        ff::block b = ff::find_block(np.path, block_name);
        if(b.found())
        {
          if(ff::remove_lines(np.path, b.start_line - 1, b.end_line))
            std::cout << "block was deleted\n";
        }
        else
        {
          std::cout << "block not found\n";
          continue;
        }
      }
      break;

      case 4:
      {
        std::string block_name = NULL_STR_KEY, arg_name = NULL_STR_KEY;
        while(block_name == NULL_STR_KEY)
        {
          std::cout << "block name: "; std::cin >> block_name;
          if(check_input_fail()) continue;
        }
        ff::block b = ff::find_block(np.path, block_name);
        if(!b.found())
        {
          std::cout << "block not found\n";
          continue;
        }
        while(arg_name == NULL_STR_KEY)
        {
          std::cout << "arg name: "; std::cin >> arg_name;
          if(check_input_fail()) continue;
        }

        ff::stream stream(np.path, WRITE);
        int line_num = ff::find_line_for_key_stream(stream, arg_name);
        ff::remove_line_stream(stream, line_num);
        stream.close();
      }
      break;

      case 5:
        clear();
        std::cout << np.filename << ":\n";
        ff::print_lines(np.path);
        std::cout << cmd_menu << "\n";
      break;
    }
  }
}