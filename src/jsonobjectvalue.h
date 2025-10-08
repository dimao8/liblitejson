#ifndef JSONOBJECTVALUE_H
#define JSONOBJECTVALUE_H

#include <litejson/jsonvalue.h>

#include <map>
#include <memory>
#include <string>

namespace litejson
{

class JSONObjectValue : public JSONValue
{
private:
  using ObjectValue = std::multimap<std::string, std::shared_ptr<JSONValue> >;
  ObjectValue m_value;

public:
  JSONObjectValue () = delete;
  explicit JSONObjectValue (int line);

  virtual ~JSONObjectValue ();

  ///
  /// \brief Add entry to the object
  /// \param [in] key -- New entry key
  /// \param [in] val -- New entry value
  ///
  /// Convert value to the object (if needed) and add new entry
  ///
  virtual void
  add_object_entry (const std::string &key,
                    const std::shared_ptr<JSONValue> &val) override final;

  ///
  /// Is value null
  ///
  virtual bool is_null () const override final;

  ///
  /// Is value object
  ///
  virtual bool is_object () const override final;

  ///
  /// \brief Return value from object
  /// \param [in] key -- Key of the value in object
  /// \return Return value
  ///
  /// Try to extract JSONValue from object by key.
  ///
  virtual std::shared_ptr<const JSONValue>
  as_object (const std::string &key, size_t index = 0) const override final;

  ///
  /// \brief Return value from object
  /// \param [in] key -- Key of the value in object
  /// \return Return value
  ///
  /// Try to extract JSONValue from object by key.
  ///
  virtual std::shared_ptr<JSONValue>
  as_object (const std::string &key, size_t index = 0) override final;

  ///
  /// \brief Return size of the object
  /// \return Return size
  ///
  virtual size_t size () const override final;

  ///
  /// \brief Get number ov values with the same name
  /// \param [in] key -- Key for searching
  /// \return Return number of entries with key
  ///
  /// Function searches object for entries with the defined key and count'em.
  /// If no entry with such key is exists, return 0.
  ///
  virtual size_t object_key_size (const std::string &key) const override final;

  virtual const std::string &as_object_next_key (const std::string &key
                                                 = "") const override;

  ///
  /// \brief Remove object entry and all it's subtree
  /// \param [in] key -- Key of the entry to be removed
  /// \param [in] index -- Index of the entry to be removed. Can be 0
  /// \return Returns result of deletion
  ///
  /// Remove object entry if JSONValue is an object.
  /// \warning Entry will be removed with all it's subtree. Try not delete the
  /// whole JSON tree
  ///
  virtual bool remove_entry (const std::string &key,
                             size_t index = 0) override final;

  virtual void print (std::ostream &stream,
                      size_t indent) const override final;
};

}

#endif // JSONOBJECTVALUE_H
