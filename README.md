# R/W results 
**Go (gomem):**
```
writes 327171 / sec
reads 1148995 / sec
```

**Typescript (Frida):**
```
writes 896751 / sec
reads 1041273 / sec
```
###### (averaged over 5 seconds)

# byte-pattern-scan-test

create a byte pattern scan in go vs typescript to see
1. how simple it is in each language to read and manipulate a foreign process
2. how much more faster can go be in such algorithm heavy tasks?
3. how cool of an algorithm i can make to get fast binary scans :)

<img width="572" alt="image" src="https://github.com/JohnDeved/byte-pattern-scan-test/assets/24187269/67519cb3-58fc-4b3c-ba34-fa4f1aac3f77">

# research

VM DMA 
1. would need to spoof/hide that is running in a VM
2. use memflow/pcileech to R/W VM memory
  - https://news.ycombinator.com/item?id=29153564
  - https://github.com/memflow/memflow
  - https://github.com/ufrisk/pcileech
  - https://www.unknowncheats.me/forum/anti-cheat-bypass/565881-discussing-learning-hypervisor-based-anti-cheat-bypassing.html
  - https://github.com/a0rtega/pafish

Kernel Driver [Leaked Cert Method](https://www.unknowncheats.me/forum/anti-cheat-bypass/492166-questions-kernel-driver-signing-security.html)
  1. sign own driver with leaked cert https://www.unknowncheats.me/forum/anti-cheat-bypass/491501-nvidia-leaked-code-driver-cert.html
  2. map into R/W Memory code into some official driver with own driver
  3. unload own driver and hide tracks to avoid leaked cert detection by AC

# resources
https://github.com/gmh5225/awesome-game-security

- nim [CreateToolhelp32Snapshot](https://github.com/byt3bl33d3r/OffensiveNim/blob/master/src/taskbar_ewmi_bin.nim#L21C6-L21C22) (processes)
- nim win https://github.com/khchen/winim
- nim mem https://github.com/qb-0/Nimem
- zig [CreateToolhelp32Snapshot](https://github.com/ziglang/zig/blob/b9fc0d2908371dc4f7c95c03972d42e290d6e1e0/lib/std/debug.zig#L1198) (modules)
- zig win https://github.com/marlersoft/zigwin32
- zig mem https://github.com/Sirius902/grindel
- go win https://pkg.go.dev/golang.org/x/sys/windows
- go mem https://pkg.go.dev/github.com/Erickson400/GoMem/windows
- rust mem https://github.com/pseuxide/toy-arms

