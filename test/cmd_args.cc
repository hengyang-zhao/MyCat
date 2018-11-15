#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "cmd_args.h"

TEST(CmdArgs, ParseEmptyArgs) {
    const CmdArgs cmd_args(0, nullptr);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre());
}

TEST(CmdArgs, ParseProgNameOnly) {
    const char *args[] = {"prog_name"};
    const CmdArgs cmd_args(1, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre());
}

TEST(CmdArgs, ParseGoodArgs1) {
    const char *args[] = {"cat", "-A"};
    const CmdArgs cmd_args(2, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre());
}

TEST(CmdArgs, ParseGoodArgs2) {
    const char *args[] = {"cat", "--help"};
    const CmdArgs cmd_args(2, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre());
}

TEST(CmdArgs, ParseGoodArgs3) {
    const char *args[] = {"cat", "--version"};
    const CmdArgs cmd_args(2, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre());
}

TEST(CmdArgs, ParseGoodArgs4) {
    const char *args[] = {"cat", "a", "-n", "b", "c"};
    const CmdArgs cmd_args(5, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre("a", "b", "c"));
}

TEST(CmdArgs, ParseGoodArgs5) {
    const char *args[] = {"cat", "a", "-n", "-A", "--", "--help", "b", "c", "-z"};
    const CmdArgs cmd_args(9, args);

    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER_NONBLANK));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_ENDS));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::NUMBER));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::SQUEEZE_BLANK));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_TABS));
    EXPECT_TRUE(cmd_args.GetFlag(CmdArgs::Flag::SHOW_NONPRINTING));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::HELP));
    EXPECT_FALSE(cmd_args.GetFlag(CmdArgs::Flag::VERSION));

    EXPECT_THAT(cmd_args.GetFileNames(), testing::ElementsAre("a", "--help", "b", "c", "-z"));
}

TEST(CmdArgs, ParseBadArgs1) {
    const char *args[] = {"cat", "-z"};
    EXPECT_THROW(new CmdArgs(2, args), std::runtime_error);
}

TEST(CmdArgs, ParseBadArgs2) {
    const char *args[] = {"cat", "-z", "a", "b"};
    EXPECT_THROW(new CmdArgs(4, args), std::runtime_error);
}

TEST(CmdArgs, ParseBadArgs3) {
    const char *args[] = {"cat", "file", "--help?", "a", "b"};
    EXPECT_THROW(new CmdArgs(5, args), std::runtime_error);
}

