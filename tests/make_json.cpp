#include <litejson/jsonvalue.h>
#include <litejson/litejson.h>

#include <iostream>
#include <memory>
#include <ostream>
#include <string>

void usage ();
void version ();

/* ********************************* usage ********************************* */

void
usage ()
{
  std::cout << "Usage: make_json OPTIONS" << std::endl;
  std::cout << "where OPTIONS are:" << std::endl;
  std::cout << "  -h, --help               Print this message and exit"
            << std::endl;
  std::cout << "  -v, --version            Print version prompt and exit"
            << std::endl;
}

/* ******************************** version ******************************** */

void
version ()
{
  std::cout << "make_json v0.1" << std::endl;
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  std::string str;

  if (argc > 1)
    {
      for (auto i = 1; i < argc; i++)
        {
          str = argv[i];
          if (str == "-h" || str == "--help")
            {
              usage ();
              exit (0);
            }
          else if (str == "-v" || str == "--version")
            {
              version ();
              exit (0);
            }
        }
    }

  litejson::JSONLoader ldr;
  std::shared_ptr<litejson::JSONValue> current;
  ldr.set_root_value (litejson::JSONValue::make_object (0));
  current = ldr.get_root ();
  current->add_object_entry (
      "String", litejson::JSONValue::make_string (0, "Hello, World!"));
  current->add_object_entry ("Number",
                             litejson::JSONValue::make_number (0, 2.581E-3));
  current->add_object_entry ("Null", litejson::JSONValue::make_null (0));
  current->add_object_entry ("Boolean",
                             litejson::JSONValue::make_boolean (0, false));

  current->add_object_entry ("Array", litejson::JSONValue::make_array (0));
  current = current->as_object ("Array");
  current->add_array_entry (litejson::JSONValue::make_null (0));
  current->add_array_entry (litejson::JSONValue::make_number (0, 1));
  current->add_array_entry (litejson::JSONValue::make_number (0, 2));
  current->add_array_entry (litejson::JSONValue::make_boolean (0, false));
  current = current->parent ().lock ();
  if (current == nullptr)
    return -1;

  current->add_object_entry ("Object", litejson::JSONValue::make_object (0));
  current = current->as_object ("Object");
  current->add_object_entry (
      "String", litejson::JSONValue::make_string (0, "Object.String"));
  current->add_object_entry ("Number",
                             litejson::JSONValue::make_number (0, 122));
  return ldr.export_file ("export.json") ? 0 : -1;
}