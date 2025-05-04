#include <stack>
#include <iostream>
using namespace std;

struct Call {
    int n; // Parameter
    int a, b, c, d; // Local variables
    int cur_loc; // Location of next statement to be executed
};

int G(int n) // Non-recursive simulation of F()
{
    Call initial_call;
    initial_call.n = n;
    initial_call.cur_loc = 0;

    stack<Call> st;
    st.push(initial_call);

    int last_ret_val = 0; // Holds the return value of last finished call

    while (!st.empty()) {
        Call& call = st.top();

        if (call.cur_loc == 0) {
            if (call.n <= 1) {
                last_ret_val = 1;
                st.pop();
            } else {
                Call new_call;
                new_call.cur_loc = 0;
                new_call.n = call.n - 1;
                st.push(new_call);
                call.cur_loc = 1;
            }
        } 
        else if (call.cur_loc == 1) {
            call.a = call.n * last_ret_val;
            last_ret_val = call.a;
            st.pop();
            // Call new_call;
            // new_call.cur_loc = 0;
            // new_call.n = call.n / 2;
            // st.push(new_call);
            // call.cur_loc = 2;
        } 
        // else if (call.cur_loc == 2) {
        //     call.b = call.n * last_ret_val;
        //     call.c = call.n - 2 - (call.a + call.b) % 2;
        //     Call new_call;
        //     new_call.cur_loc = 0;
        //     new_call.n = call.c;
        //     st.push(new_call);
        //     call.cur_loc = 3;
        // } 
        // else if (call.cur_loc == 3) {
        //     call.d = last_ret_val;
        //     last_ret_val = call.a + call.b + call.d;
        //     st.pop();
        // }
    }

    return last_ret_val;
}

int main() {
    for (int n = 0; n <= 5; ++n) {
        cout << "G(" << n << ") = " << G(n) << endl;
    }
    return 0;
}
