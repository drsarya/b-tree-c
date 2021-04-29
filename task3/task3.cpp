﻿// task3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Printer.cpp"
#include "Tree.cpp"

int main()
{
	Tree<int>* tree = new Tree<int>(4);
	 Printer<int>* p = new Printer<int>();
	tree->add(1);
 
	tree->add(2);
	tree->add(3);
	tree->add(4);
	 
	tree->add(5);
	tree->add(6);
	tree->add(7);
	tree->add(8);
	tree->add(9);
	tree->add(10);
	tree->add(11);
	tree->add(12);  
	tree->add(13);
	tree->add(14);
	tree->add(15);
	tree->add(16);
	tree->add(7);
	tree->add(9);
	tree->add(19);
	tree->add(20);
	tree->add(21);
	tree->add(22);
	tree->add(23);
	tree->add(24);
 	p->printTree(tree);

	std::cout << "\n";
	tree->deleteKey(9);
	tree->deleteKey(1);
	tree->deleteKey(4);
	tree->deleteKey(11);
	tree->deleteKey(12);
//	p->printTree(tree);
	  p->printTree(tree);

	std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
