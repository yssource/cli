// file      : cli/parser.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#ifndef CLI_PARSER_HXX
#define CLI_PARSER_HXX

#include <map>
#include <string>
#include <vector>
#include <memory> // std::auto_ptr
#include <istream>

#include "semantics/elements.hxx"
#include "semantics/unit.hxx"

class token;
class lexer;

class parser
{
public:
  typedef std::vector<semantics::path> paths;

  parser (paths const& include_paths): include_paths_ (include_paths) {}

  struct invalid_input {};

  std::auto_ptr<semantics::cli_unit>
  parse (std::istream& is, semantics::path const& path);

private:
  struct error {};

  void
  def_unit ();

  void
  include_decl ();

  bool
  decl (token&);

  void
  namespace_def ();

  void
  class_def ();

  bool
  option_def (token&);

  bool
  qualified_name (token&, std::string& name);

  bool
  fundamental_type (token&, std::string& name);

private:
  void
  recover (token& t);

private:
  paths const include_paths_;

  bool valid_;
  semantics::path const* path_;

  lexer* lexer_;

  semantics::cli_unit* root_;
  semantics::cli_unit* cur_;
  semantics::scope* scope_;

  typedef std::map<semantics::path, semantics::cli_unit*> include_map;
  include_map include_map_;
};

#endif // CLI_PARSER_HXX
