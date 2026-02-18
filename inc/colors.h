#ifndef COLORS_H
#define COLORS_H

// ==========================================
// 基础颜色代码 (不用背，复制粘贴即可)
// ==========================================
#define _RST    "\033[0m"       // Reset (重置)
#define _BLK    "\033[30m"      // Black
#define _RED    "\033[31m"      // Red (警告/错误)
#define _GRN    "\033[32m"      // Green (成功/Flag)
#define _YEL    "\033[33m"      // Yellow (提示/高亮)
#define _BLU    "\033[34m"      // Blue
#define _MAG    "\033[35m"      // Magenta (紫色/神秘)
#define _CYN    "\033[36m"      // Cyan (青色/科技感)
#define _WHT    "\033[37m"      // White

// ==========================================
// 样式代码
// ==========================================
#define _BOLD   "\033[1m"       // 加粗 (强调)
#define _DIM    "\033[2m"       // 变暗 (次要信息)
#define _ITAL   "\033[3m"       // 斜体
#define _UNDL   "\033[4m"       // 下划线
#define _BLNK   "\033[5m"       // 闪烁 (非常适合 Crash/Alert)
#define _REV    "\033[7m"       // 反色 (背景高亮)

// ==========================================
// 懒人宏 (直接包住字符串)
// 原理：C语言会自动拼接 "A" "B" 为 "AB"
// ==========================================
#define RED(s)   _RED s _RST
#define GREEN(s) _GRN s _RST
#define YELLOW(s)_YEL s _RST
#define BLUE(s)  _BLU s _RST
#define PURPLE(s)_MAG s _RST
#define CYAN(s)  _CYN s _RST
#define WHITE(s) _WHT s _RST

// 组合技：加粗的颜色
#define B_RED(s)    _BOLD _RED s _RST
#define B_CYAN(s)   _BOLD _CYN s _RST
#define B_PURPLE(s) _BOLD _MAG s _RST
#define B_GREEN(s)  _BOLD _GRN s _RST
#define B_YELLOW(s) _BOLD _YEL s _RST
#define B_BLUE(s)   _BOLD _BLU s _RST

// 特效：故障风
#define GLITCH(s)   _BLNK _RED s _RST  // 红闪
#define VOID_TXT(s) _REV _BLK s _RST   // 反色黑 (像被涂黑的机密文档)

#endif