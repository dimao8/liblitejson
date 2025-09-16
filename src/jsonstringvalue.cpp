#include "jsonstringvalue.h"
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
  stream << "\"" << m_value << "\"";
}

}