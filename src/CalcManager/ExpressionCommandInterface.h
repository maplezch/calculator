// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include <memory> // for std::shared_ptr
#include <vector>
#include "Command.h"
#include "sal_cross_platform.h"

class ISerializeCommandVisitor;

class IExpressionCommand
{
public:
    virtual CalculationManager::CommandType GetCommandType() const = 0;
    virtual void Accept(_In_ ISerializeCommandVisitor& commandVisitor) = 0;
};
/*
所有表达式命令的基类接口。

GetCommandType()：返回命令的类型（比如数字、加法、括号等）。
Accept(...)：典型的访问者模式，用于将命令传递给序列化器或解释器。
*/

class IOperatorCommand : public IExpressionCommand
{
public:
    virtual void SetCommand(int command) = 0;
};
/*
抽象“运算符命令”，继承自 IExpressionCommand。

SetCommand:一个通用的设置命令代码的方法，可能代表 +、-、× 等操作符（通常是枚举值或整数常量）。
*/

class IUnaryCommand : public IOperatorCommand
{
public:
    virtual const std::shared_ptr<std::vector<int>>& GetCommands() const = 0;
    virtual void SetCommands(int command1, int command2) = 0;
};
/*
一元运算符命令（如正负号、平方根、倒数）。

储存一个或多个命令代码（因为某些一元操作可能需要多个低层命令组合实现）。
可能应用于一个操作数之上。
*/

class IBinaryCommand : public IOperatorCommand
{
public:
    virtual void SetCommand(int command) override = 0;
    virtual int GetCommand() const = 0;
};
/*
二元运算符命令（如加减乘除）。

除了设置命令，还能获取命令。
表示“两个操作数之间”的运算。
*/

class IOpndCommand : public IExpressionCommand
{
public:
    virtual const std::shared_ptr<std::vector<int>>& GetCommands() const = 0;
    virtual void AppendCommand(int command) = 0;
    virtual void ToggleSign() = 0;
    virtual void RemoveFromEnd() = 0;
    virtual bool IsNegative() const = 0;
    virtual bool IsSciFmt() const = 0;
    virtual bool IsDecimalPresent() const = 0;
    virtual const std::wstring& GetToken(wchar_t decimalSymbol) = 0;
    virtual void SetCommands(std::shared_ptr<std::vector<int>> const& commands) = 0;
};
/*
操作数命令接口，表示一个数字，比如 123.45。
*/

class IParenthesisCommand : public IExpressionCommand
{
public:
    virtual int GetCommand() const = 0;
};
/*
括号命令接口，用于表示表达式中的括号。

返回括号命令的类型（如左括号或右括号）。
*/
