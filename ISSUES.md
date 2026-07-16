# BalanceCar 问题记录

> 每次遇到问题 → 查一下有没有同类记录，有就直接引用，没有才新增。方便以后查漏补缺。

---


### ✅ Timer.c 未定义标识符（Motor_SetLeftSpeed 等）+ TIM3_IRQn 未定义

**原因：** 两个问题：
1. #include "motor.h" 大小写不对，实际文件是 Motor.h（大写 M），VSCode IntelliSense 区分大小写
2. c_cpp_properties.json 缺少 STM32F10X_MD 宏定义，IntelliSense 不知道芯片型号，无法解析中断向量（TIM3_IRQn 等）

**修复：** Timer.c 和 Motor.c 中 "motor.h" → "Motor.h"；c_cpp_properties.json 的 defines 中添加 "STM32F10X_MD"

**教训：** 
- #include 文件名大小写必须和实际文件完全一致
- c_cpp_properties.json 的 defines 必须包含 STM32F10X_MD（或对应型号），否则无法解析 STM32 中断向量

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


### ✅ Timer.c 未定义标识符（Motor_SetLeftSpeed 等）+ TIM3_IRQn 未定义

**原因：** 两个问题：
1. #include "motor.h" 大小写不对，实际文件是 Motor.h（大写 M），VSCode IntelliSense 区分大小写
2. c_cpp_properties.json 缺少 STM32F10X_MD 宏定义，IntelliSense 不知道芯片型号，无法解析中断向量（TIM3_IRQn 等）

**修复：** Timer.c 和 Motor.c 中 "motor.h" → "Motor.h"；c_cpp_properties.json 的 defines 中添加 "STM32F10X_MD"

**教训：** 
- #include 文件名大小写必须和实际文件完全一致
- c_cpp_properties.json 的 defines 必须包含 STM32F10X_MD（或对应型号），否则无法解析 STM32 中断向量

### ✅ 编译产物干扰 Git 状态

**原因：** 项目没有 .gitignore，Objects/、Listings/ 等编译输出和日志文件都被 Git 跟踪，每次编译后 git status 一片红。

**修复：** 创建 .gitignore，忽略编译产物和 IDE 日志。

---
