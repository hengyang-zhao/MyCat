#include <iostream>

#include "cmd_args.h"

void PrintHelpMessage(const std::string &progname)
{
    const std::string message =
        "Usage: " + progname + R"( [OPTION]... [FILE]...
Concatenate FILE(s) to standard output.

With no FILE, or when FILE is -, read standard input.

  -A, --show-all           equivalent to -vET
  -b, --number-nonblank    number nonempty output lines, overrides -n
  -e                       equivalent to -vE
  -E, --show-ends          display $ at end of each line
  -n, --number             number all output lines
  -s, --squeeze-blank      suppress repeated empty output lines
  -t                       equivalent to -vT
  -T, --show-tabs          display TAB characters as ^I
  -u                       (ignored)
  -v, --show-nonprinting   use ^ and M- notation, except for LFD and TAB
      --help     display this help and exit
      --version  output version information and exit

Examples:
  )" + progname + R"( f - g  Output f's contents, then standard input, then g's contents.
  )" + progname + R"(        Copy standard input to standard output.)";

    std::cout << message << std::endl;
}

int main(int argc, const char *argv[])
{
    try {
        const CmdArgs cmd_args(argc, argv);
        if (cmd_args.GetFlag(CmdArgs::Flag::HELP)) {
            PrintHelpMessage(argv[0]);
            return 0;
        }
    }
    catch (std::runtime_error& e) {
        std::cout << argv[0] << ": invalid option -- '" << e.what() <<
            "'\nTry `cat --help' for more information.\n";
        return 1;
    }




    return 0;
}
