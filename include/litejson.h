#ifndef LITEJSON_H
#define LITEJSON_H

#include <string>

namespace litejson
{

  class json_loader
  {

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
