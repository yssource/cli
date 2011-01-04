// file      : cli/semantics/class.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include <cutl/compiler/type-info.hxx>

#include <semantics/class.hxx>

namespace semantics
{
  // type info
  //
  namespace
  {
    struct init
    {
      init ()
      {
        using compiler::type_info;

        type_info ti (typeid (class_));
        ti.add_base (typeid (scope));
        insert (ti);
      }
    } init_;
  }
}
