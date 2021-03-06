// file      : cli/html.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <vector>
#include <iostream>

#include "html.hxx"

using namespace std;

namespace
{
  struct option: traversal::option, context
  {
    option (context& c) : context (c) {}

    virtual void
    traverse (type& o)
    {
      using semantics::names;

      type::doc_list const& doc (o.doc ());

      if (options.suppress_undocumented () && doc.empty ())
        return;

      names& n (o.named ());

      os << "  <dt><code><b>";

      for (names::name_iterator i (n.name_begin ()); i != n.name_end (); ++i)
      {
        if (i != n.name_begin ())
          os << "</b></code>|<code><b>";

        os << escape_html (*i);
      }

      os << "</b></code>";

      string type (o.type ().name ());

      std::set<string> arg_set;

      if (type != "bool")
      {
        string s (
          translate_arg (
            doc.size () > 0 ? doc[0] : string ("<arg>"), arg_set));

        os << ' ' << format (escape_html (s), ot_html);
      }

      os << "</dt>" << endl;

      string d;

      // If we have both the long and the short descriptions, use
      // the long one.
      //
      if (type == "bool")
      {
        if (doc.size () > 1)
          d = doc[1];
        else if (doc.size () > 0)
          d = doc[0];
      }
      else
      {
        if (doc.size () > 2)
          d = doc[2];
        else if (doc.size () > 1)
          d = doc[1];
      }

      // Format the documentation string.
      //
      d = format (escape_html (translate (d, arg_set)), ot_html);

      os << "  <dd>";

      if (!d.empty ())
      {
        size_t b (0), e (0), i (0);

        for (size_t n (d.size ()); i < n; ++i)
        {
          if (d[i] == ' ' || d[i] == '\n')
            e = i;

          if (d[i] == '\n' || (i - b >= 76 && e != b))
          {
            if (b != 0)
            {
              os << endl
                 << "  ";
            }

            os << string (d, b, e - b);

            if (d[i] == '\n')
              os << endl;

            b = e = e + 1;
          }
        }

        // Flush the last line.
        //
        if (b != i)
        {
          if (b != 0)
          {
            os << endl
               << "  ";
          }

          os << string (d, b, i - b);
        }
      }

      os << "</dd>" << endl
         << endl;
    }

  private:
    string
    escape_html (string const& s)
    {
      string r;
      r.reserve (s.size ());

      for (size_t i (0), n (s.size ()); i < n; ++i)
      {
        switch (s[i])
        {
        case '<':
          {
            r += "&lt;";
            break;
          }
        case '&':
          {
            r += "&amp;";
            break;
          }
        default:
          {
            r += s[i];
            break;
          }
        }
      }

      return r;
    }
  };

  //
  //
  struct class_: traversal::class_, context
  {
    class_ (context& c)
        : context (c), option_ (c)
    {
      *this >> inherits_base_ >> base_ >> inherits_base_;
      base_ >> names_option_;

      names_option_ >> option_;
    }

    virtual void
    traverse (type& c)
    {
      if (!options.exclude_base ())
        inherits (c, inherits_base_);

      names (c, names_option_);
    }

  private:
    option option_;
    traversal::names names_option_;

    traversal::class_ base_;
    traversal::inherits inherits_base_;
  };
}

void
generate_html (context& ctx)
{
  traversal::cli_unit unit;
  traversal::names unit_names;
  traversal::namespace_ ns;
  class_ cl (ctx);

  unit >> unit_names >> ns;
  unit_names >> cl;

  traversal::names ns_names;

  ns >> ns_names >> ns;
  ns_names >> cl;

  ctx.os << "<dl class=\"options\">" << endl;

  if (ctx.options.class_ ().empty ())
    unit.dispatch (ctx.unit);
  else
  {
    for (vector<string>::const_iterator i (ctx.options.class_ ().begin ());
         i != ctx.options.class_ ().end (); ++i)
    {
      string n (*i);

      // Strip leading :: if present.
      //
      if (n.size () > 2 && n[0] == ':' && n[1] == ':')
        n = string (n, 2, string::npos);

      if (semantics::class_* c = ctx.unit.lookup<semantics::class_> ("", n))
        cl.traverse (*c);
      else
      {
        cerr << "error: class '" << *i << "' not found" << endl;
        throw generation_failed ();
      }
    }
  }

  ctx.os << "</dl>" << endl;
}
