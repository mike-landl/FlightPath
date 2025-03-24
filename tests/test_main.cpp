#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp>

#include <vector>

int main([[maybe_unused]] int argc, char* argv[])
{
    std::vector<const char*> new_argv{
        argv[0],
        "--reporter", "console",
        "--durations", "yes",
        "--verbosity", "high",
        "-#"
    };

    const int result = Catch::Session().run(
        static_cast<int>(new_argv.size()),
        const_cast<char**>(new_argv.data())
    );

    return result;
}
