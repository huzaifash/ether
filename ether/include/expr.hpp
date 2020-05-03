#pragma once

#include <typedef.hpp>
#include <vector>

enum ExprType {
	E_BINARY,
	E_CAST,
	E_FUNC_CALL,
	E_ARRAY_ACCESS,
	E_VARIABLE_REF,
	E_NUMBER,
	E_STRING,
	E_CHAR,
};

struct SourceFile;
struct Stmt;
struct DataType;
struct Token;

struct Expr {
	ExprType type;
	Token* head;
	Token* tail;
	union {
		struct {
			Token* identifier;
			Stmt* variable_refed;
		} variable_ref;

		struct {
			Expr* left;
			std::vector<Expr*>* args;
			Stmt* function_called;
		} func_call;

		struct {
			Expr* left;
			Expr* index;
		} array_access;
		
		struct {
			Expr* left;
			Expr* right;
			Token* op;
		} binary;

		struct {
			DataType* cast_to;
			Expr* right;
		} cast;
		
		Token* number;
		Token* string;
		Token* chr;
	};
};

u64 get_expr_char_count(Expr* expr);
