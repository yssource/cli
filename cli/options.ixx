// This code was generated by CLI, a command line interface
// compiler for C++.
//

namespace cli
{
  // unknown_mode
  //
  inline unknown_mode::
  unknown_mode (value v)
  : v_ (v)
  {
  }

  // exception
  //
  inline std::ostream&
  operator<< (std::ostream& os, const exception& e)
  {
    e.print (os);
    return os;
  }

  // unknown_option
  //
  inline unknown_option::
  unknown_option (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& unknown_option::
  option () const
  {
    return option_;
  }

  // unknown_argument
  //
  inline unknown_argument::
  unknown_argument (const std::string& argument)
  : argument_ (argument)
  {
  }

  inline const std::string& unknown_argument::
  argument () const
  {
    return argument_;
  }

  // missing_value
  //
  inline missing_value::
  missing_value (const std::string& option)
  : option_ (option)
  {
  }

  inline const std::string& missing_value::
  option () const
  {
    return option_;
  }

  // invalid_value
  //
  inline invalid_value::
  invalid_value (const std::string& option,
                 const std::string& value)
  : option_ (option),  value_ (value)
  {
  }

  inline const std::string& invalid_value::
  option () const
  {
    return option_;
  }

  inline const std::string& invalid_value::
  value () const
  {
    return value_;
  }
}

// options
//

inline const bool& options::
help () const
{
  return help_;
}

inline const bool& options::
version () const
{
  return version_;
}

inline const std::string& options::
output_dir () const
{
  return output_dir_;
}

inline const bool& options::
suppress_inline () const
{
  return suppress_inline_;
}

inline const bool& options::
suppress_usage () const
{
  return suppress_usage_;
}

inline const bool& options::
long_usage () const
{
  return long_usage_;
}

inline const std::size_t& options::
option_length () const
{
  return option_length_;
}

inline const bool& options::
generate_cxx () const
{
  return generate_cxx_;
}

inline const bool& options::
generate_man () const
{
  return generate_man_;
}

inline const bool& options::
generate_html () const
{
  return generate_html_;
}

inline const std::string& options::
man_prologue () const
{
  return man_prologue_;
}

inline const std::string& options::
man_epilogue () const
{
  return man_epilogue_;
}

inline const std::string& options::
html_prologue () const
{
  return html_prologue_;
}

inline const std::string& options::
html_epilogue () const
{
  return html_epilogue_;
}

inline const std::string& options::
class_ () const
{
  return class__;
}

inline const bool& options::
stdout () const
{
  return stdout_;
}

inline const std::string& options::
hxx_suffix () const
{
  return hxx_suffix_;
}

inline const std::string& options::
ixx_suffix () const
{
  return ixx_suffix_;
}

inline const std::string& options::
cxx_suffix () const
{
  return cxx_suffix_;
}

inline const std::string& options::
man_suffix () const
{
  return man_suffix_;
}

inline const std::string& options::
html_suffix () const
{
  return html_suffix_;
}

inline const std::string& options::
option_prefix () const
{
  return option_prefix_;
}

inline const std::string& options::
option_separator () const
{
  return option_separator_;
}

inline const bool& options::
include_with_brackets () const
{
  return include_with_brackets_;
}

inline const std::string& options::
include_prefix () const
{
  return include_prefix_;
}

inline const std::string& options::
guard_prefix () const
{
  return guard_prefix_;
}

inline const std::map<std::string, std::string>& options::
reserved_name () const
{
  return reserved_name_;
}

