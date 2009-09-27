// file      : cli/runtime-source.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2009 Code Synthesis Tools CC
// license   : MIT; see accompanying LICENSE file

#include "runtime-source.hxx"

using namespace std;

void
generate_runtime_source (context& ctx)
{
  ostream& os (ctx.os);

  os << "#include <string>" << endl
     << "#include <vector>" << endl
     << "#include <ostream>" << endl
     << "#include <sstream>" << endl
     << endl;

  os << "namespace cli"
     << "{";

  // unknown_option
  //
  os << "// unknown_option" << endl
     << "//" << endl
     << "unknown_option::" << endl
     << "~unknown_option () throw ()"
     << "{"
     << "}"
     << "void unknown_option::" << endl
     << "print (std::ostream& os) const"
     << "{"
     << "os << \"unknown option '\" << option () << \"'\";"
     << "}"
     << "const char* unknown_option::" << endl
     << "what () const throw ()"
     << "{"
     << "return \"unknown option\";"
     << "}";

  // unknown_argument
  //
  os << "// unknown_argument" << endl
     << "//" << endl
     << "unknown_argument::" << endl
     << "~unknown_argument () throw ()"
     << "{"
     << "}"
     << "void unknown_argument::" << endl
     << "print (std::ostream& os) const"
     << "{"
     << "os << \"unknown argument '\" << argument () << \"'\";"
     << "}"
     << "const char* unknown_argument::" << endl
     << "what () const throw ()"
     << "{"
     << "return \"unknown argument\";"
     << "}";

  // missing_value
  //
  os << "// missing_value" << endl
     << "//" << endl
     << "missing_value::" << endl
     << "~missing_value () throw ()"
     << "{"
     << "}"
     << "void missing_value::" << endl
     << "print (std::ostream& os) const"
     << "{"
     << "os << \"missing value for option '\" << option () << \"'\";"
     << "}"
     << "const char* missing_value::" << endl
     << "what () const throw ()"
     << "{"
     << "return \"missing option value\";"
     << "}";

  // invalid_value
  //
  os << "// invalid_value" << endl
     << "//" << endl
     << "invalid_value::" << endl
     << "~invalid_value () throw ()"
     << "{"
     << "}"
     << "void invalid_value::" << endl
     << "print (std::ostream& os) const"
     << "{"
     << "os << \"invalid value '\" << value () << \"' for option '\"" << endl
     << "   << option () << \"'\";"
     << "}"
     << "const char* invalid_value::" << endl
     << "what () const throw ()"
     << "{"
     << "return \"invalid option value\";"
     << "}";

  // parser class template & its specializations
  //
  os << "template <typename X>" << endl
     << "struct parser"
     << "{"
     << "static int" << endl
     << "parse (X& x, char** argv, int n)"
     << "{"
     << "if (n > 1)"
     << "{"
     << "std::istringstream is (argv[1]);"
     << "if (!(is >> x && is.eof ()))" << endl
     << "throw invalid_value (argv[0], argv[1]);"
     << "return 2;"
     << "}"
     << "else" << endl
     << "throw missing_value (argv[0]);"
     << "}"
     << "};";

  // parser<bool>
  //
  os << "template <>" << endl
     << "struct parser<bool>"
     << "{"
     << "static int" << endl
     << "parse (bool& x, char**, int)"
     << "{"
     << "x = true;"
     << "return 1;"
     << "}"
     << "};";

  // parser<string>
  //
  os << "template <>" << endl
     << "struct parser<std::string>"
     << "{"
     << "static int" << endl
     << "parse (std::string& x, char** argv, int n)"
     << "{"
     << "if (n > 1)"
     << "{"
     << "x = argv[1];"
     << "return 2;"
     << "}"
     << "else" << endl
     << "throw missing_value (argv[0]);"
     << "}"
     << "};";

  // parser<std::vector<X>>
  //
  os << "template <typename X>" << endl
     << "struct parser<std::vector<X> >"
     << "{"
     << "static int" << endl
     << "parse (std::vector<X>& v, char** argv, int n)"
     << "{"
     << "X x;"
     << "int i (parser<X>::parse (x, argv, n));"
     << "v.push_back (x);"
     << "return i;"
     << "}"
     << "};";

  // Parser thunk.
  //
  os << "template <typename X, typename T, T X::*P>" << endl
     << "int" << endl
     << "thunk (X& x, char** argv, int n)"
     << "{"
     << "return parser<T>::parse (x.*P, argv, n);"
     << "}";

  os << "}"; // namespace cli
}