#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <csptr/smart_ptr.h>

/* COLORs */
#define RED      "\x1B[31m"
#define GRN      "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE     "\x1B[34m"
#define MAG      "\x1B[35m"
#define CYN      "\x1B[36m"

// BOLD COLORs
#define BOLD_RED     "\x1B[1;31m"
#define BOLD_GRN     "\x1B[1;32m"
#define BOLD_YELLOW  "\x1B[1;33m"
#define BOLD_BLUE    "\x1B[1;34m"
#define BOLD_MAG     "\x1B[1;35m"
#define BOLD_CYN     "\x1B[1;36m"

// RESET COLOR
#define RESET    "\x1B[0m"

/* Global Sandbox Mode */
int sandbox_mode = 0;

void free_wrapper(void *ptr, void *meta) {
    (void)meta;
    free(ptr);
}
void simple_free(void *ptr) {
    free(ptr);
}

/* Helper function to get bwrap prefix */
void get_bwrap_prefix(char *buffer, size_t size) {
    snprintf(buffer, size,
        "bwrap --unshare-all --new-session --ro-bind / / --proc /proc --dev /dev --tmpfs /tmp --bind . /mnt --chdir /mnt");
}

/* Helper function to get prompt string */
void get_prompt(char *buffer, size_t size) {
    if (sandbox_mode == 1) {
        snprintf(buffer, size, BOLD_RED "[SANDBOX] " RESET MAG "heyshell➤ " RESET);
    } else {
        snprintf(buffer, size, MAG "heyshell➤ " RESET);
    }
}

void banner();
void help();
void handle_sigint(int sig);

int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint);
    if (argc == 1) {
        printf(
                "HeyShell CLI Tool:\n"
                "Designed for Reverse Engineering, CTFs, CyberSec Nerds.\n\n"
                "Try \"heyshell <FILE>\"\n"
        );
        return 0;
    }
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf(
                "HeyShell CLI Tool:\n"
                "Designed for Reverse Engineering, CTFs, CyberSec Nerds.\n\n"
                "Try \"heyshell <FILE>\"\n"
        );
        return 0;
    } else if (access(argv[1], F_OK) != 0) {
        printf(
                "File Not Found: Try \"heyshell --help\".\n"
        );
        return 1;
    }

    banner();
    char fullCmd[102400];
    char prompt[256];
    for (int i = 0; i < 3; ) {
        // USER INPUT
        get_prompt(prompt, sizeof(prompt));
        char *raw_input = readline(prompt);
        char *input = raw_input;
        if (input == NULL) break;
        if (*input) {
            add_history(input);
        }
        printf(RESET);

        // If found Space at start of User_Input, Remove it.
        char *command = input;
        while (isspace((unsigned char)*command)) {
            command++;
        }
        if (*command == '\0') continue;

        // COMMANDs
        command[strcspn(command, "\n")] = 0;
        if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) {
            i = 3;
        } else if (strcmp(command, "help") == 0) {
            help();
        } else if (strcmp(command, "banner") == 0) {
            banner();
        } else if (strcmp(command, "sandbox") == 0) {
            sandbox_mode = !sandbox_mode;
            if (sandbox_mode == 1) {
                printf(BOLD_RED "Sandbox Mode: ON (All commands will run inside bwrap)\n" RESET);
            } else {
                printf(GRN "Sandbox Mode: OFF (Commands run normally)\n" RESET);
            }
        }
        // The bash commands allowed to run directly in HeyShell with add in their additional arguments
        else if (strncmp(command, "ls", 2) == 0 || strncmp(command, "lsd", 3) == 0 || strncmp(command, "cat", 3) == 0 || strncmp(command, "echo", 4) == 0 || strncmp(command, "python", 6) == 0 || strncmp(command, "bash", 4) == 0 || strncmp(command, "man", 3) == 0 || strncmp(command, "readelf", 7) == 0 || strncmp(command, "nm", 2) == 0 || strncmp(command, "strace", 6) == 0 || strncmp(command, "hexdump", 7) == 0 || strncmp(command, "base64", 6) == 0 || strncmp(command, "binwalk", 7) == 0 || strncmp(command, "nc", 2) == 0 || strncmp(command, "ssh", 3) == 0 || strncmp(command, "r2", 2) == 0 || strncmp(command, "radare2", 7) == 0 || strncmp(command, "frida", 5) == 0 || strncmp(command, "afl-", 4) == 0 || strncmp(command, "valgrind", 8) == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s %s", bwrap_prefix, command);
                system(fullCmd);
            } else {
                system(command);
            }
        }
        else if (strncmp(command, "cyclic", 6) == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s pwn %s", bwrap_prefix, command);
                system(fullCmd);
            } else {
                snprintf(fullCmd, sizeof(fullCmd), "pwn %s", command);
                system(fullCmd);
            }
        }
        // Shell Commands
        else if (strcmp(command, "bash") == 0 || strcmp(command, "python") == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s %s", bwrap_prefix, command);
                system(fullCmd);
            } else {
                system(command);
            }
        }
        // Common Basic Commands
        else if (strcmp(command, "strings") == 0 || strcmp(command, "file") == 0 || strcmp(command, "ltrace") == 0 || strcmp(command, "gdb") == 0 || strcmp(command, "size") == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s %s %s", bwrap_prefix, command, argv[1]);
                system(fullCmd);
            } else {
                snprintf(fullCmd, sizeof(fullCmd), "%s %s", command, argv[1]);
                system(fullCmd);
            }
        }
        else if (strcmp(command, "checksec") == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s %s --file %s", bwrap_prefix, command, argv[1]);
                system(fullCmd);
            } else {
                snprintf(fullCmd, sizeof(fullCmd), "%s --file %s", command, argv[1]);
                system(fullCmd);
            }
        }
        else if (strcmp(command, "objdump") == 0) {
            if (sandbox_mode == 1) {
                char bwrap_prefix[256];
                get_bwrap_prefix(bwrap_prefix, sizeof(bwrap_prefix));
                snprintf(fullCmd, sizeof(fullCmd), "%s %s -M intel -d %s > %s.disasm", bwrap_prefix, command, argv[1], argv[1]);
                system(fullCmd);
            } else {
                snprintf(fullCmd, sizeof(fullCmd), "%s -M intel -d %s > %s.disasm", command, argv[1], argv[1]);
                system(fullCmd);
            }
        }
        else {
            printf("❌️ Undefined command: \"%s\". Try \"help\". \n", command);
        }
        free(input);
    }
}

void banner() {
    char title[] =
        BLUE " ██╗  ██╗███████╗██╗   ██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"
             " ██║  ██║██╔════╝╚██╗ ██╔╝██╔════╝██║  ██║██╔════╝██║     ██║     \n"
             " ███████║█████╗   ╚████╔╝ ███████╗███████║█████╗  ██║     ██║     \n"
             " ██╔══██║██╔══╝    ╚██╔╝  ╚════██║██╔══██║██╔══╝  ██║     ██║     \n"
             " ██║  ██║███████╗   ██║   ███████║██║  ██║███████╗███████╗███████╗\n"
             " ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n" RESET;
    char desc[] =
        BOLD_CYN "HeyShell 1.0\n" RESET
        "Copyright (C) 2026 " YELLOW "Ooi Teng Qing - Hey1Me\n" RESET
        "License GPLv3 <" GRN "https://github.com/hey1me/HeyShell/blob/main/LICENSE" RESET ">.\n"
        "For help, type \"" YELLOW "help\".\n" RESET;

    printf("%s\n%s\n", title, desc);
}

void help() {
    char helpCmd[] = 
        BOLD_BLUE "HeyShell is a CLI Tool designed for Reverse Engineering, CTFs, CyberSec Nerds.\n" RESET
        YELLOW "\n---" RESET    " Available Bash Commands to directly use in HeyShell " YELLOW "---\n" RESET
        GRN "ls <...>" RESET      "       -- List Directory Contents\n"
        GRN "lsd <...>" RESET     "       -- List Directory Contents with Additional Icons\n"
        GRN "cat <...>" RESET     "       -- Concatenate files and print on the standard output\n"
        GRN "echo <...>" RESET    "       -- Display a line of text\n"
        GRN "man <...>" RESET     "       -- An interface to the system reference manuals\n"
        GRN "bash <...>" RESET    "       -- GNU Bourne-Again SHell\n"
        GRN "python <...>" RESET  "       -- An interpreted, interactive, object-oriented programming language\n"
        GRN "nm <...>" RESET      "       -- List symbols from object files\n"
        GRN "readelf <...>" RESET "       -- Display information about elf files\n"
        GRN "strace <...>" RESET  "       -- Trace system calls and signals\n"
        GRN "hexdump <...>" RESET "       -- Display file contents in hexadecimal, decimal, octal, or ascii\n"
        GRN "base64 <...>" RESET  "       -- Base64 encode/decode data and print to standard output\n"
        GRN "binwalk <...>" RESET "       -- Analyzes data for embedded file types\n"
        GRN "cyclic <...>" RESET  "       -- Cyclic pattern creator/finder\n"
        GRN "r2 <...>" RESET " / " GRN "radare2 <...>" RESET      "       -- Advanced command-line hexadecimal editor, disassembler and debugger\n"
        GRN "frida <...>" RESET  "       -- Dynamic Analysis\n"
        GRN "afl-<...> <...>" RESET  "       -- AFL++\n"
        GRN "valgrind <...>" RESET  "       -- A suite of tools for debugging and profiling programs\n"
        YELLOW "\n---" RESET    " Security Commands(Auto run with your selected binary file) " YELLOW "---\n" RESET
        GRN "sandbox" RESET     "       -- Toggle 'Sandbox' Mode (Use Bubblewrap)\n"
        GRN "file" RESET        "       -- Determine the binary file type\n"
        GRN "size" RESET        "       -- List section sizes and total size of binary files\n"
        GRN "strings" RESET     "       -- Print the sequences of printable characters of the binary file\n"
        GRN "ltrace" RESET      "       -- Library call tracer\n"
        GRN "checksec" RESET    "       -- Check executables and kernel properties\n"
        GRN "objdump" RESET     "       -- Write 'Intel Syntax Assembler Code' of the binary file into \"<binary-name>.disasm\"\n"
        YELLOW "\n---" RESET    " Remote Access & Connectivity " YELLOW "---\n" RESET
        GRN "nc" RESET          "       -- Arbitrary TCP and UDP connections and listens\n"
        GRN "ssh" RESET         "       -- OpenSSH remote login client\n"
        YELLOW "\n---" RESET    " Interactive Shells " YELLOW "---\n" RESET
        GRN "python" RESET      "       -- Python Shell\n"
        GRN "bash" RESET        "       -- Bash Shell\n"
        YELLOW "\n---" RESET    " HeyShell Additional Commands " YELLOW "---\n" RESET
        GRN "gdb" RESET         "       -- GNU Debugger\n"
        GRN "banner" RESET      "       -- Show Banner\n"
        GRN "help" RESET        "       -- Show This Session\n"
        GRN "quit" RESET " / " GRN "exit" RESET "       -- Exit HeyShell\n"
        "\n";
    printf("%s", helpCmd);
}


void handle_sigint(int sig) {
    (void)sig; 
    printf("\n");
    rl_on_new_line(); 
    rl_replace_line("", 0); 
    rl_redisplay(); 
}
