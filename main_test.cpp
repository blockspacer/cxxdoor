#include <gtest/gtest.h>
#include <folly/init/Init.h>

int main(int argc, char *argv[])
{
    folly::init(&argc, &argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

