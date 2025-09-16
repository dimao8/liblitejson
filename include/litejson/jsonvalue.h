/**
 * \file json_value.h
 */

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <memory>
#include <optional>
#include <ostream>
#include <string>

namespace litejson
{

///
/// \brief Value type
///
enum class JSONValueType
{
  Null,    /// The value is null
  Boolean, /// The value is boolean
  Number,  /// The value is number
  String,  /// The value is string
  Array,   /// The value is value array
  Object   /// The value is object
};

///
/// \brief JSON Value class
///
/// JSON parser unit. Parse single JSON file and manage it.
///
class JSONValue : public std::enable_shared_from_this<JSONValue>
{

private:
  std::weak_ptr<JSONValue> m_parent;
  // void *m_data_ptr;
  // JSONValueType m_value_type;
  int m_line;

  ///
  /// \brief Set parent JSONValue
  ///
  void set_parent (const std::shared_ptr<JSONValue> &parent);

public:
  JSONValue () = delete;

  ///
  /// \brief Default constructor
  ///
  explicit JSONValue (int line);

  ///
  /// \brief Destructor
  ///
  virtual ~JSONValue ();

  ///
  /// \brief Add new entry to the array
  /// \param [in] val -- New entry
  ///
  /// Convert value to the array (if needed) and add new entry
  ///
  virtual void add_array_entry (const std::shared_ptr<JSONValue> &val);

  ///
  /// \brief Add entry to the object
  /// \param [in] key -- New entry key
  /// \param [in] val -- New entry value
  ///
  /// Convert value to the object (if needed) and add new entry
  ///
  ///
  virtual void add_object_entry (const std::string &key,
                                 const std::shared_ptr<JSONValue> &val);

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
  ///
  /// Try to extract string from JSONValue.
  ///
  virtual std::optional<const std::string> as_string () const;

  ///
  /// \brief Return integer value
  /// \return Return value as integer
  ///
  /// Try to extract integer from JSONValue.
  ///
  virtual std::optional<int> as_integer () const;

  ///
  /// \brief Return float value
  /// \return Return value as float
  ///
  /// Try to extract float from JSONValue.
  ///
  virtual std::optional<float> as_float () const;

  ///
  /// \brief Return boolean value
  /// \return Return value as boolean
  ///
  /// Try to extract boolean from JSONValue.
  ///
  virtual std::optional<bool> as_boolean () const;

  ///
  /// \brief Return value from array
  /// \param [in] index -- Index of the value in array
  /// \return Return value
  ///
  /// Try to extract JSONValue from array by index.
  ///
  virtual std::shared_ptr<const JSONValue> as_array (size_t index) const;

  ///
  /// \brief Return value from array
  /// \param [in] index -- Index of the value in array
  /// \return Return value
  ///
  /// Try to extract JSONValue from array by index.
  ///
  virtual std::shared_ptr<JSONValue> as_array (size_t index);

  ///
  /// \brief Return size of the array
  /// \return Return size
  ///
  virtual size_t array_size () const;

  ///
  /// \brief Return value from object
  /// \param [in] key -- Key of the value in object
  /// \return Return value
  ///
  /// Try to extract JSONValue from object by key.
  ///
  virtual std::shared_ptr<const JSONValue> as_object (const std::string &key,
                                                      size_t index = 0) const;

  ///
  /// \brief Return value from object
  /// \param [in] key -- Key of the value in object
  /// \return Return value
  ///
  /// Try to extract JSONValue from object by key.
  ///
  virtual std::shared_ptr<JSONValue> as_object (const std::string &key,
                                                size_t index = 0);

  ///
  /// \brief Get number ov values with the same name
  /// \param [in] key -- Key for searching
  /// \return Return number of entries with key
  ///
  /// Function searches object for entries with the defined key and count'em.
  /// If no entry with such key is exists, return 0.
  ///
  virtual size_t object_key_size (const std::string &key) const;

  const std::weak_ptr<JSONValue> &parent () const;
  int line () const;

  virtual void print (std::ostream &stream, size_t indent) const;

public:
  static std::shared_ptr<JSONValue> make_null (int line);
  static std::shared_ptr<JSONValue> make_boolean (int line, bool b);
  static std::shared_ptr<JSONValue> make_string (int line,
                                                 const std::string &s);
  static std::shared_ptr<JSONValue> make_number (int line, float f);
  static std::shared_ptr<JSONValue> make_object (int line);
  static std::shared_ptr<JSONValue> make_array (int line);

private:
  friend class JSONArrayValue;
  friend class JSONBooleanValue;
  friend class JSONNumberValue;
  friend class JSONObjectValue;
  friend class JSONStringValue;
};

std::ostream &operator<< (std::ostream &stream, const JSONValue &val);

}

#endif // JSONVALUE_H
