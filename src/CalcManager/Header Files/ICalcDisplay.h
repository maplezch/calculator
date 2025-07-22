// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "../ExpressionCommandInterface.h"

// Callback interface to be implemented by the clients of CCalcEngine
// CCalcEngine 客户端需要实现的回调接口
class ICalcDisplay
{
public:
    virtual void SetPrimaryDisplay(const std::wstring& pszText, bool isError) = 0; // 设置主显示区文本，isError 为 true 时表示是错误信息
    virtual void SetIsInError(bool isInError) = 0;                                 // 通知 UI 当前是否处于错误状态
    virtual void SetExpressionDisplay(
        _Inout_ std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens,
        _Inout_ std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands) = 0;
    // 设置表达式的显示（如 1 + 2 × 3）。
    // tokens: 表达式中每个部分（操作数、操作符）及其类型（可能是 int 表示优先级或类别）。
    // commands : 对应的命令对象，用于表达式的可视化或重构。
    virtual void SetParenthesisNumber(_In_ unsigned int count) = 0; // 设置当前表达式中左括号的数量，可能用于提示是否括号不平衡。
    virtual void OnNoRightParenAdded() = 0;                         // 通知 UI 无法添加右括号（可能是因为没有对应的左括号）。
    virtual void MaxDigitsReached() = 0;                            // not an error but still need to inform UI layer.
    // 通知 UI 数字位数已达上限（例如最多输入 10 位数字）。
    // 虽不是错误，但可能需要弹出提示或声音反馈。
    virtual void BinaryOperatorReceived() = 0;                             // 收到一个二元运算符（如 +, -, ×, /）时的通知，可用于 UI 特效或格式更新。
    virtual void OnHistoryItemAdded(_In_ unsigned int addedItemIndex) = 0; // 表达式计算后被添加到历史记录。
    // 通知 UI 某个新项被加入历史列表，可以刷新列表界面。
    virtual void SetMemorizedNumbers(const std::vector<std::wstring>& memorizedNumbers) = 0; // 设置当前存储器中保存的数字列表（用于“M+”、“MR”等记忆功能）。
    virtual void MemoryItemChanged(unsigned int indexOfMemory) = 0;                          // 通知 UI 第 indexOfMemory 个内存槽发生变化（如被修改或清除）。
    virtual void InputChanged() = 0; // 通知 UI 输入框内容发生变化（例如按下数字或清除按钮），可能用于启用“计算”按钮或更新状态。
};

// std::wstring 是 C++ 标准库中提供的 宽字符字符串类型