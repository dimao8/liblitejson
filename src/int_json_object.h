/**
 * \file int_json_object.h
 */

#ifndef INT_JSON_OBJECT_H
#define INT_JSON_OBJECT_H

#include <json_value.h>

#include <map>

#include <json_object.h>

namespace litejson
{

  /**
   * Internal private JSON Object value class
   */
  class int_json_object
  {

  protected:

    friend void json_object_value::print();

    std::map<std::string, json_value> m_values;       //!< JSON values in the object

  public:

    /**
     * Default constructor
     * 
     */
    int_json_object();

    // Block copy constructor
    int_json_object(const int_json_object& other) = delete;

    // Block copy constructor
    int_json_object& operator=(const int_json_object& other) = delete;

    /**
     * Get value from object by name
     * 
     * \param [in] key -- Key of the value
     */
    json_value* at(const std::string& key);

    /**
     * Return number of children values.
     */
    size_t size();

    void add_entry(const std::string& key, json_value& val);

  };

}

#endif // INT_JSON_OBJJECT_H

