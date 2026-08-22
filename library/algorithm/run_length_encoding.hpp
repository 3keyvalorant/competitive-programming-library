#pragma once
#include "../basic/base.hpp"
template<class Seq> auto run_length_encoding(const Seq&s){using T=typename Seq::value_type;vector<pair<T,int>>r;for(auto&x:s){if(r.empty()||r.back().first!=x)r.push_back({x,1});else++r.back().second;}return r;}

