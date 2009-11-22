// This code was generated by CLI, a command line interface
// compiler for C++.
//

#include "options.hxx"

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace cli
{
  // unknown_option
  //
  unknown_option::
  ~unknown_option () throw ()
  {
  }

  void unknown_option::
  print (std::ostream& os) const
  {
    os << "unknown option '" << option () << "'";
  }

  const char* unknown_option::
  what () const throw ()
  {
    return "unknown option";
  }

  // unknown_argument
  //
  unknown_argument::
  ~unknown_argument () throw ()
  {
  }

  void unknown_argument::
  print (std::ostream& os) const
  {
    os << "unknown argument '" << argument () << "'";
  }

  const char* unknown_argument::
  what () const throw ()
  {
    return "unknown argument";
  }

  // missing_value
  //
  missing_value::
  ~missing_value () throw ()
  {
  }

  void missing_value::
  print (std::ostream& os) const
  {
    os << "missing value for option '" << option () << "'";
  }

  const char* missing_value::
  what () const throw ()
  {
    return "missing option value";
  }

  // invalid_value
  //
  invalid_value::
  ~invalid_value () throw ()
  {
  }

  void invalid_value::
  print (std::ostream& os) const
  {
    os << "invalid value '" << value () << "' for option '"
       << option () << "'";
  }

  const char* invalid_value::
  what () const throw ()
  {
    return "invalid option value";
  }

  template <typename X>
  struct parser
  {
    static int
    parse (X& x, char** argv, int n)
    {
      if (n > 1)
      {
        std::istringstream is (argv[1]);
        if (!(is >> x && is.eof ()))
          throw invalid_value (argv[0], argv[1]);
        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <>
  struct parser<bool>
  {
    static int
    parse (bool& x, char**, int)
    {
      x = true;
      return 1;
    }
  };

  template <>
  struct parser<std::string>
  {
    static int
    parse (std::string& x, char** argv, int n)
    {
      if (n > 1)
      {
        x = argv[1];
        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <typename X>
  struct parser<std::vector<X> >
  {
    static int
    parse (std::vector<X>& v, char** argv, int n)
    {
      X x;
      int i = parser<X>::parse (x, argv, n);
      v.push_back (x);
      return i;
    }
  };

  template <typename X>
  struct parser<std::set<X> >
  {
    static int
    parse (std::set<X>& s, char** argv, int n)
    {
      X x;
      int i = parser<X>::parse (x, argv, n);
      s.insert (x);
      return i;
    }
  };

  template <typename K, typename V>
  struct parser<std::map<K, V> >
  {
    static int
    parse (std::map<K, V>& m, char** argv, int n)
    {
      if (n > 1)
      {
        std::string s (argv[1]);
        std::string::size_type p = s.find ('=');

        if (p == std::string::npos)
        {
          K k = K ();

          if (!s.empty ())
          {
            std::istringstream ks (s);

            if (!(ks >> k && ks.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          m[k] = V ();
        }
        else
        {
          K k = K ();
          V v = V ();
          std::string kstr (s, 0, p);
          std::string vstr (s, p + 1);

          if (!kstr.empty ())
          {
            std::istringstream ks (kstr);

            if (!(ks >> k && ks.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          if (!vstr.empty ())
          {
            std::istringstream vs (vstr);

            if (!(vs >> v && vs.eof ()))
              throw invalid_value (argv[0], argv[1]);
          }

          m[k] = v;
        }

        return 2;
      }
      else
        throw missing_value (argv[0]);
    }
  };

  template <typename X, typename T, T X::*P>
  int
  thunk (X& x, char** argv, int n)
  {
    return parser<T>::parse (x.*P, argv, n);
  }
}

#include <map>
#include <cstring>

// options
//

options::
options (int argc,
         char** argv,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: help_ (),
  version_ (),
  output_dir_ (),
  generate_modifier_ (),
  suppress_inline_ (),
  suppress_usage_ (),
  long_usage_ (),
  option_length_ (0),
  generate_cxx_ (),
  generate_man_ (),
  generate_html_ (),
  man_prologue_ (),
  man_epilogue_ (),
  html_prologue_ (),
  html_epilogue_ (),
  class__ (),
  stdout_ (),
  hxx_suffix_ (".hxx"),
  ixx_suffix_ (".ixx"),
  cxx_suffix_ (".cxx"),
  man_suffix_ (".1"),
  html_suffix_ (".html"),
  option_prefix_ ("-"),
  option_separator_ ("--"),
  include_with_brackets_ (),
  include_prefix_ (),
  guard_prefix_ (),
  reserved_name_ ()
{
  _parse (1, argc, argv, opt, arg);
}

options::
options (int start,
         int argc,
         char** argv,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: help_ (),
  version_ (),
  output_dir_ (),
  generate_modifier_ (),
  suppress_inline_ (),
  suppress_usage_ (),
  long_usage_ (),
  option_length_ (0),
  generate_cxx_ (),
  generate_man_ (),
  generate_html_ (),
  man_prologue_ (),
  man_epilogue_ (),
  html_prologue_ (),
  html_epilogue_ (),
  class__ (),
  stdout_ (),
  hxx_suffix_ (".hxx"),
  ixx_suffix_ (".ixx"),
  cxx_suffix_ (".cxx"),
  man_suffix_ (".1"),
  html_suffix_ (".html"),
  option_prefix_ ("-"),
  option_separator_ ("--"),
  include_with_brackets_ (),
  include_prefix_ (),
  guard_prefix_ (),
  reserved_name_ ()
{
  _parse (start, argc, argv, opt, arg);
}

options::
options (int argc,
         char** argv,
         int& end,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: help_ (),
  version_ (),
  output_dir_ (),
  generate_modifier_ (),
  suppress_inline_ (),
  suppress_usage_ (),
  long_usage_ (),
  option_length_ (0),
  generate_cxx_ (),
  generate_man_ (),
  generate_html_ (),
  man_prologue_ (),
  man_epilogue_ (),
  html_prologue_ (),
  html_epilogue_ (),
  class__ (),
  stdout_ (),
  hxx_suffix_ (".hxx"),
  ixx_suffix_ (".ixx"),
  cxx_suffix_ (".cxx"),
  man_suffix_ (".1"),
  html_suffix_ (".html"),
  option_prefix_ ("-"),
  option_separator_ ("--"),
  include_with_brackets_ (),
  include_prefix_ (),
  guard_prefix_ (),
  reserved_name_ ()
{
  end = _parse (1, argc, argv, opt, arg);
}

options::
options (int start,
         int argc,
         char** argv,
         int& end,
         ::cli::unknown_mode opt,
         ::cli::unknown_mode arg)
: help_ (),
  version_ (),
  output_dir_ (),
  generate_modifier_ (),
  suppress_inline_ (),
  suppress_usage_ (),
  long_usage_ (),
  option_length_ (0),
  generate_cxx_ (),
  generate_man_ (),
  generate_html_ (),
  man_prologue_ (),
  man_epilogue_ (),
  html_prologue_ (),
  html_epilogue_ (),
  class__ (),
  stdout_ (),
  hxx_suffix_ (".hxx"),
  ixx_suffix_ (".ixx"),
  cxx_suffix_ (".cxx"),
  man_suffix_ (".1"),
  html_suffix_ (".html"),
  option_prefix_ ("-"),
  option_separator_ ("--"),
  include_with_brackets_ (),
  include_prefix_ (),
  guard_prefix_ (),
  reserved_name_ ()
{
  end = _parse (start, argc, argv, opt, arg);
}

void options::
print_usage (::std::ostream& os)
{
  os << "--help                       Print usage information and exit." << ::std::endl;

  os << "--version                    Print version and exit." << ::std::endl;

  os << "--output-dir|-o <dir>        Write the generated files to <dir> instead of the" << ::std::endl
     << "                             current directory." << ::std::endl;

  os << "--generate-modifier          Generate option value modifiers in addition to" << ::std::endl
     << "                             accessors." << ::std::endl;

  os << "--suppress-inline            Generate all functions non-inline." << ::std::endl;

  os << "--suppress-usage             Suppress the generation of the usage printing code." << ::std::endl;

  os << "--long-usage                 If no short documentation string is provided, use" << ::std::endl
     << "                             the complete long documentation string in usage." << ::std::endl;

  os << "--option-length <len>        Indent option descriptions <len> characters when" << ::std::endl
     << "                             printing usage." << ::std::endl;

  os << "--generate-cxx               Generate C++ code." << ::std::endl;

  os << "--generate-man               Generate documentation in the man page format." << ::std::endl;

  os << "--generate-html              Generate documentation in the HTML format." << ::std::endl;

  os << "--man-prologue <file>        Insert the content of <file> at the beginning of" << ::std::endl
     << "                             the man page file." << ::std::endl;

  os << "--man-epilogue <file>        Insert the content of <file> at the end of the man" << ::std::endl
     << "                             page file." << ::std::endl;

  os << "--html-prologue <file>       Insert the content of <file> at the beginning of" << ::std::endl
     << "                             the HTML file." << ::std::endl;

  os << "--html-epilogue <file>       Insert the content of <file> at the end of the HTML" << ::std::endl
     << "                             file." << ::std::endl;

  os << "--class <fq-name>            Generate the man page or HTML documentation only" << ::std::endl
     << "                             for the <fq-name> options class." << ::std::endl;

  os << "--stdout                     Write output to STDOUT instead of a file." << ::std::endl;

  os << "--hxx-suffix <suffix>        Use <suffix> instead of the default '.hxx' to" << ::std::endl
     << "                             construct the name of the generated header file." << ::std::endl;

  os << "--ixx-suffix <suffix>        Use <suffix> instead of the default '.ixx' to" << ::std::endl
     << "                             construct the name of the generated inline file." << ::std::endl;

  os << "--cxx-suffix <suffix>        Use <suffix> instead of the default '.cxx' to" << ::std::endl
     << "                             construct the name of the generated source file." << ::std::endl;

  os << "--man-suffix <suffix>        Use <suffix> instead of the default '.1' to" << ::std::endl
     << "                             construct the name of the generated man page file." << ::std::endl;

  os << "--html-suffix <suffix>       Use <suffix> instead of the default '.html' to" << ::std::endl
     << "                             construct the name of the generated HTML file." << ::std::endl;

  os << "--option-prefix <prefix>     Use <prefix> instead of the default '-' as an" << ::std::endl
     << "                             option prefix." << ::std::endl;

  os << "--option-separator <sep>     Use <sep> instead of the default '--' as an" << ::std::endl
     << "                             optional separator between options and arguments." << ::std::endl;

  os << "--include-with-brackets      Use angle brackets (<>) instead of quotes (\"\") in" << ::std::endl
     << "                             the generated '#include' directives." << ::std::endl;

  os << "--include-prefix <prefix>    Add <prefix> to the generated '#include' directive" << ::std::endl
     << "                             paths." << ::std::endl;

  os << "--guard-prefix <prefix>      Add <prefix> to the generated header inclusion" << ::std::endl
     << "                             guards." << ::std::endl;

  os << "--reserved-name <name>=<rep> Add <name> with an optional <rep> replacement to" << ::std::endl
     << "                             the list of names that should not be used as" << ::std::endl
     << "                             identifiers." << ::std::endl;
}

typedef
std::map<std::string, int (*) (options&, char**, int)>
_cli_options_map;

static _cli_options_map _cli_options_map_;

struct _cli_options_map_init
{
  _cli_options_map_init ()
  {
    _cli_options_map_["--help"] = 
    &::cli::thunk< options, bool, &options::help_ >;
    _cli_options_map_["--version"] = 
    &::cli::thunk< options, bool, &options::version_ >;
    _cli_options_map_["--output-dir"] = 
    &::cli::thunk< options, std::string, &options::output_dir_ >;
    _cli_options_map_["-o"] = 
    &::cli::thunk< options, std::string, &options::output_dir_ >;
    _cli_options_map_["--generate-modifier"] = 
    &::cli::thunk< options, bool, &options::generate_modifier_ >;
    _cli_options_map_["--suppress-inline"] = 
    &::cli::thunk< options, bool, &options::suppress_inline_ >;
    _cli_options_map_["--suppress-usage"] = 
    &::cli::thunk< options, bool, &options::suppress_usage_ >;
    _cli_options_map_["--long-usage"] = 
    &::cli::thunk< options, bool, &options::long_usage_ >;
    _cli_options_map_["--option-length"] = 
    &::cli::thunk< options, std::size_t, &options::option_length_ >;
    _cli_options_map_["--generate-cxx"] = 
    &::cli::thunk< options, bool, &options::generate_cxx_ >;
    _cli_options_map_["--generate-man"] = 
    &::cli::thunk< options, bool, &options::generate_man_ >;
    _cli_options_map_["--generate-html"] = 
    &::cli::thunk< options, bool, &options::generate_html_ >;
    _cli_options_map_["--man-prologue"] = 
    &::cli::thunk< options, std::string, &options::man_prologue_ >;
    _cli_options_map_["--man-epilogue"] = 
    &::cli::thunk< options, std::string, &options::man_epilogue_ >;
    _cli_options_map_["--html-prologue"] = 
    &::cli::thunk< options, std::string, &options::html_prologue_ >;
    _cli_options_map_["--html-epilogue"] = 
    &::cli::thunk< options, std::string, &options::html_epilogue_ >;
    _cli_options_map_["--class"] = 
    &::cli::thunk< options, std::string, &options::class__ >;
    _cli_options_map_["--stdout"] = 
    &::cli::thunk< options, bool, &options::stdout_ >;
    _cli_options_map_["--hxx-suffix"] = 
    &::cli::thunk< options, std::string, &options::hxx_suffix_ >;
    _cli_options_map_["--ixx-suffix"] = 
    &::cli::thunk< options, std::string, &options::ixx_suffix_ >;
    _cli_options_map_["--cxx-suffix"] = 
    &::cli::thunk< options, std::string, &options::cxx_suffix_ >;
    _cli_options_map_["--man-suffix"] = 
    &::cli::thunk< options, std::string, &options::man_suffix_ >;
    _cli_options_map_["--html-suffix"] = 
    &::cli::thunk< options, std::string, &options::html_suffix_ >;
    _cli_options_map_["--option-prefix"] = 
    &::cli::thunk< options, std::string, &options::option_prefix_ >;
    _cli_options_map_["--option-separator"] = 
    &::cli::thunk< options, std::string, &options::option_separator_ >;
    _cli_options_map_["--include-with-brackets"] = 
    &::cli::thunk< options, bool, &options::include_with_brackets_ >;
    _cli_options_map_["--include-prefix"] = 
    &::cli::thunk< options, std::string, &options::include_prefix_ >;
    _cli_options_map_["--guard-prefix"] = 
    &::cli::thunk< options, std::string, &options::guard_prefix_ >;
    _cli_options_map_["--reserved-name"] = 
    &::cli::thunk< options, std::map<std::string, std::string>, &options::reserved_name_ >;
  }
} _cli_options_map_init_;

int options::
_parse (int start,
        int argc,
        char** argv,
        ::cli::unknown_mode opt_mode,
        ::cli::unknown_mode arg_mode)
{
  bool opt = true;

  for (; start < argc;)
  {
    const char* s = argv[start];

    if (std::strcmp (s, "--") == 0)
    {
      start++;
      opt = false;
      continue;
    }

    _cli_options_map::const_iterator i (
      opt ? _cli_options_map_.find (s) : _cli_options_map_.end ());

    if (i != _cli_options_map_.end ())
    {
      start += (*(i->second)) (*this, argv + start, argc - start);
    }
    else if (opt && std::strncmp (s, "-", 1) == 0 && s[1] != '\0')
    {
      switch (opt_mode)
      {
        case ::cli::unknown_mode::skip:
        {
          start++;
          continue;
        }
        case ::cli::unknown_mode::stop:
        {
          break;
        }
        case ::cli::unknown_mode::fail:
        {
          throw ::cli::unknown_option (s);
        }
      }

      break;
    }
    else
    {
      switch (arg_mode)
      {
        case ::cli::unknown_mode::skip:
        {
          start++;
          continue;
        }
        case ::cli::unknown_mode::stop:
        {
          break;
        }
        case ::cli::unknown_mode::fail:
        {
          throw ::cli::unknown_argument (s);
        }
      }

      break;
    }
  }

  return start;
}

