#include "JsonParser.h"
#include <iostream>

JsonObject JsonParser::toObject(string str) //��json�ַ���תΪjson���� (json�ַ���: û���������ո񡢻��е�json�ļ�)
{
	JsonObject res;
	int i = 1;

	if (str[0] == '{') { //��object
		toObjectInner(str, res, i);
	}
	else if (str[0] == '[') { //��array
		toArrayInner(str, res, i);
	}

	return res;
}
JsonObject JsonParser::doc(string str) //��json�ļ�תΪjson����
{
	//�ַ���Ԥ����ɾ�����ж���Ŀո��Ʊ�������з�
	string res = "";
	bool isInString = false;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '"') {
			res += str[i];
			if(str[i - 1] != '\\') isInString = !isInString;
		}
		else if (isInString) res += str[i]; //�ַ�������ַ�����ɾ
		else if (!isInString && str[i] != ' ' && str[i] != '\t' && str[i] != '\n') res += str[i];
	}

	return toObject(res); //����
}

void JsonParser::toObjectInner(string& str, JsonObject& obj, int& index) //str: ԭ�ַ���; obj: ��Ҫ�����ݵĶ���(object); index: str����
{
	for (; index < str.size(); index++) {
		if (str[index] == ',') continue; //���ж����������һ��ѭ��
		if (str[index] == '}') return; //��Ϊ } ����ȫ�����꣬����
		//һ����ֵ���ж����str[index]������������: '}' �� ',' 
		//���� '}' ��ʾ�˲㼶�ļ�ֵ���Ѿ�ȫ������
		//���� ',' ��ʾ���м�ֵ��

		if (str[index] == '"') { //�Ǽ�ֵ��

			//��ȡkey
			index++;
			string key;
			for (; index < str.size() && str[index] != '"'; index++) {
				key += str[index];
			}
			index += 2;

			//val����obj��arr��������һ���ж�
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

			//��ȡval
			string val;
			getValueInner(str, val, index);

			//�ж�val
			setValueInner(val, obj[key]);
		}
	}
}

void JsonParser::toArrayInner(string& str, JsonObject& obj, int& index)  //str: ԭ�ַ���; obj: ��Ҫ�����ݵĶ���(array); index: str����
{
	for (; index < str.size(); index++) {
		if (str[index] == ',') continue; //���ж����������һ��ѭ��
		if (str[index] == ']') return; //��Ϊ ] ����ȫ�����꣬����

		size_t arrIndex = obj.toArray().size(); //��Ҫ�ӵ��ĵط�

		//val����obj��arr��������һ���ж�
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

		//��ȡval
		string val;
		getValueInner(str, val, index);

		//�ж�val
		setValueInner(val, obj[arrIndex]);
	}
}
void JsonParser::getValueInner(string& str, string& res, int& index)  //str: ԭ�ַ���; res: ������; index: str����
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

void JsonParser::setValueInner(string& val, JsonObject& obj)  //val: ��Ҫ������ַ���; obj: �������洢������
{
	if (val == "null") { //��null
		obj;
	}
	else if (val == "true") { //��bool
		obj = true;
	}
	else if (val == "false") {
		obj = false;
	}

	else if (val[0] == '"') { //��string
		obj = val.substr(1, val.size() - 1);
	}
	else if (val.find('.') != -1) { //��С��
		if (val[val.size() - 1] == 'f') obj = stof(val.substr(0, val.size() - 1)); //float
		else obj = stod(val); //double
	}
	else { //��int
		obj = stoi(val);
	}
}

string JsonParser::toString(JsonObject obj) //json����תΪjson�ַ���
{
	string res;
	if (obj.isObject()) {
		res += '{';

		for (auto &it : obj.toObject()) {
			res += "\"" + it.first + "\":" + toString(it.second) + ",";
		}

		if(res != "{") res.erase(res.size() - 1, 1); //object��Ϊ�ղ�Ҫɾ����
		res += '}';
	}
	else if (obj.isArray()) {
		res += '[';

		for (auto& it : obj.toArray()) {
			res += toString(it) + ",";
		}

		if (res != "[") res.erase(res.size() - 1, 1); //array��Ϊ�ղ�Ҫɾ����
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
string JsonParser::toDoc(JsonObject obj) //json����תΪjson�ļ�
{
	string str = toString(obj);
	string res;
	bool isInString = false;
	string tabs = "";

	// '[', '{' ���滻�м��Ʊ��; ']', '}' ǰ�滻�м��Ʊ��; ',' ���滻�м��Ʊ��; ':' ����ӿո�;
	for (int i = 0; i < str.size(); i++) {
		res += str[i];
		if (str[i] == '"' && str[i - 1] != '\\') isInString = !isInString;
		else if (!isInString) { //�����ַ���������ض��ַ���Ҫ��
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

ostream& operator<<(ostream& out, JsonObject& obj) //������������, ��json�ַ�����ʽ���obj
{
	out << JsonParser::toString(obj);
	return out;
}
