
#include "jsonobjectvalue.h"

#include <iostream>
#include <memory>

namespace litejson
{

/* ******************** JSONObjectValue::JSONObjectValue ******************* */

JSONObjectValue::JSONObjectValue (int line) : JSONValue (line)
{
  //
}

/* ******************* JSONObjectValue::~JSONObjectValue ******************* */

JSONObjectValue::~JSONObjectValue ()
{
  //
}

/* ******************* JSONObjectValue::add_object_entry ******************* */

void
JSONObjectValue::add_object_entry (const std::string &key,
                                   const std::shared_ptr<JSONValue> &val)
{
  auto it = m_value.emplace (key, val);
  val->set_parent (shared_from_this ());
}

/* ************************ JSONObjectValue::is_null *********************** */

bool
JSONObjectValue::is_null () const
{
  return false;
}

/* *********************** JSONObjectValue::is_object ********************** */

bool
JSONObjectValue::is_object () const
{
  return true;
}

/* *********************** JSONObjectValue::as_object ********************** */

std::shared_ptr<const JSONValue>
JSONObjectValue::as_object (const std::string &key, size_t index) const
{
  std::pair<ObjectValue::const_iterator, ObjectValue::const_iterator> range;
  ObjectValue::const_iterator it;

  if (index >= object_key_size (key))
    return nullptr;
  else
    {
      range = m_value.equal_range (key);
      it = range.first;
      if (index)
        for (auto i = 0; i < index; i++, it++)
          {
          }
      return it->second;
    }
}

/* *********************** JSONObjectValue::as_object ********************** */

std::shared_ptr<JSONValue>
JSONObjectValue::as_object (const std::string &key, size_t index)
{
  std::pair<ObjectValue::const_iterator, ObjectValue::const_iterator> range;
  ObjectValue::const_iterator it;

  if (index >= object_key_size (key))
    return nullptr;
  else
    {
      range = m_value.equal_range (key);
      it = range.first;
      if (index)
        for (auto i = 0; i < index; i++, it++)
          {
          }
      return it->second;
    }
}

/* ******************** JSONObjectValue::object_key_size ******************* */

size_t
JSONObjectValue::object_key_size (const std::string &key) const
{
  return m_value.count (key);
}

/* ********************* JSONObjectValue::remove_entry ********************* */

bool
JSONObjectValue::remove_entry (const std::string &key, size_t index)
{
  std::pair<ObjectValue::const_iterator, ObjectValue::const_iterator> range;
  ObjectValue::const_iterator it;

  if (index >= object_key_size (key))
    return false;
  else
    {
      range = m_value.equal_range (key);
      it = range.first;
      if (index)
        for (auto i = 0; i < index; i++, it++)
          {
          }
      m_value.erase (it);
      return true;
    }
}

/* ************************* JSONObjectValue::print ************************ */

void
JSONObjectValue::print (std::ostream &stream, size_t indent) const
{
  std::string filler (indent + 2, ' ');
  stream << "{" << std::endl;

  auto sz = m_value.size ();
  size_t i = 0;
  if (sz > 0)
    {
      for (auto it = m_value.cbegin (); it != m_value.cend (); it++, i++)
        {
          stream << filler << "\"" << it->first << "\" : ";
          it->second->print (stream, indent + 2);
          if (i != sz - 1)
            stream << ",";
          stream << std::endl;
        }
    }
  stream << filler.substr (0, indent) << "}";
}

}
