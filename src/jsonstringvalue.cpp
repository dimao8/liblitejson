#include "jsonstringvalue.h"

#include <cstdio>
#include <iostream>

namespace litejson
{

/* ******************** JSONStringValue::JSONStringValue ******************* */

JSONStringValue::JSONStringValue (int line, const std::string &str)
    : JSONValue (line), m_value (str)
{
  //
}

/* ******************* JSONStringValue::~JSONStringValue ******************* */

JSONStringValue::~JSONStringValue ()
{
  //
}

/* ************************ JSONStringValue::is_null *********************** */

bool
JSONStringValue::is_null () const
{
  return false;
}

/* *********************** JSONStringValue::is_string ********************** */

bool
JSONStringValue::is_string () const
{
  return true;
}

/* *********************** JSONStringValue::as_string ********************** */

std::optional<const std::string>
JSONStringValue::as_string () const
{
  return m_value;
}

/* ************************* JSONStringValue::print ************************ */

void
JSONStringValue::print (std::ostream &stream, size_t indent) const
{
  std::string str;
  char substr[7];

  for (auto it : m_value)
    {
      if (it == '\x08')
        str += "\\b";
      else if (it == '\x09')
        str += "\\t";
      else if (it == '\x0A')
        str += "\\n";
      else if (it == '\x0C')
        str += "\\f";
      else if (it == '\x0D')
        str += "\\r";
      else if (it == '\x22')
        str += "\\\"";
      else if (it == '\x2F')
        str += "\\/";
      else if (it == '\x5C')
        str += "\\\\";
      else if (it > '\x00' && it < '\x1F')
        {
          std::snprintf (substr, 7, "\\u%04hhx", it);
          str += substr;
        }
      else
        str.push_back (it);
    }

  stream << "\"" << str << "\"";
}

}