#include "ccinfra/options/program_options/Option.hpp"
#include <iostream>

CCINFRA_NS_BEGIN

using namespace std;
    
Option::Option(const string& key,const string& value)
    : _key(key)
    , _value(value)
{
}

void  Option::dump() const
{
    cout << "option dump start string key = " << _key << endl;
    cout << "option value dump start" << endl;
    cout << _value << endl;
}

const string& Option::value() const
{
    return _value;
}
    
const string& Option::key() const
{
    return _key;
}       

CCINFRA_NS_END
