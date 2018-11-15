#ifndef CMD_ARGS_H
#define CMD_ARGS_H

#include <list>
#include <string>
#include <stdexcept>

class CmdArgs
{
public:
    enum class Flag
    {
        NUMBER_NONBLANK     = 0x1 << 0,
        SHOW_ENDS           = 0x1 << 1,
        NUMBER              = 0x1 << 2,
        SQUEEZE_BLANK       = 0x1 << 3,
        SHOW_TABS           = 0x1 << 4,
        SHOW_NONPRINTING    = 0x1 << 5,
        HELP                = 0x1 << 6,
        VERSION             = 0x1 << 7,
    };

public:
    CmdArgs(int argc, const char *argv[]);

    bool GetFlag(Flag flag) const;
    const std::list<std::string> &GetFileNames() const { return file_names; }

private:
    void ParseArgs();

private:
    std::list<std::string> args;
    std::list<std::string> file_names;

    unsigned flags;
};

#endif // CMD_ARGS_H
