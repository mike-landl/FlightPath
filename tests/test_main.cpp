#define CATCH_CONFIG_RUNNER
#include <catch2/catch_session.hpp>

#include <vector>
#include <filesystem>

int main([[maybe_unused]] int argc, char* argv[])
{
    std::filesystem::current_path(PROJECT_ROOT_PATH);

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
