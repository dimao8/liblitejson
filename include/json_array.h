/**
 * \file json_array.h
 */

#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include <json_value.h>

namespace litejson
{

  class int_json_array;

  /**
   * \addtogroup json_value_classes
   * \{
   */
  
  /**
   * JSON array value class
   * 
   * This class incapsulate array value from a JSON file.
   * The object of this class contains the array of the json_value entries.
   * 
   * Every entry can be extracted by using at() method. The at() method
   * returns the reference of the json_value class object or empty_array_object
   * if an index is out of bounds. You can compare its value with an
   * empty_array_object to determine result of the extraction operation.
   * 
   * There is also size() function that return the number of the entries
   * in the array. It returns 0 if has been called on empty array.
   */
  class json_array_value : public json_value
  {

  protected:

    int_json_array* m_internal;                                       //!< Private json array value
    
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
    json_value& at(size_t index);

    /**
     * Get size of the value array
     */
    size_t size();

  };

  /**
   * \}
   */

  /**
   * Default value for empty array.
   */
  extern json_array_value empty_array_value;

}

#endif // JSON_ARRAY_H
