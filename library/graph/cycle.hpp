#pragma once
#include "../basic/base.hpp"

namespace cycle_detail {
inline vector<int> path(const vector<vector<int>>& g,int s,int t,int banned_vertex=-1,pair<int,int> banned_edge={-1,-1},bool directed=true){
    if(s==banned_vertex||t==banned_vertex)return{};
    vector<int>pre(g.size(),-1);queue<int>q;pre[s]=s;q.push(s);
    while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){bool bad=v==banned_edge.first&&to==banned_edge.second;if(!directed)bad=bad||(v==banned_edge.second&&to==banned_edge.first);if(bad||to==banned_vertex||pre[to]>=0)continue;pre[to]=v;q.push(to);}}
    if(pre[t]<0)return{};
    vector<int>p;for(int v=t;;v=pre[v]){p.push_back(v);if(v==s)break;}reverse(all(p));return p;
}
inline bool distinct(const vector<int>& p){auto q=p;sort(all(q));return adjacent_find(all(q))==q.end();}
}

inline vector<int> find_cycle_directed(const vector<vector<int>>& g){
    int n=g.size();vector<int>state(n),pos(n,-1),st;for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>dfs{{s,0}};state[s]=1;pos[s]=st.size();st.push_back(s);while(!dfs.empty()){auto&[v,i]=dfs.back();if(i==(int)g[v].size()){state[v]=2;pos[v]=-1;st.pop_back();dfs.pop_back();continue;}int to=g[v][i++];if(!state[to])state[to]=1,pos[to]=st.size(),st.push_back(to),dfs.push_back({to,0});else if(state[to]==1)return vector<int>(st.begin()+pos[to],st.end());}}return{};
}
inline bool has_cycle_directed(const vector<vector<int>>&g){return !find_cycle_directed(g).empty();}

inline vector<int> find_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>par(n,-1),dep(n),state(n);for(int s=0;s<n;++s)if(!state[s]){vector<pair<int,int>>st{{s,0}};state[s]=1;while(!st.empty()){auto&[v,i]=st.back();if(i==(int)g[v].size()){state[v]=2;st.pop_back();continue;}int to=g[v][i++];if(to==v)return{v};if(to==par[v])continue;if(!state[to])par[to]=v,dep[to]=dep[v]+1,state[to]=1,st.push_back({to,0});else if(state[to]==1&&dep[to]<dep[v]){vector<int>c;for(int x=v;x!=to;x=par[x])c.push_back(x);c.push_back(to);reverse(all(c));return c;}}}return{};
}
inline bool has_cycle_undirected(const vector<vector<int>>&g){return !find_cycle_undirected(g).empty();}

inline vector<int> find_cycle_through_directed(const vector<vector<int>>&g,int x){for(int to:g[x]){if(to==x)return{x};auto p=cycle_detail::path(g,to,x);if(!p.empty()){p.pop_back();p.insert(p.begin(),x);return p;}}return{};}
inline bool has_cycle_through_directed(const vector<vector<int>>&g,int x){return !find_cycle_through_directed(g,x).empty();}
inline vector<int> find_cycle_through_undirected(const vector<vector<int>>&g,int x){
    for(int to:g[x])if(to==x)return{x};
    for(int i=0;i<(int)g[x].size();++i)for(int j=i+1;j<(int)g[x].size();++j){int a=g[x][i],b=g[x][j];auto p=cycle_detail::path(g,a,b,x,{-1,-1},false);if(!p.empty()){p.insert(p.begin(),x);return p;}}
    return{};
}
inline bool has_cycle_through_undirected(const vector<vector<int>>&g,int x){return !find_cycle_through_undirected(g,x).empty();}

inline vector<int> find_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,v,u);if(p.empty())return{};p.pop_back();p.insert(p.begin(),u);return p;}
inline bool has_cycle_through_edge_directed(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_directed(g,u,v).empty();}
inline vector<int> find_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);return p.empty()?vector<int>{}:p;}
inline bool has_cycle_through_edge_undirected(const vector<vector<int>>&g,int u,int v){return !find_cycle_through_edge_undirected(g,u,v).empty();}

inline vector<int> find_odd_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();vector<int>color(n,-1),par(n,-1),dep(n);for(int s=0;s<n;++s)if(color[s]<0){queue<int>q;q.push(s);color[s]=0;while(!q.empty()){int v=q.front();q.pop();for(int to:g[v]){if(to==v)return{v};if(color[to]<0)color[to]=color[v]^1,par[to]=v,dep[to]=dep[v]+1,q.push(to);else if(color[to]==color[v]){int a=v,b=to;vector<int>x,y;while(dep[a]>dep[b])x.push_back(a),a=par[a];while(dep[b]>dep[a])y.push_back(b),b=par[b];while(a!=b)x.push_back(a),y.push_back(b),a=par[a],b=par[b];x.push_back(a);reverse(all(y));x.insert(x.end(),all(y));return x;}}}}return{};
}
inline bool has_odd_cycle_undirected(const vector<vector<int>>&g){return !find_odd_cycle_undirected(g).empty();}

inline vector<int> find_even_cycle_undirected(const vector<vector<int>>&g){
    int n=g.size();for(int u=0;u<n;++u)for(int v:g[u])if(u<v){int states=2*n;vector<int>pre(states,-1),pv(states,-1);queue<int>q;int s=2*u;pre[s]=s;q.push(s);while(!q.empty()){int z=q.front();q.pop();int x=z/2,p=z%2;for(int to:g[x]){if((x==u&&to==v)||(x==v&&to==u))continue;int nz=2*to+(p^1);if(pre[nz]<0)pre[nz]=z,pv[nz]=x,q.push(nz);}}int t=2*v+1;if(pre[t]<0)continue;vector<int>p;for(int z=t;;z=pre[z]){p.push_back(z/2);if(z==s)break;}reverse(all(p));if(cycle_detail::distinct(p))return p;}return{};
}
inline bool has_even_cycle_undirected(const vector<vector<int>>&g){return !find_even_cycle_undirected(g).empty();}

inline vector<int> find_shortest_cycle_directed(const vector<vector<int>>&g){vector<int>best;for(int s=0;s<(int)g.size();++s)for(int to:g[s]){auto p=cycle_detail::path(g,to,s);if(!p.empty()){p.pop_back();p.insert(p.begin(),s);if(best.empty()||p.size()<best.size())best=move(p);}}return best;}
inline vector<int> find_shortest_cycle_undirected(const vector<vector<int>>&g){vector<int>best;for(int u=0;u<(int)g.size();++u)for(int v:g[u])if(u<=v){auto p=cycle_detail::path(g,u,v,-1,{u,v},false);if(!p.empty()&&(best.empty()||p.size()<best.size()))best=move(p);}return best;}
inline vector<int> find_cycle_at_most_directed(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_directed(g);return (int)c.size()<=k?c:vector<int>{};}
inline vector<int> find_cycle_at_most_undirected(const vector<vector<int>>&g,int k){auto c=find_shortest_cycle_undirected(g);return (int)c.size()<=k?c:vector<int>{};}
