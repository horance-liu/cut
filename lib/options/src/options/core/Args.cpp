#include "options/core/Args.h"
#include <string.h>

OPT_NS_BEGIN

Args::Args(const std::vector<std::string>& options)
  : m_argc(options.size()), m_argv(new const char*[m_argc])
{
    for (size_t i=0; i<m_argc; i++)
    {
        m_argv[i] = new char[options[i].size() + 1];
        ::strcpy((char*)m_argv[i], options[i].c_str());
    }
}

Args::~Args()
{
    for (size_t i=0; i<m_argc; i++)
    {
        delete [] m_argv[i];
    }
    delete [] m_argv;
}

int Args::argc() const
{
    return int(m_argc);
}

const char** Args::argv() const
{
    return m_argv;
}

OPT_NS_END
