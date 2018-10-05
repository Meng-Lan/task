#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<ll,int> P;
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

typedef std::vector<std::string>::iterator It;

int free_sz=1<<30;
const int low_sz=1<<29;
const int sigma_size=128;
void sort(std::vector<std::string*> &pvs,int l,int r,int d){
	if(l+1==r) return;
	{
		std::vector<std::string*> tpvs[sigma_size];
		FOR(i,l,r){
			if(pvs[i]->size()<=d) tpvs[0].pb(pvs[i]);
			else tpvs[(*pvs[i])[d]].pb(pvs[i]);
		}
		int j=l;
		l+=tpvs[0].size();
		FOR(i,0,sigma_size){
			for(auto &v:tpvs[i]) pvs[j++]=v;
		}
	}
	int i=l,j=l;
	while(i<r){
		while(j<r&&(*pvs[j])[d]==(*pvs[i])[d]) ++j;
		sort(pvs,i,j,d+1);
		i=j;
	}
}

struct Node{
	std::string s;
	FILE *file;
	ll cnt;
	bool operator<(const Node &rhs)const{return s<rhs.s;}
};

struct Lan{
	std::vector<std::string> vs;
	int kase=0;
	int maxsz=0;

	void append(std::string &s){
		maxsz=std::max(maxsz,(int)s.size());
		vs.pb(std::string());
		free_sz-=sizeof(std::string);
		free_sz-=s.size();
		vs[vs.size()-1].swap(s);

		if(free_sz<(low_sz)){
			print();
			clear();
		}
	}

	void print(){
		if(vs.empty()) return;
		// std::vector<std::string*> pvs;
		// FOR(i,0,vs.size()){
		// 	pvs.pb(&vs[i]);
		// }
		// sort(pvs,0,pvs.size(),0);
		std::sort(vs.begin(),vs.end());
		char file_name[10];
		sprintf(file_name,"Lan.%d",kase++);
		FILE *file=fopen(file_name,"w");
		// for(int i=0,j;i<pvs.size();i=j){
		// 	j=i+1;
		// 	while(j<pvs.size()&&(*pvs[j])==(*pvs[i])) ++j;
		// 	fprintf(file,"%s %d\n",pvs[i]->c_str(),j-i);
		// }

		for(int i=0,j;i<vs.size();i=j){
			j=i+1;
			while(j<vs.size()&&vs[j]==vs[i]) ++j;
			fprintf(file,"%s %d\n",vs[i].c_str(),j-i);
		}
		fclose(file);
	}

	void clear(){
		if(vs.empty()) return;
		free_sz+=vs.size()*sizeof(std::string);
		for(auto &v:vs) free_sz+=v.size();
		vs.clear();
	}

	void merge(){
		// PV(1)
		int count=(low_sz)/maxsz;
		assert(count>=2);
		std::vector<int> now,tmp;
		FOR(i,0,kase) now.pb(i);
		char *s=new char[maxsz+1];
		ll cnt;
		while(now.size()>=2){
			// PV(2)
			while(now.size()>=2){
				std::vector<FILE*> files;
				for(int i=0;i<count&&!now.empty();++i){
					char file_name[10];
					sprintf(file_name,"Lan.%d",now.back());
					FILE *file=fopen(file_name,"r");
					files.pb(file);
					now.pop_back();
				}
				std::multiset<Node> ns;
				for(auto &v:files){
					if(fscanf(v,"%s %lld",s,&cnt)==EOF) continue;
					Node t;
					t.s=s;
					t.file=v;
					t.cnt=cnt;
					ns.insert(t);
				}

				char file_name[10];
				sprintf(file_name,"Lan.%d",kase);
				FILE *file=fopen(file_name,"w");

				while(!ns.empty()){
					auto node=*ns.begin();
					ns.erase(ns.begin());

					if(fscanf(node.file,"%s %lld",s,&cnt)!=EOF){
						Node t;
						t.s=s;
						t.file=node.file;
						t.cnt=cnt;
						ns.insert(t);
					}
					else fclose(node.file);

					while(!ns.empty()&&ns.begin()->s==node.s){
						node.cnt+=ns.begin()->cnt;
						auto t_file=ns.begin()->file;
						ns.erase(ns.begin());

						if(fscanf(t_file,"%s %lld",s,&cnt)!=EOF){
							Node t;
							t.s=s;
							t.file=t_file;
							t.cnt=cnt;
							ns.insert(t);
						}
						else fclose(t_file);
					}

					fprintf(file,"%s %lld\n",node.s.c_str(),node.cnt);
				}

				fclose(file);
				tmp.pb(kase);
				++kase;
			}
			for(auto &v:now) tmp.pb(v);
			now=tmp;
		}

		// PV(3)
		int top=100;
		char file_name[10];
		sprintf(file_name,"Lan.%d",now.front());
		FILE *file=fopen(file_name,"r");

		// PV(4)
		std::set<P> sp;
		std::vector<std::string> _vs;
		while(fscanf(file,"%s %lld",s,&cnt)==2){
			std::string ss(s);
			if(sp.size()<top){
				_vs.pb(std::string());
				_vs.back().swap(ss);
				sp.insert(P(cnt,_vs.size()-1));
			}
			else{
				if(cnt>sp.begin()->fi){
					auto tmp=*sp.begin();
					sp.erase(sp.begin());
					_vs[tmp.se].swap(ss);
					sp.insert(P(cnt,tmp.se));
				}
			}
		}

		// PV(5)
		fclose(file);
		file=fopen("ans1","w");
		for(auto it=sp.rbegin();it!=sp.rend();it++){
			fprintf(file,"%s %lld\n",_vs[it->se].c_str(),it->fi);
		}
		fclose(file);

		delete[] s;
	}
};
Lan lan;

int main() {
#ifdef MengLan
	int Beginning=clock();
	freopen("in","r",stdin);
	// freopen("out1","w",stdout);
#endif // MengLan

	
	std::string s;
	while(cin>>s){
		lan.append(s);
	}
	// printf("Time: %d\n",clock()-Beginning);
	lan.print();
	lan.clear();
	// printf("Time: %d\n",clock()-Beginning);
	lan.merge();



#ifdef MengLan
	printf("Time: %d\n",clock()-Beginning);
    system("pause");
#endif // MengLan
	return 0;
}
