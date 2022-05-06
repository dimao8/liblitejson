/**
 * \file litejson.cpp
 */

#include <litejson.h>

#include <iostream>
#include <cctype>

#include "json_object.h"
#include "json_array.h"

namespace litejson
{

/*******************  json_loader::json_loader  *******************/

  json_loader::json_loader()
  : m_root(nullptr),
    m_badbit(false)
  {
    // TODO : Constructor
  }


/*******************  json_loader::json_loader  *******************/

  json_loader::json_loader(const std::string& file_name)
  : m_root(nullptr),
    m_badbit(false)
  {
    int line;

    std::ifstream ifs(file_name);

    if (!ifs)
      {
        m_badbit = true;
        return;
      }

    // Lexical analysis
    if (!lexical(ifs, &line))
      {
        std::cerr << "Lexical error(" << line << ")" << std::endl;
        std::cerr.flush();
        m_badbit = true;
        return;
      }
  }

/*********************  json_loader::lexical  *********************/

  bool json_loader::lexical(std::ifstream& stream, int* n)
  {
    std::string str;

    *n = 0;

    while (!std::getline(stream, str).eof())
      {
        (*n)++;
        if (!parse_string(str, *n))
          return false;
      }

    return true;
  }

/*******************  json_loader::parse_string  ******************/

  bool json_loader::parse_string(std::string& str, int n)
  {
    auto it = str.begin();
    std::string str_token;

    while (*it)
      {
        str_token.clear();
        if (*it == '\"')                            // String
          {
            it++;
            while (*it != '\"')
              {
                if (*it == 0)
                  return false;
                else
                  str_token.push_back(*it);
                it++;
              }
            it++;
            m_tokens.emplace_back(token::tok_string, str_token, n);
            // TODO : Extract coded characters
          }
        else if (*it == '-' || std::isdigit(*it))   // Numeric
          {
            if (*it == '-')                         // Extract mantissa sign
              {
                str_token.push_back(*it);
                it++;
              }

            if (!std::isdigit(*it))                      // Extract mantissa integer part
              return false;
            while (std::isdigit(*it))
              {
                str_token.push_back(*it);
                it++;
              }

            if (*it == '.')                         // Extract decimal point
              {
                str_token.push_back(*it);
                it++;

                if (!std::isdigit(*it))                  // Extract fractional part
                  return false;
                
                while (std::isdigit(*it))
                  {
                    str_token.push_back(*it);
                    it++;
                  }
              }

            if (*it == 'e' || *it == 'E')           // Extract exponent character
              {
                str_token.push_back(*it);
                it++;

                if (*it == '-')                     // Extract exponent sign
                  {
                    str_token.push_back(*it);
                    it++;
                  }

                if (!std::isdigit(*it))                  // Extract exponent part
                  return false;

                while (std::isdigit(*it))
                  {
                    str_token.push_back(*it);
                    it++;
                  }
              }

            m_tokens.emplace_back(token::tok_number, str_token, n);
          }
        else if ((*it == '{')                       // Operator
                || (*it == '}')
                || (*it == '[')
                || (*it == ']')
                || (*it == ':')
                || (*it == ','))
          {
            str_token.push_back(*it);
            m_tokens.emplace_back(token::tok_operator, str_token, n);
            it++;
          }
        else if (std::isalpha(*it))                 // null, false, true
          {
            while (std::isalpha(*it))
              {
                str_token.push_back(*it);
                it++;
              }

            if (str_token == "null")
              {
                m_tokens.emplace_back(token::tok_null, str_token, n);
              }
            else if (str_token == "true")
              {
                m_tokens.emplace_back(token::tok_boolean, str_token, n);
              }
            else if (str_token == "false")
              {
                m_tokens.emplace_back(token::tok_boolean, str_token, n);
              }
            else
              return false;
          }
        else if (isspace(*it))
          {
            it++;
          }
        else if (*it == 0)
          {
            return true;
          }
        else
          return false;
      }

    return true;
  }

/**********************  json_loader::syntax  *********************/

  bool json_loader::syntax(int* n)
  {
    int index = 0;

    if (parse_node(&m_root, &index))
      return true;
    else
      {
        clear_tree();
        return false;
      }
  }

/********************  json_loader::parse_node  *******************/

  bool json_loader::parse_node(json_value** val, int* index)
  {
    std::string name;
    json_value* local_val;
    json_object_value obj_val;
    json_array_value array_val;

    if (val == nullptr)
      return false;

    switch (m_tokens[*index].type)
      {

      case token::tok_operator:
        if (m_tokens[*index].text[0] == '{')                    // Object
          {
            (*index)++;
            while (true)
              {
                // Get name
                if (m_tokens[*index].type != token::tok_string)
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): String expected" << std::endl;
                    return false;
                  }

                name = m_tokens[*index].text;
                (*index)++;

                // Get :
                if (m_tokens[*index].type != token::tok_operator || m_tokens[*index].text[0] != ':')
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``:\'\' expected" << std::endl;
                    return false;
                  }

                (*index)++;

                // Get value
                if (!parse_node(&local_val, index))
                  return false;

                obj_val = (*val)->as_object();
                if (obj_val != empty_object_value)
                  obj_val.add_entry(name, *local_val);

                if (m_tokens[*index].type == token::tok_operator)
                  {
                    if (m_tokens[*index].text[0] == ',')
                      {
                        (*index)++;
                        continue;
                      }
                    else if (m_tokens[*index].text[0] == '}')
                      break;
                    else
                      {
                        std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                                  << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                        return false;
                      }
                  }
                else
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                              << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                    return false;
                  }
              }
          }
        else if (m_tokens[*index].text[0] == '[')               // Array
          {

          }
        else
          {
            std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                      << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
            return false;
          }
        break;

      case token::tok_null:                                     // Null
        break;

      case token::tok_boolean:                                  // Boolean
        break;

      case token::tok_string:                                   // String
        break;

      case token::tok_number:                                   // Number
        break;
      }
  }

/***********************  json_loader::bad  ***********************/

  bool json_loader::bad()
  {
    return m_badbit;
  }

/*****************  json_loader::print_json_tree  *****************/

  void json_loader::print_json_tree()
  {
    if (!m_tokens.empty())
      {
        for (auto it : m_tokens)
          {
            switch (it.type)
              {

              case token::tok_null:
                std::cout << "null : ``";
                break;

              case token::tok_boolean:
                std::cout << "boolean : ``";
                break;

              case token::tok_number:
                std::cout << "number : ``";
                break;

              case token::tok_string:
                std::cout << "string : ``";
                break;

              case token::tok_operator:
                std::cout << "operator : ``";
                break;

              }

            std::cout << it.text << "\'\'" << std::endl;
          }
      }
    else
      std::cout << "empty!" << std::endl;
  }

}
