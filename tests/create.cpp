#include "litejson/jsonvalue.h"
#include <litejson/litejson.h>

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#define PACKAGE "create"
#define VERSION "0.1"

void usage ();
void version ();

/* ********************************* usage ********************************* */

void
usage ()
{
  std::cout << "Usage: " << PACKAGE << " OPTIONS file1" << std::endl;
  std::cout << "Open file1 and print it. If -o argument hs been given, output"
            << std::endl;
  std::cout << "to the file and compare result" << std::endl;
  std::cout << "where OPTIONS are:" << std::endl;
  std::cout << "  -h, --help               Print this message and exit"
            << std::endl;
  std::cout << "  -v, --version            Print version prompt and exit"
            << std::endl;
  std::cout << "  -o file, --output=file   Output JSON tree to file"
            << std::endl;
}

/* ******************************** version ******************************** */

void
version ()
{
  std::cout << PACKAGE << " " << VERSION << std::endl;
}

/* **************************** compare_subtree **************************** */

bool
compare_subtree (const std::shared_ptr<litejson::JSONValue> &val1,
                 const std::shared_ptr<litejson::JSONValue> &val2)
{
  bool b1, b2;
  float f1, f2;
  std::string str1, str2;
  bool result;

  if (val1 == nullptr || val2 == nullptr)
    {
      std::cout << "[E] value1 or value2 is nullptr" << std::endl;
      return false;
    }

  if (val1->is_null ()) // Check for null
    {
      std::cout << "[I] Value of the subtree is null" << std::endl;
      if (val2->is_null ())
        {
          std::cout << "[I] value1 and value2 are both null" << std::endl;
          return true;
        }
      else
        {
          std::cout << "[E] Value2 is not a null" << std::endl;
          return false;
        }
    }
  else if (val1->is_boolean ()) // Check for boolean
    {
      std::cout << "[I] Value of the subtree is boolean" << std::endl;
      if (!val2->as_boolean ())
        {
          std::cout << "[E] Value2 is not a boolean" << std::endl;
          return false;
        }
      else
        {
          b1 = val1->as_boolean ().value ();
          b2 = val2->as_boolean ().value ();
          if (b1 == b2)
            std::cout << "[I] value1 and value2 are both "
                      << (b1 ? "true" : "false") << std::endl;
          else
            std::cout << "[E] value1 and value2 are not the same boolean"
                      << std::endl;
          return b1 == b2;
        }
    }
  else if (val1->is_string ()) // Check for string
    {
      std::cout << "[I] Value of the subtree is string" << std::endl;
      if (!val2->as_string ())
        {
          std::cout << "[E] Value2 is not a string" << std::endl;
          return false;
        }
      else
        {
          str1 = val1->as_string ().value ();
          str2 = val2->as_string ().value ();
          if (str1 == str2)
            std::cout << "[I] value1 and value2 are both \"" << str1 << "\""
                      << std::endl;
          else
            std::cout << "[E] value1 and value2 are not the same string"
                      << std::endl;
          return str1 == str2;
        }
    }
  else if (val1->is_number ()) // Check for number
    {
      std::cout << "[I] Value of the subtree is number" << std::endl;
      if (!val2->as_float ())
        {
          std::cout << "[E] Value2 is not a number" << std::endl;
          return false;
        }
      else
        {
          f1 = val1->as_float ().value ();
          f2 = val2->as_float ().value ();
          if (f1 == f2)
            std::cout << "[I] value1 and value2 are both " << f1 << std::endl;
          else
            std::cout << "[E] value1 and value2 are not the same number"
                      << std::endl;
          return f1 == f2;
        }
    }
  else if (val1->is_array ()) // Check for array
    {
      std::cout << "[I] Value of the subtree is an array" << std::endl;
      if (!val2->is_array ())
        {
          std::cout << "[E] Value2 is not an array" << std::endl;
          return false;
        }
      else
        {
          if (val1->size () != val2->size ()) // Check for size
            {
              std::cout
                  << "[E] Size of value2 is not the same as size of value2"
                  << std::endl;
              return false;
            }
          if (val1->size () == 0)
            return true;
          for (auto i = 0; i < val1->size (); i++)
            {
              result
                  = compare_subtree (val1->as_array (i), val2->as_array (i));
              if (!result)
                return false;
            }
          return true;
        }
    }
  else if (val1->is_object ()) // Check for object
    {
      std::cout << "[I] Value of the subtree is an object" << std::endl;

      std::string key = val1->as_object_next_key ();
      size_t n, i, j;
      bool cmp_result = false;

      while (!key.empty ())
        {
          n = val1->object_key_size (key);
          if (n != val2->object_key_size (key))
            {
              std::cout << "[E] Number of values with key \"" << key
                        << "\" is not the same" << std::endl;
              return false;
            }
          for (i = 0; i < n; i++)
            {
              cmp_result = false;
              for (j = 0; j < n; j++)
                {
                  if (compare_subtree (val1->as_object (key, i),
                                       val2->as_object (key, j)))
                    {
                      cmp_result = true;
                      break;
                    }
                }
              if (!cmp_result)
                return false;
            }
          key = val1->as_object_next_key (key);
        }

      return true;
    }
  else
    {
      std::cout << "[E] Unknown type for value1" << std::endl;
      return false;
    }
}

/* ******************************** compare ******************************** */

bool
compare (litejson::JSONLoader &op1, litejson::JSONLoader &op2)
{
  std::shared_ptr<litejson::JSONValue> val1;
  std::shared_ptr<litejson::JSONValue> val2;

  val1 = op1.get_root ();
  val2 = op2.get_root ();

  return compare_subtree (val1, val2);
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  std::string str;
  std::string out_file_name;

  if (argc <= 1)
    return -1;

  for (int i = 1; i < argc; i++)
    {
      str = argv[i];
      if (str == "--help" || str == "-h")
        {
          usage ();
          return 0;
        }
      else if (str == "--version" || str == "-v")
        {
          version ();
          return 0;
        }
      else if (str == "-o")
        {
          i++;
          if (i >= argc)
            return -1;
          else
            out_file_name = argv[i];
        }
    }

  if (out_file_name.empty ())
    return -1;

  litejson::JSONLoader ldr;
  std::shared_ptr<litejson::JSONValue> current;
  std::shared_ptr<litejson::JSONValue> val
      = litejson::JSONValue::make_object (0);
  ldr.set_root_value (val);

  current = val;
  val = litejson::JSONValue::make_array (0);
  val->add_array_entry (litejson::JSONValue::make_number (0, 1.2f));
  val->add_array_entry (litejson::JSONValue::make_string (0, "Hello"));
  val->add_array_entry (litejson::JSONValue::make_boolean (0, false));
  val->add_array_entry (litejson::JSONValue::make_null (0));
  current->add_object_entry ("array", val);
  current->add_object_entry ("number",
                             litejson::JSONValue::make_number (0, 3.3f));
  current->add_object_entry ("string",
                             litejson::JSONValue::make_string (0, "World\n\r\t\b\f\\/\"\x02"));
  current->add_object_entry ("boolean",
                             litejson::JSONValue::make_boolean (0, true));
  current->add_object_entry ("null", litejson::JSONValue::make_null (0));

  ldr.export_file (out_file_name);

  litejson::JSONLoader ld (out_file_name);

  bool result = compare (ldr, ld);

  std::remove (out_file_name.c_str ());

  return result ? 0 : -1;
}
