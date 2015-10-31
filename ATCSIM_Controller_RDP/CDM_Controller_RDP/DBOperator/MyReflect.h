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

typedef void* (*CreateFunction)(void);//回调函数
//工厂类
class ClassFatoryAPI ClassFatory
{
private:
	static std::map<std::string,CreateFunction>& func_newMap();

public:
	static void* GetClassByName(std::string name);//函数返回map中通过回调函数创建的类的实例化，参数为传入的类名

	static void fRegistClass(std::string name, CreateFunction method);//fRegistClass()函数来实现类名和函数的插入

	static ClassFatory& sharedClassFatory();

};
#endif
#ifndef DYNAMICLASS_H
#define DYNAMICLASS_H
//动态创建类的类，被创建的类通过本类的一个静态对象来向类工厂注册对象创建的函数
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

