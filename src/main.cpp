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

static std::string PROJECT_NAME = "";

void info_output(char *argv)
{
    fmt::print(fg(fmt::color::gray), "Usage: {} new <project_name>\n", argv[0]);
    fmt::print(fg(fmt::color::gray), "Usage: {} run\n", argv[0]);
}

void readFile(std::ifstream &file, std::string &content)
{
    if (!file.is_open())
    {
        std::cerr << "Error opening the file!";
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        size_t pos = 0;
        while ((pos = line.find("{NAME}", pos)) != std::string::npos)
        {
            line.replace(pos, 6, PROJECT_NAME);
            pos += PROJECT_NAME.length();
        }
        content += line + "\n";
    }
}

// TODO: use exceptions
void create_project(std::string &project_name)
{
    PROJECT_NAME = project_name;
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

    std::ifstream mainFile("../files/main.txt");
    std::ifstream buildFile("../files/build.txt");
    std::ifstream gitignoreFile("../files/gitignore.txt");
    std::ifstream readmeFile("../files/README.txt");
    std::ifstream cmakeFile("../files/CMakelistsT.txt");

    std::string mainContent{};
    std::string cmakeContent{};
    std::string readmeContent{};
    std::string ignoreContent{};
    std::string buildContent{};

    readFile(mainFile, mainContent);
    readFile(cmakeFile, cmakeContent);
    readFile(readmeFile, readmeContent);
    readFile(gitignoreFile, ignoreContent);
    readFile(buildFile, buildContent);

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
    fmt::print(fg(fmt::color::gray), "cppcli v1.0.1 (stable)\n");
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
