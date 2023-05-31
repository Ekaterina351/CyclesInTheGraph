#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>


using namespace std;

struct Vertex {
	std::string name;
	std::vector<Vertex*> adjacentVertices;
	bool visited = false;


	explicit Vertex(const std::string& vertexName) : name(vertexName) {}
};


class InvalidGraphAssignment : public std::exception {
public:
	explicit InvalidGraphAssignment(const std::string& message) : m_message(message) {}

	const char* what() const noexcept override {
		return m_message.c_str();
	}
private:
	std::string m_message;
};


/*! Получить правильное имя цикла. Правильное имя состоит из строки, полученной при
	конкатенации имен каждой вершины, и сортировки полученной строки в алфавитном порядке.
* \param[in] cycle - цикл, для которого необходимо получить правильное имя.
* \return правильное имя цикла.
*/
std::string getCorrectCycleName(const std::vector<Vertex*>& cycle);


/*! Определить наличие цикла для указанной вершины, используя алгоритм поиска в глубину.
* \param[in] viewedVertex - рассматриваемая вершина.
* \param[in, out] recStack - массив для промежуточного хранения цикла.
* // TODO убарть \param[in, out] visited - массив для хранения просмотренных вершин. std::set<Vertex*> visited
* \param[in] cycles - массив с найденными циклами.
* \return 0 - если цикл не найден. 1 - если цикл найден.
*/
bool dfs(Vertex* viewedVertex, std::vector<Vertex*>& recStack,
	const std::map<std::string, std::vector<Vertex*>>& cycles);


/*! Поиск всех уникальных циклов в графе.
* \param[in] graph - массив с вершинами (граф), в котором идет поиск.
* \param[out] cycles - массив с найденными циклами.
* \return 0 - если цикл не найден. 1 - если цикл найден.
*/
bool findCycles(const std::vector<Vertex*>& graph, std::map<std::string, std::vector<Vertex*>>& cycles);


/*! Найти первую вершину с указанным названием в графе.
* \param[in] vertexName - название искомой вершины.
* \param[out] graph - массив с вершинами (граф), в котором идет поиск.
* return найденная вершина или нулевой указатель
*/
Vertex* findVertexInGraph(const std::string& vertexName, const std::vector<Vertex*>& graph);


/*! Удалить перечисленные символы и слева и справа от строки.
* \param[in, out] str строка из которой удаляют крайние правые и левые символы.
* \param[in] stripBy список удаляемых символов справа от строки.
*/
void strip(std::string& str, const char* stripBy = " \t\n\v\f\r");


/*! Прочитывает входные данные из CSV файла, на их основе
	создает вершины Vertex и сохраняет их в массив graph.
* \param[in] input_file_path - строка с путем к файлу с входными данными.
* \param[out] graph - массив с вершинами.
* \param[out] delimiter - разделитель элементов в строке, использующийся в CSV файле.
*/
void readCSVFile(const std::string& input_file_path, std::vector<Vertex*>& graph, const char delimiter = ';');
