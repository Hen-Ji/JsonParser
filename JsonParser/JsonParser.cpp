#include "JsonParser.h"
#include <iostream>

JsonObject JsonParser::toObject(string str) //将json字符串转为json对象 (json字符串: 没有缩进、空格、换行的json文件)
{
	JsonObject res;
	int i = 1;

	if (str[0] == '{') { //是object
		toObjectInner(str, res, i);
	}
	else if (str[0] == '[') { //是array
		toArrayInner(str, res, i);
	}

	return res;
}
JsonObject JsonParser::doc(string str) //将json文件转为json对象
{
	//字符串预处理：删除所有多余的空格、制表符、换行符
	string res = "";
	bool isInString = false;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '"') {
			res += str[i];
			if(str[i - 1] != '\\') isInString = !isInString;
		}
		else if (isInString) res += str[i]; //字符串里的字符不用删
		else if (!isInString && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') res += str[i];
	}

	return toObject(res); //解析
}

void JsonParser::toObjectInner(string& str, JsonObject& obj, int& index) //str: 原字符串; obj: 需要加数据的对象(object); index: str索引
{
	for (; index < str.size(); index++) {
		if (str[index] == ',') continue; //若有逗号则进入下一轮循环
		if (str[index] == '}') return; //若为 } 则已全部加完，返回
		//一个键值对判断完后，str[index]会出现两种情况: '}' 和 ',' 
		//出现 '}' 表示此层级的键值对已经全部找完
		//出现 ',' 表示还有键值对

		if (str[index] == '"') { //是键值对

			//获取key
			index++;
			string key;
			for (; index < str.size() && str[index] != '"'; index++) {
				key += str[index];
			}
			index += 2;

			//val若是obj或arr，继续下一步判断
			if (str[index] == '{') {
				index++;
				obj[key].setType(JSON_OBJECT);
				toObjectInner(str, obj[key], index);
				continue;
			}
			else if (str[index] == '[') {
				index++;
				obj[key].setType(JSON_ARRAY);
				toArrayInner(str, obj[key], index);
				continue;
			}

			//获取val
			string val;
			getValueInner(str, val, index);

			//判断val
			setValueInner(val, obj[key]);
		}
	}
}

void JsonParser::toArrayInner(string& str, JsonObject& obj, int& index)  //str: 原字符串; obj: 需要加数据的对象(array); index: str索引
{
	for (; index < str.size(); index++) {
		if (str[index] == ',') continue; //若有逗号则进入下一轮循环
		if (str[index] == ']') return; //若为 ] 则已全部加完，返回

		size_t arrIndex = obj.toArray().size(); //需要加到的地方

		//val若是obj或arr，继续下一步判断
		if (str[index] == '{') {
			index++;
			obj[arrIndex].setType(JSON_OBJECT);
			toObjectInner(str, obj[arrIndex], index);
			continue;
		}
		else if (str[index] == '[') {
			index++;
			obj[arrIndex].setType(JSON_ARRAY);
			toArrayInner(str, obj[arrIndex], index);
			continue;
		}

		//获取val
		string val;
		getValueInner(str, val, index);

		//判断val
		setValueInner(val, obj[arrIndex]);
	}
}
void JsonParser::getValueInner(string& str, string& res, int& index)  //str: 原字符串; res: 处理结果; index: str索引
{
	while (index < str.size()) {
		res += str[index];
		index++;
		if (res[0] == '"') {
			if (str[index] == '"' && str[index - 1] != '\\') {
				break;
			}
		}
		else if (str[index] == ',' || str[index] == '}' || str[index] == ']') {
			index--;
			break;
		}
	}
}

void JsonParser::setValueInner(string& val, JsonObject& obj)  //val: 需要处理的字符串; obj: 处理结果存储在这里
{
	if (val == "null") { //是null
		obj;
	}
	else if (val == "true") { //是bool
		obj = true;
	}
	else if (val == "false") {
		obj = false;
	}

	else if (val[0] == '"') { //是string
		obj = val.substr(1, val.size() - 1);
	}
	else if (val.find('.') != -1) { //是小数
		if (val[val.size() - 1] == 'f') obj = stof(val.substr(0, val.size() - 1)); //float
		else obj = stod(val); //double
	}
	else { //是int
		obj = stoi(val);
	}
}

string JsonParser::toString(JsonObject obj) //json对象转为json字符串
{
	string res;
	if (obj.isObject()) {
		res += '{';

		for (auto &it : obj.toObject()) {
			res += "\"" + it.first + "\":" + toString(it.second) + ",";
		}

		if(res != "{") res.erase(res.size() - 1, 1); //object不为空才要删逗号
		res += '}';
	}
	else if (obj.isArray()) {
		res += '[';

		for (auto& it : obj.toArray()) {
			res += toString(it) + ",";
		}

		if (res != "[") res.erase(res.size() - 1, 1); //array不为空才要删逗号
		res += ']';
	}
	else if (obj.isNull()) {
		res = "null";
	}
	else if (obj.isString()) {
		res = "\"" + obj.toString() + "\"";
	}
	else if (obj.isInt()) {
		res = to_string(obj.toInt());
	}
	else if (obj.isFloat()) {
		res = to_string(obj.toFloat()) + "f";
	}
	else if (obj.isDouble()) {
		res = to_string(obj.toDouble());
	}
	else if (obj.isBool()) {
		res = obj.toBool() ? "true" : "false";
	}

	return res;
}
string JsonParser::toDoc(JsonObject obj) //json对象转为json文件
{
	string str = toString(obj);
	string res;
	bool isInString = false;
	string tabs = "";

	// '[', '{' 后面换行加制表符; ']', '}' 前面换行加制表符; ',' 后面换行加制表符; ':' 后面加空格;
	for (int i = 0; i < str.size(); i++) {
		res += str[i];
		if (str[i] == '"' && str[i - 1] != '\\') isInString = !isInString;
		else if (!isInString) { //不在字符串里面的特定字符需要加
			if (str[i] == '[' || str[i] == '{') {
				tabs += '\t';
				res += '\n' + tabs;
			}
			else if (str[i] == ']' || str[i] == '}') {
				tabs.erase(tabs.size() - 1, 1);
				res.insert(res.size() - 1, '\n' + tabs);
			}
			else if (str[i] == ',') {
				res += '\n' + tabs;
			}
			else if (str[i] == ':') {
				res += ' ';
			}
		}
	}

	return res;
}

ostream& operator<<(ostream& out, JsonObject& obj) //重载输出运算符, 以json字符串形式输出obj
{
	out << JsonParser::toString(obj);
	return out;
}
