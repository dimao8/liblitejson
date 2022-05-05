#include "int_json_array.h"

#include <stdexcept>

namespace litejson
{

/**********  int_json_array::int_json_array  **********/

  int_json_array::int_json_array()
  {
    // ctor
  }

/****************  int_json_array::at  ****************/

  json_value* int_json_array::at(size_t n)
  {
    json_value* it;

    try
      {
        it = &(m_values.at(n));
      }
    catch (const std::out_of_range& oor)
      {
        return nullptr;
      }

    return it;
  }

/***************  int_json_array::size  ***************/

  size_t int_json_array::size()
  {
    return m_values.size();
  }

}