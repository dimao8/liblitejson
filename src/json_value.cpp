/**
 * \file json_value.cpp
 */

#include <json_value.h>

#include <stdexcept>
#include <iostream>
#include <cmath>

namespace litejson
{

/*******************  json_value::json_value  *******************/

  json_value::json_value()
  : m_value_type(t_null),
    m_data(nullptr)
  {
    //ctor
  }

/*******************  json_value::~json_value  ******************/

  json_value::~json_value()
  {
    if (m_data != nullptr)
      {
        if (m_value_type == t_array)
          {
            for (auto it : *(reinterpret_cast<value_array_t*>(m_data)))
              delete it;
          }
        else if (m_value_type == t_object)
          {
            for (auto it : *(reinterpret_cast<value_object_t*>(m_data)))
              delete it.second;
          }
        delete m_data;
      }
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(const json_value& other)
  : m_value_type(other.m_value_type),
    m_data(other.m_data)
  {
    //copy ctor
  }

/********************  json_value::operator=  *******************/

  json_value& json_value::operator=(const json_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    
    if (m_data != nullptr)
      delete m_data;
    m_data = other.m_data;
    m_value_type = other.m_value_type;
    return *this;
  }

/*********************  json_value::is_null  ********************/

  bool json_value::is_null() const
  {
    return m_value_type == t_null;
  }

/********************  json_value::is_boolean  ******************/

  bool json_value::is_boolean() const
  {
    return m_value_type == t_boolean;
  }

/********************  json_value::is_number  *******************/

  bool json_value::is_number() const
  {
    return m_value_type == t_number;
  }

/********************  json_value::is_string  *******************/

  bool json_value::is_string() const
  {
    return m_value_type == t_string;
  }

/*********************  json_value::is_array  *******************/

  bool json_value::is_array() const
  {
    return m_value_type == t_array;
  }

/********************  json_value::is_object  *******************/

  bool json_value::is_object() const
  {
    return m_value_type == t_object;
  }

/********************  json_value::as_string  *******************/

  const std::string& json_value::as_string()
  {
    if (m_value_type != t_string)
      {
        throw std::runtime_error("is not a string");
      }
    else
      {
        return *(reinterpret_cast<std::string*>(m_data));
      }
  }

/********************  json_value::as_integer  ******************/

  int json_value::as_integer()
  {
    if (m_value_type != t_number)
      {
        throw std::runtime_error("is not a number");
      }
    else
      {
        return nearbyint(*(reinterpret_cast<float*>(m_data)));
      }
  }

/*********************  json_value::as_float  *******************/

  float json_value::as_float()
  {
    if (m_value_type != t_number)
      {
        throw std::runtime_error("is not a number");
      }
    else
      {
        return *(reinterpret_cast<float*>(m_data));
      }
  }

/********************  json_value::as_boolean  ******************/

  bool json_value::as_boolean()
  {
    if (m_value_type != t_boolean)
      {
        throw std::runtime_error("is not a boolean");
      }
    else
      {
        return *(reinterpret_cast<bool*>(m_data));
      }
  }

/*********************  json_value::as_array  *******************/

  json_value* json_value::as_array(int index)
  {
    if (m_value_type != t_array)
      {
        throw std::runtime_error("is not an array");
      }
    else
      {
        if (index < reinterpret_cast<value_array_t*>(m_data)->size())
          return reinterpret_cast<value_array_t*>(m_data)->at(index);
        else
          return nullptr;
      }
  }

/********************  json_value::as_object  *******************/

  json_value* json_value::as_object(const std::string& key)
  {
    if (m_value_type != t_object)
      {
        throw std::runtime_error("is not an object");
      }
    else
      {
        auto it = reinterpret_cast<value_object_t*>(m_data)->find(key);
        if (it != reinterpret_cast<value_object_t*>(m_data)->end())
          return it->second;
        else
          return nullptr;
      }
  }

/**********************  json_value::print  *********************/

  void json_value::print(std::fstream& stream)
  {
    int sz;
    value_object_t::const_iterator it;

    switch (m_value_type)
      {

      case t_null:
        stream << "null";
        break;

      case t_boolean:
        stream << (as_boolean() ? "true" : "false");
        break;

      case t_number:
        stream << as_float();
        break;

      case t_string:
        stream << "\"" << as_float() << "\"";
        break;

      case t_array:
        stream << "[" << std::endl;
        sz = reinterpret_cast<value_array_t*>(m_data)->size();
        if (sz != 0)
          {
            for (int i = 0; i < sz; i++)
              {
                as_array(i)->print(stream);
                if (i != sz - 1)
                  stream << "," << std::endl;
                else
                  stream << std::endl;
              }
          }
        stream << "]" << std::endl;
        break;

      case t_object:
        stream << "{" << std::endl;
        sz = reinterpret_cast<value_object_t*>(m_data)->size();
        if (sz != 0)
          {
            for (it = reinterpret_cast<value_object_t*>(m_data)->begin();
                 it != reinterpret_cast<value_object_t*>(m_data)->end(); it++)
              {
                stream << "\"" << it->first << " : ";
                it->second->print(stream);
                stream << "," << std::endl;
              }
          }
        stream << "}" << std::endl;
        break;

      }
  }

}
