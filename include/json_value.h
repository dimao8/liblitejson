/**
 * \file json_value.h
 */

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>
#include <vector>
#include <map>
#include <fstream>

namespace litejson
{

  /**
   * \defgroup json_value_classes JSON value classes
   */

  /**
   * JSON Value class
   * JSON parser unit. Parse single JSON file and manage it.
   * \addtogroup json_value_classes
   * \{
   */
  class json_value
  {

  protected:

    /**
     * Value type
     */
    enum json_value_type_t
    {
      t_null,                                     //!< The value is null
      t_boolean,                                  //!< The value is boolean
      t_number,                                   //!< The value is number
      t_string,                                   //!< The value is string
      t_array,                                    //!< The value is value array
      t_object                                    //!< The value is object
    } m_value_type;

    typedef std::vector<json_value*> value_array_t;
    typedef std::map<std::string, json_value*> value_object_t;

    void* m_data;

  public:

    /**
     * Default constructor
     */
    json_value();

    /**
     * Destructor
     */
    virtual ~json_value();

    /**
     * Copy constructor from another JSON Value object.
     * 
     * \param [in] other -- JSON Value to copy from
     * 
     * \note Old content of the JSON Value object will be lost.
     */
    json_value(const json_value& other);

    /**
     * Assignment opertor
     * 
     * \note Old content of the JSON Value object will be lost.
     */
    json_value& operator=(const json_value& other);

    /**
     * Is value null
     */
    virtual bool is_null() const;

    /**
     * Is value string
     */
    virtual bool is_string() const;

    /**
     * Is value boolean
     */
    virtual bool is_boolean() const;

    /**
     * Is value number
     */
    virtual bool is_number() const;

    /**
     * Is value object
     */
    virtual bool is_object() const;

    /**
     * Is value value array
     */
    virtual bool is_array() const;

    // TODO : Should i throw an exception if value is not same as extract function
    virtual const std::string& as_string();
    virtual int as_integer();
    virtual float as_float();
    virtual bool as_boolean();
    virtual json_value* as_array(int index);
    virtual json_value* as_object(const std::string& key);

    virtual void print(std::fstream& stream);

  };

  /**
   * \}
   */

}

#endif // JSON_VALUE_H
