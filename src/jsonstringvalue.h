#ifndef JSONSTRINGVALUE_H
#define JSONSTRINGVALUE_H

#include <litejson/jsonvalue.h>

#include <string>

namespace litejson
{

///
/// \brief JSON string value
///
class JSONStringValue : public JSONValue
{
private:
  std::string m_value; /// String value

public:
  JSONStringValue () = delete;
  JSONStringValue (int) = delete;

  ///
  /// \brief Create new JSON string value
  /// \param [in] line -- Line position in JSON file
  /// \param [in] str -- String value
  ///
  explicit JSONStringValue (int line, const std::string &str);

  virtual ~JSONStringValue ();

  ///
  /// Is value null
  ///
  virtual bool is_null () const override final;

  ///
  /// Is value string
  ///
  virtual bool is_string () const override final;

  ///
  /// \brief Return string value
  /// \return Return value as string
  ///
  /// Try to extract string from JSONValue.
  ///
  virtual std::optional<const std::string> as_string () const override final;

  ///
  /// \brief Print string value to the std::ostream
  /// \param [in] stream -- Stream to output to
  /// \param [in] tab -- Number of TAB symbols (for indentation purpose)
  ///
  virtual void print (std::ostream &stream, size_t indent) const override final;
};

}

#endif // JSONSTRINGVALUE_H
