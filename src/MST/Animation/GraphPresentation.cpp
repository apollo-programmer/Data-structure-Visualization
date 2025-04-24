#include "MST/Animation/GraphPresentation.h"

GraphPresentation::GraphPresentation(float & speed, Graph * graph,
                                        std::vector<std::vector<Graph*>>& historyState, int& currentPresentationIndex, int&currentStateIndex)
                                        :speed(speed), graph(graph), currentStep(0), currentPresentationIndex(currentPresentationIndex), currentStateIndex(currentStateIndex), historyState(historyState) {
    parent.resize(3, 0);
    rank.resize(3, 0);
}

void GraphPresentation::CreateGraph(int numofNode){
    //graph->createGraph(numofNode);

    //move to finpos
    GraphSetofOperation movetoFin(speed);
    for(int i = 0; i < graph->vertices.size(); i++){
        //std::cout<<"toi day"<<std::endl;
        GraphOperation move(speed, graph->vertices[i]);
        move.type = GraphOperation::MOVE_NODE;
        movetoFin.AddOperation(move);
        std::cout<<"Trong animation: POSITION node "<<i<<": ("<<graph->vertices[i]->finalPos.x<<"; "<<graph->vertices[i]->finalPos.y<<")"<<std::endl;
    }
    this->SetOperations.push_back(movetoFin);
    return;
}

// Hàm Disjoint Set
void GraphPresentation::initDisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i; // Mỗi node là tập hợp riêng
    }
}

int GraphPresentation::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

bool GraphPresentation::unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY) return false; // Đã cùng tập hợp, tạo chu trình

    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    return true;
}

void GraphPresentation::Kruskal() {
    if (graph == nullptr || graph->vertices.empty()) return;

    // Khởi tạo Disjoint Set
    int numVertices = graph->vertices.size();
    initDisjointSet(numVertices);
    if(!SetOperations.empty()) SetOperations.clear();

    // Sắp xếp các cạnh theo trọng số
    std::vector<GraphEdge*> sortedEdges = graph->edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), 
        [](GraphEdge* a, GraphEdge* b) { return a->weight < b->weight; });

    // Duyệt qua từng cạnh
    for (GraphEdge* edge : sortedEdges) {
        // Tìm node đầu và cuối của cạnh
        GraphNode* node1 = edge->nodes[0];
        GraphNode* node2 = edge->nodes[1];
        int u = node1->data;
        int v = node2->data;

        // Animation: Làm sáng cạnh đang xét
        GraphSetofOperation highlightEdge(speed);
        GraphOperation highlightEdgeOp(speed, edge);
        highlightEdgeOp.type = GraphOperation::FLUR_EDGE;
        highlightEdge.AddOperation(highlightEdgeOp);

        // Animation: Làm sáng hai node liên quan
        GraphOperation highlightNode1(speed, node1);
        highlightNode1.type = GraphOperation::CHOSEN_NODE;
        highlightEdge.AddOperation(highlightNode1);
        GraphOperation highlightNode2(speed, node2);
        highlightNode2.type = GraphOperation::CHOSEN_NODE;
        highlightEdge.AddOperation(highlightNode2);

        SetOperations.push_back(highlightEdge);

        // Kiểm tra chu trình
        if (unionSets(u, v)) {
            // Không tạo chu trình, thêm cạnh vào MST
            GraphSetofOperation addEdgeToMST(speed);
            GraphOperation addEdgeOp(speed, edge);
            addEdgeOp.type = GraphOperation::CHOSEN_EDGE;
            addEdgeToMST.AddOperation(addEdgeOp);

            // Đổi màu node về bình thường
            GraphOperation resetNode1(speed, node1);
            resetNode1.type = GraphOperation::NORMAL_NODE;
            addEdgeToMST.AddOperation(resetNode1);
            GraphOperation resetNode2(speed, node2);
            resetNode2.type = GraphOperation::NORMAL_NODE;
            addEdgeToMST.AddOperation(resetNode2);

            SetOperations.push_back(addEdgeToMST);
        } else {
            // Tạo chu trình, bỏ qua cạnh này
            GraphSetofOperation rejectEdge(speed);
            GraphOperation rejectEdgeOp(speed, edge);
            rejectEdgeOp.type = GraphOperation::NORMAL_EDGE;
            rejectEdge.AddOperation(rejectEdgeOp);

            // Đổi màu node về bình thường
            GraphOperation resetNode1(speed, node1);
            resetNode1.type = GraphOperation::NORMAL_NODE;
            rejectEdge.AddOperation(resetNode1);
            GraphOperation resetNode2(speed, node2);
            resetNode2.type = GraphOperation::NORMAL_NODE;
            rejectEdge.AddOperation(resetNode2);

            SetOperations.push_back(rejectEdge);
        }
    }
    GraphSetofOperation highlightAll(speed);
    for(int i = 0; i < graph->vertices.size(); i++){
        GraphOperation hl(speed, graph->vertices[i]);
        hl.type = GraphOperation::CHOSEN_NODE;
        highlightAll.AddOperation(hl);
    }
    SetOperations.push_back(highlightAll);

    std::cout << "Kruskal completed with " << SetOperations.size() << " animation steps.\n";
}

void GraphPresentation::Prim() {
    if (graph == nullptr || graph->vertices.empty()) return;

    if(!SetOperations.empty()) SetOperations.clear();

    int numVertices = graph->vertices.size();
    std::vector<bool> inMST(numVertices, false); // Đánh dấu node đã thuộc MST
    std::vector<int> key(numVertices, INT_MAX);  // Trọng số nhỏ nhất để đến node
    std::vector<GraphEdge*> mstEdge(numVertices, nullptr); // Lưu cạnh dẫn đến node trong MST

    // Danh sách lưu thứ tự node được thăm và cạnh được chọn
    std::vector<int> visitedNodes; // Thứ tự node được thăm
    std::vector<GraphEdge*> mstEdges; // Các cạnh trong MST

    // Hàng đợi ưu tiên: {trọng số, cạnh}
    using EdgePair = std::pair<int, GraphEdge*>;
    std::priority_queue<EdgePair, std::vector<EdgePair>, std::greater<EdgePair>> pq;

    // Bắt đầu từ node 0
    int startVertex = 1;
    key[startVertex] = 1;

    // Thêm node bắt đầu vào danh sách
    inMST[startVertex] = true;
    visitedNodes.push_back(startVertex);

    // Thêm các cạnh từ node bắt đầu vào hàng đợi
    for (GraphEdge* edge : graph->vertices[startVertex]->edge) {
        GraphNode* otherNode = (edge->nodes[0]->data == startVertex) ? edge->nodes[1] : edge->nodes[0];
        int otherVertex = otherNode->data;
        if (!inMST[otherVertex]) {
            key[otherVertex] = edge->weight;
            mstEdge[otherVertex] = edge;
            pq.push({edge->weight, edge});
        }
    }

    // Tính toán MST: Xác định thứ tự node và cạnh
    while (!pq.empty() && visitedNodes.size() < numVertices) {
        // Lấy cạnh có trọng số nhỏ nhất
        EdgePair pair = pq.top();
        pq.pop();

        int weight = pair.first;
        GraphEdge* edge = pair.second;
        // Xác định node chưa thuộc MST
        GraphNode* node1 = edge->nodes[0];
        GraphNode* node2 = edge->nodes[1];
        int u = node1->data;
        int v = node2->data;
        int newVertex = inMST[u] ? v : u;
        if (inMST[newVertex]) continue; // Bỏ qua nếu node đã thuộc MST

        // Thêm node mới vào MST
        inMST[newVertex] = true;
        visitedNodes.push_back(newVertex);
        mstEdges.push_back(edge); // Lưu cạnh được chọn

        // Thêm các cạnh mới từ node vừa thêm vào hàng đợi
        for (GraphEdge* nextEdge : graph->vertices[newVertex]->edge) {
            GraphNode* nextNode = (nextEdge->nodes[0]->data == newVertex) ? nextEdge->nodes[1] : nextEdge->nodes[0];
            int otherVertex = nextNode->data;
            if (!inMST[otherVertex] && nextEdge->weight < key[otherVertex]) {
                key[otherVertex] = nextEdge->weight;
                mstEdge[otherVertex] = nextEdge;
                pq.push({nextEdge->weight, nextEdge});
            }
        }
    }

    // Tạo kịch bản animation dựa trên thứ tự node và cạnh
    // Bước 1: Highlight node bắt đầu
    GraphSetofOperation startStep(speed);
    GraphOperation highlightStartNode(speed, graph->vertices[startVertex]);
    highlightStartNode.type = GraphOperation::CHOSEN_NODE;
    startStep.AddOperation(highlightStartNode);
    SetOperations.push_back(startStep);

    // Bước 2: Highlight các node và cạnh theo thứ tự
    for (size_t i = 1; i < visitedNodes.size(); i++) {
        int nodeIdx = visitedNodes[i];
        GraphEdge* edge = mstEdges[i - 1]; // Cạnh dẫn đến node này

        // Animation: Highlight node
        GraphSetofOperation highlightNodeStep(speed);
        GraphOperation highlightNodeOp(speed, graph->vertices[nodeIdx]);
        highlightNodeOp.type = GraphOperation::CHOSEN_NODE;
        highlightNodeStep.AddOperation(highlightNodeOp);
        SetOperations.push_back(highlightNodeStep);

        // Animation: Highlight cạnh
        GraphSetofOperation highlightEdgeStep(speed);
        GraphOperation highlightEdgeOp(speed, edge);
        highlightEdgeOp.type = GraphOperation::CHOSEN_EDGE;
        highlightEdgeStep.AddOperation(highlightEdgeOp);
        SetOperations.push_back(highlightEdgeStep);
    }

    // Bước 3: Highlight tất cả node khi hoàn thành (để đồng bộ)
    GraphSetofOperation highlightAll(speed);
    for (int i = 0; i < numVertices; i++) {
        if (inMST[i]) {
            GraphOperation hl(speed, graph->vertices[i]);
            hl.type = GraphOperation::CHOSEN_NODE;
            highlightAll.AddOperation(hl);
        }
    }
    SetOperations.push_back(highlightAll);

    std::cout << "Prim completed with " << SetOperations.size() << " animation steps.\n";
}

bool GraphPresentation::DrawPresentation(){
    if(SetOperations.empty() || currentStep >= SetOperations.size()){
        // if(SetOperations.empty()){
        //     //std::cout<<"empty mat roi.\n";
        // }
        return true;
    }

    if(SetOperations[currentStep].Draw()){
        std::cout<<"CO ANIMATION NGHEN.\n";
        Graph * temp = new Graph(this->graph);
        if(currentStep == 0){
            currentPresentationIndex++;
            std::vector<Graph*> tempVec = {};
            tempVec.push_back(temp);
            historyState.push_back(tempVec);
            currentStateIndex = historyState.back().size() - 1;
        }
        else{
            historyState.back().push_back(temp);
            currentStateIndex = historyState.back().size() - 1;
        }
        currentStep++;
    }
    if(currentStep >= SetOperations.size()){
        std::cout<<"Presentation Size: "<<SetOperations.size()<<std::endl;
        currentStep = 0;
        this->SetOperations.clear();
        return true;
    }
    return false;
}