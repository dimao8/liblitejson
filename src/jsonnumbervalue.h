#ifndef JSONNUMBERVALUE_H
#define JSONNUMBERVALUE_H

#include <litejson/jsonvalue.h>

namespace litejson
{

class JSONNumberValue : public JSONValue
{
private:
  float m_value;

public:
  JSONNumberValue () = delete;
  JSONNumberValue (int) = delete;

  ///
  /// \brief Create new JSON number value
  /// \param [in] line -- Line position in JSON file
  /// \param [in] n -- Numeric value
  ///
  explicit JSONNumberValue (int line, float n);
  virtual ~JSONNumberValue ();

  ///
  /// Is value null
  ///
  virtual bool is_null () const override final;

  ///
  /// Is value a number
  ///
  virtual bool is_number () const override final;

  ///
  /// \brief Return integer value
  /// \return Return value as integer
  ///
  /// Try to extract integer from JSONValue.
  ///
  virtual std::optional<int> as_integer () const override final;

  ///
  /// \brief Return float value
  /// \return Return value as float
  ///
  /// Try to extract float from JSONValue.
  ///
  virtual std::optional<float> as_float () const override final;

  ///
  /// \brief Print value to the std::ostream
  /// \param [in] stream -- Stream to output to
  /// \param [in] tab -- Number of TAB symbols (for indentation purpose)
  ///
  virtual void print (std::ostream &stream,
                      size_t indent) const override final;
};

}

#endif // JSONNUMBERVALUE_H
