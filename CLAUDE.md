# CLAUDE.md — BalanceCar 项目

> 本文件为 Claude Code 提供项目上下文和行为规范。通用 AI 协作规范见 [AGENTS.md](AGENTS.md)。

---

## 项目概况

- **芯片：** STM32F103C8T6 (Cortex-M3)
- **IDE：** Keil MDK（工程文件 `Project.uvprojx`）
- **语言：** C（C89/C90 风格，非 C99/C11）
- **编码：** UTF-8，注释可用中文

## 目录结构

| 目录 | 性质 | 可修改 |
|------|------|--------|
| `User/` | 用户主程序 | ✅ |
| `Hardware/` | 硬件驱动（Encoder/Motor/OLED/PWM/Key/LED/Track） | ✅ |
| `System/` | 系统模块（Delay/PID/Timer） | ✅ |
| `Library/` | STM32 标准外设库 | ❌ **禁止修改** |
| `Start/` | CMSIS 启动文件 | ❌ **禁止修改** |
| `Objects/` `Listings/` `DebugConfig/` | 编译产物/调试配置 | ❌ Git 忽略 |

新增 `.c`/`.h` 放入对应目录，不在根目录乱丢文件。

## 编码规范

### 头文件自给自足（铁律）

每个 `.h` 必须独立包含它自己需要的所有依赖，**不依赖调用方的 include 顺序**。

```c
// ✅ 正确
#ifndef __MOTOR_H
#define __MOTOR_H
#include <stdint.h>   // 因为下面用了 int8_t
void Motor_SetSpeed(int8_t Speed);
#endif

// ❌ 错误 — 缺少 stdint.h，int8_t 未定义
```

### 命名约定

- **函数名：** `模块名_动作()` — 如 `Encoder1_Init()`、`OLED_ShowNum()`
- **变量名：** `snake_case` — 如 `left_pid`、`now_speed`
- **类型名：** `snake_case_t` — 如 `pid_t`
- **include 守卫：** `__文件名大写_H` — 如 `__ENCODER_H`
- **新增代码保持与现有代码风格一致**

### 注释

- 函数上方写功能、参数、返回值说明
- 复杂逻辑写行内注释，简单的不必
- 中文注释 OK

## Git 规则

### Commit 格式

```
type: 简短描述
```

| type | 用途 |
|------|------|
| `fix:` | 修 bug |
| `feat:` | 新功能 |
| `chore:` | 杂项（配置、清理） |
| `docs:` | 文档 |

示例：`fix: add missing stdint.h includes in headers`

### 禁止提交

- `.o` `.d` `.crf` `.axf` 等编译产物
- `Project.uvguix.*` / `Project.uvoptx`（Keil 用户配置）
- `.vscode/*.log`

### 每次修改完成后

**主动询问是否需要 commit & push。**

## 问题记录

修改后如有值得记录的问题或修复，追加到 [ISSUES.md](ISSUES.md)，格式：日期 → 问题 → 原因 → 修复 → 教训。

## 行为约束

- **永远不要改 `Library/` 和 `Start/` 下的文件**
- **新增代码先看现有模块，复用已有的初始化方式**
- **头文件必须自给自足**
- **不引入不必要的外部库或复杂抽象**
- **回答简洁，聚焦代码，不扩展无关话题**
