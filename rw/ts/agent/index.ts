const money = Process.getModuleByName("Sakura Clicker.exe").base.add(0x2F0DD8).readPointer().add(0x24).readPointer().add(0x8)

let time = Date.now() + 5000
let index = 0
for (; time >= Date.now(); index++) money.writeDouble(index)
console.log('writes', index/5, '/ sec')

time = Date.now() + 5000
index = 0
for (; time >= Date.now(); index++) void money.readDouble()
console.log('reads', index/5, '/ sec')