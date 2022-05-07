/**
 * \file json_value.cpp
 */

#include <json_value.h>

#include <stdexcept>
#include <iostream>

namespace litejson
{

/*******************  json_value::json_value  *******************/

  json_value::json_value()
  : m_value_type(t_null)
  {
    //ctor
  }

/*******************  json_value::~json_value  ******************/

  json_value::~json_value()
  {
    //dtor
  }

/*******************  json_value::json_value  *******************/

  json_value::json_value(const json_value& other)
  : m_value_type(other.m_value_type)
  {
    //copy ctor
  }

/********************  json_value::operator=  *******************/

  json_value& json_value::operator=(const json_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    //assignment operator
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

/*********************  json_value::as_array  *******************/

  json_array_value& json_value::as_array()
  {
    throw std::logic_error("JSON value is not an array");
  }

/********************  json_value::as_object  *******************/

  json_object_value& json_value::as_object()
  {
    throw std::logic_error("JSON value is not an object");
  }

/*******************  json_value::as_integer  *******************/

  int json_value::as_integer()
  {
    throw std::logic_error("JSON value is not a number");
  }

/*********************  json_value::as_float  *******************/

  float json_value::as_float()
  {
    throw std::logic_error("JSON value is not a number");
  }

/********************  json_value::as_string  *******************/

  const std::string& json_value::as_string()
  {
    throw std::logic_error("JSON value is not a string");
  }

/*******************  json_value::as_boolean  *******************/

  bool json_value::as_boolean()
  {
    throw std::logic_error("JSON value is not a boolean");
  }

  void json_value::print()
  {
    std::cout << "null";
  }

/***********  json_boolean_value::json_boolean_value  ***********/

  json_boolean_value::json_boolean_value()
  : json_value(),
    m_data(false)
  {
    m_value_type = t_boolean;
  }

/***********  json_boolean_value::json_boolean_value  ***********/

  json_boolean_value::json_boolean_value(const json_boolean_value& other)
  : json_value(),
    m_data(other.m_data)
  {
    m_value_type = t_boolean;
  }

/***********  json_boolean_value::json_boolean_value  ***********/

  json_boolean_value::json_boolean_value(bool b)
  : json_value(),
    m_data(b)
  {
    m_value_type = t_boolean;
  }

/****************  json_boolean_value::operator=  ***************/

  json_boolean_value& json_boolean_value::operator=(const json_boolean_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    //assignment operator
    return *this;
  }

/****************  json_boolean_value::operator=  ***************/

  json_boolean_value& json_boolean_value::operator=(bool b)
  {
    m_data = b;
    return *this;
  }

/***************  json_boolean_value::as_boolean  ***************/

  bool json_boolean_value::as_boolean()
  {
    return m_data;
  }

/******************  json_boolean_value::print  *****************/

  void json_boolean_value::print()
  {
    if (m_data)
      std::cout << "true";
    else
      std::cout << "false";
  }

/***********  json_numeric_value::json_numeric_value  ***********/

  json_numeric_value::json_numeric_value()
  : json_value(),
    m_f_data(0.0f),
    m_i_data(0)
  {
    m_value_type = t_number;
  }

/***********  json_numeric_value::json_numeric_value  ***********/

  json_numeric_value::json_numeric_value(const json_numeric_value& other)
  : json_value(),
    m_i_data(other.m_i_data),
    m_f_data(other.m_f_data)
  {
    m_value_type = t_number;
  }

/***********  json_numeric_value::json_numeric_value  ***********/

  json_numeric_value::json_numeric_value(float f)
  : json_value(),
    m_i_data(f),
    m_f_data(f)
  {
    m_value_type = t_number;
  }

/****************  json_numeric_value::operator=  ***************/

  json_numeric_value& json_numeric_value::operator=(const json_numeric_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    //assignment operator
    return *this;
  }

/****************  json_numeric_value::operator=  ***************/

  json_numeric_value& json_numeric_value::operator=(float f)
  {
    m_f_data = f;
    m_i_data = f;
    return *this;
  }

/****************  json_numeric_value::operator=  ***************/

  json_numeric_value& json_numeric_value::operator=(int i)
  {
    m_f_data = i;
    m_i_data = i;
    return *this;
  }

/***************  json_boolean_value::as_integer  ***************/

  int json_numeric_value::as_integer()
  {
    return m_i_data;
  }

/****************  json_boolean_value::as_float  ****************/

  float json_numeric_value::as_float()
  {
    return m_f_data;
  }

/******************  json_boolean_value::print  *****************/

  void json_numeric_value::print()
  {
    std::cout << m_f_data;
  }

/************  json_string_value::json_string_value  ************/

  json_string_value::json_string_value()
  : json_value(),
    m_data()
  {
    m_value_type = t_string;
  }

/************  json_string_value::json_string_value  ************/

  json_string_value::json_string_value(const json_string_value& other)
  : json_value(),
    m_data(other.m_data)
  {
    m_value_type = t_string;
  }

/************  json_string_value::json_string_value  ************/

  json_string_value::json_string_value(const std::string& str)
  : json_value(),
    m_data(str)
  {
    m_value_type = t_string;
  }

/****************  json_string_value::operator=  ****************/

  json_string_value& json_string_value::operator=(const json_string_value& other)
  {
    if (this == &other) return *this; // handle self assignment
    //assignment operator
    return *this;
  }

/****************  json_string_value::operator=  ****************/

  json_string_value& json_string_value::operator=(const std::string& str)
  {
    m_data = str;
    return *this;
  }

/****************  json_string_value::as_string  ****************/

  const std::string& json_string_value::as_string()
  {
    return m_data;
  }

  void json_string_value::print()
  {
    std::cout << "\"" << m_data << "\"";
  }
}
