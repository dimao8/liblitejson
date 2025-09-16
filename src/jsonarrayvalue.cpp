#include "jsonarrayvalue.h"
#include "litejson/jsonvalue.h"

#include <iostream>

namespace litejson
{

/* ********************* JSONArrayValue::JSONArrayValue ******************** */

JSONArrayValue::JSONArrayValue (int line) : JSONValue (line)
{
  //
}

/* ******************** JSONArrayValue::~JSONArrayValue ******************** */

JSONArrayValue::~JSONArrayValue ()
{
  //
}

/* ******************** JSONArrayValue::add_array_entry ******************** */

void
JSONArrayValue::add_array_entry (const std::shared_ptr<JSONValue> &val)
{
  m_value.push_back (val);
  val->set_parent (shared_from_this ());
}

/* ************************ JSONArrayValue::is_null ************************ */

bool
JSONArrayValue::is_null () const
{
  return false;
}

/* ************************ JSONArrayValue::is_array *********************** */

bool
JSONArrayValue::is_array () const
{
  return true;
}

/* ************************ JSONArrayValue::as_array *********************** */

std::shared_ptr<const JSONValue>
JSONArrayValue::as_array (size_t index) const
{
  if (index >= m_value.size ())
    return nullptr;
  else
    return m_value[index];
}

/* ************************ JSONArrayValue::as_array *********************** */

std::shared_ptr<JSONValue>
JSONArrayValue::as_array (size_t index)
{
  if (index >= m_value.size ())
    return nullptr;
  else
    return m_value[index];
}

/* *********************** JSONArrayValue::array_size ********************** */

size_t
JSONArrayValue::array_size () const
{
  return m_value.size ();
}

/* ************************* JSONArrayValue::print ************************* */

void
JSONArrayValue::print (std::ostream &stream, size_t indent) const
{
  std::string filler (indent + 2, ' ');
  stream << "[" << std::endl;

  auto sz = array_size ();
  if (sz > 0)
    {
      for (auto i = 0; i < sz; i++)
        {
          stream << filler;
          as_array (i)->print (stream, indent + 2);
          if (i != sz - 1)
            stream << ",";
          stream << std::endl;
        }
    }
  stream << filler.substr (0, indent) << "]";
}

}
