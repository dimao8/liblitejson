#include "jsonnumbervalue.h"
#include "litejson/jsonvalue.h"

#include <cmath>
#include <iostream>
#include <optional>

namespace litejson
{

/* ******************** JSONNumberValue::JSONNumberValue ******************* */

JSONNumberValue::JSONNumberValue (int line, float n)
    : JSONValue (line), m_value (n)
{
  //
}

/* ******************* JSONNumberValue::~JSONNumberValue ******************* */

JSONNumberValue::~JSONNumberValue ()
{
  //
}

/* ************************ JSONNumberValue::is_null *********************** */

bool
JSONNumberValue::is_null () const
{
  return false;
}

/* *********************** JSONNumberValue::is_number ********************** */

bool
JSONNumberValue::is_number () const
{
  return true;
}

/* ********************** JSONNumberValue::as_integer ********************** */

std::optional<int>
JSONNumberValue::as_integer () const
{
  return std::optional<int> (std::nearbyintf (m_value));
}

/* *********************** JSONNumberValue::as_float *********************** */

std::optional<float>
JSONNumberValue::as_float () const
{
  return m_value;
}

/* ************************* JSONNumberValue::print ************************ */

void
JSONNumberValue::print (std::ostream &stream, size_t indent) const
{
  stream << m_value;
}

}