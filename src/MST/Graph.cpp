#include "MST/Graph.h"
#include "MST/GraphEdge.h"
#include <raylib.h>
#include <set>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random> // Thêm để dùng std::shuffle
#include <map>

Graph::Graph() : vertices(0), edges(0) {}

Graph::Graph(std::vector<GraphNode*> vertices, std::vector<GraphEdge*> edges)
    : vertices(vertices), edges(edges) {
}

Graph::Graph(Graph* graph) {
    // Xóa dữ liệu hiện tại nếu có
    if (!vertices.empty() || !edges.empty()) {
        for (GraphNode* node : vertices) {
            delete node;
        }
        for (GraphEdge* edge : edges) {
            delete edge;
        }
        vertices.clear();
        edges.clear();
    }

    // Kiểm tra graph null
    if (!graph) {
        vertices = {};
        edges = {};
        return;
    }

    // Map để theo dõi các node mới tương ứng với node cũ
    std::map<GraphNode*, GraphNode*> nodeMap;

    // 1. Sao chép các đỉnh (GraphNode)
    for (GraphNode* oldNode : graph->vertices) {
        GraphNode* newNode = new GraphNode(
            oldNode->data,
            {}, // Danh sách cạnh sẽ được cập nhật sau
            oldNode->position
        );
        newNode->size = oldNode->size;
        newNode->colorNormal = oldNode->colorNormal;
        newNode->colorCurrent = oldNode->colorCurrent;
        newNode->colorChosen = oldNode->colorChosen;
        newNode->textCur = oldNode->textCur;
        newNode->textNor = oldNode->textNor;
        newNode->textCho = oldNode->textCho;
        newNode->isVisited = oldNode->isVisited;
        newNode->isDragging = oldNode->isDragging;
        newNode->dragOffset = oldNode->dragOffset;
        newNode->finalPos = oldNode->finalPos;
        newNode->position = oldNode->position;
        vertices.push_back(newNode);
        nodeMap[oldNode] = newNode;
    }

    // 2. Sao chép các cạnh (GraphEdge) và cập nhật danh sách cạnh của đỉnh
    for (GraphEdge* oldEdge : graph->edges) {
        // Lấy hai đỉnh của cạnh cũ và ánh xạ sang đỉnh mới
        GraphNode* oldNode1 = oldEdge->nodes[0];
        GraphNode* oldNode2 = oldEdge->nodes[1];
        GraphNode* newNode1 = nodeMap[oldNode1];
        GraphNode* newNode2 = nodeMap[oldNode2];

        // Tạo cạnh mới
        GraphEdge* newEdge = new GraphEdge(
            std::vector<GraphNode*>{newNode1, newNode2},
            oldEdge->weight
        );
        newEdge->colorNormal = oldEdge->colorNormal;
        newEdge->colorChosen = oldEdge->colorChosen;
        newEdge->colorFlur = oldEdge->colorFlur;
        newEdge->currentColor = oldEdge->currentColor;
        newEdge->thick = oldEdge->thick;

        // Thêm cạnh vào danh sách cạnh của các đỉnh mới
        newNode1->edge.push_back(newEdge);
        newNode2->edge.push_back(newEdge);
        edges.push_back(newEdge);
    }
}

Graph::~Graph() {
    for (GraphNode* node : vertices) {
        delete node;
    }
    for (GraphEdge* edge : edges) {
        delete edge;
    }
}

void Graph::createGraph(int numOfVer) {
    if (numOfVer <= 0) {
        std::cout << "Lỗi: Số lượng đỉnh phải lớn hơn 0\n";
        return;
    }

    if (!vertices.empty() || !edges.empty()) {
        for (GraphNode* node : vertices) {
            delete node;
        }
        for (GraphEdge* edge : edges) {
            delete edge;
        }
        vertices.clear();
        edges.clear();
    }

    // --- Tạo các nút theo vòng tròn ---
    float radius = 300.0f;
    Vector2 center = {800.0f, 450.0f};
    float angleStep = 2 * PI / numOfVer;

    for (int i = 0; i < numOfVer; ++i) {
        float angle = i * angleStep;
        Vector2 pos = {
            center.x + radius * cosf(angle),
            center.y + radius * sinf(angle)
        };

        GraphNode* node = new GraphNode(i, {}, pos);
        node->size = 30.0f;
        node->colorNormal = BLACK;
        node->colorCurrent = BLACK;
        node->colorChosen = YELLOW;
        vertices.push_back(node);
    }

    // --- Tạo danh sách các cặp cạnh có thể (i, j) không trùng ---
    std::vector<std::pair<int, int>> possibleEdges;
    for (int i = 0; i < numOfVer; ++i) {
        for (int j = i + 1; j < numOfVer; ++j) {
            possibleEdges.emplace_back(i, j);
        }
    }

    // --- Tạo số lượng cạnh ngẫu nhiên ---
    int maxEdges = numOfVer * (numOfVer - 1) / 2;
    int minEdges = (numOfVer > 1) ? numOfVer - 1 : 0;
    int numEdges = 0;

    if (numOfVer > 1) {
        numEdges = rand() % (maxEdges - minEdges + 1) + minEdges;

        // Thay std::random_shuffle bằng std::shuffle
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(possibleEdges.begin(), possibleEdges.end(), g);

        for (int i = 0; i < numEdges; ++i) {
            int u = possibleEdges[i].first;
            int v = possibleEdges[i].second;
            int weight = rand() % 50 + 1;

            // Truyền con trỏ đến node thay vì tọa độ
            GraphEdge* edge = new GraphEdge(
                std::vector<GraphNode*>{vertices[u], vertices[v]},
                weight
            );

            edge->colorNormal = DARKGRAY;
            edge->colorChosen = YELLOW;
            edge->colorFlur = SKYBLUE;
            edge->currentColor = edge->colorNormal;
            edge->thick = 3.0f;

            vertices[u]->edge.push_back(edge);
            vertices[v]->edge.push_back(edge);
            edges.push_back(edge);
        }
    }

    std::cout << "Da tao " << vertices.size() << " nut va " << edges.size() << " canh.\n";
}

void Graph::CreateGraphFromInput(std::vector<std::vector<int>> input) {
    // Kiểm tra input hợp lệ
    if (input.empty() || input[0].size() != 2) {
        std::cout << "Lỗi: Input không hợp lệ\n";
        return;
    }

    // Xóa dữ liệu cũ nếu có
    if (!vertices.empty() || !edges.empty()) {
        for (GraphNode* node : vertices) {
            delete node;
        }
        for (GraphEdge* edge : edges) {
            delete edge;
        }
        vertices.clear();
        edges.clear();
    }

    // Lấy số đỉnh (n) và số cạnh (m) từ input[0]
    int numOfVer = input[0][0];
    int numOfEdges = input[0][1];

    if (numOfVer <= 0 || numOfEdges < 0 || numOfEdges > numOfVer * (numOfVer - 1) / 2) {
        std::cout << "Loi so dinh khong hop le\n";
        return;
    }

    // Kiểm tra số lượng dòng input
    if (input.size() != numOfEdges + 1) {
        std::cout << "Loi so luongg canh khong khop\n";
        return;
    }

    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size(); j++){
            std::cout<<input[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    // --- Tạo các nút theo vòng tròn ---
    float radius = 300.0f;
    Vector2 center = {800.0f, 450.0f};
    float angleStep = 2 * PI / numOfVer;

    for (int i = 0; i < numOfVer; ++i) {
        float angle = i * angleStep;
        Vector2 pos = {
            center.x + radius * cosf(angle),
            center.y + radius * sinf(angle)
        };

        GraphNode* node = new GraphNode(i, {}, pos);
        node->size = 30.0f;
        node->colorNormal = BLACK;
        node->colorCurrent = BLACK;
        node->colorChosen = YELLOW;
        vertices.push_back(node);
        std::cout<<"Position node "<<node->data<<":("<<node->finalPos.x<<"; "<<node->finalPos.y<<")"<<std::endl;
    }

    // --- Tạo các cạnh từ input ---
    for (int i = 1; i <= numOfEdges; ++i) {
        if (input[i].size() != 3) {
            std::cout << "Lỗi: Dữ liệu cạnh không hợp lệ\n";
            continue;
        }

        int u = input[i][0];
        int v = input[i][1];
        int weight = input[i][2];

        // Kiểm tra đỉnh hợp lệ
        if (u < 0 || u >= numOfVer || v < 0 || v >= numOfVer || u == v) {
            std::cout << "Lỗi: Đỉnh không hợp lệ cho cạnh " << i << "\n";
            continue;
        }

        // Kiểm tra trọng số hợp lệ
        if (weight <= 0) {
            std::cout << "Lỗi: Trọng số không hợp lệ cho cạnh " << i << "\n";
            continue;
        }

        // Tạo cạnh
        GraphEdge* edge = new GraphEdge(
            std::vector<GraphNode*>{vertices[u], vertices[v]},
            weight
        );

        edge->colorNormal = DARKGRAY;
        edge->colorChosen = YELLOW;
        edge->colorFlur = SKYBLUE;
        edge->currentColor = edge->colorNormal;
        edge->thick = 3.0f;

        // Thêm cạnh vào danh sách cạnh của các đỉnh
        vertices[u]->edge.push_back(edge);
        vertices[v]->edge.push_back(edge);
        edges.push_back(edge);
    }

    std::cout << "Tao tao " << vertices.size() << " dinh dinh và " << edges.size() << " canhcanh.\n";
}

void Graph::DrawGraph() {
    if (vertices.empty()) return;
    for (GraphEdge* edge : edges) {
        if (edge) edge->DrawEdge();
    }
    for (GraphNode* node : vertices) {
        if (node) node->DrawNode();
    }
}

void Graph::Draw() {
    DrawGraph();
}

void Graph::Update() {
    for (GraphNode* node : vertices) {
        if (node) node->UpdatePosition();
    }
}