
## 用途

用于实现自动并行化


## 实现线程库技术路线

- c代码嵌入riscv汇编代码编译得到完全.s的risc代码 / 完全直接用riscv汇编代码实现
- 使用clone系统调用
- 使用读写屏障相关riscv指令

