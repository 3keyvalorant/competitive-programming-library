#include "../library/all.hpp"

long long sum_op(long long a,long long b){return a+b;} long long sum_e(){return 0;}
int min_op(int a,int b){return min(a,b);}
struct Node{long long sum;int len;};Node node_op(Node a,Node b){return{a.sum+b.sum,a.len+b.len};}Node node_e(){return{0,0};}Node add_map(long long f,Node s){return{s.sum+f*s.len,s.len};}long long add_comp(long long f,long long g){return f+g;}long long add_id(){return 0;}

bool has_simple_cycle_brute(const vector<vector<int>>&g,int parity){
    int n=g.size();for(int s=0;s<n;++s){vector<char>used(n);used[s]=1;auto dfs=[&](auto&&self,int v,int len)->bool{for(int to:g[v]){if(to==s&&len>=2&&(len+1)%2==parity)return true;if(!used[to]&&to>=s){used[to]=1;if(self(self,to,len+1))return true;used[to]=0;}}return false;};if(dfs(dfs,s,0))return true;}return false;
}

int main(){
    mt19937 rng(712367);
    for(int n=1;n<=30;++n){
        vector<long long>a(n);for(auto&x:a)x=(int)(rng()%21)-10;FenwickTree<long long>fw(a);segtree<long long,sum_op,sum_e>sg(a);
        for(int q=0;q<100;++q){int l=rng()%n,r=rng()%n;if(l>r)swap(l,r);++r;long long want=accumulate(a.begin()+l,a.begin()+r,0LL);assert(fw.sum(l,r)==want&&sg.prod(l,r)==want);int i=rng()%n,d=(int)(rng()%11)-5;a[i]+=d;fw.add(i,d);sg.set(i,a[i]);}
    }
    for(int n=1;n<=50;++n){vector<int>a(n);for(int&x:a)x=rng()%1000;SparseTable<int,min_op>st(a);for(int l=0;l<n;++l)for(int r=l+1;r<=n;++r)assert(st.prod(l,r)==*min_element(a.begin()+l,a.begin()+r));}
    {vector<Node>a(20,{0,1});lazy_segtree<Node,node_op,node_e,long long,add_map,add_comp,add_id>sg(a);sg.apply(2,10,3);sg.apply(5,15,2);assert(sg.prod(0,20).sum==44&&sg.get(6).sum==5);}
    UnionFind uf(6);assert(uf.merge(0,1)&&uf.marge(1,2)&&uf.same(0,2)&&uf.size(1)==3);WeightedUnionFind<long long>wuf(4);assert(wuf.merge(0,1,3)&&wuf.merge(1,2,-2)&&wuf.difference(0,2)==1);
    assert(mint(-1).val()==998244352&&mint(2).pow(10)==mint(1024));combination<mint>co(20);assert(co.C(5,2)==mint(10)&&co.P(5,2)==mint(20));long long x,y;assert(extgcd(30,18,x,y)==6&&30*x+18*y==6);assert((crt({2,3},{3,5})==pair<long long,long long>(8,15)));assert(integer_sqrt(LLONG_MAX)==3037000499LL);
    for(int n=1;n<=8;++n)for(int tc=0;tc<300;++tc){
        vector<vector<int>>g(n);for(int i=0;i<n;++i)for(int j=i+1;j<n;++j)if(rng()%4==0)g[i].push_back(j),g[j].push_back(i);
        assert(has_odd_cycle_undirected(g)==has_simple_cycle_brute(g,1));
        assert(has_even_cycle_undirected(g)==has_simple_cycle_brute(g,0));
        auto c=find_shortest_cycle_undirected(g);assert(c.empty()==(!has_simple_cycle_brute(g,0)&&!has_simple_cycle_brute(g,1)));
    }
    for(int n=1;n<=8;++n)for(int tc=0;tc<100;++tc){
        TwoSAT sat(n);vector<array<int,4>>clauses;for(int q=0;q<20;++q){int i=rng()%n,j=rng()%n;bool f=rng()%2,g=rng()%2;sat.add_clause(i,f,j,g);clauses.push_back({i,f,j,g});}
        bool brute=false;for(int mask=0;mask<(1<<n);++mask){bool ok=true;for(auto c:clauses)ok&=(((mask>>c[0]&1)==c[1])||((mask>>c[2]&1)==c[3]));brute|=ok;}assert(sat.satisfiable()==brute);if(brute){auto a=sat.answer();for(auto c:clauses)assert(a[c[0]]==c[1]||a[c[2]]==c[3]);}
    }
    for(int n=1;n<=100;++n){vector<int>to(n);for(int&next:to)next=rng()%n;FunctionalGraph fg(to);for(int v=0;v<n;++v){int cur=v;for(int k=0;k<200;++k){assert(fg.jump(v,k)==cur);cur=to[cur];}assert(fg.dist_to_cycle(v)>=0&&fg.cycle_size(v)>0);}}
    for(int n=1;n<=100;++n){string s;for(int i=0;i<n;++i)s+=char('a'+rng()%3);auto z=z_algorithm(s);for(int i=0;i<n;++i){int k=0;while(i+k<n&&s[k]==s[i+k])++k;assert(z[i]==k);}auto d=manacher_odd(s);for(int i=0;i<n;++i){int k=0;while(i-k>=0&&i+k<n&&s[i-k]==s[i+k])++k;assert(d[i]==k);}}
    BinaryLifting<long long>bl(6);bl.add_edge(0,1,2);bl.add_edge(1,2,3);bl.add_edge(1,3,4);bl.add_edge(0,4,5);bl.add_edge(4,5,6);bl.build();assert(bl.lca(2,3)==1&&bl.dist(2,5)==16&&bl.jump(2,2)==0);
    {Dijkstra<long long>d(4);d.make_directedgraph(0,1,5);d.make_directedgraph(0,2,1);d.make_directedgraph(2,1,2);d.make_directedgraph(1,3,4);d.do_dijkstra(0);assert(d.output(3)==7&&d.path(3)==vector<int>({0,2,1,3}));auto bf=bellman_ford<long long>(3,{{0,1,1},{1,2,-3},{2,1,1}},0);assert(bf.negative[1]&&bf.negative[2]);}
    {auto mst=kruskal<long long>(4,{{0,1,4},{0,2,1},{1,2,2},{1,3,1},{2,3,5}});assert(mst.connected&&mst.cost==4);Dinic<long long>flow(4);flow.add_edge(0,1,2);flow.add_edge(0,2,1);flow.add_edge(1,2,1);flow.add_edge(1,3,1);flow.add_edge(2,3,2);assert(flow.flow(0,3)==3);}
    {EulerTour et(4);et.addVCost(0,1);et.addVCost(1,2);et.addVCost(2,3);et.addVCost(3,4);et.addEdge(0,1,5);et.addEdge(1,2,6);et.addEdge(1,3,7);et.build();assert(et.distV(2,3)==9&&et.distE(2,3)==13&&et.partV(1)==9&&et.partE(1)==13);et.changeECost(1,3,10);assert(et.distE(2,3)==16&&et.partE(1)==16);}
    assert(lis_length(vector<int>{3,1,4,1,5,9,2,6})==4);RollingHash rh(string("abracadabra"));assert(rh.get(0,4)==rh.get(7,11));assert(kmp_search(string("aaaaa"),string("aa"))==vector<int>({0,1,2,3}));
    cout<<"random tests passed\n";
}
