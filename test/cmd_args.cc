#include "gtest/gtest.h"

#include "cmd_args.h"

TEST(CmdArgs, ParseOptions) {
    const CmdArgs cmd_args(0, nullptr);

    // TODO: Update this according to the correct implementation
    EXPECT_TRUE(cmd_args.HelpMessageRequested());
}
