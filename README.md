# JsonParser
JsonParser: Json解析器，包含字符串与json对象的互相转换

我们可以通过这个库很方便地操作json对象，例：
```cpp
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
```

输出:
```
{
	"obj": {
		"id": 10,
		"target": [
			"cat",
			"brown color",
			true
		]
	},
	"data": {
		"name": "tom",
		"age": "3"
	}
}
["cat","brown color",true]
tom 0
```

