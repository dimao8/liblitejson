#include "jsonbooleanvalue.h"
#include "litejson/jsonvalue.h"
#include <iostream>

namespace litejson
{

/* ******************* JSONBooleanValue::JSONBooleanValue ****************** */

JSONBooleanValue::JSONBooleanValue (int line, bool b)
    : JSONValue (line), m_value (b)
{
  //
}

/* ****************** JSONBooleanValue::~JSONBooleanValue ****************** */

JSONBooleanValue::~JSONBooleanValue ()
{
  //
}

/* *********************** JSONBooleanValue::is_null *********************** */

bool
JSONBooleanValue::is_null () const
{
  return false;
}

/* ********************** JSONBooleanValue::is_boolean ********************* */

bool
JSONBooleanValue::is_boolean () const
{
  return true;
}

/* ********************** JSONBooleanValue::as_boolean ********************* */

std::optional<bool>
JSONBooleanValue::as_boolean () const
{
  return m_value;
}

/* ************************ JSONBooleanValue::print ************************ */

void
JSONBooleanValue::print (std::ostream &stream, size_t indent) const
{
  stream << (m_value ? "true" : "false");
}

}