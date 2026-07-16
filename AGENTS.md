# AGENTS.md — BalanceCar 项目 AI 协作规范

> 本文档适用于所有 AI 编程助手（Codex、Copilot 等），确保代码风格统一、减少低级错误。

---

## 1. 项目概况

- **芯片：** STM32F103C8T6
- **IDE：** Keil MDK（工程文件 Project.uvprojx）
- **语言：** C
- **编码：** UTF-8，注释可用中文

---

## 2. 目录结构（不可随意改动）

| 目录 | 性质 | 规则 |
|------|------|------|
| User/ | 用户代码 | ✅ 可修改 |
| Hardware/ | 硬件驱动 | ✅ 可修改 |
| System/ | 系统模块（Delay/PID/Timer） | ✅ 可修改 |
| Library/ | STM32 标准外设库 | ❌ 禁止修改 |
| Start/ | CMSIS 启动文件 | ❌ 禁止修改 |
| Objects/ | 编译产物 | ❌ Git 忽略 |
| Listings/ | 编译产物 | ❌ Git 忽略 |
| DebugConfig/ | 调试配置 | ❌ Git 忽略 |

**新增 .c/.h 放对应目录，不要在根目录乱丢文件。**

---

## 3. 编码规范

### 3.1 头文件必须自给自足

每个 .h 文件必须包含它自己需要的所有头文件，**不许依赖调用方帮你 include**。

`c
// ✅ 正确示例
#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>   // 因为下面用了 int8_t

void Motor_SetSpeed(int8_t Speed);
#endif
`

`c
// ❌ 错误示例（stdint.h 没包含，依赖 .c 文件先 include）
#ifndef __MOTOR_H
#define __MOTOR_H

void Motor_SetSpeed(int8_t Speed);  // int8_t 未定义！
#endif
`

### 3.2 命名约定

- 函数名：模块名_动作() — 如 Encoder1_Init()、OLED_ShowNum()
- 变量名：CamelCase — 如 left_pid、
ow_speed
- 宏/define 守卫：__文件名大写_H — 如 __ENCODER_H
- 新增代码保持和现有代码风格一致

### 3.3 注释

- 函数上方写功能、参数、返回值说明（参考现有 Encoder.c 的注释格式）
- 复杂逻辑写行内注释，简单的不必
- 中文注释 OK

---

## 4. Git 规则

### 4.1 Commit 格式

`
type: 简短描述
`

| type | 用途 |
|------|------|
| ix: | 修 bug |
| eat: | 新功能 |
| chore: | 杂项（配置、清理） |
| docs: | 文档 |

示例：ix: add missing stdint.h includes in headers

### 4.2 禁止提交

- .o .d .crf .axf 等编译产物
- Project.uvguix.* / Project.uvoptx（Keil 用户配置）
- .vscode/*.log

### 4.3 推送

每次修改完成后，AI 应主动询问是否需要 commit & push。

---

## 5. 问题记录

项目根目录的 ISSUES.md 用于记录已解决的问题。

- 每次解决一个 bug 或技术疑问 → 追加一条记录
- 格式：日期 → 问题描述 → 原因 → 修复 → 教训
- AI 修复问题后应主动建议追加到 ISSUES.md

---

## 6. 对 AI 的特别约束


- **同类问题不重复记录**：如果遇到的问题在 ISSUES.md 中已有相同原因的记录，直接引用已有记录即可，不新增重复条目。

- **永远不要改 Library/ 和 Start/ 下的文件**
- **新增代码前先看看现有模块，复用已有的外设初始化方式**
- **头文件 require 自己 include，这是铁律**
- **不要引入不必要的外部库或复杂抽象**
- **修改后主动问是否 commit & push**
- **回答要简洁，说的都是代码相关，不扩展无关话题**
