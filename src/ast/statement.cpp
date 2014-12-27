#include "statement.hpp"
#include "visitor.hpp"

Statement::~Statement()
{
}


void ExprStmt::accept(Visitor& v)
{
    v.visit(*this);
}
void Return::accept(Visitor& v)
{
    v.visit(*this);
}
void Block::accept(Visitor& v)
{
    v.visit(*this);
}
void Class::accept(Visitor& v)
{
    v.visit(*this);
}
void Concept::accept(Visitor& v)
{
    v.visit(*this);
}
void Function::accept(Visitor& v)
{
    v.visit(*this);
}
void Forever::accept(Visitor& v)
{
    v.visit(*this);
}
void While::accept(Visitor& v)
{
    v.visit(*this);
}
void For::accept(Visitor& v)
{
    v.visit(*this);
}
void If::accept(Visitor& v)
{
    v.visit(*this);
}
void Switch::accept(Visitor& v)
{
    v.visit(*this);
}
void Match::accept(Visitor& v)
{
    v.visit(*this);
}
