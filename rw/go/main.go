package main

import (
	"fmt"
	"time"

	gomem "github.com/Erickson400/GoMem/windows"
)

func main() {
	process, err := gomem.ProcessByName("Sakura Clicker.exe", false)
	if err != nil {
		fmt.Println(err)
		return
	}

	ptr1, _ := process.ReadInt32(process.ModBaseAddr + 0x2F0DD8)
	ptr2, _ := process.ReadInt32(uintptr(ptr1) + 0x24)
	moneyAddr := uintptr(ptr2) + 0x8

	// see how many writes we can do in a second
	// process.WriteFloat64(moneyAddr, 1337)

	index := 0
	for timeEnd := time.Now().Add(time.Second * 5).UnixMilli(); timeEnd > time.Now().UnixMilli(); index++ {
		process.WriteFloat64(moneyAddr, float64(index))
	}
	fmt.Println("writes", index/5, "per second")

	index = 0
	for timeEnd := time.Now().Add(time.Second * 5).UnixMilli(); timeEnd > time.Now().UnixMilli(); index++ {
		process.ReadFloat64(moneyAddr)
	}

	fmt.Println("reads", index/5, "per second")
}
