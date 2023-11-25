#include "JsonObject.h"

JsonObject::JsonObject()
{
	type = JSON_NULL;
}

JsonObject::~JsonObject()
{

}

JsonObject& JsonObject::operator[](string str)
{
	type = JSON_OBJECT;
	return object[str.c_str()];
}
JsonObject& JsonObject::operator[](const char* str)
{
	type = JSON_OBJECT;
	return object[str];
}

JsonObject& JsonObject::operator[](int i)
{
	type = JSON_ARRAY;
	if (jsonArray.size() <= i)
	{
		jsonArray.resize(i + 1);
	}
	return jsonArray[i];
}

JsonObject& JsonObject::operator[](size_t i)
{
	type = JSON_ARRAY;
	if (jsonArray.size() <= i)
	{
		jsonArray.resize(i + 1);
	}
	return jsonArray[i];
}

void JsonObject::operator=(int value)
{
	this->value.i = value;
	type = JSON_INT;
}
void JsonObject::operator=(float value)
{
	this->value.d = value;
	type = JSON_FLOAT;
}
void JsonObject::operator=(double value)
{
	this->value.d = value;
	type = JSON_DOUBLE;
}
void JsonObject::operator=(string value)
{
	this->value.s = value;
	type = JSON_STRING;
}
void JsonObject::operator=(const char* value)
{
	this->value.s = value;
	type = JSON_STRING;
}
void JsonObject::operator=(bool value)
{
	this->value.i = value;
	type = JSON_BOOL;
}
void JsonObject::operator=(const unordered_map<string, JsonObject>& value)
{
	object = value;
	type = JSON_OBJECT;
}
void JsonObject::operator=(const vector<JsonObject>& value)
{
	jsonArray = value;
	type = JSON_ARRAY;
}
void JsonObject::operator=(const JsonObject& value)
{
	object = value.object;
	jsonArray = value.jsonArray;
	this->value = value.value;
	type = value.type;
}

JsonObject::operator int()
{
	if (type == JSON_INT) return value.i;
	return 0;
}

JsonObject::operator float()
{
	if (type == JSON_FLOAT) return float(value.d);
	return 0;
}
JsonObject::operator double()
{
	if (type == JSON_DOUBLE) return value.d;
	return 0;
}
JsonObject::operator string()
{
	if (type == JSON_STRING) return value.s;
	return "";
}
JsonObject::operator bool()
{
	if (type == JSON_BOOL) return value.i;
	return false;
}
JsonObject::operator unordered_map<string, JsonObject>()
{
	if (type == JSON_OBJECT) return object;
	return unordered_map<string, JsonObject>();
}
JsonObject::operator vector<JsonObject>()
{
	if (type == JSON_ARRAY) return jsonArray;
	return vector<JsonObject>();
}

int JsonObject::toInt()
{
	if(type == JSON_INT) return value.i;
	return 0;
}
float JsonObject::toFloat()
{
	if (type == JSON_FLOAT) return float(value.d);
	return 0;
}
double JsonObject::toDouble()
{
	if (type == JSON_DOUBLE) return value.d;
	return 0;
}
string JsonObject::toString()
{
	if (type == JSON_STRING) return value.s;
	return "";
}
bool JsonObject::toBool()
{
	if (type == JSON_BOOL) return bool(value.i);
	return 0;
}
unordered_map<string, JsonObject>& JsonObject::toObject()
{
	return object;
}
vector<JsonObject>& JsonObject::toArray()
{
	return jsonArray;
}

void JsonObject::setType(int type)
{
	this->type = type;
}
int JsonObject::getType()
{
	return type;
}

bool JsonObject::isInt()
{
	if (type == JSON_INT) return true;
	return false;
}
bool JsonObject::isFloat()
{
	if (type == JSON_FLOAT) return true;
	return false;
}
bool JsonObject::isDouble()
{
	if (type == JSON_DOUBLE) return true;
	return false;
}
bool JsonObject::isString()
{
	if (type == JSON_STRING) return true;
	return false;
}
bool JsonObject::isBool()
{
	if (type == JSON_BOOL) return true;
	return false;
}
bool JsonObject::isObject()
{
	if (type == JSON_OBJECT) return true;
	return false;
}
bool JsonObject::isArray()
{
	if (type == JSON_ARRAY) return true;
	return false;
}
bool JsonObject::isNull()
{
	if (type == JSON_NULL) return true;
	return false;
}

void JsonObject::remove()
{
	object.clear();
	type = JSON_NULL;
}
void JsonObject::remove(string key)
{
	object.erase(key);
}
void JsonObject::remove(int num)
{
	jsonArray.erase(jsonArray.begin() + num);
}