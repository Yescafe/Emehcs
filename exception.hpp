#ifndef EMEHCS_EXCEPTIONS_HPP
#define EMEHCS_EXCEPTIONS_HPP

#include <string>
#include <string_view>
#include <preload.hpp>
#include <sstream>
#include <value.hpp>

namespace emehcs {

using ::std::string;
using ::std::string_view;

class LispException {
  public:
    LispException(string str = "[Exception] A so-called exception caused by", ValueSharedPtr vsp = nullptr)
        : vsp{vsp}
    {
        message = str + ": " + (vsp ? show(*vsp, true) : "<null>");
    }
    virtual ~LispException() = default;
    virtual string_view what() const {
        return message;
    }

  protected:
    string message;
    ValueSharedPtr vsp;
};

class NumArgsException : public LispException {
    static constexpr string_view text_prefix {"[NumArgsException] Excepted "};
    static constexpr string_view text_suffix {" arg(s): "};
    static constexpr string_view at_least {"at least "};
  public:
    NumArgsException(int nArgs, ValueSharedPtr vsp = nullptr, bool showAtLeast = false)
        : nArgs{nArgs}
    {
        ::std::stringstream ss;
        ss << text_prefix << (showAtLeast ? at_least : "") << nArgs << text_suffix;
        if (vsp) {
            ss << show(*vsp, true);
        }
        else {
            ss << "<null>";
        }

        LispException::message = ss.str();
        LispException::vsp = vsp;
    }

  private:
    int nArgs;
};

class TypeMismatchException : public LispException {
  public:
    TypeMismatchException(string str = "[TypeMismatch] Caused by", ValueSharedPtr vsp = nullptr)
        : LispException(str, vsp)
    { }
};

class ParserError : public LispException {
  public:
    ParserError(string str = "[ParserError] Unknown error")
    {
        message = str;
    }
};

class BadSpecialFormException : public LispException {
  public:
    BadSpecialFormException(string str = "[BadSpecialFormException] Caused by", ValueSharedPtr vsp = nullptr)
        : LispException(str, vsp)
    {
//        if (vsp == nullptr) {
//            message = str;
//        }
    }
};

class NotFunctionException : public LispException {
  public:
    NotFunctionException(string str = "[NotFunctionException] Caused by", ValueSharedPtr vsp = nullptr)
        : LispException(str, vsp)
    { }
};

class UnboundVarException : public LispException {
  public:
    UnboundVarException (string str = "[UnboundVarException] Caused by", ValueSharedPtr vsp = nullptr)
        : LispException(str, vsp)
    { }
};

class IdentifierException : public LispException {
  public:
    IdentifierException (string str = "[IdentifierException] Caused by", ValueSharedPtr vsp = nullptr)
            : LispException(str, vsp)
    { }
};

}

#endif //EMEHCS_EXCEPTIONS_HPP