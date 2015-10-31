#ifndef CLASSFACTORY_H
#define CLASSFACTORY_H
#ifdef ClassFatoryLIBDll  
#define ClassFatoryAPI _declspec(dllexport)  
#else  
#define ClassFatoryAPI  _declspec(dllimport)  
#endif 
#include <string>
#include <utility>
#include <map>
#include <iostream>

typedef void* (*CreateFunction)(void);//�ص�����
//������
class ClassFatoryAPI ClassFatory
{
private:
	static std::map<std::string,CreateFunction>& func_newMap();

public:
	static void* GetClassByName(std::string name);//��������map��ͨ���ص��������������ʵ����������Ϊ���������

	static void fRegistClass(std::string name, CreateFunction method);//fRegistClass()������ʵ�������ͺ����Ĳ���

	static ClassFatory& sharedClassFatory();

};
#endif
#ifndef DYNAMICLASS_H
#define DYNAMICLASS_H
//��̬��������࣬����������ͨ�������һ����̬���������๤��ע����󴴽��ĺ���
#ifdef DynamicClassLIBDll  
#define DynamicClassAPI _declspec(dllexport)  
#else  
#define DynamicClassAPI  _declspec(dllimport)
#endif 
class DynamicClassAPI DynamicClass
{
public:
	DynamicClass(std::string name,CreateFunction method);
};
#define DECLARE_CLASS(className)\
	std::string className##Name ;\
	static DynamicClass* m_className##dc ;
#define IMPLEMENT_CLASS(className) \
	DynamicClass* className::m_className##dc = new DynamicClass(#className, className::CreateInstance);
#endif

