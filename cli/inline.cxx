// file      : cli/inline.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include "inline.hxx"

namespace
{
  //
  //
  struct option: traversal::option, context
  {
    option (context& c) : context (c) {}

    virtual void
    traverse (type& o)
    {
      string name (ename (o));
      string type (o.type ().name ());
      string scope (escape (o.scope ().name ()));

      os << inl << "const " << type << "& " << scope << "::" << endl
         << name << " () const"
         << "{"
         << "return this->" << emember (o) << ";"
         << "}";

      if (modifier)
        os << inl << "void " << scope << "::" << endl
           << name << "(const " << type << "& x)"
           << "{"
           << "this->" << emember (o) << " = x;"
           << "}";
    }
  };

  //
  //
  struct class_: traversal::class_, context
  {
    class_ (context& c)
        : context (c), option_ (c)
    {
      names_option_ >> option_;
    }

    virtual void
    traverse (type& c)
    {
      string name (escape (c.name ()));

      os << "// " << name << endl
         << "//" << endl
         << endl;

      names (c, names_option_);
    }

  private:
    option option_;
    traversal::names names_option_;
  };
}

void
generate_inline (context& ctx)
{
  traversal::cli_unit unit;
  traversal::names unit_names;
  namespace_ ns (ctx);
  class_ cl (ctx);

  unit >> unit_names >> ns;
  unit_names >> cl;

  traversal::names ns_names;

  ns >> ns_names >> ns;
  ns_names >> cl;

  unit.dispatch (ctx.unit);
}
