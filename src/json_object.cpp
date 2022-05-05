/**
 * \file json_object.cpp
 */

#include <json_object.h>

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

}