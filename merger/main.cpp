#include <iostream>
#include <string>
#include <vector>

#include "merger.hpp"

int main()
{
    std::vector<std::string> files{"../../include/top.h",

                                   "../../include/public_api.h",
                                   "../../include/fail_info.h",
                                   "../../include/binary_operators.h",
                                   "../../include/printing.h",
                                   "../../include/check.h",
                                   "../../include/test.h",
                                   "../../include/linker_sections.h",
                                   "../../include/test_runner.h",

                                   "../../include/bottom.h"
    };

    merge(files.begin(), files.end(), "../../single_header/sutf.hpp", "SUTF");

    return 0;
}
