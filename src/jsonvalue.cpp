///
/// \file jsonvalue.cpp
///

#include <jsonvalue.h>

#include <cmath>
#include <iomanip>
#include <stdexcept>

namespace litejson
{

const JSONValue JSONValue::invalid_value = JSONValue::invalid ();

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue ()
{
  m_data_smartptr.reset ();
  m_value_type = JSONValueType::Null;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (float f)
{
  m_data_smartptr = std::make_shared<float> (f);
  m_value_type = JSONValueType::Number;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (bool b)
{
  m_data_smartptr = std::make_shared<bool> (b);
  m_value_type = JSONValueType::Boolean;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (const std::string &str)
{
  m_data_smartptr = std::make_shared<std::string> (str);
  m_value_type = JSONValueType::String;
}

/* ************************* JSONValue::~JSONValue ************************* */

JSONValue::~JSONValue ()
{
  // dtor
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (const JSONValue &other)
{
  m_data_smartptr = other.m_data_smartptr;
  m_value_type = other.m_value_type;
}

/* ************************** JSONValue::operator= ************************* */

JSONValue &
JSONValue::operator= (const JSONValue &other)
{
  m_data_smartptr = other.m_data_smartptr;
  m_value_type = other.m_value_type;
  return *this;
}

bool
JSONValue::is_valid () const
{
  return m_value_type != JSONValueType::Invalid;
}

/* *************************** JSONValue::is_null ************************** */

bool
JSONValue::is_null () const
{
  return m_value_type == JSONValueType::Null;
}

/* ************************* JSONValue::is_boolean ************************* */

bool
JSONValue::is_boolean () const
{
  return m_value_type == JSONValueType::Boolean;
}

/* ************************** JSONValue::is_number ************************* */

bool
JSONValue::is_number () const
{
  return m_value_type == JSONValueType::Number;
}

/* ************************** JSONValue::is_string ************************* */

bool
JSONValue::is_string () const
{
  return m_value_type == JSONValueType::String;
}

/* ************************** JSONValue::is_array ************************** */

bool
JSONValue::is_array () const
{
  return m_value_type == JSONValueType::Array;
}

/* ************************** JSONValue::is_object ************************* */

bool
JSONValue::is_object () const
{
  return m_value_type == JSONValueType::Object;
}

/* ************************** JSONValue::as_string ************************* */

const std::string &
JSONValue::as_string () const
{
  if (m_value_type != JSONValueType::String)
    throw std::runtime_error ("Not a string");
  else
    return *(std::static_pointer_cast<const std::string> (m_data_smartptr));
}

/* ************************* JSONValue::as_integer ************************* */

int
JSONValue::as_integer () const
{
  if (m_value_type != JSONValueType::Number)
    throw std::runtime_error ("Not a number");
  else
    return std::nearbyintf (
        *(std::static_pointer_cast<float> (m_data_smartptr)));
}

/* ************************** JSONValue::as_float ************************** */

float
JSONValue::as_float () const
{
  if (m_value_type != JSONValueType::Number)
    throw std::runtime_error ("Not a number");
  else
    return *(std::static_pointer_cast<float> (m_data_smartptr));
}

/* ************************* JSONValue::as_boolean ************************* */

bool
JSONValue::as_boolean () const
{
  if (m_value_type != JSONValueType::Boolean)
    throw std::runtime_error ("Not a boolean");
  else
    return *(std::static_pointer_cast<bool> (m_data_smartptr));
}

/* ************************** JSONValue::as_array ************************** */

const JSONValue &
JSONValue::as_array (int index) const
{
  if (m_value_type != JSONValueType::Array)
    throw std::runtime_error ("Not an array");
  else if (index >= (std::static_pointer_cast<value_array_t> (m_data_smartptr))
                        ->size ())
    throw std::out_of_range ("Index is out of range");
  else
    return (std::static_pointer_cast<value_array_t> (m_data_smartptr))
        ->at (index);
}

/* *********************** JSONValue::object_key_size ********************** */

size_t
JSONValue::object_key_size (const std::string &key) const
{
  if (m_value_type != JSONValueType::Object)
    throw std::runtime_error ("Not an object");
  else
    return (std::static_pointer_cast<value_object_t> (m_data_smartptr))
        ->count (key);
}

/* ************************** JSONValue::as_object ************************* */

const JSONValue &
JSONValue::as_object (const std::string &key, size_t index) const
{
  std::pair<value_object_t::iterator, value_object_t::iterator> range;
  value_object_t::iterator it;

  if (m_value_type != JSONValueType::Object)
    throw std::runtime_error ("Not an object");
  else if (index >= object_key_size (key))
    throw std::out_of_range ("Index is out of range");
  else
    {
      range = (std::static_pointer_cast<value_object_t> (m_data_smartptr))
                  ->equal_range (key);
      it = range.first;
      if (index)
        for (auto i = 0; i < index; i++, it++) {}
      return it->second;
    }
}

/* *********************** JSONValue::add_array_entry ********************** */

void
JSONValue::add_array_entry (const JSONValue &val)
{
  if (m_value_type != JSONValueType::Array)
    {
      m_value_type = JSONValueType::Array;
      m_data_smartptr = std::make_shared<value_array_t> ();
    }

  (std::static_pointer_cast<value_array_t> (m_data_smartptr))->push_back (val);
}

/* ********************** JSONValue::add_object_entry ********************** */

void
JSONValue::add_object_entry (const std::string &key, const JSONValue &val)
{
  if (m_value_type != JSONValueType::Object)
    {
      m_value_type = JSONValueType::Object;
      m_data_smartptr = std::make_shared<value_object_t> ();
    }

  (std::static_pointer_cast<value_object_t> (m_data_smartptr))
      ->emplace (key, val);
}

/* ************************* JSONValue::array_size ************************* */

size_t
JSONValue::array_size () const
{
  if (m_value_type != JSONValueType::Boolean)
    throw std::runtime_error ("Not an array");
  else
    return (std::static_pointer_cast<value_array_t> (m_data_smartptr))
        ->size ();
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const JSONValue &val)
{
  switch (val.m_value_type)
    {

    case JSONValueType::Null:
      stream << "null";
      break;

    case JSONValueType::Number:
      stream << val.as_float ();
      break;

    case JSONValueType::String:
      stream << "\"" << val.as_string () << "\"";
      break;

    case JSONValueType::Boolean:
      stream << (val.as_boolean () ? "true" : "false");
      break;

    case JSONValueType::Array:
      stream << "[" << std::endl;
      for (size_t i = 0;
           i < (std::static_pointer_cast<value_array_t> (val.m_data_smartptr))
                   ->size ();
           i++)
        {
          stream << (std::static_pointer_cast<value_array_t> (
                         val.m_data_smartptr))
                        ->at (i);
          if (i
              < (std::static_pointer_cast<value_array_t> (val.m_data_smartptr))
                        ->size ()
                    - 1)
            stream << ",";
          stream << std::endl;
        }
      stream << "]" << std::endl;
      break;

    case JSONValueType::Object:
      stream << "{" << std::endl;
      for (auto it :
           *(std::static_pointer_cast<value_object_t> (val.m_data_smartptr)))
        {
          stream << "\"" << it.first << "\" : ";
          stream << it.second << ",";
          stream << std::endl;
        }
      stream << "}" << std::endl;
      break;
    }

  return stream;
}

/* *************************** JSONValue::invalid ************************** */

JSONValue
JSONValue::invalid ()
{
  JSONValue val;
  val.m_value_type = JSONValueType::Invalid;
  val.m_data_smartptr.reset ();
  return val;
}

}
