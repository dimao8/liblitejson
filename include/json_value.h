/**
 * \file json_value.h
 */

#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include <string>

namespace litejson
{

  class json_boolean_value;
  class json_numeric_value;
  class json_string_value;
  class json_array_value;
  class json_object_value;

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
    virtual json_array_value& as_array();
    virtual json_object_value& as_object();

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

  };

  /**
   * \}
   */

  /**
   * JSON value with boolean
   * 
   * \addtogroup json_value_classes
   * \{
   */
  class json_boolean_value : public json_value
  {

  protected:

    bool m_data;                                //!< Boolean data of the value

  public:

    /**
     * Default constructor
     */
    json_boolean_value();

    /**
     * Copy constructor
     */
    json_boolean_value(const json_boolean_value& other);

    /**
     * Construct from boolean value
     */
    json_boolean_value(bool b);

    /**
     * Assignment operator
     */
    json_boolean_value& operator=(const json_boolean_value& other);

    /**
     * Assign from boolean value
     */
    json_boolean_value& operator=(bool b);

    /**
     * Return boolean value
     */
    virtual bool as_boolean();

  };

  /**
   * \}
   */

  /**
   * JSON value with numeric
   * 
   * \addtogroup json_value_classes
   * \{
   */
  class json_numeric_value : public json_value
  {

  protected:

    int m_i_data;                                //!< Integer data of the value
    float m_f_data;                              //!< Float data of the value

  public:

    /**
     * Default constructor
     */
    json_numeric_value();

    /**
     * Copy constructor
     */
    json_numeric_value(const json_numeric_value& other);

    /**
     * Construct from float value
     */
    explicit json_numeric_value(float f);

    /**
     * Construct from integer value
     */
    explicit json_numeric_value(int i);

    /**
     * Assignment operator
     */
    json_numeric_value& operator=(const json_numeric_value& other);

    /**
     * Assignment from float value
     */
    json_numeric_value& operator=(float f);

    /**
     * Assignment from integer value
     */
    json_numeric_value& operator=(int i);

    /**
     * Return integer value
     */
    virtual int as_integer();
    
    /**
     * Return float value
     */
    virtual float as_float();

  };

  /**
   * \}
   */

  /**
   * JSON value with string
   * 
   * \addtogroup json_value_classes
   * \{
   */
  class json_string_value : public json_value
  {

  protected:

    std::string m_data;                                //!< String data of the value

  public:

    /**
     * Default constructor
     */
    json_string_value();

    /**
     * Copy constructor
     */
    json_string_value(const json_string_value& other);

    /**
     * Construct from string value
     */
    json_string_value(const std::string& str);

    /**
     * Assignment operator
     */
    json_string_value& operator=(const json_string_value& other);

    /**
     * Assign from boolean value
     */
    json_string_value& operator=(const std::string& str);

    /**
     * Return boolean value
     */
    virtual const std::string& as_string();

  };

  /**
   * \}
   */

}

#endif // JSON_VALUE_H
