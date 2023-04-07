#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CyclesInTheGraph.h"


int main()
{
	Vertex* v1 = new Vertex("1");
	Vertex* v2 = new Vertex("2");
	Vertex* v3 = new Vertex("3");
	v1->adjacentVertices.push_back(v2);
	v2->adjacentVertices.push_back(v1);
	v2->adjacentVertices.push_back(v3);
	v3->adjacentVertices.push_back(v1);
	std::vector<Vertex*> input_graph = { v1, v2, v3 };

	std::map<std::string, std::vector<Vertex*>> cycles;
	bool search_res = findCycles(input_graph, cycles);
	cout << search_res << "\n";

	for (const auto& [cycleName, cycleVector] : cycles) {
		for (int j = 0; j < cycleVector.size(); j++) {
			cout << cycleVector[j]->name;
			if (j < cycleVector.size() - 1) cout << '-';
		}
		cout << '\n';
	}
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


bool dfs(Vertex* viewedVertex, std::vector<Vertex*>& recStack, std::set<Vertex*> visited,
	const std::map<std::string, std::vector<Vertex*>>& cycles) {
	// Помещаем вершину в массив посещенных
	visited.insert(viewedVertex);
	// Добавляем текущую вершину в массив с формируемым циклом
	recStack.push_back(viewedVertex);

	// Для каждлой смежной вершины у просматриваемой вершины
	for (Vertex* v : viewedVertex->adjacentVertices) {
		// Если смежную вершину еще не посещали
		if (!visited.contains(v)) {
			// Запускаем алгоритм поиска в глубину для смежной вершины
			if (dfs(v, recStack, visited, cycles)) {
				// Если нашли цикл, то возвращаем истину
				return true;
			}
		}
		// Если смежную вершину уже посещали и вершина является 
		// первой в списке с формируемом циклом, значит, мы нашли цикл
		else if (v == recStack[0]) {
			// Если ранее цикл с таким же правильным именем не находили
			if (!cycles.contains(getCorrectCycleName(recStack))) {
				// Считаем, что нашли новый цикл и возвращаем истину
				return true;
			}
		}
	}
	// Если цикл не нашли, то удаляем вершину из массива с формируемым циклом 
	// и снимаем пометку о ее песещении
	recStack.pop_back();
	visited.erase(viewedVertex);

	// Возвращаем ложь, т.к. цикл не нашли
	return false;
}


bool findCycles(const std::vector<Vertex*>& graph, std::map<std::string, std::vector<Vertex*>>& cycles) {
	// Определить массив для хранения возможного цикла и массив посещенных вершин
	std::vector<Vertex*> recStack;
	std::set<Vertex*> visited;

	bool isAnyCycleFound = false; // Считаем, что ни один цикл не найден

	// Для каждой вершины графа
	for (Vertex* v : graph) {
		// Пока возможно найти уникальный цикл у рассматриваемой вершины 
		// с помощью алгоритма поиска в глубину
		while (dfs(v, recStack, visited, cycles)) {
			// Добавляем цикл в массив найденных циклов
			std::string cycleName = getCorrectCycleName(recStack);

			recStack.push_back(v);
			cycles[cycleName] = recStack;

			// Помечаем, что был найден цикл
			isAnyCycleFound = true;

			// Очищаем массив для хранения возможного цикла перед поиском 
			// нового уникального цикла для рассматриваемой вершины
			recStack.clear();
			visited.clear();
		}
		visited.clear();
	}
	// Возвращаем результат поиска цикла в графе
	return isAnyCycleFound;
}