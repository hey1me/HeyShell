<p align="center">
  <img src="https://ghrb.waren.build/banner?header=HeyShell&subheader=Open+Source+RE+CLI+Tool&bg=E7F9FF-90C4E8&color=0060A0" alt="HeyShell Banner">
</p>

<p align="center">
  <a href="https://github.com/hey1me/HeyShell/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/License-GPLv3-green.svg" alt="License: GPLv3">
  </a>
  <a href="https://github.com/hey1me/HeyShell/stargazers">
    <img src="https://img.shields.io/github/stars/hey1me/HeyShell?style=social" alt="Stars">
  </a>
  <a href="https://github.com/hey1me/HeyShell/issues">
    <img src="https://img.shields.io/github/issues/hey1me/HeyShell.svg" alt="Issues">
  </a>
</p>

<img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/colored.png">

## 🎯 What is HeyShell?

HeyShell is an **interactive CLI tool** designed specifically for **Beginners, Reverse Engineering, CTFs (Capture The Flag), and CyberSecurity enthusiasts**. It provides a streamlined shell environment with pre-integrated security tools, making your workflow faster and more efficient.

Whether you're analyzing binaries, debugging exploits, or solving CTF challenges — HeyShell has you covered.

---

## 🚀 Features

### 🔒 Sandbox Mode
- **Bubblewrap (bwrap) Integration** — Run potentially dangerous commands in a secure, isolated container
- Toggle sandbox mode with a single `sandbox` command
- Protects your host system while experimenting with malware samples or exploits

### 🛠️ Pre-integrated Security Tools

| Category | Tools |
|----------|-------|
| **Disassembly & Analysis** | `readelf`, `objdump`, `nm`, `strings`, `file`, `size` |
| **Debugging** | `gdb`, `ltrace`, `strace` |
| **Binary Exploitation** | `cyclic`, `pwntools` |
| **Reverse Engineering** | `radare2` / `r2`, `hexdump`, `binwalk` |
| **Encoding** | `base64` |
| **Remote Access** | `nc`, `ssh` |

### ⌨️ Interactive Shell
- **Readline Support** — Command history, tab completion, and line editing
- Colored prompt and output for better readability
- Customizable prompt (shows `[SANDBOX]` when enabled)

### 🎨 Beautiful UI
- ASCII art banner on startup
- Color-coded command output (Red, Green, Yellow, Blue, Magenta, Cyan)
- Clean and professional terminal experience

### ⚡ Quick Commands
- All common bash commands (`ls`, `cat`, `echo`, `bash`, `python`, `man`) available directly
- No need to prefix with `!` or `bash -c`
- Auto-run security tools with your target binary

---

## 📦 Installation

### Prerequisites

Install the required dependencies:

```bash
# Debian/Ubuntu
sudo apt-get update
sudo apt-get install -y build-essential libreadline-dev libreadline8 bubblewrap

# Fedora
sudo dnf install gcc make readline-devel bubblewrap

# Arch Linux
sudo pacman -S base-devel readline bubblewrap

# macOS (Homebrew)
brew install readline bubblewrap
```

### Build HeyShell

```bash
git clone https://github.com/hey1me/HeyShell.git
cd HeyShell
gcc heyshell.c -o heyshell -lreadline -lncurses
sudo mv heyshell /usr/local/bin/
```

---

## 📖 Usage

### Basic Usage

```bash
# Run HeyShell with a binary file
heyshell <binary-file>
```

### Available Commands

```
help        — Show all available commands
banner      — Display HeyShell banner
sandbox    — Toggle Sandbox Mode (bwrap protection)
quit/exit   — Exit HeyShell
```

#### Security Tools (Auto-run with binary)

```bash
file <file>       # Determine file type
size <file>       # List section sizes
strings <file>    # Extract printable strings
ltrace <file>    # Trace library calls
gdb <file>       # GNU Debugger
objdump <file>    # Disassemble to Intel syntax
```

#### Direct Commands

```bash
ls, cat, echo, python, bash, man, readelf, nm, strace
hexdump, base64, binwalk, cyclic, nc, ssh, r2, frida, afl++
```

---

## 🖥️ Demo

```
$ heyshell vuln_binary

 ██╗  ██╗███████╗██╗   ██╗███████╗██╗  ██╗███████╗██╗     ██╗     
 ██║  ██║██╔════╝╚██╗ ██╔╝██╔════╝██║  ██║██╔════╝██║     ██║     
 ███████║█████╗   ╚████╔╝ ███████╗███████║█████╗  ██║     ██║     
 ██╔══██║██╔══╝    ╚██╔╝  ╚════██║██╔══██║██╔══╝  ██║     ██║     
 ██║  ██║███████╗   ██║   ███████║██║  ██║███████╗███████╗███████╗
 ╚═╝  ╚═╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

HeyShell 1.0
Copyright (C) 2026 Ooi Teng Qing - Hey1Me
License GPLv3+: GNU GPL version 3 or later.

heyshell➤ file vuln_binary
vuln_binary: ELF 64-bit LSB executable, x86-64, version 1 (SYSV)

heyshell➤ strings vuln_binary
...
heyshell➤ objdump
Disassembly saved to vuln_binary.disasm

heyshell➤ sandbox
Sandbox Mode: ON (All commands will run inside bwrap)

[Sandbox] heyshell➤ quit
```

---

## 📝 License

This project is licensed under the **GPLv3 License** — see the [LICENSE](https://github.com/hey1me/HeyShell/blob/main/LICENSE) file for details.

---

## ⭐ Show Your Support

If you find HeyShell useful, please give it a ⭐️ on GitHub!

[![Star HeyShell](https://img.shields.io/github/stars/hey1me/HeyShell?style=social)](https://github.com/hey1me/HeyShell)

---

## 💝 Donations and Tips

<a href="https://nowpayments.io/donation/hey1me" target="_blank" rel="noreferrer noopener"><img src="https://nowpayments.io/images/embeds/donation-button-black.svg" alt="Crypto donation button by NOWPayments"></a>
<br>
[![Crypto donation Link by NOWPayments](https://img.shields.io/badge/Crypto-Tip-blue?style=for-the-badge&logo=dollar-sign&logoColor=white)](https://nowpayments.io/donation/hey1me)
<br>

---

<p align="center">
  Made with ❤️ by <a href="https://github.com/heyshell">Hey1Me</a>
</p>
