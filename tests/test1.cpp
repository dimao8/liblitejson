#include <litejson.h>

#include <iostream>

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Not enough arguments" << std::endl;
      return -2;
    }

  litejson::json_loader loader(argv[1]);

  if (loader.bad())
    {
      loader.print_json_tree(std::cout);
      return -1;
    }
  // else if (loader.empty())
  //   return -2;
  else
    {
      loader.print_json_tree(std::cout);
      return 0;
    }
}