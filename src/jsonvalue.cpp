///
/// \file jsonvalue.cpp
///

#include "jsonarrayvalue.h"
#include "jsonbooleanvalue.h"
#include "jsonnumbervalue.h"
#include "jsonobjectvalue.h"
#include "jsonstringvalue.h"

#include <litejson/jsonvalue.h>

#include <cmath>
#include <iostream>
#include <memory>
#include <optional>

namespace litejson
{

/* ************************* JSONValue::set_parent **************************/

void
JSONValue::set_parent (const std::shared_ptr<JSONValue> &parent)
{
  m_parent = parent;
}

/* ************************** JSONValue::JSONValue ************************* */

JSONValue::JSONValue (int line) : m_line (line)
{
  //
}

/* ************************* JSONValue::~JSONValue ************************* */

JSONValue::~JSONValue ()
{
  //
}

/* *************************** JSONValue::is_null ************************** */

bool
JSONValue::is_null () const
{
  return true;
}

/* ************************* JSONValue::is_boolean ************************* */

bool
JSONValue::is_boolean () const
{
  return false;
}

/* ************************** JSONValue::is_number ************************* */

bool
JSONValue::is_number () const
{
  return false;
}

/* ************************** JSONValue::is_string ************************* */

bool
JSONValue::is_string () const
{
  return false;
}

/* ************************** JSONValue::is_array ************************** */

bool
JSONValue::is_array () const
{
  return false;
}

/* ************************** JSONValue::is_object ************************* */

bool
JSONValue::is_object () const
{
  return false;
}

/* ************************** JSONValue::as_string ************************* */

std::optional<const std::string>
JSONValue::as_string () const
{
  return std::nullopt;
}

/* ************************* JSONValue::as_integer ************************* */

std::optional<int>
JSONValue::as_integer () const
{
  return std::nullopt;
}

/* ************************** JSONValue::as_float ************************** */

std::optional<float>
JSONValue::as_float () const
{
  return std::nullopt;
}

/* ************************* JSONValue::as_boolean ************************* */

std::optional<bool>
JSONValue::as_boolean () const
{
  return std::nullopt;
}

/* ************************** JSONValue::as_array ************************** */

std::shared_ptr<const JSONValue>
JSONValue::as_array (size_t index) const
{
  return nullptr;
}

/* ************************** JSONValue::as_array ************************** */

std::shared_ptr<JSONValue>
JSONValue::as_array (size_t index)
{
  return nullptr;
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
  return 0;
}

/* ************************** JSONValue::as_object ************************* */

std::shared_ptr<const JSONValue>
JSONValue::as_object (const std::string &key, size_t index) const
{
  return nullptr;
}

/* ************************** JSONValue::as_object ************************* */

std::shared_ptr<JSONValue>
JSONValue::as_object (const std::string &key, size_t index)
{
  return nullptr;
}

/* *********************** JSONValue::add_array_entry ********************** */

void
JSONValue::add_array_entry (const std::shared_ptr<JSONValue> &val)
{
  //
}

/* ********************** JSONValue::add_object_entry ********************** */

void
JSONValue::add_object_entry (const std::string &key,
                             const std::shared_ptr<JSONValue> &val)
{
  //
}

/* ************************* JSONValue::array_size ************************* */

size_t
JSONValue::array_size () const
{
  return 0;
}

/* *************************** JSONValue::parent *************************** */

const std::weak_ptr<JSONValue> &
JSONValue::parent () const
{
  return m_parent;
}

/* ************************** JSONValue::make_null ************************* */

std::shared_ptr<JSONValue>
JSONValue::make_null (int line)
{
  return std::make_shared<JSONValue> (line);
}

/* ************************ JSONValue::make_boolean ************************ */

std::shared_ptr<JSONValue>
JSONValue::make_boolean (int line, bool b)
{
  return std::make_shared<JSONBooleanValue> (line, b);
}

/* ************************* JSONValue::make_string ************************ */

std::shared_ptr<JSONValue>
JSONValue::make_string (int line, const std::string &s)
{
  return std::make_shared<JSONStringValue> (line, s);
}

/* ************************* JSONValue::make_number ************************ */

std::shared_ptr<JSONValue>
JSONValue::make_number (int line, float f)
{
  return std::make_shared<JSONNumberValue> (line, f);
}

/* ************************* JSONValue::make_object ************************ */

std::shared_ptr<JSONValue>
JSONValue::make_object (int line)
{
  return std::make_shared<JSONObjectValue> (line);
}

/* ************************* JSONValue::make_array ************************* */

std::shared_ptr<JSONValue>
JSONValue::make_array (int line)
{
  return std::make_shared<JSONArrayValue> (line);
}

/* **************************** JSONValue::print *************************** */

void
JSONValue::print (std::ostream &stream, size_t indent) const
{
  stream << "null";
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const JSONValue &val)
{
  val.print (stream, 0);
  return stream;
}

}
