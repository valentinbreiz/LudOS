/*
kmain.cpp

Copyright (c) 23 Yann BOUCHER (yann)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

// TODO : FAT32 write
// TODO : system calls
// TODO : user mode
// TODO : POC calculatrice
// TODO : Paging
// TODO : VFS
// TODO : initialisation PS/2
// TODO : enum pour les key qui se mappe au keymap

#ifndef __cplusplus
#error Must be compiler using C++ !
#endif

#ifndef NDEBUG
#define DEBUG
#endif

#include "greet.hpp"

#ifdef ARCH_i686
#include "i686/pc/init.hpp"
#endif

#include "fs/fat.hpp"
#include "fs/vfs.hpp"

#ifdef ARCH_i686
extern "C"
void kmain(uint32_t magic, const multiboot_info_t* mbd_info)
#else
void kmain()
#endif
{
#ifdef ARCH_i686
    i686::pc::init(magic, mbd_info);
#endif

    vfs::init();

    auto fs = fat::read_fat_fs(0, 0);
    if (fs.valid)
    {
        log("FAT %zd filesystem found on drive %zd\n", (size_t)fs.type, fs.drive);

        auto entries = fat::root_entries(fs);
        log("%zd\n", entries.size());
        for (const auto& entry : entries)
        {
            std::vector<uint8_t> data(entry.length);
            entry.read(data.data(), data.size());
            data.push_back('\0'); // sentinel value
            log("name : %s\n%s\n", entry.filename.data(), data.data());
        }
    }
    else
    {
        warn ("No FAT fs found\n");
    }

    greet();

    while (1)
    {
        nop();
    }
}
