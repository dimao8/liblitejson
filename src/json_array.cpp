#include <json_array.h>

#include "int_json_array.h"

namespace litejson
{

  json_array_value empty_array_value;

/**********  json_array_value::json_array_value  **********/
  
  json_array_value::json_array_value()
  : json_value()
  {
    m_value_type = t_array;
    m_internal = new int_json_array();
  }

/**********  json_array_value::json_array_value  **********/
  
  json_array_value::json_array_value(const json_array_value& other)
  : json_value()
  {
    m_value_type = t_array;
    m_internal = other.m_internal;
  }

/**************  json_array_value::operator=  *************/

  json_array_value& json_array_value::operator=(const json_array_value& other)
  {
    if (&other == this)
      return *this;
    else
      {
        m_internal = other.m_internal;
        return *this;
      }
  }

/**************  json_array_value::operator==  ************/

  bool json_array_value::operator==(const json_array_value& other)
  {
    return other.m_internal == m_internal;
  }

/******************  json_array_value::at  ****************/

  json_value& json_array_value::at(size_t index)
  {
    json_value* val;

    if (m_internal == nullptr)
      return empty_array_value;
    else
      {
        val = m_internal->at(index);
        if (val == nullptr)
          return empty_array_value;
        else
          return *val;
      }
  }

/*****************  json_array_value::size  ***************/

  size_t json_array_value::size()
  {
    if (m_internal == nullptr)
      return 0;
    else
      return m_internal->size();
  }

}
