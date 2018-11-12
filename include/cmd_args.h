#ifndef CMD_ARGS_H
#define CMD_ARGS_H

#include <list>
#include <string>

class CmdArgs
{
public:
    CmdArgs(int argc, char **argv);

    bool HelpMessageRequested() const;

    const std::string &GetHelpMessage() const;

private:
    std::list<std::string> args;
};

#endif // CMD_ARGS_H
