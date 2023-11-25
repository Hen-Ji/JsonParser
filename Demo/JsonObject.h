#pragma once
#include "JsonValue.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

#define JSON_NULL 0
#define JSON_OBJECT 1
#define JSON_ARRAY 2
#define JSON_INT 3
#define JSON_FLOAT 4
#define JSON_DOUBLE 5
#define JSON_STRING 6
#define JSON_BOOL 7

class JsonObject //json��
{
private:
	unordered_map<string, JsonObject> object;
	vector<JsonObject> jsonArray;
	JsonValue value;

	int type;

public:
	JsonObject();
	~JsonObject();

	JsonObject& operator[](string str);
	JsonObject& operator[](const char* str); //������������ת������(�� operator int();)ʱ, ���������� string, ��Ҫ�� const char*
	//��Ϊ�����string����������� const char* ʱ������֪����Ӧ�ý� const char* תΪ string ����Ӧ�ý� JsonObject תΪ int�� �����ڶ�����
	JsonObject& operator[](int i);
	JsonObject& operator[](size_t i);

	void operator=(int value);
	void operator=(float value);
	void operator=(double value);
	void operator=(string value);
	void operator=(const char* value); //û��������صĻ� const char* �ᱻ��ʽת��Ϊ bool, ������ string
	void operator=(bool value);
	void operator=(const unordered_map<string, JsonObject>& value);
	void operator=(const vector<JsonObject>& value);
	void operator=(const JsonObject& value);

	operator int();
	operator float();
	operator double();
	operator string();
	operator bool();
	operator unordered_map<string, JsonObject>();
	operator vector<JsonObject>();

	int toInt();
	float toFloat();
	double toDouble();
	string toString();
	bool toBool();
	unordered_map<string, JsonObject>& toObject();
	vector<JsonObject>& toArray();

	void setType(int type);
	int getType();

	bool isInt();
	bool isFloat();
	bool isDouble();
	bool isString();
	bool isBool();
	bool isObject();
	bool isArray();
	bool isNull();

	void remove();
	void remove(string key);
	void remove(int num);

};

