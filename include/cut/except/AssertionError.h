#ifndef H9B2734EF_6E30_4E1E_BCBF_6E3F73F776AC
#define H9B2734EF_6E30_4E1E_BCBF_6E3F73F776AC

#include <cut/cut.h>
#include <exception>
#include <string>

CUT_NS_BEGIN

struct AssertionError : std::exception
{
    AssertionError(const std::string& source, const std::string& msg);
    ~AssertionError() noexcept = default;

    const char* what() const noexcept;

private:
    std::string msg;
};

CUT_NS_END

#endif
