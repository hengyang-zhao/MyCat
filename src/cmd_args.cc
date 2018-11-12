#include "cmd_args.h"

CmdArgs::CmdArgs(int argc, char **argv)
{
    // TODO: Fill up this->args
}

bool
CmdArgs::HelpMessageRequested() const
{
    // TODO: Check this->args and then return true/false
    return true;
}

const std::string &
CmdArgs::GetHelpMessage() const
{
    static const std::string &message = R"(Usage: cat [OPTION]... [FILE]...
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
  cat f - g  Output f's contents, then standard input, then g's contents.
  cat        Copy standard input to standard output.)";

    // TODO: Use argv[0] to replace "cat" in the first line
    return message;
}
