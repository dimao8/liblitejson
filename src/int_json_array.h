/**
 * \file int_json_array.h
 */

#ifndef INT_JSON_ARRAY_H
#define INT_JSON_ARRAY_H

#include <json_value.h>

#include <vector>

namespace litejson
{

  /**
   * Internal private JSON Array class
   */
  class int_json_array
  {

  protected:

    std::vector<json_value> m_values;       //!< JSON values in the object

  public:

    /**
     * Default constructor
     * 
     */
    int_json_array();

    // Block copy constructor
    int_json_array(const int_json_array& other) = delete;

    // Block copy constructor
    int_json_array& operator=(const int_json_array& other) = delete;

    /**
     * Get value from object by name
     * 
     * \param [in] key -- Key of the value
     */
    json_value* at(size_t n);

    /**
     * Add new value to the array
     * 
     * \param [in] val -- New value to add
     */
    void add(json_value& val);

    /**
     * Return number of children values.
     */
    size_t size();

  };

}

#endif // INT_JSON_ARRAY_H
