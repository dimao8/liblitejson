///
/// \file litejson.h
///

#ifndef LITEJSON_H
#define LITEJSON_H

#include <fstream>
#include <list>
#include <ostream>
#include <string>

#include "jsonvalue.h"

namespace litejson
{

///
/// \brief Token type enumerator
///
enum class TokenType
{
  Null,     /// \c null keyword
  True,     /// \c true keyword
  False,    /// \c false keyword
  String,   /// string
  Number,   /// number
  Lbrace,   /// left brace {
  Rbrace,   /// right brace }
  Lbracket, /// left bracket [
  Rbracket, /// right bracket ]
  Comma,    /// comma ,
  Colon     /// colon :
};

///
/// \brief Token structure
///
struct Token
{
  TokenType type;   /// Token type
  std::string text; /// Token text (make sense only for numbers and strings)
  int line;         /// Position of the token in lines

  ///
  /// Constructor of the token
  ///
  Token (TokenType tt, const std::string &str, int l)
  {
    type = tt;
    text = str;
    line = l;
  }

  Token
  operator= (const Token &token)
  {
    type = token.type;
    text = token.text;
    line = token.line;

    return *this;
  }
};

///
/// JSON parser class
///
class JSONLoader
{

private:
  JSONValue *m_root;          /// Root element of the JSON tree
  bool m_badbit;             /// Bad flag for JSON parser
  std::list<Token> m_tokens; /// Token list

  ///
  /// \brief Convert 4-digit hex to utf32 value
  /// \param [in] it      -- Input string iterator
  /// \param [out] result -- Output value
  /// \return Return false if string does not contain valid UTF16 sequence
  ///
  bool hextochar (std::string::iterator &it, int &result);

  ///
  /// \brief Convert utf32 value to the utf8 sequence
  /// \param [in] c -- Input UTF32 character
  /// \return Return UTF8 sequence equivalent
  ///
  const std::string utf32toutf8s(int c);

  ///
  /// Make lexical analysis
  ///
  /// \param [in] stream -- Stream to extract strings
  /// \param [out] n     -- Number of the line with error
  /// \return Return result of operation. false on error.
  ///
  bool lexical (std::ifstream &stream, int &n);

  ///
  /// Make syntax analysis
  /// \param [out] n     -- Number of the line with error
  /// \return Return result of operation. false on error.
  ///
  bool syntax (int &n);

  ///
  /// Make lexical analysis of single string
  ///
  /// \param [in] str    -- String to parse
  /// \param [in] n      -- Number of string
  /// \return Return result of operation. false on error.
  ///
  bool parse_string (std::string &str, int n);

  ///
  /// Parse token list and extract current node. This function
  /// must be called recursively to parse whole JSON file.
  ///
  /// \param [in, out]
  /// \return Extracted node or nullptr
  ///
  JSONValue *get_value (std::list<Token>::const_iterator &it);

public:
  ///
  /// Make empty JSON tree
  ///
  JSONLoader ();

  ///
  /// Make JSON tree from text file
  ///
  /// \param [in] file_name -- Name of the JSON text file
  ///
  JSONLoader (const std::string &file_name);

  ///
  /// Return state of the JSON parser. If true is return,
  /// last operation on the JSON object was unsuccessful.
  ///
  bool is_bad ();

  ///
  /// Delete JSON tree
  ///
  void clear_tree ();

  ///
  /// \brief Get root JSONValue
  ///
  JSONValue *get_root () const;

  ///
  /// \brief Write JSON tree to the output stream.
  /// \param [in] stream -- Stream to output
  /// \param [in] loader -- Loader object
  /// \return Return stream reference
  ///
  /// Function writes JSON tree to the output stream with valid formatting. If
  /// there is no valid tree, \c empty word will be written.
  ///
  friend std::ostream &operator<< (std::ostream &stream,
                                   const JSONLoader &loader);
};

}

#endif // LITEJSON_H
