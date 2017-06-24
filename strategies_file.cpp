#include <map>
#include <set>
#include <regex>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <exception>
#include "strategies_file.h"
using namespace std;


PFile::PFile(const char* filename)
{
    read_file(filename);
}

string PFile::hash(string str,int len)
{
    assert(len<5);
    unsigned long long mod = 1;
    for (int i=0;i<len;i++)mod *= 26;
    unsigned long long p = 0;
    for (auto c : str)
        p = (p*127+int(c))%mod;
    for (int i=0;i<len;i++)
        str+=p%26+'a',p/=26;
    return str;

}


string PFile::deal_keyword(string &ss)
{
    static const char* keywords_arr[]=//{{{
    {"asm","do","if","return","typedef","auto","double","inline","short","typeid","bool","dynamic_cast","int","signed","typename","break","else","long","sizeof","union","case","enum","mutable","static","unsigned","catch","explicit","namespace","static_cast","using","char","export","new","struct","virtual","class","extern","operator","switch","void","const","false","private","template","volatile","const_cast","float","protected","this","wchar_t","continue","for","public","throw","while","default","friend","register","true","delete","goto","reinterpret_cast","try"};
    //}}}
    static set<string> keywords(keywords_arr,keywords_arr+sizeof(keywords_arr)/sizeof(char*));
    for (auto &s : keywords)
        if (ss.substr(0,s.length()) == s)
        {
            ss = ss.substr(s.length(),ss.length()-s.length());
            return s;
        }
    return "";
}

string PFile::deal_variable(string &ss)
{
    string::iterator it1 = ss.begin();
    if (!((*it1<='z' && *it1>='a') ||
                (*it1<='Z' && *it1>='A') ||
                (*it1 == '_')))
        return "";
    while (it1!=ss.end() && (
                (*it1<='z' && *it1>='a') ||
                (*it1<='Z' && *it1>='A') ||
                (*it1<='9' && *it1>='0') ||
                (*it1 == '_')))
        it1++;
    string res = string(ss.begin(),it1);
    ss = string(it1,ss.end());
    return res;
}

string PFile::deal_precompiled(string &ss)
{
    if (ss[0] == '#')
    {
        string::iterator it1 = ss.begin();
        while (it1!=ss.end() && *it1!='\n')
            it1++;
        string res = string(ss.begin(),it1);
        ss = string(it1,ss.end());
        return res;
    }
    return "";
}

string PFile::deal_comment(string &ss)
{
    if (ss[0] == '/' &&  ss[1] =='/')
    {
        string::iterator it1 = ss.begin();
        while (it1!=ss.end() && *it1!='\n')
            it1++;
        string res = string(ss.begin(),it1);
        ss = string(it1,ss.end());
        return res;
    }
    if (ss[0] == '/' && ss[1] == '*')
    {
        string::iterator it1 = ss.begin();
        while ((it1+1)!=ss.end() && !(*it1=='*' && *(it1+1)=='/'))
            it1++;
        string res = string(ss.begin(),it1);
        ss = string(it1,ss.end());
        return res;
    }
    return "";
}

string PFile::deal_string(string &ss)
{
    if (ss[0] == '"' || ss[0]=='\'')
    {
        string::iterator it1 = ss.begin()+1;
        while (it1!=ss.end() && *it1!=ss[0])
        {
            if (*it1!='\\')
                it1++;
            else
                it1+=2;
        }
        if (*it1==ss[0])
            it1++;
        string res = string(ss.begin(),it1);
        ss = string(it1,ss.end());
        return res;
    }
    return "";
}
string PFile::deal_number(string &ss)
{
    string::iterator it1;
    it1 = ss.begin();
    if (*it1<='9' && *it1>='0')
    {
        while (!isspace(*it1))
            it1++;
        string res = string(ss.begin(),it1);
        ss = string(it1,ss.end());
        return ss;
    }
    return "";
}
void PFile::make_fingerprint()
{
    string str = content;
    bool p_newline;
    vector<string> detail;
    while (str.length())
    {
        //cout<<"TEXT"<<str<<endl;
        p_newline = false;
        //去除空白字符
        {
            static char blank_arr[] = {' ','\t','\n','\r'};
            static set<char> blank(blank_arr,blank_arr+4);
            string::iterator it1 = str.begin();
            bool f1=false;
            while (blank.find(*it1)!=blank.end())
            {
                if (*it1 == '\n')f1 = true;
                it1++;
            }
            str = string(it1,str.end());
            if (f1)
                p_newline = true;
            if (!str.length())break;
        }
        //处理预编译指令
        {
            string res = deal_precompiled(str);
            if (res!="")
            {
                fp_structure+='#';
                detail.push_back(res);
                continue;
            }
        }
        //关键字
        {
            string f1,f2;
            f1 = deal_keyword(str);
            if (f1!="")
            {
                fp_structure+=f1[0]-'a'+'A';
                detail.push_back("");
                continue;
            }
        }
        //变量
        {
            string f1,f2;
            f1 = deal_variable(str);
            if (f1!="")
            {
                fp_structure+="v";
                detail.push_back(f1);
                continue;
            }
        }
        //注释
        {
            string f1;
            f1 = deal_comment(str);
            if (f1!="")
            {
                fp_structure+="/";
                detail.push_back(f1);
                continue;
            }
        }
        //字符串
        {
            string f1;
            f1 = deal_string(str);
            if (f1!="" && f1[0]=='"')
            {
                fp_structure+="s";
                st_strings.insert(f1);
                detail.push_back(f1);
                continue;
            }
            else if (f1!="" && f1[0]=='\'')
            {
                fp_structure+="c";
                detail.push_back(f1);
                continue;
            }
        }
        //数字
        {
            string f1;
            f1 = deal_number(str);
            if (f1!="")
            {
                fp_structure+="n";
                detail.push_back(f1);
                continue;
            }
        }
        //操作符
        {
            fp_structure+=str[0];
            detail.push_back("");
            str = str.substr(1,str.length()-1);
        }
    }
    for (auto &c : fp_structure)
        if (c!='C')
            fp_nocomment_structure += c;
}

void PFile::print_fp()
{
    cout<<"===============fp_structure=========="<<endl;
    cout<<fp_structure<<endl;
    cout<<"==========fp_nocomment_structure====="<<endl;
    cout<<fp_nocomment_structure<<endl;
    cout<<"=============st_strings=============="<<endl;
    for (auto w:st_strings)
        cout<<w<<"|";
    cout<<endl;
}

double string_compare(string s1,string s2)
{
    double A,B;
    double C=0,D=0;
    A=B=0;
    int l = min(s1.length(),s2.length());
    static const int tlen[] =
    {1,2,3,4,5,11,17,29,37,47,57,89,103,311,-1};
    for (int i=0;tlen[i]*4<l && ~tlen[i];i++)
    {
        int c1 = 0,c2=0;
        for (int j=0;j<50;j++)
        {
            string sx;
            sx = s1.substr(rand()%(s1.length()-(tlen[i])+1),tlen[i]);
            if (s2.find(sx)!=(unsigned long)(-1))
                c1++;
            sx = s2.substr(rand()%(s2.length()-(tlen[i])+1),tlen[i]);
            if (s1.find(sx)!=(unsigned long)(-1))
                c2++;
        }
        A+=1.0*pow((c1+c2)/100.0,1.0/(tlen[i]));
        B+=1.0;
        if (c1+c2)
        {
            C+=1.0*c1/(c1+c2);
            D++;
        }
    }
    if (!B || !D)return 0;
    C = exp(-abs(.5-C/D)*3);
    return A/B * C;
}

double set_compare(set<string> &s1,set<string> &s2)
{
    if (!s1.size() || !s2.size())
        return s1 == s2;
    set<string> result;
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),insert_iterator<set<string> > (result,result.begin()));
    return 1.0*result.size()/min(s1.size(),s2.size());
}

double fingerprint_compare(PFile &pf1,PFile &pf2)
{
    double A = string_compare(pf1.fp_structure,pf2.fp_structure);
    double B = string_compare(pf1.fp_nocomment_structure,pf2.fp_nocomment_structure);
    double C = set_compare(pf1.st_strings,pf2.st_strings);
    //cout<<A<<" "<<B<<" "<<C<<endl;
    return (A+B+C)/3.0;
}
