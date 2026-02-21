    /////////////////////////////////////////////////////////////////////////////////////////////
    // 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
    // 아래 표준 입출력 예제 필요시 참고하세요.
    // 표준 입력 예제
    // int a;
    // float b, c;
    // double d, e, f;
    // char g;
    // char var[256];
    // long long AB;
    // cin >> a;                            // int 변수 1개 입력받는 예제
    // cin >> b >> c;                       // float 변수 2개 입력받는 예제 
    // cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
    // cin >> g;                            // char 변수 1개 입력받는 예제
    // cin >> var;                          // 문자열 1개 입력받는 예제
    // cin >> AB;                           // long long 변수 1개 입력받는 예제
    /////////////////////////////////////////////////////////////////////////////////////////////
    // 표준 출력 예제
    // int a = 0;                            
    // float b = 1.0, c = 2.0;               
    // double d = 3.0, e = 0.0; f = 1.0;
    // char g = 'b';
    // char var[256] = "ABCDEFG";
    // long long AB = 12345678901234567L;
    // cout << a;                           // int 변수 1개 출력하는 예제
    // cout << b << " " << c;               // float 변수 2개 출력하는 예제
    // cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
    // cout << g;                           // char 변수 1개 출력하는 예제
    // cout << var;                         // 문자열 1개 출력하는 예제
    // cout << AB;                          // long long 변수 1개 출력하는 예제
    /////////////////////////////////////////////////////////////////////////////////////////////

    #include<iostream>

    using namespace std;
    struct Node{
        int key;
        char label;
        Node* left;
        Node* right;
    };

    constexpr size_t MAX_NODE = 1000;
    Node nodes[MAX_NODE];
    int node_count = 1;

    Node* createNode(int key, char label){
        nodes[node_count].key = key;
        nodes[node_count].label = label;
        nodes[node_count].left = nullptr;
        nodes[node_count].right = nullptr;
        return &nodes[node_count++];
    }
    Node* root;

    void init(){
        root = nullptr;
        node_count = 1;
    }

    void traverse_tree(Node* node){
        if(node == nullptr) return;
        traverse_tree(node->left);
        cout << node->label;
        traverse_tree(node->right);
    }


    int main(int argc, char** argv)
    {
        int test_case;
        int T;
        /*
        아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
        앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
        //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
        freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
        따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
        freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
        단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
        */
        //freopen("input.txt", "r", stdin);
        T=10;   
        /*
        여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
        */
        for(test_case = 1; test_case <= T; ++test_case)
        {
            init();
            int N;
            cin >> N;//트리 정점 개수
            for(int i = 1; i <= N; i++){
                createNode(i, 0);
                if(i == 1) root = &nodes[i];
                if(i%2 == 0){
                    nodes[i/2].left = &nodes[i];
                }else{
                    nodes[i/2].right = &nodes[i];
            }}

            int mkey;
            char mlabel;
            
            for(int i = 0; i<N ; i++){
                cin >> mkey >> mlabel;
                if(2*mkey <= N) { int tmp; cin >> tmp; }      // 왼쪽 자식 번호 버리기
                if(2*mkey+1 <= N) { int tmp; cin >> tmp; }    // 오른쪽 자식 번호 버리기
                nodes[mkey].label = mlabel;
            }
            cout << "#" << test_case << " ";
            traverse_tree(root);
            cout << "\n";

            /////////////////////////////////////////////////////////////////////////////////////////////
            /*
                이 부분에 여러분의 알고리즘 구현이 들어갑니다.
            */
            /////////////////////////////////////////////////////////////////////////////////////////////


        }
        return 0;//정상종료시 반드시 0을 리턴해야합니다.
    }