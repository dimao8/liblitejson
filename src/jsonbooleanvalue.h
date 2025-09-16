#ifndef JSONBOOLEANVALUE_H
#define JSONBOOLEANVALUE_H

#include <litejson/jsonvalue.h>

namespace litejson
{

class JSONBooleanValue : public JSONValue
{
private:
  bool m_value;

public:
  JSONBooleanValue () = delete;
  JSONBooleanValue (int) = delete;

  ///
  /// \brief Create new JSON boolean value
  /// \param [in] line -- Line position in JSON file
  /// \param [in] b -- Boolean value
  ///
  explicit JSONBooleanValue (int line, bool b);
  virtual ~JSONBooleanValue ();

  ///
  /// Is value null
  ///
  virtual bool is_null () const override final;

  ///
  /// Is value a boolean
  ///
  virtual bool is_boolean () const override final;

  ///
  /// \brief Return boolean value
  /// \return Return value as boolean
  ///
  /// Try to extract boolean from JSONValue.
  ///
  virtual std::optional<bool> as_boolean () const override final;

  ///
  /// \brief Print value to the std::ostream
  /// \param [in] stream -- Stream to output to
  /// \param [in] tab -- Number of TAB symbols (for indentation purpose)
  ///
  virtual void print (std::ostream &stream, size_t indent) const override final;
};

}

#endif // JSONBOOLEANVALUE_H
