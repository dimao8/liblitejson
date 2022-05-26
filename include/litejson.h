/**
 * \file litejson.h
 */

#ifndef LITEJSON_H
#define LITEJSON_H

#include <string>
#include <ostream>
#include <fstream>
#include <vector>

#include "json_value.h"

namespace litejson
{

  /**
   * JSON parser class
   */
  class json_loader
  {

  private:

    json_value * m_root;                                //!< Root element of the JSON tree
    bool m_badbit;                                      //!< Bad flag for JSON parser

    struct token
    {
      enum token_type
      {
        tok_null,
        tok_boolean,
        tok_string,
        tok_number,
        tok_operator
      } type;
      std::string text;
      int line;
      token(token_type tt, const std::string& str, int l) { type = tt; text = str; line = l; }
    };
    std::vector<token> m_tokens;                        //!< Token list

    /**
     * Make lexical analysis
     * 
     * \param [in] stream -- Stream to extract strings
     * \param [out] n     -- Number of the line with error
     * \return Return result of operation. false on error.
     */
    bool lexical(std::ifstream& stream, int* n);

    /**
     * Make syntax analysis
     * \param [out] n     -- Number of the line with error
     * \return Return result of operation. false on error.
     */
    bool syntax(int* n);

    /**
     * Make lexical analysis of single string
     * 
     * \param [in] str    -- String to parse
     * \param [in] n      -- Number of string
     * \return Return result of operation. false on error.
     */
    bool parse_string(std::string& str, int n);

    /**
     * Parse token list and extract current node. This function
     * must be called recursively to parse whole JSON file.
     * 
     * \param [in] node         -- Node, which receives children from JSON
     * \param [in, out] index   -- Index of the current token
     * \return Extracted node or nullptr
     */
    json_value* parse_node(int* index);

  public:

    /**
     * Make empty JSON tree
     */
    json_loader();

    /**
     * Make JSON tree from text file
     *
     * \param [in] file_name -- Name of the JSON text file
     */
    json_loader(const std::string& file_name);

    /**
     * Return state of the JSON parser. If true is return,
     * last operation on the JSON object was unsuccessful.
     */
    bool bad();

    /**
     * Print JSON tree to stdout
     * 
     */
    void print_json_tree(std::ostream& stream);

    /**
     * Delete JSON tree
     */
    void clear_tree();

  };

}

#endif // LITEJSON_H
