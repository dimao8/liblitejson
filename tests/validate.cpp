#include <litejson.h>

#include <iostream>

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Not enough arguments" << std::endl;
      return -2;
    }

  litejson::JSONLoader loader(argv[1]);

  if (loader.is_bad())
    return -1;
  else
    return 0;
}