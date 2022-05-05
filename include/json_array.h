#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <json_value.h>

namespace litejson
{

  class int_json_array;
  
  class json_array_value : public json_value
  {

  protected:

    int_json_array* m_internal;
    
  public:

    /**
     * Default constructor
     */
    json_array_value();

    /**
     * Copy constructor
     */
    json_array_value(const json_array_value& other);

    /**
     * Copy assignment operator
     */
    json_array_value& operator=(const json_array_value& other);

    /**
     * Equal operator
     */
    bool operator==(const json_array_value& other);

    /**
     * Get value from array by index
     * 
     * \param [in] index -- Index of the element
     * \return Return value by index or empty_array_value.
     */
    json_value& json_array_value::at(size_t index);

    /**
     * Get size of the value array
     */
    size_t size();

  };

  extern json_array_value empty_array_value;

}

#endif // JSON_ARRAY_H
