// #include "matrix.h"

#include <iostream>
#include "mathFunctions.h"
using namespace std;

int main() {
    Matrix m(4, 3);
    Matrix n(4, 3);
    
    m.matrix_fill_with_same_value(2.2);
    n.matrix_fill_with_same_value(3);

    Matrix sum = add(m, n);
    sum.matrix_print();

    // sum.matrix_save("NEWdata.txt");

    Matrix p(3, 1);
    p.matrix_fill_with_same_value(3);
    p.matrix_custom_randomize(6,5,"he");

    Matrix id = identity_matrix(5);
    cout << "matrix identity: " << endl;
    id.matrix_print();

    return 0;
}