#include <litejson/jsonvalue.h>
#include <litejson/litejson.h>

#include <cstdio>
#include <iostream>
#include <memory>
#include <optional>
#include <ostream>
#include <string>

#define PACKAGE "export_compare"
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
      std::cout << "[I] Value1 or value2 is nullptr" << std::endl;
      return false;
    }

  if (val1->is_null ()) // Check for null
    {
      if (val2->is_null ())
        return true;
      else
        {
          std::cout << "[I] Value2 is not a null" << std::endl;
          return false;
        }
    }
  else if (val1->is_boolean ()) // Check for boolean
    {
      if (!val2->as_boolean ())
        {
          std::cout << "[I] Value2 is not a boolean" << std::endl;
          return false;
        }
      else
        {
          b1 = val1->as_boolean ().value ();
          b2 = val2->as_boolean ().value ();
          return b1 == b2;
        }
    }
  else if (val1->is_string ()) // Check for string
    {
      if (!val2->as_string ())
        {
          std::cout << "[I] Value2 is not a string" << std::endl;
          return false;
        }
      else
        {
          str1 = val1->as_string ().value ();
          str2 = val2->as_string ().value ();
          return str1 == str2;
        }
    }
  else if (val1->is_number ()) // Check for number
    {
      if (!val2->as_float ())
        {
          std::cout << "[I] Value2 is not a number" << std::endl;
          return false;
        }
      else
        {
          f1 = val1->as_float ().value ();
          f2 = val2->as_float ().value ();
          return str1 == str2;
        }
    }
  else if (val1->is_array ()) // Check for array
    {
      if (!val2->is_array ())
        {
          std::cout << "[I] Value2 is not an array" << std::endl;
          return false;
        }
      else
        {
          if (val1->size () != val2->size ()) // Check for size
            {
              std::cout
                  << "[I] Size of value2 is not the same as size of value2"
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
      if (val1->size () != val2->size ()) // Check for size
        {
          std::cout << "[I] Size of value2 is not the same as size of value1"
                    << std::endl;
          return false;
        }
      auto it2 = val2->begin ();
      for (auto it1 = val1->begin (); it1 != val1->end (); it1++, it2++)
        {
          result = compare_subtree (*it1, *it2);
          if (result == false)
            return false;
        }
      return true;
    }
  else
    {
      std::cout << "[I] Unknown type for value1" << std::endl;
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

/* ******************************** cleanup ******************************** */

void
cleanup (const std::string &file_name)
{
  std::remove (file_name.c_str ());
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  std::string str;
  std::string in_file_name;
  std::string out_file_name;
  bool do_compare = false;

  if (argc < 2)
    return -1;

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
      else if (str == "-c" || str == "--compare")
        {
          do_compare = true;
        }
      else if (str == "-o")
        {
          i++;
          out_file_name = str;
        }
      else if (str.substr (0, 9) == "--output=")
        out_file_name = str.substr (9, std::string::npos);
      else if (i == argc - 1)
        in_file_name = str;
    }

  if (in_file_name.empty ())
    {
      std::cout << "[E] No input" << std::endl;
      return -1;
    }

  // Output status
  std::cout << "[I] Input file is \"" << in_file_name << "\"" << std::endl;
  std::cout << "[I] Output file is \"" << out_file_name << "\"" << std::endl;

  // Open and compare
  litejson::JSONLoader ldr1 (in_file_name);
  if (ldr1.is_bad ())
    {
      std::cout << "[E] JSON input file is invalid" << std::endl;
      return -1;
    }
  if (out_file_name.empty ())
    {
      if (!ldr1.export_stream (std::cout))
        {
          std::cout << "[E] Export error" << std::endl;
          return -1;
        }
    }
  else
    {
      if (!ldr1.export_file (out_file_name))
        {
          std::cout << "[E] Export error" << std::endl;
          return -1;
        }
    }

  if (do_compare)
    {
      if (out_file_name.empty ())
        {
          std::cout << "[E] No generated output. Use -o argument" << std::endl;
          return -1;
        }

      litejson::JSONLoader ldr2 (out_file_name);
      if (ldr2.is_bad ())
        {
          std::cout << "[E] JSON output file is invalid" << std::endl;
          cleanup (out_file_name);
          return -1;
        }
      if (!compare (ldr1, ldr2))
        {
          std::cout << "[E] JSON trees are not the same" << std::endl;
          cleanup (out_file_name);
          return -1;
        }
      else
        {
          std::cout << "[I] JSON trees are the same" << std::endl;
          cleanup (out_file_name);
          return 0;
        }
    }

  cleanup (out_file_name);
  return 0;
}