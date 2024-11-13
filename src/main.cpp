#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <fmt/core.h>
#include <fmt/color.h>
#include <stdexcept>
#include <exception>
#include <sstream>
#include "Contents.hpp"

void info_output(char *argv)
{
    fmt::print(fg(fmt::color::gray), "Usage: {} new <project_name>\n", argv[0]);
    fmt::print(fg(fmt::color::gray), "Usage: {} run\n", argv[0]);
}

// TODO: use exceptions
void create_project(std::string &project_name)
{
    std::cout << "asd" << std::endl;

    std::filesystem::create_directory(project_name);

    std::filesystem::current_path(project_name);

    std::filesystem::create_directory("src");
    std::filesystem::create_directory("lib");
    std::filesystem::create_directory("include");
    std::filesystem::create_directory("build");

    std::ofstream cmake("CMakeLists.txt");
    std::ofstream main("src/main.cpp");
    std::ofstream readme("README.md");
    std::ofstream build("build.sh");
    std::ofstream ignore(".gitignore");

    auto content = contents(project_name);

    std::string cmakeContent{content["cmake"]};
    std::string mainContent{content["main"]};
    std::string readmeContent{content["readme"]};
    std::string ignoreContent{content["ignore"]};
    std::string buildContent{content["build"]};

    cmake << cmakeContent;
    main << mainContent;
    build << buildContent;
    ignore << ignoreContent;
    readme << readmeContent;

    fmt::print(fg(fmt::color::green), "SUCCESS: Project created successfully.\n");
}

void run_project()
{
    if (std::filesystem::remove("build/main"))
    {
        fmt::print(fg(fmt::color::green), "SUCCESS: Deleted old binary");
    }
    if (std::filesystem::exists("build.sh") != true)
    {
        fmt::print(fg(fmt::color::red), "ERROR: build.sh does not exists\n");
        return;
    }

    system(("chmod +x build.sh"));
    system("./build.sh");
}

void show_version()
{
    fmt::print(fg(fmt::color::gray), "cppcli v1.0.0 (stable)\n");
}

// TODO: Commands Enum.
enum class Commands
{
    New,
    Run,
    Version,
    Unknown
};

// TODO: OpenGL support tho.
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        info_output(*argv);
        return 1;
    }

    std::string command = argv[1];
    std::string project_name;

    if (argc < 2)
    {
        info_output(*argv);
        return 1;
    }

    if (command == "--version")
    {
        show_version();
        return 0;
    }
    else if (command == "run")
    {
        run_project();
        return 0;
    }
    else if (command == "new")
    {
        // Ensure that the project name is provided as the second argument
        if (argc < 3) // Check if project name is provided
        {
            fmt::print(fg(fmt::color::red), "ERROR: Missing project name\n");
            info_output(*argv);
            return 1;
        }

        project_name = argv[2]; // Assign project name from argv[2]
        create_project(project_name);
        return 0;
    }
    else
    {
        std::cout << "Unknown command: " << argv[1] << std::endl;
        info_output(*argv);
    }

    return 0;
}
