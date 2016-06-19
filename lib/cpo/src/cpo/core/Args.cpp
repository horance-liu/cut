#include <cpo/core/Args.h>

#include <string.h>

CPO_NS_BEGIN

Args::Args(const std::vector<std::string>& opt)
  : m_argc(opt.size()), m_argv(new const char*[m_argc])
{
    for (size_t i=0; i<m_argc; i++)
    {
        m_argv[i] = new char[opt[i].size() + 1];
        ::strcpy((char*)m_argv[i], opt[i].c_str());
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

CPO_NS_END
