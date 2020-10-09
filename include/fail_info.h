#pragma once

namespace sutf::_internal
{
    ////////////////////////////////////////////
    //   ASSERT/EXPECT FAIL INFO GENERATION   //
    ////////////////////////////////////////////

    #ifndef __FUNCTION_NAME__
        #ifdef SUTF_OS_WINDOWS
            #define __FUNCTION_NAME__   __FUNCTION__
        #else
            #define __FUNCTION_NAME__   __func__
        #endif
    #endif

    /*
     * STRINGIZE converts its argument into a string constant
     * see:
     * https://gcc.gnu.org/onlinedocs/gcc-7.5.0/cpp/Stringizing.html
     * https://stackoverflow.com/a/4368983
     */

    #define STRINGIZE_IMPLEMENTATION(arg) #arg
    #define STRINGIZE(arg) STRINGIZE_IMPLEMENTATION(arg)

    /*
     * CONCAT merges its arguments into one token
     * see:
     * https://gcc.gnu.org/onlinedocs/cpp/Concatenation.html
     * https://stackoverflow.com/a/4368983
     */

    #define CONCAT_IMPLEMENTATION(arg1, arg2) arg1 ## arg2
    #define CONCAT(arg1, arg2) CONCAT_IMPLEMENTATION(arg1, arg2)

    // fail info generator
    // is used in various assert and expect macros
    #define FAIL_INFO(failed_macro_name, x, op, y)              \
        #failed_macro_name " failed: " #x " " #op " " #y ", "   \
        __FILE__ ":" STRINGIZE(__LINE__)

    #define CHECK_FAIL_INFO(x, y, type, op, iop)                            \
        STRINGIZE(type ## _ ## op) " failed: " #x " " #iop " " #y ", "      \
        __FILE__ ":" STRINGIZE(__LINE__)

} // namespace sutf::_internal
