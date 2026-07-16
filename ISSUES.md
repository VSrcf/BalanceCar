# BalanceCar 问题记录

> 每次遇到问题 → 解决后追加一条，方便以后查漏补缺。

---

## 2026-07-16

### ✅ int16_t 未定义标识符（VSCode 报红线，Keil 正常）

**原因：** Encoder.h 等 5 个头文件使用了 <stdint.h> 的类型（int16_t、uint8_t、uint32_t 等），但都没写 #include <stdint.h>。Keil 编译没问题是因为 .c 文件先 include 了 stm32f10x.h（内部链式引入 stdint.h），但 VSCode IntelliSense 独立分析每个头文件时发现缺少依赖。

**修复：** 给 5 个头文件补充 #include <stdint.h>：
- Hardware/Encoder.h
- Hardware/Motor.h
- Hardware/PWM.h
- Hardware/OLED.h
- System/PID.h

**教训：** 每个头文件应该自给自足，依赖什么就 include 什么，不要靠调用方帮你 include。

---

### ✅ 编译产物干扰 Git 状态

**原因：** 项目没有 .gitignore，Objects/、Listings/ 等编译输出和日志文件都被 Git 跟踪，每次编译后 git status 一片红。

**修复：** 创建 .gitignore，忽略编译产物和 IDE 日志。

---
