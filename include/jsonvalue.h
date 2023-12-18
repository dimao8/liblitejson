/**
 * \file json_value.h
 */

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace litejson
{

///
/// \brief Value type
///
enum class JSONValueType
{
  Invalid,
  Null,    /// The value is null
  Boolean, /// The value is boolean
  Number,  /// The value is number
  String,  /// The value is string
  Array,   /// The value is value array
  Object   /// The value is object
};

class JSONValue;

typedef std::vector<JSONValue *> value_array_t;
typedef std::multimap<std::string, JSONValue *> value_object_t;

///
/// \brief JSON Value class
///
/// JSON parser unit. Parse single JSON file and manage it.
///
class JSONValue
{

private:
  JSONValue *m_parent;
  void *m_data_ptr;
  JSONValueType m_value_type;
  int m_line;

  ///
  /// \brief Set parent JSONValue
  ///
  void set_parent (JSONValue *parent);

public:
  ///
  /// \brief Default constructor
  ///
  JSONValue (int line);

  ///
  /// \brief Destructor
  ///
  virtual ~JSONValue ();

  ///
  /// \brief Constructor from float
  /// \param [in] f -- Float or int value
  ///
  /// Construct a new json value from number. Set the type of json value as
  /// t_number
  ///
  JSONValue (float f, int line);

  ///
  /// \brief Constructor from boolean
  /// \param [in] b -- Boolean value
  ///
  /// Construct a new json value from boolean. Set the type of json value as
  /// t_boolean
  ///
  JSONValue (bool b, int line);

  ///
  /// \brief Constructor from string
  /// \param [in] str -- String value
  ///
  /// Construct a new json value from string. Set the type of json value as
  /// t_string
  ///
  JSONValue (const std::string &str, int line);

  ///
  /// \brief Add new entry to the array
  /// \param [in] val -- New entry
  ///
  /// Convert value to the array (if needed) and add new entry
  ///
  void add_array_entry (JSONValue *val);

  ///
  /// \brief Add entry to the object
  /// \param [in] key -- New entry key
  /// \param [in] val -- New entry value
  ///
  /// Convert value to the object (if needed) and add new entry
  ///
  ///
  void add_object_entry (const std::string &key, JSONValue *val);

  ///
  /// Is value valid
  ///
  virtual bool is_valid () const;

  ///
  /// Is value null
  ///
  virtual bool is_null () const;

  ///
  /// Is value string
  ///
  virtual bool is_string () const;

  ///
  /// Is value boolean
  ///
  virtual bool is_boolean () const;

  ///
  /// Is value number
  ///
  virtual bool is_number () const;

  ///
  /// Is value object
  ///
  virtual bool is_object () const;

  ///
  /// Is value array
  ///
  virtual bool is_array () const;

  ///
  /// \brief Return string value
  /// \return Return value as string
  /// \throw Throws std::runtime_error if JSONValue is not a string
  ///
  /// Try to extract string from JSONValue.
  ///
  virtual const std::string &as_string () const;

  ///
  /// \brief Return integer value
  /// \return Return value as integer
  /// \throw Throws std::runtime_error if JSONValue is not a number
  ///
  /// Try to extract integer from JSONValue.
  ///
  virtual int as_integer () const;

  ///
  /// \brief Return float value
  /// \return Return value as float
  /// \throw Throws std::runtime_error if JSONValue is not a number
  ///
  /// Try to extract float from JSONValue.
  ///
  virtual float as_float () const;

  ///
  /// \brief Return boolean value
  /// \return Return value as boolean
  /// \throw Throws std::runtime_error if JSONValue is not a boolean
  ///
  /// Try to extract boolean from JSONValue.
  ///
  virtual bool as_boolean () const;

  ///
  /// \brief Return value from array
  /// \param [in] index -- Index of the value in array
  /// \return Return value
  /// \throw Throws std::runtime_error if JSONValue is not an array
  /// \throw Throws std::out_of_range if index is beyond the array size
  ///
  /// Try to extract JSONValue from array by index.
  ///
  virtual JSONValue *as_array (int index) const;

  ///
  /// \brief Return size of the array
  /// \return Return size
  /// \throw Throws std::runtime_error if JSONValue is not an array
  ///
  virtual size_t array_size () const;

  ///
  /// \brief Return value from object
  /// \param [in] key -- Key of the value in object
  /// \return Return value
  /// \throw Throws std::runtime_error if JSONValue is not an object
  /// \throw Throws std::out_of_range if key is not in object list
  ///
  /// Try to extract JSONValue from object by key.
  ///
  virtual JSONValue *as_object (const std::string &key,
                                      size_t index = 0) const;

  ///
  /// \brief Get number ov values with the same name
  /// \param [in] key -- Key for searching
  /// \return Return number of entries with key
  ///
  /// Function searches object for entries with the defined key and count'em.
  /// If no entry with such key is exists, return 0.
  ///
  virtual size_t object_key_size (const std::string &key) const;

  JSONValue *parent () const;
  int line () const;

  std::ostream &print (std::ostream &stream, int tab) const;
  std::ostream &print_ancestor (std::ostream &stream) const;

public:
  static JSONValue *make_object (int line);
  static JSONValue *make_array (int line);
  friend std::ostream &operator<< (std::ostream &stream, const JSONValue &val);
};

}

#endif // JSONVALUE_H
