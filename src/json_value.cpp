/**
 * \file json_value.cpp
 */

#include <json_value.h>

#include <stdexcept>
#include <cmath>

namespace litejson
{

/*******************  json_value::json_value  *******************/

  json_value::json_value()
  : m_value_type(t_null),
    m_data_smartptr(nullptr, [&](void* p)
    {
      switch (m_value_type)
        {

        case t_string:
          delete reinterpret_cast<std::string*>(p);
          break;

        case t_boolean:
          delete reinterpret_cast<bool*>(p);
          break;

        case t_number:
          delete reinterpret_cast<float*>(p);
          break;

        case t_array:
          for (auto it : *(reinterpret_cast<value_array_t*>(p)))
            delete it;
          delete reinterpret_cast<value_array_t*>(p);
          break;

        case t_object:
          for (auto it : *(reinterpret_cast<value_object_t*>(p)))
            delete it.second;
          delete reinterpret_cast<value_object_t*>(p);
          break;

        default:
          break;

        }
    })
  {
    //ctor
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(float f)
  : m_value_type(t_number),
    m_data_smartptr(new float(f), [&](void* p)
    {
      switch (m_value_type)
        {

        case t_string:
          delete reinterpret_cast<std::string*>(p);
          break;

        case t_boolean:
          delete reinterpret_cast<bool*>(p);
          break;

        case t_number:
          delete reinterpret_cast<float*>(p);
          break;

        case t_array:
          for (auto it : *(reinterpret_cast<value_array_t*>(p)))
            delete it;
          delete reinterpret_cast<value_array_t*>(p);
          break;

        case t_object:
          for (auto it : *(reinterpret_cast<value_object_t*>(p)))
            delete it.second;
          delete reinterpret_cast<value_object_t*>(p);
          break;

        default:
          break;

        }
    })
  {
    // ctor
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(bool b)
  : m_value_type(t_boolean),
    m_data_smartptr(new bool(b), [&](void* p)
    {
      switch (m_value_type)
        {

        case t_string:
          delete reinterpret_cast<std::string*>(p);
          break;

        case t_boolean:
          delete reinterpret_cast<bool*>(p);
          break;

        case t_number:
          delete reinterpret_cast<float*>(p);
          break;

        case t_array:
          for (auto it : *(reinterpret_cast<value_array_t*>(p)))
            delete it;
          delete reinterpret_cast<value_array_t*>(p);
          break;

        case t_object:
          for (auto it : *(reinterpret_cast<value_object_t*>(p)))
            delete it.second;
          delete reinterpret_cast<value_object_t*>(p);
          break;

        default:
          break;

        }
    })
  {
    // ctor
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(const std::string& str)
  : m_value_type(t_string),
    m_data_smartptr(new std::string(str), [&](void* p)
    {
      switch (m_value_type)
        {

        case t_string:
          delete reinterpret_cast<std::string*>(p);
          break;

        case t_boolean:
          delete reinterpret_cast<bool*>(p);
          break;

        case t_number:
          delete reinterpret_cast<float*>(p);
          break;

        case t_array:
          for (auto it : *(reinterpret_cast<value_array_t*>(p)))
            delete it;
          delete reinterpret_cast<value_array_t*>(p);
          break;

        case t_object:
          for (auto it : *(reinterpret_cast<value_object_t*>(p)))
            delete it.second;
          delete reinterpret_cast<value_object_t*>(p);
          break;

        default:
          break;

        }
    })
  {
    // ctor
  }

/*******************  json_value::~json_value  ******************/

  json_value::~json_value()
  {
    // dtor
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(const json_value& other)
  : m_value_type(other.m_value_type)
  {
    m_data_smartptr = other.m_data_smartptr;
  }

/********************  json_value::operator=  *******************/

  json_value& json_value::operator=(const json_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    
    m_data_smartptr = other.m_data_smartptr;
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
        return *(std::static_pointer_cast<std::string>(m_data_smartptr));
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
        return nearbyint(*(std::static_pointer_cast<float>(m_data_smartptr)));
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
        return *(std::static_pointer_cast<float>(m_data_smartptr));
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
        return *(std::static_pointer_cast<bool>(m_data_smartptr));
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
        if (index < std::static_pointer_cast<value_array_t>(m_data_smartptr)->size())
          return std::static_pointer_cast<value_array_t>(m_data_smartptr)->at(index);
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
        auto it = std::static_pointer_cast<value_object_t>(m_data_smartptr)->find(key);
        if (it != std::static_pointer_cast<value_object_t>(m_data_smartptr)->end())
          return it->second;
        else
          return nullptr;
      }
  }

/**********************  json_value::print  *********************/

  void json_value::print(std::ostream& stream)
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
        sz = std::static_pointer_cast<value_array_t>(m_data_smartptr)->size();
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
        sz = std::static_pointer_cast<value_object_t>(m_data_smartptr)->size();
        if (sz != 0)
          {
            for (it = std::static_pointer_cast<value_object_t>(m_data_smartptr)->begin();
                 it != std::static_pointer_cast<value_object_t>(m_data_smartptr)->end(); it++)
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

/*****************  json_value::add_array_entry  ****************/

  void json_value::add_array_entry(json_value* val)
  {
    if (m_value_type == t_null)
      {
        m_data_smartptr = std::make_shared<value_array_t>();
      }
    else if (m_value_type != t_array)
      {
        m_data_smartptr = nullptr;
        m_data_smartptr = std::make_shared<value_array_t>();
      }
    
    std::static_pointer_cast<value_array_t>(m_data_smartptr)->push_back(val);
  }

/*****************  json_value::add_object_entry  ***************/

  void json_value::add_object_entry(const std::string& key, json_value* val)
  {
    if (m_value_type == t_null)
      {
        m_data_smartptr = std::make_shared<value_object_t>();
      }
    else if (m_value_type != t_object)
      {
        m_data_smartptr = nullptr;
        m_data_smartptr = std::make_shared<value_object_t>();
      }
    
    std::static_pointer_cast<value_object_t>(m_data_smartptr)->at(key) = val;
  }

}
