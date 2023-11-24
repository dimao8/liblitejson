/**
 * \file litejson.cpp
 */

#include <litejson.h>

#include <iomanip>
#include <iostream>
#include <locale>

namespace litejson
{

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

  // Try syntax
  if (!syntax (n))
    {
      m_tokens.clear ();
      clear_tree ();
      m_badbit = true;
      return;
    }
}

/* ************************* JSONLoader::hextochar ************************* */

bool
JSONLoader::hextochar (std::string::iterator &it, int &result)
{
  result = 0;

  for (auto i = 0; i < 4; i++)
    {
      result <<= 4;
      if (*it >= '0' && *it <= '9')
        result += *it - '0';
      else if (*it >= 'A' && *it <= 'F')
        result += *it - 'A' + 10;
      else if (*it >= 'a' && *it <= 'f')
        result += *it - 'a' + 10;
      else
        return false;
      it++;
    }

  return true;
}

/* ************************ JSONLoader::utf32toutf8s *********************** */

const std::string
JSONLoader::utf32toutf8s (int c)
{
  std::string s;

  if (c < 128)
    s.push_back (c);
  else if (c < 2048)
    {
      s.push_back (0xC0 | ((c & 0xFC0) >> 6));
      s.push_back ((c & 0x3F) | 0x80);
    }
  else if (c < 65536)
    {
      s.push_back (0xE0 | ((c & 0xF000) >> 12));
      s.push_back (0x80 | ((c & 0xFC0) >> 6));
      s.push_back ((c & 0x3F) | 0x80);
    }
  else
    {
      s.push_back (0xF0 | ((c & 0x380000) >> 18));
      s.push_back (0x80 | ((c & 0xF000) >> 12));
      s.push_back (0x80 | ((c & 0xFC0) >> 6));
      s.push_back ((c & 0x3F) | 0x80);
    }

  return s;
}

/* ************************** JSONValue::get_root ************************** */

const JSONValue &
JSONLoader::get_root () const
{
  return m_root;
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
  int utf32;

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
                  if (*it == '\\') // Skipped
                    {
                      it++;
                      if (*it == '\"' || *it == '\\' || *it == '/')
                        {
                          s.push_back (*it);
                          it++;
                        }
                      else if (*it == 'r')
                        {
                          s.push_back ('\x0D');
                          it++;
                        }
                      else if (*it == 't')
                        {
                          s.push_back ('\x09');
                          it++;
                        }
                      else if (*it == 'n')
                        {
                          s.push_back ('\x0A');
                          it++;
                        }
                      else if (*it == 'f')
                        {
                          s.push_back ('\x0C');
                          it++;
                        }
                      else if (*it == 'b')
                        {
                          s.push_back ('\x08');
                          it++;
                        }
                      else if (*it == 'u')
                        {
                          it++;
                          if (!hextochar (it, utf32))
                            {
                              std::cout << "[E] Syntax error (" << n
                                        << "): wrong string sequence"
                                        << std::endl;
                              return false;
                            }
                          s += utf32toutf8s (utf32);
                        }
                      else
                        {
                          std::cout << "[E] Syntax error (" << n
                                    << "): wrong string sequence" << std::endl;
                          return false;
                        }
                    }
                  else if (*it == '\"')
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
  std::list<Token>::const_iterator it = m_tokens.begin ();

  m_root = get_value (it);

  return m_root.is_valid ();
}

/* ************************* JSONLoader::get_value ************************* */

const JSONValue
JSONLoader::get_value (std::list<Token>::const_iterator &it)
{
  JSONValue val;
  JSONValue child;
  std::string name;

  if (it == m_tokens.end ())
    return JSONValue::invalid_value;

  switch (it->type)
    {

    case TokenType::Null:
      val = JSONValue ();
      it++;
      return val;

    case TokenType::True:
      val = JSONValue (true);
      it++;
      return val;

    case TokenType::False:
      val = JSONValue (false);
      it++;
      return val;

    case TokenType::String:
      val = JSONValue (it->text);
      it++;
      return val;

    case TokenType::Number:
      val = JSONValue (static_cast<float> (std::atof (it->text.c_str ())));
      it++;
      return val;

    case TokenType::Lbrace:
      it++; // Skip lbrace
      while (true)
        {
          if (it->type == TokenType::String) // Pair
            {
              name = it->text;
              it++; // Skip name
              if (it->type != TokenType::Colon)
                {
                  std::cout << "[E] Syntax error (" << it->line
                            << "): ``:\'\' expected at token ``" << it->text
                            << "\'\'" << std::endl;
                  return JSONValue::invalid_value;
                }
              it++; // Skip colon
              child = get_value (it);
              if (child.is_valid ())
                val.add_object_entry (name, child);
              else
                return JSONValue::invalid_value;
              if (it->type == TokenType::Comma) // Skip comma
                it++;
            }
          else if (it->type == TokenType::Rbrace) // rbrace
            {
              it++;
              break;
            }
          else
            {
              std::cout << "[E] Syntax error (" << it->line
                        << "): string or ``}\'\' expected at token ``"
                        << it->text << "\'\'" << std::endl;
              return JSONValue::invalid_value;
            }
        }
      return val;

    case TokenType::Lbracket:
      it++; // Skip lbracket
      while (true)
        {
          if (it->type == TokenType::Rbracket)
            {
              it++;
              break;
            }
          else
            {
              child = get_value (it);
              if (child.is_valid ())
                val.add_array_entry (child);
              else
                return JSONValue::invalid_value;

              if (it->type == TokenType::Comma) // Skip comma
                it++;
            }
        }
      return val;

    default:
      std::cout
          << "[E] Syntax error (" << it->line
          << "): ``null\'\', ``true\'\', ``false\'\', string, number, ``[\'\' "
             "or ``]\'\' expected at token ``"
          << it->text << "\'\'" << std::endl;
      return JSONValue::invalid_value;
    }
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
  m_root = JSONValue ();
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const JSONLoader &loader)
{
  stream << loader.m_root;
  return stream;
}

}
