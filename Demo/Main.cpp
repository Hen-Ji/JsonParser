#include "JsonObject.h"
#include "JsonParser.h"
#include "Timer.h"
#include <fstream>
#include <iostream>
using namespace std;

int main()
{
	Timer timer;


	//获取json文件
	timer.begin();
	ifstream file;
	file.open("jsonData.json", ios::in);
	string str, temp;
	while (getline(file, temp)) str += temp + "\n";
	file.close();
	double dt = timer.delta();

	cout << str << endl << dt << endl;
	cout << endl;

	//json文件解析为json对象
	timer.begin();
	JsonObject json;
	json = JsonParser::doc(str);
	double dt1 = timer.delta();

	//json对象解析为json字符串
	timer.begin();
	string json2;
	json2 = JsonParser::toString(json);
	double dt2 = timer.delta();

	cout << json2 << endl << dt1 << ' ' << dt2 << endl;
	cout << endl;

	//json字符串解析为json对象
	timer.begin();
	JsonObject json3 = JsonParser::toObject(json2);
	double dt3 = timer.delta();

	cout << JsonParser::toString(json3) << endl << dt3 << endl;
	cout << endl;

	//json对象解析为json文件
	timer.begin();
	string json4;
	json4 = JsonParser::toDoc(json3);
	double dt4 = timer.delta();

	cout << json4 << endl << dt4 << endl;
	cout << endl;

	JsonObject js;
	js["obj"]["id"] = 10;
	js["data"] = JsonParser::doc("{\"name\": \"tom\", \"age\": \"3\"}");
	js["obj"]["target"][0] = "cat";
	js["obj"]["target"][1] = "brown color";
	js["obj"]["target"][2] = true;

	string name = js["data"]["name"];
	int age = js["data"]["age"];

	cout << JsonParser::toDoc(js) << endl;
	cout << js["obj"]["target"] << endl;
	cout << name << ' ' << age << endl;

	return 0;
}
