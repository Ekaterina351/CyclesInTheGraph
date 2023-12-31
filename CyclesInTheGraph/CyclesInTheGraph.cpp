﻿#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CyclesInTheGraph.h"


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	// Если указано неверное количество аргементов командной строки
	if (argc != 3)
	{
		std::cerr << "Неправильно указаны параметры запуска. "
			"Убедитесь, что параметры соотвествуют шаблону: \n"
			<< argv[0] << " <path/to/input_file.csv> <path/to/output_file.txt>\n";
		return 1;
	}

	std::ifstream input_file(argv[1]);

	// Если не удалось открыть файл с входными данными
	if (!input_file.is_open()) {
		std::cerr << "Неверно указан файл с входными данными. Возможно, файл не существует." << argv[1] << '\n';
		return 1;
	}

	filesystem::path output_path = filesystem::path(argv[2]);

	// Если не удалось определить путь для выходного файла
	if (!(filesystem::exists(output_path.parent_path()) &&
		filesystem::is_directory(output_path.parent_path()) &&
		output_path.has_filename()))
	{
		std::cerr << "Неверно указан файл для выходных данных. "
			"Возможно указанного расположения не существует или нет прав на запись." << '\n';
		return 1;
	}
	std::ofstream output_file(output_path);

	// Если не удалось открыть файл для записи выходных данных
	if (!output_file.is_open()) {
		std::cerr << "Неверно указан файл для выходных данных. "
			"Возможно указанного расположения не существует или нет прав на запись." << '\n';
		return 1;
	}

	std::vector<Vertex*> graph;
	try {
		// Считываем и валидируем матрицу смежностей
		readCSVFile(argv[1], graph);
	}
	catch (const InvalidGraphAssignment& e) {
		std::cerr << e.what();
		return 1;
	}

	std::map<std::string, vector<Vertex*>> cycles;

	// Находим все уникальные циклы в графе и 
	// выводим результат поиска в файл
	if (findCycles(graph, cycles)) {
		output_file << "True" << '\n';
	}
	else {
		output_file << "False" << '\n';
	}

	// Выводим найденные циклы в файл
	for (const auto& [cycleName, cycleVector] : cycles) {
		for (int j = 0; j < cycleVector.size(); j++) {
			output_file << cycleVector[j]->name;
			if (j < cycleVector.size() - 1) output_file << '-';
		}
		output_file << '\n';
	}
	// Закрыть файлы
	input_file.close();
	output_file.close();

	return 0;
}


std::string getCorrectCycleName(const std::vector<Vertex*>& cycle) {
	// Конкатенируем названия вершин в одну строку
	std::string cycleName = ""; // Определяем строку для создания правильного имени цикла
	// Для каждой вершины цикла
	for (const Vertex* v : cycle) {
		// добавить имя рассматриваемой вершины в строку для создания правильного имени цикла
		cycleName += v->name;
	}
	// Получаем правильное имя цикла, отсортировав строку
	std::sort(cycleName.begin(), cycleName.end());
	// Возвращаем правильное имя цикла
	return cycleName;
}


bool dfs(Vertex* viewedVertex, std::vector<Vertex*>& recStack, const std::map<std::string, std::vector<Vertex*>>& cycles) {
	// Помечаем вершину как посещенную
	viewedVertex->visited = true;
	// Добавляем текущую вершину в массив с формируемым циклом
	recStack.push_back(viewedVertex);

	// Для каждлой смежной вершины у просматриваемой вершины
	for (Vertex* v : viewedVertex->adjacentVertices) {
		// Если смежную вершину еще не посещали
		if (!v->visited) {
			// Запускаем алгоритм поиска в глубину для смежной вершины
			if (dfs(v, recStack, cycles)) {
				// Снимаем пометку о посещении вершины 
				viewedVertex->visited = false;

				// Если нашли цикл, то возвращаем истину
				return true;
			}
		}
		// Если смежную вершину уже посещали и вершина является 
		// первой в списке с формируемом циклом, значит, мы нашли цикл
		else if (v == recStack[0]) {
			// Если ранее цикл с таким же правильным именем не находили
			if (!cycles.contains(getCorrectCycleName(recStack))) {
				// Снимаем пометку о песещении вершины 
				viewedVertex->visited = false;

				// Считаем, что нашли новый цикл и возвращаем истину
				return true;
			}
		}
	}
	// Если цикл не нашли, то удаляем вершину из массива с формируемым циклом 
	// и снимаем пометку о ее песещении
	recStack.pop_back();
	viewedVertex->visited = false;

	// Возвращаем ложь, т.к. цикл не нашли
	return false;
}


bool findCycles(const std::vector<Vertex*>& graph, std::map<std::string, std::vector<Vertex*>>& cycles) {
	// Определить массив для хранения возможного цикла и массив посещенных вершин
	std::vector<Vertex*> recStack;

	bool isAnyCycleFound = false; // Считаем, что ни один цикл не найден

	// Для каждой вершины графа
	for (Vertex* v : graph) {
		// Пока возможно найти уникальный цикл у рассматриваемой вершины 
		// с помощью алгоритма поиска в глубину
		while (dfs(v, recStack, cycles)) {
			// Добавляем цикл в массив найденных циклов
			std::string cycleName = getCorrectCycleName(recStack);

			recStack.push_back(v);
			cycles[cycleName] = recStack;

			// Помечаем, что был найден цикл
			isAnyCycleFound = true;

			// Очищаем массив для хранения возможного цикла перед поиском 
			// нового уникального цикла для рассматриваемой вершины
			recStack.clear();
		}
	}
	// Возвращаем результат поиска цикла в графе
	return isAnyCycleFound;
}


Vertex* findVertexInGraph(const std::string& vertexName, const std::vector<Vertex*>& graph) {
	// Для всех вершин графа
	for (Vertex* v : graph) {
		// Если имя вершины равно искомому имени, вернуть эту вершину
		if (v->name == vertexName) return v;
	}
	// Если не нашли вершину с искомым именем, вернуть пустой указатель
	return nullptr;
}


void strip(std::string& str, const char* stripBy) {
	size_t start = str.find_first_not_of(stripBy); // поиск первого непробельного символа
	size_t end = str.find_last_not_of(stripBy); // поиск последнего непробельного символа
	if (start == std::string::npos || end == std::string::npos) { // если строка состоит только из пробельных символов
		str.clear(); // очистить строку
	}
	else {
		str = str.substr(start, end - start + 1); // выделить подстроку без пробельных символов
	}
}


void readCSVFile(const std::string& input_file_path, std::vector<Vertex*>& graph, const char delimiter) {
	// Открываем файл
	std::ifstream input_file(input_file_path); // Закрывать не надо, т.к. после завершения функции закроется автоматом

	// Объявляем переменные для строки файла и строки для считанной клетки
	std::string line, buff; 

	// Считываем заголовок таблицы
	std::getline(input_file, line);

	// Открываем поток для строки, чтобы разделить ее по разделителям
	std::stringstream hs(line);

	std::getline(hs, buff, delimiter); // Первую клетку читаем в пустоту

	std::vector<Vertex*> headers_vertexes; // массив для вершин из заголовка

	// Читаем заголовок с названиями вершин
	while (std::getline(hs, buff, delimiter)) {
		strip(buff);
		if (buff.empty())
			throw InvalidGraphAssignment("Неверное название вершины. Имя вершины не должно быть пустой "
				"строкой или состоять из белых разделителей.");

		// Проверяем на дублирование названий вершин
		if (findVertexInGraph(buff, headers_vertexes) != nullptr) 
			throw InvalidGraphAssignment("Неверные входные данные. Повторение вершины " + buff);
		// Добавляем вершину в массив вершин
		headers_vertexes.push_back(new Vertex(buff));
	}
	// Ошибка чтения фала, если граф полностью пустой
	if (headers_vertexes.size() == 0) 
		throw InvalidGraphAssignment("Неверные входные данные. Граф не содержит вершин.");

	// Читаем остальной файл
	// Считаем, что количество линий в файле (не считая заголов) - это количество вершин
	int vertexes_count = 0;

	// Определяем массив для хранения вершин, указанных в первом столбце
	std::map<std::string, Vertex*> body_vertexes; 

	// Пока не встретили пустую строку 
	while (std::getline(input_file, line)) {
		// Инкрементируем счетчик вершин, т.к. считаем, что каждая строка - описание вершин
		vertexes_count++;

		// Если строк больше, чем столбоц в заголовке, то ошибка размерности
		if (vertexes_count > headers_vertexes.size()) 
			throw InvalidGraphAssignment("Неверные входные данные. Ошибка размерности матрицы.");

		// Открываем поток для строки, чтобы разделить ее по разделителям
		std::stringstream bs(line);
		std::getline(bs, buff, delimiter); // Первая клетка содержит название вершины

		strip(buff);
		if (buff.empty())
			throw InvalidGraphAssignment("Неверное название вершины. Имя вершины не должно быть пустой "
				"строкой или состоять из белых разделителей.");

		// Проверяем, что вершина была указана в множестве вершин из заголовка
		if (findVertexInGraph(buff, headers_vertexes) == nullptr)
			throw InvalidGraphAssignment("Неверные входные данные. Содержится лишняя вершина " + buff);

		// Проверяем, что название вершины не повторяется
		if (body_vertexes.contains(buff))
			throw InvalidGraphAssignment("Неверные входные данные. Повторение вершины " + buff);

		// Получаем объект вершины их массива вершин из заголовка, т.е. уже созаднную
		Vertex* vertex = body_vertexes[buff] = findVertexInGraph(buff, headers_vertexes);

		// Создаем связи для вершины в строке
		int count_cells = 0;
		// Пока имеются клетки в строке матрицы
		while (std::getline(bs, buff, delimiter)) {
			strip(buff);

			// Переходим к следующему столбцу
			count_cells++;
			if (count_cells > headers_vertexes.size())  // количество клеток больше, чем количество вершин
				throw InvalidGraphAssignment("Неверные входные данные. Матрица смежностей имеет неправильные размеры.");
 
			if (buff == "1") // в клетке установлена 1
			{
				// Если новая связть создат петлю, то  выдаем ошибку
				if (vertex->name == headers_vertexes[count_cells - 1]->name) 
					throw InvalidGraphAssignment("Неверные входные данные. В графе содержатся петли.");
				// Создаем связь, добавлением одной вершины в массив связанных у другой
				vertex->adjacentVertices.push_back(headers_vertexes[count_cells - 1]);
			}
			else if (buff != "0") // в клетке установлено значение отличное 0
				throw InvalidGraphAssignment("Неверные входные данные. Неверные параметры обозначения связей.");
		}
		if (count_cells != headers_vertexes.size())
			throw InvalidGraphAssignment("Неверные входные данные. Неверные параметры обозначения связей.");
	}
	// Копируем вершины в выходной параметр графа.
	for (Vertex* v : headers_vertexes) {
		graph.push_back(v);
	}
}