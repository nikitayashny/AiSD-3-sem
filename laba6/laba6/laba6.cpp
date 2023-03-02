#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node	// Узел дерева
{
	char ch;
	int freq;
	Node *left, *right;
};

Node* getNode(char ch, int freq, Node* left, Node* right)	// Функция для выделения нового узла дерева
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

struct comp	// Объект сравнения, который будет использоваться для упорядочения кучи
{
	bool operator()(Node* l, Node* r) 
	{
		return	l->freq > r->freq;	// Элемент с наивысшим приоритетом имеет наименьшую частоту		
	}
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode)	// Пройдём по дереву Хаффмана и сохраним коды Хаффмана на карте
{
	if (root == nullptr)
	{
		return;
	}
	
	if (!root->left && !root->right)	// Ищем листовой узел
	{														
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)	// Пройдём по дереву Хаффмана и декодируем закодированную строку
{
	if (root == nullptr)
	{
		return;
	}
	

	if (!root->left && !root->right)	// Ищем листовой узел 
	{														
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
	{
		decode(root->left, index, str);
	}
	else 
	{
		decode(root->right, index, str);
	}
}

void buildHuffmanTree(string text)
{
	cout << "Таблица встречаемости символов в тексте:" << endl << endl;	// Считаем частоту появления каждого символа и сохраняем его на карте 

	unordered_map<char, int> freq;															
	int counter = 0;

	for (char ch : text) 
	{
		freq[ch]++;	
		counter++;
	}

	char* arr = new char[counter];
	char* arrf = new char[counter];

	for (char ch : text) 
	{	
		arr[ch] = ch;
		if (arr[ch] != arrf[ch]) {
			cout << arr[ch] << ": " << freq[ch] << " раз" << endl;
		}
		arrf[ch] = arr[ch];
	}
	cout << endl;
 
	priority_queue<Node*, vector<Node*>, comp> pq;	// Создаём приоритетную очередь для хранения активных узлов дерева Хаффмана

	for (auto pair : freq)	// Создаём листовой узел для каждого символа и добавляем в приоритетную очередь
	{																
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)	// Выполняем до тех пор пока в очереди не будет более одного узла
	{
		Node* left = pq.top(); pq.pop();	// Удаляем два узла с наивысшим приоритетом (самой низкой частотой) из очереди
		Node* right = pq.top();	pq.pop();

		int sum = left->freq + right->freq;			// Создаём новый внутренний узел с этими двумя узлами как дети и с частотой,
		pq.push(getNode('\0', sum, left, right));	// равной сумме частот двух узлов. Добавляем новый узел в приоритетную очередь				
	}

	Node* root = pq.top();	// root хранит указатель на корень дерева Хаффмана 

	unordered_map<char, string> huffmanCode;	// Проходим по дереву Хаффмана и сохраняем коды Хаффмана на карте  
	encode(root, "", huffmanCode);

	cout << "Таблица соответствия символа и кодовой последовательности:" << endl << endl;
	for (auto pair : huffmanCode) 
	{
		cout << pair.first << ": " << pair.second << endl;
	}

	string str = "";
	for (char ch : text) 
	{
		str += huffmanCode[ch];
	}
	cout << "\nВыходная последовательность:" << endl << str << endl;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	
	string text = "максим лыаовлыв";
	buildHuffmanTree(text);
}