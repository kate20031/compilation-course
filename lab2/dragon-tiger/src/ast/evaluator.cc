#include "evaluator.hh"

#include "../utils/errors.hh"

namespace ast {

int32_t Evaluator::visit(const IntegerLiteral &literal) {
  return literal.value;
}

int32_t Evaluator::visit(const BinaryOperator &binop) {
  int32_t left = binop.get_left().accept(*this);
  int32_t right = binop.get_right().accept(*this);

  switch (binop.op) {
  case o_plus:
    return left + right;
  case o_minus:
    return left - right;
  case o_times:
    return left * right;
  case o_divide:
    if (right == 0)
      utils::error(binop.loc, "division by zero");
    return left / right;
  case o_eq:
    return left == right;
  case o_neq:
    return left != right;
  case o_lt:
    return left < right;
  case o_le:
    return left <= right;
  case o_gt:
    return left > right;
  case o_ge:
    return left >= right;
  default:
    utils::error(binop.loc, "unsupported binary operator");
  }

  return 0;
}

int32_t Evaluator::visit(const Sequence &seq) {
  const auto exprs = seq.get_exprs();

  if (exprs.empty())
    utils::error(seq.loc, "cannot evaluate empty sequence");

  int32_t result = 0;

  for (auto expr : exprs)
    result = expr->accept(*this);

  return result;
}

int32_t Evaluator::visit(const IfThenElse &ite) {
  int32_t condition = ite.get_condition().accept(*this);

  if (condition)
    return ite.get_then_part().accept(*this);

  return ite.get_else_part().accept(*this);
}

int32_t Evaluator::visit(const StringLiteral &node) {
  utils::error(node.loc, "cannot evaluate string literal");
  return 0;
}

int32_t Evaluator::visit(const Let &node) {
  utils::error(node.loc, "cannot evaluate let expression");
  return 0;
}

int32_t Evaluator::visit(const Identifier &node) {
  utils::error(node.loc, "cannot evaluate identifier");
  return 0;
}

int32_t Evaluator::visit(const VarDecl &node) {
  utils::error(node.loc, "cannot evaluate variable declaration");
  return 0;
}

int32_t Evaluator::visit(const FunDecl &node) {
  utils::error(node.loc, "cannot evaluate function declaration");
  return 0;
}

int32_t Evaluator::visit(const FunCall &node) {
  utils::error(node.loc, "cannot evaluate function call");
  return 0;
}

int32_t Evaluator::visit(const WhileLoop &node) {
  utils::error(node.loc, "cannot evaluate while loop");
  return 0;
}

int32_t Evaluator::visit(const ForLoop &node) {
  utils::error(node.loc, "cannot evaluate for loop");
  return 0;
}

int32_t Evaluator::visit(const Break &node) {
  utils::error(node.loc, "cannot evaluate break");
  return 0;
}

int32_t Evaluator::visit(const Assign &node) {
  utils::error(node.loc, "cannot evaluate assignment");
  return 0;
}

} 