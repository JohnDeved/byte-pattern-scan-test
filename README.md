# R/W results 
**Go (gomem):**
```
writes 327.171 / sec
reads 1.148.995 / sec
```

**Typescript (Frida QuickJS):**
```
writes 896.751 / sec
reads 1.041.273 / sec
```

**Typescript (Frida v8):**
```
write 4.445.842 / sec
read 4.287.941 / sec
```

**C (Write/ReadProcessMemory)**
```
writes 404.634 / sec
reads 1.558.873 / sec
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

---

[FFI overhead](https://github.com/dyu/ffi-overhead) is a real problem in many languages, Go being one of the main offenders apparently.
This sadly makes Go useless/unviable for many applications that rely on many FFI calls. (like win API calls)
Nim seems to score way better in this. I need to test nim mem and see how it compares to Go and Frida.
According to recorded benchmarks, I can expect Nim to be 28.5 times faster than go with FFI. I wonder how that translates to RPM calls per second.
If it's a 1 to 1 translation, that would mean Nim has the potential to read 28.5 million addresses in a second. that would be about 6.5 times faster than Frida v8.
The question at some point kind of becomes "Does it matter?" and in the case of byte pattern scanning using only FFI calls it definitely does, but in most cases, it will never make a noticeable difference. Frida for example implements its own pattern scanning function, which most likely is executed within the dll running in the target process. Meaning with just one FFI call you get an unbeatable performance, compared to trying to archive the same thing using RPM calls.

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

