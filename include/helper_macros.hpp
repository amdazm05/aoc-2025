#ifndef HELPER_MACROS
#define HELPER_MACROS

#define AOC_MAIN(name_of_input_file)                            \
int main(int argc, char* argv[]) {                              \
    Catch::Session session;                                     \
    using namespace Catch::Clara;                               \
    auto cli =                                                  \
        session.cli()                                           \
        | Opt(name_of_input_file, "file")                       \
            ["--input"]                                         \
            ("input file for test");                            \
    session.cli(cli);                                           \
    int returnCode = session.applyCommandLine(argc, argv);      \
    if (returnCode != 0)                                        \
        return returnCode;                                      \
    return session.run();                                       \
}                                                               \

#endif /* HELPER_MACROS */