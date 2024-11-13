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

static std::string PROJECT_NAME;

void info_output(char *argv)
{
    fmt::print(fg(fmt::color::gray), "Usage: {} new <project_name>\n", argv[0]);
    fmt::print(fg(fmt::color::gray), "Usage: {} run\n", argv[0]);
}

std::string read_file_content(const std::string &file_location)
{
    std::ifstream file(file_location);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + file_location);
    }

    std::ostringstream content_stream;
    content_stream << file.rdbuf();
    std::string file_content = content_stream.str();

    if (file_content.find("project_name") != std::string::npos)
    {
        file_content.replace(file_content.find("project_name"), sizeof("project_name") - 1, PROJECT_NAME);
    }

    return file_content;
}

// TODO: use exceptions
void create_project(char *argv)
{
    std::string project_name{argv[1]};

    std::filesystem::create_directory("src");
    std::filesystem::create_directory("lib");
    std::filesystem::create_directory("include");
    std::filesystem::create_directory("build");

    std::ofstream cmake("CMakeLists.txt");
    std::ofstream main("src/main.cpp");
    std::ofstream readme("README.md");
    std::ofstream build("build.sh");
    std::ofstream ignore(".gitignore");

    std::string cmakeContent{read_file_content("../contents/cmake.txt")};
    std::string mainContent{read_file_content("../contents/main.txt")};
    std::string readmeContent{read_file_content("../contents/readme.txt")};
    std::string ignoreContent{read_file_content("../contents/ignore.txt")};
    std::string buildContent{read_file_content("../contents/build.txt")};

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

// TODO: OpenGL support tho.
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        info_output(*argv);
        return 1;
    }

    const std::string command = argv[1];
    std::string project_name;

    if (argv[2] != nullptr)
    {
        project_name = argv[2];
    }

    if (command == "run")
    {
        run_project();
    }
    else if (command == "new" && project_name != "")
    {
        PROJECT_NAME = project_name;
        create_project(*argv);
    }
    else
    {
        info_output(*argv);
    }

    return 0;
}
