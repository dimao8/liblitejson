/**
 * \file litejson.cpp
 */

#include <litejson.h>

#include <iostream>
#include <cctype>

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

    if (!syntax(&line))
      {
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

    m_root = parse_node(&index);

    return m_root != nullptr;
  }

/********************  json_loader::parse_node  *******************/

  json_value* json_loader::parse_node(int* index)
  {
    std::string name;
    json_value* val;
    json_value* local_val;

    if (*index >= m_tokens.size())
      return nullptr;

    switch (m_tokens[*index].type)
      {

      case token::tok_operator:
        if (m_tokens[*index].text[0] == '{')                    // Object
          {
            val = new json_value();
            (*index)++;
            while (true)
              {
                // Get name
                if (m_tokens[*index].type != token::tok_string)
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): String expected" << std::endl;
                    delete val;
                    return nullptr;
                  }

                name = m_tokens[*index].text;
                (*index)++;

                // Get :
                if (m_tokens[*index].type != token::tok_operator || m_tokens[*index].text[0] != ':')
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``:\'\' expected" << std::endl;
                    delete val;
                    return nullptr;
                  }

                (*index)++;

                // Get value
                local_val = parse_node(index);
                if (local_val == nullptr)
                  {
                    delete val;
                    return nullptr;
                  }

                val->add_object_entry(name, local_val);

                if (m_tokens[*index].type == token::tok_operator)
                  {
                    if (m_tokens[*index].text[0] == ',')
                      {
                        (*index)++;
                        continue;
                      }
                    else if (m_tokens[*index].text[0] == '}')
                      {
                        (*index)++;
                        break;
                      }
                    else
                      {
                        std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                                  << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                        delete val;
                        return nullptr;
                      }
                  }
                else
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                              << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                    delete val;
                    return nullptr;
                  }
              }
            return val;
          }
        else if (m_tokens[*index].text[0] == '[')               // Array
          {
            val = new json_value();
            (*index)++;

            while (true)
              {
                local_val = parse_node(index);
                if (local_val == nullptr)
                  {
                    delete val;
                    return nullptr;
                  }

                val->add_array_entry(local_val);

                if (m_tokens[*index].type == token::tok_operator)
                  {
                    if (m_tokens[*index].text[0] == ',')
                      {
                        (*index)++;
                        continue;
                      }
                    else if (m_tokens[*index].text[0] == ']')
                      {
                        (*index)++;
                        break;
                      }
                    else
                      {
                        std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                                  << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                        delete val;
                        return nullptr;
                      }
                  }
                else
                  {
                    std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                              << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
                    delete val;
                    return nullptr;
                  }
              }
          }
        else
          {
            std::cerr << "Syntax error (" << m_tokens[*index].line << "): ``"
                      << m_tokens[*index].text << "\'\' is not allowed here" << std::endl;
            return nullptr;
          }
        return val;
        break;

      case token::tok_null:                                     // Null
        (*index)++;
        return new json_value();
        break;

      case token::tok_boolean:                                  // Boolean
        (*index)++;
        return new json_value(m_tokens[*index - 1].text == "true");
        break;

      case token::tok_string:                                   // String
        (*index)++;
        return new json_value(m_tokens[*index - 1].text);
        break;

      case token::tok_number:                                   // Number
        (*index)++;
        return new json_value((float)std::atof(m_tokens[*index - 1].text.c_str()));
        break;
      }
  }

/***********************  json_loader::bad  ***********************/

  bool json_loader::bad()
  {
    return m_badbit;
  }

/*****************  json_loader::print_json_tree  *****************/

  void json_loader::print_json_tree(std::ostream& stream)
  {
    if (m_root == nullptr)
      {
        stream << "empty" << std::endl;
      }
    else
      {
        m_root->print(stream);
      }
  }

/********************  json_loader::clear_tree  *******************/

  void json_loader::clear_tree()
  {
    if (m_root != nullptr)
      delete m_root;

    m_root = nullptr;
  }

}
