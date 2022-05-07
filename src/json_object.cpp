/**
 * \file json_object.cpp
 */

#include <json_object.h>

#include <iostream>

#include "int_json_object.h"

namespace litejson
{

  json_object_value empty_object_value;

/**************  json_object_value::json_object_value  **************/

  json_object_value::json_object_value()
  : json_value()
  {
    m_value_type = t_object;
    m_internal = new int_json_object();
  }

/**************  json_object_value::json_object_value  **************/

  json_object_value::json_object_value(const json_object_value& other)
  : json_value()
  {
    m_value_type = t_object;
    m_internal = other.m_internal;
  }

/**************  json_object_value::~json_object_value  *************/

  json_object_value::~json_object_value()
  {
    if (m_internal != nullptr)
      delete m_internal;
  }

/******************  json_object_value::operator=  ******************/

  json_object_value& json_object_value::operator=(const json_object_value& other)
  {
    if (this == &other)
      return *this;

    m_value_type = other.m_value_type;

    return *this;
  }

/******************  json_object_value::operator==  *****************/

  bool json_object_value::operator==(const json_object_value& other)
  {
    return other.m_internal == m_internal;
  }

/******************  json_object_value::operator!=  *****************/

  bool json_object_value::operator!=(const json_object_value& other)
  {
    return other.m_internal != m_internal;
  }

/**********************  json_object_value::at  *********************/

  json_value& json_object_value::at(const std::string& key)
  {
    json_value* val;

    if (m_internal == nullptr)
      return empty_object_value;
    else
      {
        val = m_internal->at(key);
        if (val == nullptr)
          return empty_object_value;
        else
          return *val;
      }
  }

/*********************  json_object_value::size  ********************/

  size_t json_object_value::size()
  {
    if (m_internal == nullptr)
      return 0;
    else
      return m_internal->size();
  }

  void json_object_value::add_entry(const std::string& key, json_value& val)
  {
    m_internal->add_entry(key, val);
  }

  void json_object_value::print()
  {
    std::cout << "{" << std::endl;

    if (m_internal->size() != 0)
      {
        for (auto it : m_internal->m_values)
          {
            std::cout << "\"" << it.first << "\" : ";
            it.second.print();
            std::cout << "," << std::endl;
          }
      }

    std::cout << "}" << std::endl;
  }

}