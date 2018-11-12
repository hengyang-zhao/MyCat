#include <iostream>

#include "cmd_args.h"

int main(int argc, char **argv)
{
    const CmdArgs cmd_args(argc, argv);

    if (cmd_args.HelpMessageRequested()) {
        std::cout << cmd_args.GetHelpMessage() << std::endl;
        return 0;
    }

    return 0;
}
