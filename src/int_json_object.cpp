/**
 * \file int_json_object.cpp
 */

#include "int_json_object.h"

namespace litejson
{

/*****************  int_json_object::int_json_object  *****************/

  int_json_object::int_json_object()
  {
    // ctor
  }

/************************  int_json_object::at  ***********************/

  json_value* int_json_object::at(const std::string& key)
  {
    auto it = m_values.find(key);

    if (it != m_values.end())
      return &(it->second);
    else
      return nullptr;
  }

/***********************  int_json_object::size  **********************/

  size_t int_json_object::size()
  {
    return m_values.size();
  }

  void int_json_object::add_entry(const std::string& key, json_value& val)
  {
    m_values.emplace(key, val);
  }

}