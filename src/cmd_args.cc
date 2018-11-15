#include <stdexcept>
#include <list>
#include <string>

#include "cmd_args.h"

CmdArgs::CmdArgs(int argc, const char *argv[]): flags(0)
{
    for (int i = 0; i < argc; ++i)
    {
        this->args.push_back(argv[i]);
    }

    ParseArgs();
}

void
CmdArgs::ParseArgs()
{
    bool first_arg = true;
    bool end_of_options = false;

    for (const std::string &arg: args)
    {
        if (first_arg) {
            first_arg = false;
            continue;
        }

        if (arg == "--") {
            end_of_options = true;
            continue;
        }

        if (end_of_options) {
            file_names.push_back(arg);
            continue;
        }

        if (arg.size() > 2 and arg.substr(0, 2) == "--") {

            if (arg == "--show-all") {
                flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
                flags |= static_cast<unsigned int>(Flag::SHOW_ENDS);
                flags |= static_cast<unsigned int>(Flag::SHOW_TABS);
            } else if (arg == "--number-nonblank") {
                flags |= static_cast<unsigned int>(Flag::NUMBER_NONBLANK);
            } else if (arg == "--show-ends") {
                flags |= static_cast<unsigned int>(Flag::SHOW_ENDS);
            } else if (arg == "--number") {
                flags |= static_cast<unsigned int>(Flag::NUMBER);
            } else if (arg == "--squeeze-blank") {
                flags |= static_cast<unsigned int>(Flag::SQUEEZE_BLANK);
            } else if (arg == "--show-tabs") {
                flags |= static_cast<unsigned int>(Flag::SHOW_TABS);
            } else if (arg == "--show-nonprinting") {
                flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
            } else if (arg == "--help") {
                flags |= static_cast<unsigned int>(Flag::HELP);
            } else if (arg == "--version") {
                flags |= static_cast<unsigned int>(Flag::VERSION);
            } else {
                throw std::runtime_error(arg);
            }
            continue;
        }

        if (arg.size() >= 1 and arg[0] == '-') {
            for (char c: arg.substr(1)) {
                switch (c) {
                    case 'A':   flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
                                flags |= static_cast<unsigned int>(Flag::SHOW_ENDS);
                                flags |= static_cast<unsigned int>(Flag::SHOW_TABS);
                                break;
                    case 'b':   flags |= static_cast<unsigned int>(Flag::NUMBER_NONBLANK);
                                break;
                    case 'e':   flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
                                flags |= static_cast<unsigned int>(Flag::SHOW_ENDS);
                                break;
                    case 'E':   flags |= static_cast<unsigned int>(Flag::SHOW_ENDS);
                                break;
                    case 'n':   flags |= static_cast<unsigned int>(Flag::NUMBER);
                                break;
                    case 's':   flags |= static_cast<unsigned int>(Flag::SQUEEZE_BLANK);
                                break;
                    case 't':   flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
                                flags |= static_cast<unsigned int>(Flag::SHOW_TABS);
                                break;
                    case 'T':   flags |= static_cast<unsigned int>(Flag::SHOW_TABS);
                                break;
                    case 'u':   break;
                    case 'v':   flags |= static_cast<unsigned int>(Flag::SHOW_NONPRINTING);
                                break;
                    default:    throw std::runtime_error(std::string(1, c));
                }
            }
            continue;
        }

        file_names.push_back(arg);
    }
}

bool
CmdArgs::GetFlag(Flag flag) const
{
    return flags & static_cast<unsigned>(flag);
}

