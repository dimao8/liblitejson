#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include <json_value.h>

namespace litejson
{

  class int_json_object;

  /**
   * JSON object value class
   * 
   */
  class json_object_value : public json_value
  {

    friend class int_json_object;

  protected:

    int_json_object* m_internal;

  public:

    /**
     * Default constructor
     */
    json_object_value();

    /**
     * Copy constructor
     */
    json_object_value(const json_object_value& other);

    /**
     * Assignment operator
     */
    json_object_value& operator=(const json_object_value& other);

    /**
     * Equal operator
     */
    bool operator==(const json_object_value& other);

    /**
     * Get JSON value from object by key
     * 
     * \param [in] key -- Key of the value
     * \return JSON value or empty_object_value if not found
     */
    json_value& at(const std::string& key);

    /**
     * Return number of children values.
     */
    size_t size();

  };

  extern json_object_value empty_object_value;

}

#endif // JSON_OBJECT_H
