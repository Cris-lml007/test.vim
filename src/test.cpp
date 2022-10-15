#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

struct salida{
	vector<string>text;
	salida(){}
};

string convert(string name){
	string r="";
	for(int i=0;i<name.length();i++){
		if(name[i]!='.') r+=name[i];
		else break;
	}
	return r;
}

bool rtest(vector<string>&pruebas,vector<salida>&resul,string name){
	ifstream arch;
	arch.open(name+".test");
	if(!arch.is_open()) return false;
	string text;
	bool sw=true,sw1=true;
	salida s1;
	while(getline(arch,text)){
		//if(text.length()>1){
			if(text[0]=='~'){
				if(text[1]=='~'){
					sw=false;
					continue;
				}else if(text[1]=='#') sw1=false;
			}
		//}//else sw1=true;
		if(sw)pruebas.push_back(text);
		else{
			if(sw1) s1.text.push_back(text+"\n");
			else{
				resul.push_back(s1);
				s1=salida();
				sw1=true;
			}
		}
	}
	resul.push_back(s1);
	return true;
}

long etest(string command,vector<salida>&resultado){
	long t;
	auto init=chrono::steady_clock::now();
	FILE *arch=popen(command.c_str(),"r");
	auto end=chrono::steady_clock::now();
	t=chrono::duration_cast<chrono::milliseconds>(end-init).count();
	string text="";
	salida s1;
	while(!feof(arch)){
		char a=fgetc(arch);
		if((int)a>=0){
			if(a!='\n'){
				text+=a;
			}else{
				text+=a;
				s1.text.push_back(text);
				text="";
			}
		}
	}
	resultado.push_back(s1);
	return t;
}

string analiticType(string program){
	string extend="";
	bool sw=false;
	for(int i=0;i<program.length();i++){
		if(program[i]=='.'){
			sw=true;
			continue;
		}
		if(sw) extend+=program[i];
	}
	return extend;
}

string pwd(){
	FILE *arch=popen("pwd","r");
	string text="",t="";
	while(!feof(arch)){
		char a=fgetc(arch);
		if(a>=0) text+=a;
	}
	for(int i=0;i<text.length()-1;i++){
		t+=text[i];
	}
	return t+" ";
}

string exec(string a,string program){
	string r="echo '";
	string ext="";
	r+=a;
	string extend=analiticType(program);
	if(extend=="py"){
		r+="' | python3 ";
		ext=".py";
	}else if(extend=="java"){
		r+="' | java -cp ";
		r+=pwd();
	}else if(extend=="lua"){
		r+="' | lua ";
		ext=".lua";
	}else if(extend=="js"){
		r+="' | node ";
		ext=".js";
	}else if(extend=="cs"){
		r+="' | dotnet run ";
	}else r+="' | ./";
	r+=convert(program);
	r+=ext;
	return r;
}

void showerrors(vector<salida>rc,vector<salida>rt,int t){
	int p,ver=0,l=rc[t].text.size()-1;
	cout<<"\033[41m------------OUTPUT------------\033[m"<<endl;
	for(int i=0;i<rc[t].text.size();i++){
		for(int ii=0;ii<rc[t].text[i].length();ii++){
			if(rc[t].text[i][ii]==rt[t].text[i][ii]) cout<<rc[t].text[i][ii];
			else{
				p=ii;
				ver=1;
				l=i;
				break;
			}
		}
		if(rt[t].text[l].length()>=rc[t].text[l].length()){
			for(int ii=p;ii<rt[t].text[i].size();ii++){
				if(ii!=rt[t].text[l].size()-1) cout<<"\033[41m"<<rt[t].text[i][ii];
				else cout<<"\033[m"<<rt[t].text[l][ii];
			}
		}else{
			for(int ii=p;ii<rc[t].text[l].size();ii++){
				if(ii!=rc[t].text[l].size()-1) cout<<"\033[41m"<<" ";
				else cout<<"\033[m"<<rc[t].text[l][ii];
			}
		}
		if(ver==1){
			cout<<"\033[m";
			break;
		}
	}
	cout<<"\033[42m-----------EXPECTED-----------\033[m"<<endl;
	for(int i=0;i<=l;i++) cout<<rc[t].text[i];
}

int main(int arg,char *npro[]){
	vector<string>pruebas;
	vector<salida>rc,rt;
	system("clear");
	if(!rtest(pruebas,rc,convert(npro[1]))){
		cout<<"Not found File .test\n";
		return 0;
	}
	long t[pruebas.size()];
	cout<<"-------------------------------"<<endl;
	if(pruebas.size()!=0){
		for(int i=0;i<pruebas.size();i++){
			t[i]=etest(exec(pruebas[i],npro[1]),rt);
		}
	}else{
		for(int i=0;i<rc.size();i++){
			t[i]=etest(exec("",npro[1]),rt);
		}
	}
	for(int ii=0;ii<rc.size();ii++){
		cout<<"\033[43m\ttest #"<<ii+1<<"\033[m"<<endl;
		bool ver=true;
		for(int i=0;i<rc[0].text.size();i++){
			if(rt[ii].text[i]!=rc[ii].text[i]){
				ver=false;
				break;
			}
		}
		cout<<(ver ? "\033[32myes":"\033[31mfalse")<<"\033[m"<<(ver ? "    ":"  ")<<"duration: "<<t[ii]<<" ms"<<endl;
		if(!ver) showerrors(rc,rt,ii);
		cout<<"-------------------------------"<<endl;
	}
	return 0;
}
