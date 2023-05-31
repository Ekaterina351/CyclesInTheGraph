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


/*! �������� ���������� ��� �����. ���������� ��� ������� �� ������, ���������� ���
	������������ ���� ������ �������, � ���������� ���������� ������ � ���������� �������.
* \param[in] cycle - ����, ��� �������� ���������� �������� ���������� ���.
* \return ���������� ��� �����.
*/
std::string getCorrectCycleName(const std::vector<Vertex*>& cycle);


/*! ���������� ������� ����� ��� ��������� �������, ��������� �������� ������ � �������.
* \param[in] viewedVertex - ��������������� �������.
* \param[in, out] recStack - ������ ��� �������������� �������� �����.
* // TODO ������ \param[in, out] visited - ������ ��� �������� ������������� ������. std::set<Vertex*> visited
* \param[in] cycles - ������ � ���������� �������.
* \return 0 - ���� ���� �� ������. 1 - ���� ���� ������.
*/
bool dfs(Vertex* viewedVertex, std::vector<Vertex*>& recStack,
	const std::map<std::string, std::vector<Vertex*>>& cycles);


/*! ����� ���� ���������� ������ � �����.
* \param[in] graph - ������ � ��������� (����), � ������� ���� �����.
* \param[out] cycles - ������ � ���������� �������.
* \return 0 - ���� ���� �� ������. 1 - ���� ���� ������.
*/
bool findCycles(const std::vector<Vertex*>& graph, std::map<std::string, std::vector<Vertex*>>& cycles);


/*! ����� ������ ������� � ��������� ��������� � �����.
* \param[in] vertexName - �������� ������� �������.
* \param[out] graph - ������ � ��������� (����), � ������� ���� �����.
* return ��������� ������� ��� ������� ���������
*/
Vertex* findVertexInGraph(const std::string& vertexName, const std::vector<Vertex*>& graph);


/*! ������� ������������� ������� � ����� � ������ �� ������.
* \param[in, out] str ������ �� ������� ������� ������� ������ � ����� �������.
* \param[in] stripBy ������ ��������� �������� ������ �� ������.
*/
void strip(std::string& str, const char* stripBy = " \t\n\v\f\r");


/*! ����������� ������� ������ �� CSV �����, �� �� ������
	������� ������� Vertex � ��������� �� � ������ graph.
* \param[in] input_file_path - ������ � ����� � ����� � �������� �������.
* \param[out] graph - ������ � ���������.
* \param[out] delimiter - ����������� ��������� � ������, �������������� � CSV �����.
*/
void readCSVFile(const std::string& input_file_path, std::vector<Vertex*>& graph, const char delimiter = ';');
