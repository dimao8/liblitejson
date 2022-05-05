/**
 * \file litejson.h
 */

#ifndef LITEJSON_H
#define LITEJSON_H

#include <string>
#include "json_value.h"

namespace litejson
{

  /**
   * JSON parser class
   */
  class json_loader
  {

  private:

    json_value * m_root;

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

  };

}

#endif // LITEJSON_H
