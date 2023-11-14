/**
 * \file litejson.cpp
 */

#include <litejson.h>

#include <iostream>
#include <locale>

namespace litejson
{

// TODO : Debug code -->
std::ostream &
operator<< (std::ostream &stream, const Token &tok)
{
  std::cout << "Token(";

  switch (tok.type)
    {

    case TokenType::Colon:
      std::cout << "Colon";
      break;

    case TokenType::Comma:
      std::cout << "Comma";
      break;

    case TokenType::False:
      std::cout << "False";
      break;

    case TokenType::Lbrace:
      std::cout << "Lbrace";
      break;

    case TokenType::Lbracket:
      std::cout << "Lbracket";
      break;

    case TokenType::Null:
      std::cout << "Null";
      break;

    case TokenType::Number:
      std::cout << "Number";
      break;

    case TokenType::Rbrace:
      std::cout << "Rbrace";
      break;

    case TokenType::Rbracket:
      std::cout << "Rbracket";
      break;

    case TokenType::String:
      std::cout << "String";
      break;

    case TokenType::True:
      std::cout << "True";
      break;
    }

  std::cout << ", ``" << tok.text << "\'\')";

  return stream;
}
// <--

/* ************************* JSONLoader::JSONLoader ************************ */

JSONLoader::JSONLoader () : m_badbit (false)
{
  // TODO : Constructor
}

/* ************************* JSONLoader::JSONLoader ************************ */

JSONLoader::JSONLoader (const std::string &file_name) : m_badbit (false)
{
  std::ifstream ifs (file_name);
  if (!ifs)
    {
      std::cout << "[E] Can not open file ``" << file_name << "\'\'"
                << std::endl;
      m_badbit = true;
      return;
    }

  int n = 0;

  // Try lexical
  if (!lexical (ifs, n))
    {
      m_tokens.clear ();
      m_badbit = true;
      ifs.close ();
      return;
    }

  ifs.close ();

  for (auto it : m_tokens)
    std::cout << it << std::endl;

  // Try syntax
  // if (!syntax (n))
  //   {
  //     m_tokens.clear ();
  //     m_badbit = true;
  //     return;
  //   }
}

/* ************************** JSONLoader::lexical ************************** */

bool
JSONLoader::lexical (std::ifstream &stream, int &n)
{
  std::string str;

  while (!stream.eof ())
    {
      n++;
      std::getline (stream, str);
      if (!parse_string (str, n))
        return false;
    }

  return true;
}

/* ************************ JSONLoader::parse_string *********************** */

bool
JSONLoader::parse_string (std::string &str, int n)
{
  auto it = str.begin ();
  std::locale neutral_locale ("C");
  std::string s;

  while (it != str.end ())
    {
      if (std::isspace (*it, neutral_locale)) // Skip spaces
        it++;
      else if (std::isdigit (*it, neutral_locale)
               || *it == '-') // Something like number
        {
          s.clear ();
          // Check for -
          if (*it == '-')
            {
              s.push_back (*it);
              it++;
            }

          // Check for integer part
          if (std::isdigit (*it, neutral_locale))
            {
              if (*it
                  == '0') // Check 0 route. It must not contain other digits
                {
                  s.push_back (*it);
                  it++;
                }
              else
                {
                  s.push_back (*it);
                  it++;
                  while (std::isdigit (*it, neutral_locale))
                    {
                      s.push_back (*it);
                      it++;
                    }
                }
            }

          // Check for fractional part
          if (*it == '.')
            {
              s.push_back (*it);
              it++;
              while (std::isdigit (*it, neutral_locale))
                {
                  s.push_back (*it);
                  it++;
                }
            }

          // Check for exponent
          if (*it == 'e' || *it == 'E')
            {
              s.push_back ('e');
              it++;

              if (*it == '-' || *it == '+')
                {
                  s.push_back (*it);
                  it++;
                }

              while (std::isdigit (*it, neutral_locale))
                {
                  s.push_back (*it);
                  it++;
                }
            }

          m_tokens.emplace_back (TokenType::Number, s, n);
          continue;
        }
      else if (std::isalpha (*it, neutral_locale)) // Something like keyword
        {
          s.clear ();
          while (std::isalpha (*it, neutral_locale))
            {
              s.push_back (*it);
              it++;
            }
          if (s == "null")
            {
              m_tokens.emplace_back (TokenType::Null, s, n);
              continue;
            }
          else if (s == "true")
            {
              m_tokens.emplace_back (TokenType::True, s, n);
              continue;
            }
          else if (s == "false")
            {
              m_tokens.emplace_back (TokenType::False, s, n);
              continue;
            }
          else
            {
              std::cout << "[E] Syntax error (" << n
                        << "): unexpected literal ``" << s << "\'\'"
                        << std::endl;
              return false;
            }
        }
      else
        {
          s.clear ();
          switch (*it)
            {

            case '\"': // Something like string
              it++;
              while (it != str.end ())
                {
                  if (*it == '\"')
                    break;
                  else
                    {
                      s.push_back (*it);
                      it++;
                    }
                }
              if (*it == '\"')
                {
                  it++;
                  m_tokens.emplace_back (TokenType::String, s, n);
                }
              else
                {
                  std::cout << "[E] Syntax error (" << n << "): \" expected"
                            << std::endl;
                }
              break;

            case '{': // lbrace
              m_tokens.emplace_back (TokenType::Lbrace, "{", n);
              it++;
              break;

            case '}': // rbrace
              m_tokens.emplace_back (TokenType::Rbrace, "}", n);
              it++;
              break;

            case '[': // lbracket
              m_tokens.emplace_back (TokenType::Lbracket, "[", n);
              it++;
              break;

            case ']': // rbracket
              m_tokens.emplace_back (TokenType::Rbracket, "]", n);
              it++;
              break;

            case ',': // comma
              m_tokens.emplace_back (TokenType::Comma, ",", n);
              it++;
              break;

            case ':': // colon
              m_tokens.emplace_back (TokenType::Colon, ":", n);
              it++;
              break;

            default: // Some trash )))
              std::cout << "[E] Lexical error (" << n
                        << "): unexpected character ``" << *it << "\'\'"
                        << std::endl;
              return false;
            }
          continue;
        }
    }

  return true;
}

/* *************************** JSONLoader::syntax ************************** */

bool
JSONLoader::syntax (int &n)
{
}

/* *************************** JSONLoader::is_bad ************************** */

bool
JSONLoader::is_bad ()
{
  return m_badbit;
}

/* ************************* JSONLoader::clear_tree ************************ */

void
JSONLoader::clear_tree ()
{
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const JSONLoader &loader)
{
}

}
