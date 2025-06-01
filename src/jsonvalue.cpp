///
/// \file jsonvalue.cpp
///

#include <jsonvalue.h>

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace litejson
{

/* ************************* JSONValue::set_parent **************************/

void
JSONValue::set_parent (JSONValue *parent)
{
  m_parent = parent;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (int line)
{
  m_parent = nullptr;
  m_data_ptr = nullptr;
  m_value_type = JSONValueType::Null;
  m_line = line;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (float f, int line)
{
  m_parent = nullptr;
  m_data_ptr = new float (f);
  m_value_type = JSONValueType::Number;
  m_line = line;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (bool b, int line)
{
  m_parent = nullptr;
  m_data_ptr = new bool (b);
  m_value_type = JSONValueType::Boolean;
  m_line = line;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (const std::string &str, int line)
{
  m_parent = nullptr;
  m_data_ptr = new std::string (str);
  m_value_type = JSONValueType::String;
  m_line = line;
}

/* ************************* JSONValue::~JSONValue ************************* */

JSONValue::~JSONValue ()
{
  if (m_value_type == JSONValueType::Array)
    {
      for (auto it : *(reinterpret_cast<value_array_t *> (m_data_ptr)))
        delete it;
    }
  else if (m_value_type == JSONValueType::Object)
    {
      for (auto it : *(reinterpret_cast<value_object_t *> (m_data_ptr)))
        delete it.second;
    }

  if (m_data_ptr)
    {
      switch (m_value_type)
        {

        case JSONValueType::Number:
          delete reinterpret_cast<float*>(m_data_ptr);
          break;

        case JSONValueType::String:
          delete reinterpret_cast<std::string*>(m_data_ptr);
          break;

        case JSONValueType::Boolean:
          delete reinterpret_cast<bool*>(m_data_ptr);
          break;

        case JSONValueType::Object:
          delete reinterpret_cast<value_object_t*>(m_data_ptr);
          break;

        case JSONValueType::Array:
          delete reinterpret_cast<value_array_t*>(m_data_ptr);
          break;

        default:
          break;

        }
    }
}

/* ************************** JSONValue::is_valid ************************** */

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
    return *(reinterpret_cast<std::string *> (m_data_ptr));
}

/* ************************* JSONValue::as_integer ************************* */

int
JSONValue::as_integer () const
{
  if (m_value_type != JSONValueType::Number)
    throw std::runtime_error ("Not a number");
  else
    return std::nearbyintf (*(reinterpret_cast<float *> (m_data_ptr)));
}

/* ************************** JSONValue::as_float ************************** */

float
JSONValue::as_float () const
{
  if (m_value_type != JSONValueType::Number)
    throw std::runtime_error ("Not a number");
  else
    return *(reinterpret_cast<float *> (m_data_ptr));
}

/* ************************* JSONValue::as_boolean ************************* */

bool
JSONValue::as_boolean () const
{
  if (m_value_type != JSONValueType::Boolean)
    throw std::runtime_error ("Not a boolean");
  else
    return *(reinterpret_cast<bool *> (m_data_ptr));
}

/* ************************** JSONValue::as_array ************************** */

JSONValue *
JSONValue::as_array (int index) const
{
  if (m_value_type != JSONValueType::Array)
    throw std::runtime_error ("Not an array");
  else if (index >= reinterpret_cast<value_array_t *> (m_data_ptr)->size ())
    throw std::out_of_range ("Index is out of range");
  else
    return reinterpret_cast<value_array_t *> (m_data_ptr)->at (index);
}

/* **************************** JSONValue::line **************************** */

int
JSONValue::line () const
{
  return m_line;
}

/* *********************** JSONValue::object_key_size ********************** */

size_t
JSONValue::object_key_size (const std::string &key) const
{
  if (m_value_type != JSONValueType::Object)
    throw std::runtime_error ("Not an object");
  else
    return reinterpret_cast<value_object_t *> (m_data_ptr)->count (key);
}

/* ************************** JSONValue::as_object ************************* */

JSONValue *
JSONValue::as_object (const std::string &key, size_t index) const
{
  std::pair<value_object_t::iterator, value_object_t::iterator> range;
  value_object_t::iterator it;

  if (m_value_type != JSONValueType::Object)
    throw std::runtime_error ("Not an object");
  else if (index >= object_key_size (key))
    return nullptr;
  else
    {
      range = (reinterpret_cast<value_object_t *> (m_data_ptr))
                  ->equal_range (key);
      it = range.first;
      if (index)
        for (auto i = 0; i < index; i++, it++)
          {
          }
      return it->second;
    }
}

/* *********************** JSONValue::add_array_entry ********************** */

void
JSONValue::add_array_entry (JSONValue *val)
{
  if (m_value_type != JSONValueType::Array)
    throw std::runtime_error ("Not an array");

  reinterpret_cast<value_array_t *> (m_data_ptr)->emplace_back (val);
  auto it = --((reinterpret_cast<value_array_t *> (m_data_ptr))->end ());
  (*it)->set_parent (this);
}

/* ********************** JSONValue::add_object_entry ********************** */

void
JSONValue::add_object_entry (const std::string &key, JSONValue *val)
{
  if (m_value_type != JSONValueType::Object)
    throw std::runtime_error ("Not an object");

  auto it
      = (reinterpret_cast<value_object_t *> (m_data_ptr))->emplace (key, val);
  it->second->set_parent (this);
}

/* ************************* JSONValue::array_size ************************* */

size_t
JSONValue::array_size () const
{
  if (m_value_type != JSONValueType::Array)
    throw std::runtime_error ("Not an array");
  else
    return (reinterpret_cast<value_array_t *> (m_data_ptr))->size ();
}

/* **************************** JSONValue::print *************************** */

std::ostream &
JSONValue::print (std::ostream &stream, int tab) const
{
  if (tab > 0)
    {
      for (auto i = 0; i < tab; i++)
        stream << "  ";
    }

  switch (m_value_type)
    {

    case JSONValueType::Null:
      stream << "null";
      break;

    case JSONValueType::Number:
      stream << as_float ();
      break;

    case JSONValueType::String:
      stream << "\"" << as_string () << "\"";
      break;

    case JSONValueType::Boolean:
      stream << (as_boolean () ? "true" : "false");
      break;

    case JSONValueType::Array:
      stream << "[" << std::endl;
      for (size_t i = 0;
           i < (reinterpret_cast<value_array_t *> (m_data_ptr))->size (); i++)
        {
          ((reinterpret_cast<value_array_t *> (m_data_ptr))->at (i))
              ->print (stream, tab + 1);
          if (i
              < (reinterpret_cast<value_array_t *> (m_data_ptr))->size () - 1)
            stream << ",";
          stream << std::endl;
        }
      stream << "]" << std::endl;
      break;

    case JSONValueType::Object:
      stream << "{" << std::endl;
      for (auto it : *(reinterpret_cast<value_object_t *> (m_data_ptr)))
        {
          if (tab > 0)
            {
              for (auto i = 0; i < tab + 1; i++)
                stream << "  ";
            }
          stream << "\"" << it.first << "\" : ";
          it.second->print (stream, tab);
          stream << ",";
          stream << std::endl;
        }
      stream << "}" << std::endl;
      break;
    }

  return stream;
}

/* ****************************** make_object ****************************** */

JSONValue *
JSONValue::make_object (int line)
{
  JSONValue *val = new JSONValue (line);
  if (val == nullptr)
    return nullptr;
  val->m_data_ptr = new value_object_t ();
  val->m_value_type = JSONValueType::Object;

  return val;
}

/* ******************************* make_array ****************************** */

JSONValue *
JSONValue::make_array (int line)
{
  JSONValue *val = new JSONValue (line);
  if (val == nullptr)
    return nullptr;
  val->m_data_ptr = new value_array_t ();
  val->m_value_type = JSONValueType::Array;

  return val;
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const JSONValue &val)
{
  return val.print (stream, 0);
}

/* *************************** JSONValue::parent *************************** */

JSONValue *
JSONValue::parent () const
{
  return m_parent;
}

std::ostream &
JSONValue::print_ancestor (std::ostream &stream) const
{
  if (m_parent->is_valid ())
    m_parent->print_ancestor (stream);
  else
    stream << "<root>";

  stream << "<-";

  switch (m_value_type)
    {

    case JSONValueType::Invalid:
      stream << "(<invalid value>)";
      break;

    case JSONValueType::Null:
      stream << "(null)";
      break;

    case JSONValueType::Number:
      stream << "(number)";
      break;

    case JSONValueType::String:
      stream << "(string)";
      break;

    case JSONValueType::Boolean:
      stream << "(boolean)";
      break;

    case JSONValueType::Array:
      stream << "(array)";
      break;

    case JSONValueType::Object:
      stream << "(object)";
      break;
    }
  return stream;
}

}
