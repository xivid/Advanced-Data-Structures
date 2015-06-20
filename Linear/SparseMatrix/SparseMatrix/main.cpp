#include <iostream>
using namespace std;

class SparseMatrix{
private:
    int size;
    int n;
    int *row, rows;
    int *col, cols;
    int *data;
public:
    SparseMatrix(int SIZE, int m, int n): size(SIZE), rows(m), cols(n) {
        row = new int[SIZE];
        col = new int[SIZE];
        data = new int[SIZE];
        n = 0;
    }
    
    ~SparseMatrix() {
        delete [] row;
        delete [] col;
        delete [] data;
    }
    
    bool insert(int r, int c, int d) {
        if(n && (r < row[n-1] || (r == row[n-1] && c < col[n-1]))) {
            cout << "输入顺序不合法！" << endl;
            return false;
        }
        if(n == size) {
            cout << "矩阵已存满！" << endl;
            return false;
        }
        if(!d) {
            cout << "不允许插入零元素！" << endl;
            return false;
        }
        if(r >= rows || c >= cols || r < 0 || c < 0) {
            cout << "元素位置超出矩阵规模！" << endl;
            return false;
        }
        
        row[n] = r;
        col[n] = c;
        data[n++] = d;
        return true; //success
    }
    
    SparseMatrix reverse(){
        SparseMatrix t(size, cols, rows);
        t.n = n;
        int i, index, *num = new int[cols](); //初始化为0
        for(i = 0; i < n; i++) ++num[col[i]]; //记录原矩阵每一列（转置矩阵每一行）的元素个数
        
        int *cpot = new int[cols](); //指示原矩阵每一列（转置矩阵每一行）第一个元素在转置矩阵中的存储次序，随着程序的运行，依次变为第二个、第三个……
        for(i = 1; i < cols; i++) cpot[i] = cpot[i-1] + num[i-1];
        
        for(i = 0; i < n; i++) {
            index = cpot[col[i]]++;
            t.row[index] = col[i];
            t.col[index] = row[i];
            t.data[index] = data[i];
        }
        return t;
    }
    
    void printtuple() {
        for(int i = 0; i < n; i++)
            cout << "(" << row[i] << ", " << col[i] << ", " << data[i] << ")" << endl;
    }
    
    void printmatrix() {
        int cur = 0;
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++)
                if(row[cur] == i && col[cur] == j) cout << data[cur++] << "\t";
                else cout << "0\t";
            cout << endl;
        }
    }
};
int main(){
    int choice, m, n;
    SparseMatrix* sm;
    cout << "请输入矩阵的行数m和列数n：" << endl;
    cin >> m >> n;
    cout << "请输入一个" << m << "*" << n <<"的稀疏矩阵，选择1（直接输入）或2（三元组输入）：" << endl;
    cin >> choice;
    if(choice == 1) {
        int t;
        sm = new SparseMatrix(m*n, m, n);
        cout << "请输入该矩阵：" << endl;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++) {
                cin >> t;
                if(t) sm->insert(i, j, t);
            }
        cout << "该矩阵的三元组形式如下：" << endl;
        sm->printtuple();
    }
    else if(choice == 2) {
        int N, r, c, d;
        cout << "请输入非零元（三元组）的个数：" << endl;
        cin >> N;
        sm = new SparseMatrix(N, m, n);
        cout << "请输入" << N << "个三元组（行和列下标从0开始）：" << endl;
        for(int i = 0; i < N;) {
            cin >> r >> c >> d;
            if(sm->insert(r, c, d)) ++i;
        }
        cout << "该矩阵的矩阵形式如下：" << endl;
        sm->printmatrix();
    }
    else exit(0);
    SparseMatrix rev(sm->reverse());
    cout << "转置后的矩阵如下：" << endl;
    cout << "三元组形式" << endl;
    rev.printtuple();
    cout << "矩阵形式" << endl;
    rev.printmatrix();
    return 0;
}