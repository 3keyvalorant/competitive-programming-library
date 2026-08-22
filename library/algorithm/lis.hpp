#pragma once
#include "../basic/base.hpp"
template<class T> int lis_length(const vector<T>&a,bool strict=true){vector<T>d;for(auto&x:a){auto it=strict?lower_bound(all(d),x):upper_bound(all(d),x);if(it==d.end())d.push_back(x);else*it=x;}return d.size();}

