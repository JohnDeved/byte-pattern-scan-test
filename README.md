# byte-pattern-scan-test

create a byte pattern scan in go vs typescript to see
1. how simple it is in each language to read and manipulate a foreign process
2. how much more faster can go be in such algorithm heavy tasks?
3. how cool of an algorithm i can make to get fast binary scans :)

<img width="572" alt="image" src="https://github.com/JohnDeved/byte-pattern-scan-test/assets/24187269/67519cb3-58fc-4b3c-ba34-fa4f1aac3f77">

# research

VM DMA 
  - https://news.ycombinator.com/item?id=29153564
  - https://github.com/memflow/memflow
  - https://github.com/ufrisk/pcileech
  - https://www.unknowncheats.me/forum/anti-cheat-bypass/565881-discussing-learning-hypervisor-based-anti-cheat-bypassing.html
  - https://github.com/a0rtega/pafish
  - kernel dbg, hyper-v https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/getting-started-with-windbg--kernel-mode-

Kernel Driver Method
  1. sign own driver with leaked cert https://www.unknowncheats.me/forum/anti-cheat-bypass/491501-nvidia-leaked-code-driver-cert.html
  2. map into R/W Memory code into some official driver with own driver
  3. unload own driver and hide tracks to avoid leaked cert detection by AC
