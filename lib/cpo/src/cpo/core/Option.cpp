#include <cpo/core/Option.hpp>

#include <iostream>

CPO_NS_BEGIN

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

CPO_NS_END
