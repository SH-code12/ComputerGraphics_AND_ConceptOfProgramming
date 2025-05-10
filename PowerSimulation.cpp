#include <stack>
#include <iostream>
using namespace std;

// Recurtion Power Function
int Power(int base, int pow){
    if (pow == 0) return 1;
    if (pow == 1) return base;
    return Power(base, pow - 1) * base;
}

// Simulation Of Recurtion Power
struct Call {
    int base, pow; // Parameter
    int result; // Local variables
    int cur_loc; // Location of next statement to be executed
};

int PowerSimulation(int base, int pow) // Non-recursive simulation of Power()
{
    Call initial_call;
    initial_call.base = base;
    initial_call.pow = pow;
    initial_call.cur_loc = 0;

    stack<Call> st;
    st.push(initial_call);

    int last_ret_val = 0; // Holds the return value of last finished call

    while (!st.empty()) {
        Call& call = st.top();

        if (call.cur_loc == 0) {
            if (call.pow == 0) {
                last_ret_val = 1;
                st.pop();
            } 
            if (call.pow == 1) {
                last_ret_val = call.base;
                st.pop();
            }else {
                Call new_call;
                new_call.cur_loc = 0;
                new_call.pow = call.pow - 1;
                new_call.base = call.base;
                st.push(new_call);
                call.cur_loc = 1;
            }
        } 
        else if (call.cur_loc == 1) {
            call.result = call.base * last_ret_val;
            last_ret_val = call.result;
            st.pop();
        } 
    }

    return last_ret_val;
}

int main() {
    cout<<"Shahd Elnassag ^_^\n";
    cout<<"Recurtion Power: "<<Power(2,3)<<endl;
    cout<<"Simulation Recurtion Power: "<<PowerSimulation(2,3)<<endl;

    return 0;
}
