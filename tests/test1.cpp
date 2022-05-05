#include <litejson.h>

int main(int argc, char** argv)
{
  litejson::json_loader loader(argv[1]);

  if (loader.bad())
    return -1;
  else if (loader.empty())
    return -2;
  else
    return 0;
}