#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int,int> P;
#define FOR(i,init,len) for(int i=(init);i<(len);++i)
#define For(i,init,len) for(int i=(init);i<=(len);++i)
#define fi first
#define se second
#define pb push_back
#define is insert
namespace IO {
	inline char getchar() {
		static const int BUFSIZE=5201314;
		static char buf[BUFSIZE],*begin,*end;
		if(begin==end) {
			begin=buf;
			end=buf+fread(buf,1,BUFSIZE,stdin);
			if(begin==end) return -1;
		}
		return *begin++;
	}
}
inline void read(int &in) {
	int c,symbol=1;
	while(isspace(c=IO::getchar()));
	if(c=='-') { in=0;symbol=-1; }
	else in=c-'0';
	while(isdigit(c=IO::getchar())) { in*=10;in+=c-'0'; }
	in*=symbol;
}
inline int read() { static int x;read(x);return x; }
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a; }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
#define PA(name,init,len) cout<<#name"["<<(len-init)<<"]=";FOR(_,init,len) cout<<name[_]<<" \n"[_==(len-1)];
#define Pa(name,init,len) cout<<#name"["<<(len-init+1)<<"]=";For(_,init,len) cout<<name[_]<<" \n"[_==(len)];
#define PV(name) cout<<#name"="<<name<<'\n';

const int maxn=1e6;

int main() {
#ifdef MengLan
	int Beginning=clock();
	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
#endif // MengLan

    std::default_random_engine r(time(NULL));
    FILE *in=fopen("in","w");
    FILE *out=fopen("out","w");
    // std::vector<std::string> vs;
    std::map<std::string,int> ms;
    std::vector<std::string> ans;
    FOR(i,0,maxn){
        int n=r()%20+20;
        std::string s;
        FOR(j,0,n) s+=r()%26+'a';
        // vs.pb(s);
        ms[s]++;
        if(ans.size()<100) ans.pb(s);
        fprintf(in,"%s\n",s.c_str());
    }
    FOR(i,0,ans.size()){
        ms[ans[i]]+=i+10;
        FOR(j,0,i+10) fprintf(in,"%s\n",ans[i].c_str());
    }
    fflush(in);
    // std::sort(vs.begin(),vs.end());
    for(auto &s:ms){
        fprintf(out,"%s %d\n",s.first.c_str(),s.second);
    }
    fflush(out);

    typedef std::pair<int,std::string> PIS;
    std::priority_queue<PIS> q;
    for(auto &v:ans) q.push(PIS(ms[v],v));
    
    FILE *res=fopen("ans","w");
    while(!q.empty()){
        auto u=q.top();q.pop();
        fprintf(res,"%s %d\n",u.se.c_str(),u.fi);
    }
    fflush(res);

    // PV(1)
    fclose(in);
    fclose(out);
    fclose(res);
    // PV(2);

#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    // system("pause");
#endif // MengLan
	return 0;
}
