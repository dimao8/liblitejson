#ifndef JSONARRAYVALUE_H
#define JSONARRAYVALUE_H

#include <litejson/jsonvalue.h>

#include <memory>
#include <list>

namespace litejson
{

class JSONArrayValue : public JSONValue
{
private:
  std::list<std::shared_ptr<JSONValue> > m_value;

public:
  JSONArrayValue () = delete;
  explicit JSONArrayValue (int line);

  virtual ~JSONArrayValue ();

  ///
  /// \brief Add new entry to the array
  /// \param [in] val -- New entry
  ///
  /// Add new entry to the array
  ///
  virtual void
  add_array_entry (const std::shared_ptr<JSONValue> &val) override final;

  ///
  /// Is value null
  ///
  virtual bool is_null () const override final;

  ///
  /// Is value array
  ///
  virtual bool is_array () const override final;

  ///
  /// \brief Return value from array
  /// \param [in] index -- Index of the value in array
  /// \return Return value
  ///
  /// Try to extract JSONValue from array by index.
  ///
  std::shared_ptr<const JSONValue>
  as_array (size_t index) const override final;

  ///
  /// \brief Return value from array
  /// \param [in] index -- Index of the value in array
  /// \return Return value
  ///
  /// Try to extract JSONValue from array by index.
  ///
  std::shared_ptr<JSONValue> as_array (size_t index) override final;

  ///
  /// \brief Remove array entry and all it's subtree
  /// \param [in] index -- Index of the entry to be removed
  /// \return Returns result of deletion
  ///
  /// Remove array entry if JSONValue is an array.
  /// \warning Entry will be removed with all it's subtree. Try not delete the
  /// whole JSON tree
  ///
  virtual bool remove_entry (size_t index) override final;

  ///
  /// \brief Return size of the array
  /// \return Return size
  ///
  virtual size_t array_size () const override final;

  virtual void print (std::ostream &stream,
                      size_t indent) const override final;
};

}

#endif // JSONARRAYVALUE_H
