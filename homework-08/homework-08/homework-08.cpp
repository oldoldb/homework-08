// homework-08.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<regex>
#include<memory>
#include<cassert>
using namespace std;
const int NumDelimiter=3;
const string delimiter[NumDelimiter]={"://","/","."};
class MyUrl
{
public:
	MyUrl();
	~MyUrl();
	bool Getstring();//得到输入
	void PrintResult();//输出分隔结果
	void SeperateUrl();//利用STL分隔URL
	void SeperateUrlWithoutSTL();//不用STL分隔URL
	bool IsUrl();//判断当前输入是否为URL,利用正则表达式,速度很慢

private:
	string url;//输入
	vector<string> result;//分隔结果
};

MyUrl::MyUrl()
{
}

MyUrl::~MyUrl()
{
}
void MyUrl::PrintResult()
{
	for(vector<string>::size_type i=0;i!=result.size();i++)
	{
		cout<<result[i];
		if(i==result.size()-1)
		{
			cout<<endl;
		}
		else
		{
			cout<<",";
		}
	}
}
bool MyUrl::IsUrl()
{
//	const regex pattern("^((site)|((ht|f)tp(s?)))\:\/\/[a-zA-Z0-9\u4e00-\u9fa5\-\._]+(\.[a-zA-Z0-9\u4e00-\u9fa5\-\._]+){2,}(\/?)([a-zA-Z0-9\u4e00-\u9fa5\-\.\?\,\'\/\\\+&amp;%\$#_]*)?$");//其中\u4e00-\u9fa5为中文字符unicode编码范围
//	const regex pattern("^(((ht|f)tp(s?))\://)?(www.|[a-zA-Z].)[a-zA-Z0-9\-\.]+\.(com|edu|gov|mil|net|org|biz|info|name|museum|us|ca|uk)(\:[0-9]+)*(/($|[a-zA-Z0-9\.\,\;\?\'\\\+&amp;%\$#\=~_\-]+))*$");	
	const regex pattern("^((http|https|site|ftp|ftps)\://)?(www.|[a-zA-Z].)[a-zA-Z0-9\-\.]+\.(com|edu|gov|mil|net|org|biz|info|name|museum|us|ca|uk)(\:[0-9]+)*(\/?)([a-zA-Z0-9\u4e00-\u9fa5\-\.\?\,\'\/\\\+&amp;%\$#_]*)?$");
	try
	{
		if(!regex_match(url,pattern))
		{
			throw("The format of the Url you input is not true");
		}
	}
	catch(char *ExceptionStr)
	{
		cout<<"Exception: "<<ExceptionStr<<endl;
		return false;
	}
	return true;
}
bool MyUrl::Getstring()
{
	cout<<"Please input the Url you want to seperate: "<<endl;
	try
	{
		if(getline(cin,url)==nullptr)
		{
			throw("Input Error");
		}
	}
	catch(char *ExceptionStr)
	{
		cout<<"Exception: "<<ExceptionStr<<endl;
		return false;
	}
	return true;
}
void MyUrl::SeperateUrl()
{
	size_t lastIndex=0;//截取起始点
	size_t templastIndex=0;
	size_t index=url.find_first_of(delimiter[0],lastIndex);//截取终止点
	size_t tempIndex=string::npos;
	int tempPos=0;//记录当前截取的是哪个分隔符
	
	while(index!=string::npos)
	{
		result.push_back(url.substr(lastIndex,index-lastIndex));
		lastIndex=index+delimiter[tempPos].length();
		tempIndex=string::npos;
		for(int i=0;i<NumDelimiter;i++)
		{
			templastIndex=url.find_first_of(delimiter[i],lastIndex);
			if(templastIndex<=tempIndex)
			{
				tempIndex=templastIndex;
				tempPos=i;
			}
		}
		index=tempIndex;
	}
	if(index-lastIndex>0)
	{
		result.push_back(url.substr(lastIndex,index-lastIndex));
	}
}
void MyUrl::SeperateUrlWithoutSTL()
{
	int begin=0;//记录跳过://后的开始点
	int length=url.length();
	string tempStr="";
	for(int i=0;i<length;i++)
	{
		if(url[i]==':'&&url[i+1]=='/'&&url[i+2]=='/')
		{
			result.push_back(tempStr);
			begin=i+3;//跳过://
			break;
		}
		tempStr+=url[i];
	}
	tempStr="";
	for(int i=begin;i<length;i++)
	{
		if(i==length-1)
		{
			tempStr+=url[i];
			result.push_back(tempStr);
		}
		else if(url[i]=='.'||url[i]=='/')
		{
			result.push_back(tempStr);
			tempStr="";
		}
		else
		{
			tempStr+=url[i];
		}
	}
}
int _tmain(int argc, _TCHAR* argv[])
{ 
	MyUrl myUrl=MyUrl::MyUrl();
	while(true)
	{
		if(!myUrl.Getstring())//未正确输入
		{
			continue;
		}
		if(!myUrl.IsUrl())//未输入正确格式的URL
		{
			continue;
		}
		myUrl.SeperateUrl();
//		myUrl.SeperateUrlWithoutSTL();
		myUrl.PrintResult();
		break;//正确处理后直接跳出
	}
	return 0;
}


//
///*------局部变量的生命周期的理解------*/
//void test1()//在if代码块中中定义的string局部变量str在超出该代码块时已经无法引用,会报错"未声明标识符str",即str已经被销毁
//{
//	if(true)
//	{
//		string str;
//		str="Hello,World";
//	}
//	cout<<str<<endl;
//}
///*------栈和堆两种内存申请方式------*/
///*---
//栈区:由编译器自动分配和释放,存放函数的参数值,局部变量的值等,
//	甚至函数的调用过程都是用栈来完成
//堆区:一般由程序猿手动申请以及释放,若程序猿不释放,程序结束时
//	可能由操作系统回收
//---*/
//void test2()
//{
//	/*---
//	new即分配了一块堆内存,指针p分配一块栈内存
//	即在栈内存中存放了一个指向一块堆内存的指针p
//	---*/
//	/*---
//	据说这是VC6的汇编码
//	push         14h
//
//　　0040102A    call         operator new (00401060)
//
//　　0040102F    add          esp,4
//   mov          dword ptr [ebp-8],eax
//   mov          eax,dword ptr [ebp-8]
//   mov          dword ptr [ebp-4],eax
//	---*/
//	int *p=new int[10];
//	delete[] p;
//}
///*------关于shared_ptr和unique_ptr------*/
///*---
//shared_ptr实现的是引用计数型的智能指针,可以被自由拷贝赋值,
//		  在任意的地方共享它,当引用计数为0时它才是年初被包装
//		  的动态分配的对象
//unique_ptr是独享所有权的智能指针,无法进行复制构造,也无法进行
//		  复制赋值操作,但可以进行移动构造和移动赋值操作当它本身
//		  被删除释放的时候会使用给定的删除器释放它指向的对象
//---*/
//void test3()
//{
//	shared_ptr<int> sp(new int(10));            //一个指向整数的shared_ptr
//	assert(sp.unique());                            //现在shared_ptr是指针的唯一持有者   
//	shared_ptr<int> sp2 = sp;                       //第二个shared_ptr,拷贝构造函数   
//	assert(sp == sp2 && sp.use_count() == 2);		//两个shared_ptr相等,指向同一个对象,引用计数为2  
//	*sp2 = 100;										//使用解引用操作符修改被指对象  
//	assert(*sp == 100);								//另一个shared_ptr也同时被修改   
//	sp.reset();                                     //停止shared_ptr的使用  
//	assert(!sp);                                    //sp不再持有任何指针(空指针)
//}
