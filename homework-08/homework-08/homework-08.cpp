// homework-08.cpp : �������̨Ӧ�ó������ڵ㡣
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
	bool Getstring();//�õ�����
	void PrintResult();//����ָ����
	void SeperateUrl();//����STL�ָ�URL
	void SeperateUrlWithoutSTL();//����STL�ָ�URL
	bool IsUrl();//�жϵ�ǰ�����Ƿ�ΪURL,����������ʽ,�ٶȺ���

private:
	string url;//����
	vector<string> result;//�ָ����
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
//	const regex pattern("^((site)|((ht|f)tp(s?)))\:\/\/[a-zA-Z0-9\u4e00-\u9fa5\-\._]+(\.[a-zA-Z0-9\u4e00-\u9fa5\-\._]+){2,}(\/?)([a-zA-Z0-9\u4e00-\u9fa5\-\.\?\,\'\/\\\+&amp;%\$#_]*)?$");//����\u4e00-\u9fa5Ϊ�����ַ�unicode���뷶Χ
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
	size_t lastIndex=0;//��ȡ��ʼ��
	size_t templastIndex=0;
	size_t index=url.find_first_of(delimiter[0],lastIndex);//��ȡ��ֹ��
	size_t tempIndex=string::npos;
	int tempPos=0;//��¼��ǰ��ȡ�����ĸ��ָ���
	
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
	int begin=0;//��¼����://��Ŀ�ʼ��
	int length=url.length();
	string tempStr="";
	for(int i=0;i<length;i++)
	{
		if(url[i]==':'&&url[i+1]=='/'&&url[i+2]=='/')
		{
			result.push_back(tempStr);
			begin=i+3;//����://
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
		if(!myUrl.Getstring())//δ��ȷ����
		{
			continue;
		}
		if(!myUrl.IsUrl())//δ������ȷ��ʽ��URL
		{
			continue;
		}
		myUrl.SeperateUrl();
//		myUrl.SeperateUrlWithoutSTL();
		myUrl.PrintResult();
		break;//��ȷ�����ֱ������
	}
	return 0;
}


//
///*------�ֲ��������������ڵ����------*/
//void test1()//��if��������ж����string�ֲ�����str�ڳ����ô����ʱ�Ѿ��޷�����,�ᱨ��"δ������ʶ��str",��str�Ѿ�������
//{
//	if(true)
//	{
//		string str;
//		str="Hello,World";
//	}
//	cout<<str<<endl;
//}
///*------ջ�Ͷ������ڴ����뷽ʽ------*/
///*---
//ջ��:�ɱ������Զ�������ͷ�,��ź����Ĳ���ֵ,�ֲ�������ֵ��,
//	���������ĵ��ù��̶�����ջ�����
//����:һ���ɳ���Գ�ֶ������Լ��ͷ�,������Գ���ͷ�,�������ʱ
//	�����ɲ���ϵͳ����
//---*/
//void test2()
//{
//	/*---
//	new��������һ����ڴ�,ָ��p����һ��ջ�ڴ�
//	����ջ�ڴ��д����һ��ָ��һ����ڴ��ָ��p
//	---*/
//	/*---
//	��˵����VC6�Ļ����
//	push         14h
//
//����0040102A    call         operator new (00401060)
//
//����0040102F    add          esp,4
//   mov          dword ptr [ebp-8],eax
//   mov          eax,dword ptr [ebp-8]
//   mov          dword ptr [ebp-4],eax
//	---*/
//	int *p=new int[10];
//	delete[] p;
//}
///*------����shared_ptr��unique_ptr------*/
///*---
//shared_ptrʵ�ֵ������ü����͵�����ָ��,���Ա����ɿ�����ֵ,
//		  ������ĵط�������,�����ü���Ϊ0ʱ�������������װ
//		  �Ķ�̬����Ķ���
//unique_ptr�Ƕ�������Ȩ������ָ��,�޷����и��ƹ���,Ҳ�޷�����
//		  ���Ƹ�ֵ����,�����Խ����ƶ�������ƶ���ֵ������������
//		  ��ɾ���ͷŵ�ʱ���ʹ�ø�����ɾ�����ͷ���ָ��Ķ���
//---*/
//void test3()
//{
//	shared_ptr<int> sp(new int(10));            //һ��ָ��������shared_ptr
//	assert(sp.unique());                            //����shared_ptr��ָ���Ψһ������   
//	shared_ptr<int> sp2 = sp;                       //�ڶ���shared_ptr,�������캯��   
//	assert(sp == sp2 && sp.use_count() == 2);		//����shared_ptr���,ָ��ͬһ������,���ü���Ϊ2  
//	*sp2 = 100;										//ʹ�ý����ò������޸ı�ָ����  
//	assert(*sp == 100);								//��һ��shared_ptrҲͬʱ���޸�   
//	sp.reset();                                     //ֹͣshared_ptr��ʹ��  
//	assert(!sp);                                    //sp���ٳ����κ�ָ��(��ָ��)
//}
