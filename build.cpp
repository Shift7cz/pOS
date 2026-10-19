#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void setPath(const std::string& path) {
    std::filesystem::path absolutePath = std::filesystem::absolute(path);
    std::filesystem::path projectDir = absolutePath.parent_path();
    std::filesystem::current_path(projectDir);
    system("pwd");
}

int main(int argc, char** argv) {
    setPath("../");
    const std::string cross = "riscv64-linux-gnu-";
    const std::string flags = "-march=rv64imac -mabi=lp64 -mcmodel=medany "
                              "-ffreestanding -fno-pie -fno-stack-protector -Wall -O2";

    enum TokenType { Asm, C, Linker, Identifier, Accessor, EndOfFile };
    struct Token { TokenType Type; std::string Data; };

    std::vector<std::string> asmList, cList, linkerList;

    // load
    std::ifstream file("config.pos");
    if (!file) { std::cerr << "can't read kernel.proj\n"; return 1; }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string project = buffer.str();

    // lexer
    std::vector<Token> tokens;
    std::string current;
    for (size_t i = 0; i <= project.length(); i++) {
        bool end = i == project.length();
        char c = end ? '\0' : project[i];

        if (end || c == '\n' || c == ' ' || c == '\r' || c == '\t') {
            if (!current.empty()) {
                if (current == "[ASM]") tokens.push_back({Asm, current});
                else if (current == "[C]") tokens.push_back({C, current});
                else if (current == "[LINKER]") tokens.push_back({Linker, current});
                else if (current == ">") tokens.push_back({Accessor, current});
                else tokens.push_back({Identifier, current});
                current = "";
            }
            if (end) tokens.push_back({EndOfFile, ""});
        }
        else current += c;
    }

    // parser
    TokenType group = EndOfFile; // "no group yet"
    for (size_t i = 0; i < tokens.size(); i++) {
        if (tokens[i].Type == Asm || tokens[i].Type == C || tokens[i].Type == Linker) {
            group = tokens[i].Type;
        }
        else if (tokens[i].Type == Accessor && i + 1 < tokens.size() && tokens[i + 1].Type == Identifier) {
            i++;
            switch (group) {
                case Asm:    asmList.push_back(tokens[i].Data); break;
                case C:      cList.push_back(tokens[i].Data); break;
                case Linker: linkerList.push_back(tokens[i].Data); break;
                default: std::cerr << "entry '" << tokens[i].Data << "' is outside any group\n"; return 1;
            }
        }
    }
    if (linkerList.empty()) { std::cerr << "no [LINKER] entry\n"; return 1; }

    // helper
    auto run = [](const std::string& cmd) {
        std::cout << "Running: " << cmd << "\n";
        return std::system(cmd.c_str()) == 0;
    };

    // compile
    std::string objs;
    std::vector<std::string> sources = asmList;
    sources.insert(sources.end(), cList.begin(), cList.end());

    for (const auto& src : sources) {
        std::string obj = "bin/obj/" + src + ".o";
        std::filesystem::create_directories(std::filesystem::path(obj).parent_path());
        if (!run(cross + "gcc " + flags + " -c " + src + " -o " + obj)) return 1;
        objs += obj + " ";
    }

    // link
    std::string link = cross + "gcc " + flags + " -nostdlib -nostartfiles -static -no-pie -T " +
                       linkerList[0] + " " + objs + "-o bin/kernel.elf";
    std::cout << "Linking: " << link << "\n";
    if (std::system(link.c_str()) != 0) return 1;

    // run in qemu
    std::string qemu = "qemu-system-riscv64 -machine virt -nographic -bios none -kernel bin/kernel.elf";
    if (argc > 1 && std::string(argv[1]) == "debug") qemu += " -s -S";
    std::cout << "Executing: " << qemu << "\n";
    return std::system(qemu.c_str()) == 0 ? 0 : 1;
}