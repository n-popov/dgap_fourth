#include <iostream>
#include <iterator>
#include <fstream>
#include <filesystem>

int main() {
    std::filesystem::path parent_directory("..");
    auto path_to_main = parent_directory / "main.cpp";
    auto copy_path = parent_directory / "main_copied.cpp";
    std::cout << "Absolute: " << std::filesystem::absolute(copy_path) << std::endl;
    std::cout << "Relative: " << std::filesystem::relative(copy_path) << std::endl;
    std::cout << std::endl;
    std::filesystem::copy(path_to_main, copy_path);
    std::fstream reader(copy_path, std::ios::in);
    std::copy(std::istream_iterator<std::string>(reader),
            std::istream_iterator<std::string>(),
            std::ostream_iterator<std::string>(std::cout, " "));
    reader.close();
    std::filesystem::remove(copy_path);

    auto directory_for_lookup = parent_directory / "cmake-build-debug";
    std::filesystem::directory_iterator begin{directory_for_lookup};
    std::filesystem::directory_iterator end;
    for (auto it = begin; it != end; it++) {
        auto& current_file_path = it->path();
        std::cout << "Full path: " << std::filesystem::absolute(current_file_path) << std::endl;
        auto is_directory = std::filesystem::is_directory(current_file_path);
        std::cout << "Is a directory: " << std::boolalpha << is_directory << std::endl;
        if (!is_directory) {
            std::cout << "Stem: " << current_file_path.stem() << std::endl;
            std::cout << "Extension: " << current_file_path.extension() << std::endl;
        }
        std::cout << std::endl;
    }
    std::filesystem::remove(std::filesystem::path("..") / "non-existing.cpp");

    return 0;
}
