// file      : cli/context.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CLI_CONTEXT_HXX
#define CLI_CONTEXT_HXX

#include <map>
#include <string>
#include <ostream>

#include <cutl/shared-ptr.hxx>

#include "semantics.hxx"
#include "traversal.hxx"

using std::endl;

class context
{
public:
  typedef std::string string;

private:
  struct data;
  cutl::shared_ptr<data> data_;

public:
  std::ostream& os;

  typedef std::map<string, string> reserved_name_map_type;
  reserved_name_map_type& reserved_name_map;

private:
  struct data
  {
    reserved_name_map_type reserved_name_map_;
  };

public:
  // Escape C++ keywords, reserved names, and illegal characters.
  //
  string
  escape (string const&) const;

public:
  context (std::ostream& os_);
  context (context& c);

private:
  context&
  operator= (context const&);
};

#endif // CLI_CONTEXT_HXX