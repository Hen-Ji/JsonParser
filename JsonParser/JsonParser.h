#pragma once
#include "JsonObject.h"
#include <string>
using namespace std;

class JsonParser //json����������
{
private:
	static void toObjectInner(string& str, JsonObject& obj, int& index);
	static void toArrayInner(string& str, JsonObject& obj, int& index);
	static void setValueInner(string& val, JsonObject& obj);
	static void getValueInner(string& str, string& res, int& index);

public:
	static JsonObject toObject(string str);
	static JsonObject doc(string str);
	static string toString(JsonObject obj);
	static string toDoc(JsonObject obj);

	friend ostream& operator<<(ostream& out, JsonObject& obj);
};

ostream& operator<<(ostream& out, JsonObject& obj); //��д���д���ᱨ���ж�������"<<"����Щ������ƥ��

