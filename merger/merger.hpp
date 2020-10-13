#ifndef MERGER_MERGER_HPP
#define MERGER_MERGER_HPP

#include <vector>
#include <list>
#include <string>
#include <string_view>
#include <type_traits>
#include <iterator>
#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>

template <typename Iterator>
void merge(Iterator begin_file, Iterator end_file,
           const std::string& output_filename,
           const std::string& library_name
)
{
    static_assert((std::is_same<typename Iterator::value_type, std::string>::value
                   ||
                   std::is_same<typename Iterator::value_type, std::string_view>::value),
                  "file names must be of string or string_view type"
    );


    std::ofstream ofs{output_filename};
    if(!ofs.is_open())
    {
        throw std::runtime_error(output_filename + " cannot be opened");
    }

    // ofs << "#ifndef " << library_name << "_HPP" << '\n';
    // ofs << "#define " << library_name << "_HPP" << '\n';

    while(begin_file != end_file)
    {
        std::ifstream current_file{*begin_file};
        if(!current_file.is_open())
        {
            throw std::runtime_error(*begin_file + " cannot be opened");
        }

        ofs << "\n/* start of " << *begin_file << " */\n\n";

        std::string include_directive{"#include \""};
        for(std::string line; std::getline(current_file, line); )
        {
            if(line[0] == '#' &&
               std::equal(line.begin(), std::next(line.begin(), include_directive.size()),
                          include_directive.begin(), include_directive.end()))
            {
                ofs << "// ";
            }

            ofs << line << '\n';
        }

        ofs << "\n/* end of " << *begin_file << " */\n";
        current_file.close();
        begin_file++;
    }

    // ofs << "#endif // " << library_name << "_IMPLEMENTATION_HPP" << '\n';
    // ofs << "#endif // " << library_name << "_HPP" << '\n';

    ofs.close();
}

#endif //MERGER_MERGER_HPP
